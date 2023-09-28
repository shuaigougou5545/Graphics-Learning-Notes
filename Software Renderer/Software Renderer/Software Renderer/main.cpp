#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include "tgaimage.h"
#include "vec.h"

using namespace std;


const char* file_name = "output.tga";
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width  = 600;
const int height = 600;


void line(const vec2i& p0, const vec2i& p1, TGAImage& image, TGAColor color)
{
    int x0 = p0.x, y0 = p0.y;
    int x1 = p1.x, y1 = p1.y;
    
    bool steep = false;
    if(abs(x0 - x1) < abs(y0 - y1))
    {
        swap(x0, y0);
        swap(x1, y1);
        steep = true;
    }
  
    if(x0 > x1)
    {
        swap(x0, x1);
        swap(y0, y1);
    }
  
        int dx = x1 - x0;
        int dy = y1 - y0;
        int derror2 = std::abs(dy) * 2;
        int error2 = 0;
        int y = y0;
        for(int x = x0; x <= x1; x++)
        {
            if(steep)
                image.set(y, x, color);
            else
                image.set(x, y, color);
             
        error2 += derror2;
        if (error2 > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

vec3 barycentric(const array<vec2i, 3>& pts, const vec2i& P)
{
    vec3i a = {pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - P.x};
    vec3i b = {pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - P.y};
    
    vec3i u = a.cross(b);
    
    if (std::abs(u.z) < 1) // 因为后续要除以z,这里要事先剔除
        return vec3(-1, 1, 1);
    
    return vec3(1.f - (u.x + u.y) / (float)u.z, u.x / (float)u.z, u.y / (float)u.z);
}

void triangle(const array<vec2i, 3>& pts, TGAImage &image, TGAColor color)
{
    vec2i bboxmin(image.get_width() - 1,  image.get_height() - 1);
    vec2i bboxmax(0, 0);
    vec2i clamp(image.get_width() - 1, image.get_height() - 1);
    for (int i = 0; i < 3; i++)
    {
        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));
        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    }
    vec2i P;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++)
    {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
        {
            vec3 bc_screen = barycentric(pts, P);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
                continue;
            image.set(P.x, P.y, color);
        }
    }
}


int main()
{
    TGAImage image(width, height, TGAImage::RGB);

    vec2i p0 = {100, 100}, p1 = {100, 200}, p2 = {200, 200};
    triangle({p0, p1, p2}, image, red);
//    line(p0, p1, image, green);
//    line(p1, p2, image, green);
//    line(p2, p0, image, green);
    
    image.flip_vertically();
    image.write_tga_file(file_name); // 默认:以左上角为原点
    
    std::string command = "open " + string(file_name);
    system(command.c_str());
}
