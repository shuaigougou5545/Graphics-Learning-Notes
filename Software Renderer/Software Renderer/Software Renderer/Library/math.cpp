#include "math.h"

vec2::vec2(const vec2i& v)
{
    x = v.x;
    y = v.y;
}

vec2::vec2(const vec3& v)
{
    x = v.x;
    y = v.y;
}

vec2::vec2(const vec3i& v)
{
    x = v.x;
    y = v.y;
}

vec2::vec2(const vec4& v)
{
    x = v.x;
    y = v.y;
}

vec2i::vec2i(const vec2& v)
{
    x = v.x;
    y = v.y;
}

vec2i::vec2i(const vec3& v)
{
    x = v.x;
    y = v.y;
}

vec2i::vec2i(const vec3i& v)
{
    x = v.x;
    y = v.y;
}

vec2i::vec2i(const vec4& v)
{
    x = v.x;
    y = v.y;
}

vec3::vec3(const vec2& v)
{
    x = v.x;
    y = v.y;
    z = 0.f;
}

vec3::vec3(const vec2i& v)
{
    x = v.x;
    y = v.y;
    z = 0.f;
}

vec3::vec3(const vec3i& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

vec3::vec3(const vec4& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

vec3i::vec3i(const vec2& v)
{
    x = v.x;
    y = v.y;
    z = 0;
}

vec3i::vec3i(const vec2i& v)
{
    x = v.x;
    y = v.y;
    z = 0;
}

vec3i::vec3i(const vec3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

vec3i::vec3i(const vec4& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

vec4 vec4::operator*(const mat4& m) const
{
    vec4 res(0.f);
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            res[i] += (*this)[j] * m[j][i];
    }

    return res;
}

vec4 mat4::operator*(const vec4& v)
{
    vec4 res(0.f);
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            res[i] += v[j] * (*this)[j][i];
    }

    return res;
}

mat4& mat4::operator*(const mat4& m)
{
    mat4 res = mat4().zero();
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                res[i][j] += (*this)[i][k] * m[k][j];
            }
        }
    }
    
    *this = res;
    
    return *this;
}
