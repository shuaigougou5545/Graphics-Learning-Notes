#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include "tgaimage.h"
#include "model.h"
#include "math.h"
#include "geometry.h"
#include "shader.h"

using namespace std;


const char* file_name = "output.tga";
Model model = Model("./obj/african_head.obj");
const int width  = 800;
const int height = 800;


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);


vec3 light_dir = {1,1,1};
vec3 eye = {1,1,1};
vec3 center = {0,0,0};
vec3 up = {0,1,0};


//struct FirstShader : public Shader {
//    vec3 varying_intensity;
//
//    virtual vec4 vertex();
//};



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
        draw_triangle({screen_coords[0], screen_coords[1], screen_coords[2]}, zbuffer, image, TGAColor(n.x*255, n.y*255, n.z*255, 255));
    }
    

    image.flip_vertically();
    image.write_tga_file(file_name);
    
    std::string command = "open " + string(file_name);
    system(command.c_str());
}
