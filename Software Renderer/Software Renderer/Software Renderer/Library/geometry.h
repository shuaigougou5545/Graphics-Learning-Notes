#ifndef geometry_h
#define geometry_h

#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include "tgaimage.h"
#include "math.h"


// draw line
void draw_line(const vec2i& p0, const vec2i& p1, TGAImage& image, TGAColor color);

// 2D
bool is_point_in_triangle_2d(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary);
bool is_point_in_triangle_2d_cramers_rule(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary);

// 3D
bool is_point_in_triangle_3d(const vec3& p, const std::array<vec3, 3>& pts, vec3& bary);

// barycentric - for rasterization(2D)
vec3 barycentric(const vec2& A, const vec2& B, const vec2& C, const vec2& P);


#endif /* geometry_h */
