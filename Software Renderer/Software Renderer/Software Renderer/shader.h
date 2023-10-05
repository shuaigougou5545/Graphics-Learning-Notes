#ifndef shader_h
#define shader_h

#include <iostream>
#include <vector>
#include "math.h"
#include "tgaimage.h"


void viewport(int x, int y, int w, int h);
void projection(float coeff = 0.0f);
void lookat(vec3 eye, vec3 center, vec3 up);


struct Shader{
    virtual ~Shader() = default;
    virtual vec4 vertex() = 0;
    virtual bool fragment(vec3 bar, TGAColor &color) = 0;
};

void triangle(const std::vector<vec4>& pts, Shader& shader, TGAImage &image, TGAImage &zbuffer);

#endif /* shader_h */
