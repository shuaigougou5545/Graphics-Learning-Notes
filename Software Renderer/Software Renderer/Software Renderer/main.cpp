#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include "tgaimage.h"
#include "model.h"
#include "math.h"
#include "geometry.h"

using namespace std;


const char* file_name = "output.tga";
Model model("./obj/african_head.obj");
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width  = 800;
const int height = 800;


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

void triangle(const array<vec3, 3>& pts, vector<vector<float>>& zbuffer, TGAImage &image, TGAColor color)
{
    vec2 bboxmin(numeric_limits<float>::max(), numeric_limits<float>::max());
    vec2 bboxmax(numeric_limits<float>::min(), numeric_limits<float>::min());
    vec2 clamp(image.get_width() - 1.0, image.get_height() - 1.0);
    for (int i = 0; i < 3; i++)
    {
        bboxmin.x = std::max(0.f, std::min(bboxmin.x, pts[i].x));
        bboxmin.y = std::max(0.f, std::min(bboxmin.y, pts[i].y));
        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    }
    vec3 P;
    vec3 bary;
    for(P.x = bboxmin.x; P.x <= bboxmax.x; P.x++)
    {
        for(P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
        {
            if(!isPointInTriangle2D({P.x, P.y}, {{{pts[0].x, pts[0].y},{pts[1].x, pts[1].y},{pts[2].x, pts[2].y}}}, bary))
                continue;
            
            P.z = 0.0;
            for(int i = 0; i < 3; i++)
                P.z += pts[i].z * bary[i];
            
            if(zbuffer[int(P.y)][int(P.x)] < P.z)
            {
                zbuffer[int(P.y)][int(P.x)] = P.z;
                image.set(P.x, P.y, color);
            }
        }
    }
}


int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    vector<vector<float>> zbuffer(height, vector<float>(width, numeric_limits<float>::min()));
    
    vec3 light_dir = {0.0, 0.0, -1.0};
    for(int i = 0; i < model.facet_vrt.size()/3; i++)
    {
        vec3 screen_coords[3];
        vec3 world_coords[3];
        vec3 normals[3];
        vec2 uv[3];
        for (int j = 0; j < 3; j++)
        {
            int vertex_idx = model.facet_vrt[3 * i + j];
            world_coords[j] = model.verts[vertex_idx];
            screen_coords[j].x = round((world_coords[j].x + 1.0) * width / 2.0);
            screen_coords[j].y = round((world_coords[j].y + 1.0) * height / 2.0);
            screen_coords[j].z = world_coords[j].z;
            
            int normal_idx = model.facet_nrm[3 * i + j];
            normals[j] = model.norms[normal_idx];
            
            int uv_idx = model.facet_tex[3 * i + j];
            uv[j] = model.tex_coords[uv_idx];
        }
        
        vec3 n = ((normals[0] + normals[1] + normals[2]) / 3.0 + 1.0) / 2.0;
        triangle({screen_coords[0], screen_coords[1], screen_coords[2]}, zbuffer, image, TGAColor(n.x*255, n.y*255, n.z*255, 255));
    }
    

    image.flip_vertically();
    image.write_tga_file(file_name);
    
    std::string command = "open " + string(file_name);
    system(command.c_str());
}
