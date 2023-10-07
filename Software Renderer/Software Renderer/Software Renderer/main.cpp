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


const char* filename_output = "output.tga";
const char* filename_zbuffer = "zbuffer.tga";
Model model("./obj/african_head.obj");
const int width  = 800;
const int height = 800;


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);


vec3 light_dir = {1,1,1};
vec3 eye = {1,1,1};
vec3 center = {0,0,0};
vec3 up = {0,1,0};


class BlinnPhongShader : public Shader {
public:
    vec3 varying_intensity;

    virtual vec4 vertex(int face_id, int vert_id)
    {
        varying_intensity[vert_id] = model.normal(face_id, vert_id).max(vec3(0.f)).dot(light_dir);
        vec4 gl_Vertex = model.verts[vert_id];
        
        auto dc = viewport_matrix * projection_matrix * view_matrix * model_matrix * gl_Vertex;
        return dc;
    }

    virtual bool fragment(vec3 bary, TGAColor &color)
    {
        float intensity = varying_intensity.dot(bary);
        color = TGAColor(255, 255, 255) * intensity;
        return true;
    }
};


int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);
    
    BlinnPhongShader shader;
    
//    for(int i = 0; i < model.nfaces(); i++)
//    {
//        std::vector<vec4> screen_coords;
//        screen_coords.resize(3);
//        for(int j = 0; j < 3; j++)
//        {
//            screen_coords[j] = shader.vertex(i, j);
//        }
//        triangle(screen_coords, shader, image, zbuffer);
//    }
    
    triangle({{0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}}, shader, image, zbuffer);
    

    image.flip_vertically();
    zbuffer.flip_vertically();
    image.write_tga_file(filename_output);
    zbuffer.write_tga_file(filename_zbuffer);
    
    std::string command = "open " + string(filename_output);
    system(command.c_str());
}
