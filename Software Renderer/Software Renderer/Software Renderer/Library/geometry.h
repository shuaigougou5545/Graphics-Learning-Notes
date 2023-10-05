#ifndef geometry_h
#define geometry_h

#include <iostream>
#include <vector>
#include <array>
#include "math.h"


// 2D
bool isPointInTriangle2D(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary);
bool isPointInTriangle2D_CramersRule(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary);

// 3D
bool isPointInTriangle3D(const vec3& p, const std::array<vec3, 3>& pts, vec3& bary);


#endif /* geometry_h */
