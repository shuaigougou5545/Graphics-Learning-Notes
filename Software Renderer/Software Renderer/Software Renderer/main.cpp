#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"


using namespace std;


const char* file_name = "output.tga";
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
Model *model = NULL;
const int width  = 600;
const int height = 600;


void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
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

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color)
{
    int delta_x = max(max(abs(t2.x - t1.x), abs(t1.x - t0.x)), abs(t2.x - t0.x));
    int delta_y = max(max(abs(t2.y - t1.y), abs(t1.y - t0.y)), abs(t2.y - t0.y));
    bool steep = false;
    if(delta_x < delta_y)
    {
        swap(t0.x, t0.y);
        swap(t1.x, t1.y);
        swap(t2.x, t2.y);
        steep = true;
    }
    
    if(t0.x < t1.x) swap(t0, t1);
    if(t0.x < t2.x) swap(t0, t2);
    if(t1.x < t2.x) swap(t1, t2);
    
    int dy_01 = t1.y - t0.y;
    int dy_12 = t2.y - t1.y;
    int dy_02 = t2.y - t0.y;
    
    int dx_01 = t1.x - t0.x;
    int dx_12 = t2.x - t1.x;
    int dx_02 = t2.x - t0.x;
    
    int error2_02 = 0;
    int y = t0.y;
    
    for(int x = t0.x; x <= t2.x; x++)
    {
        bool second_half = x >= t1.x;
        int derror2_02 = abs(dy_02) * 2;
        
        
        error2_02 += derror2_02;
        if(error2_02 > dx_02){
            y += 1;
        }
    }
}


int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    
//    model = new Model("./obj/african_head.obj");
//    for (int i=0; i < model->nfaces(); i++)
//    {
//        std::vector<int> face = model->face(i);
//        for (int j=0; j<3; j++)
//        {
//            Vec3f v0 = model->vert(face[j]);
//            Vec3f v1 = model->vert(face[(j + 1) % 3]);
//            int x0 = (v0.x + 1.0) * width / 2.0;
//            int y0 = (v0.y + 1.0) * height / 2.0;
//            int x1 = (v1.x + 1.0) * width / 2.0;
//            int y1 = (v1.y + 1.0) * height / 2.0;
//            line(x0, y0, x1, y1, image, white);
//        }
//    }

    Vec2i p0 = {100, 200}, p1 = {200, 400}, p2 = {300, 300};
    triangle(p0, p1, p2, image, red);
    
    image.flip_vertically();
    image.write_tga_file(file_name); // 默认:以左上角为原点
    
    delete model;
    
    std::string command = "open " + string(file_name);
    system(command.c_str());
    
    cout << endl;
    
    return 0;
}
