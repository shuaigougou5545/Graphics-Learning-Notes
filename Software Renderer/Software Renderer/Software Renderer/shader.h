#ifndef shader_h
#define shader_h

#include <iostream>
#include <vector>
#include "math.h"
#include "tgaimage.h"


extern mat4 model_matrix;
extern mat4 view_matrix;
extern mat4 projection_matrix;
extern mat4 viewport_matrix;


void viewport(int x, int y, int w, int h);
void projection(float n, float f, float alpha, float aspect_ratio);
void lookat(vec3 eye, vec3 center, vec3 up);


struct Shader{
public:
    virtual ~Shader() = default;
    virtual vec4 vertex(int face_id, int vert_id) = 0;
    virtual bool fragment(vec3 bary, TGAColor &color) = 0;
};

void triangle(const std::vector<vec4>& pts, Shader& shader, TGAImage &image, TGAImage &zbuffer);

#endif /* shader_h */
