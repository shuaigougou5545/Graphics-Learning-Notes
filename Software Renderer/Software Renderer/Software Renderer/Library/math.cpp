#include "math.h"


vec2::vec2(const vec2i& v)
{
    x = v.x;
    y = v.y;
}

vec2i::vec2i(const vec2& v)
{
    x = (int)v.x;
    y = (int)v.y;
}

vec3::vec3(const vec3i& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

vec3i::vec3i(const vec3& v)
{
    x = (int)v.x;
    y = (int)v.y;
    z = (int)v.z;
}
