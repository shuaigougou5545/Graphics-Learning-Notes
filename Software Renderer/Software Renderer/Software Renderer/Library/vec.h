#ifndef vec_h
#define vec_h

#include <iostream>

class vec2;
class vec2i;
class vec3;
class vec3i;
class vec4;


class vec2{
public:
    vec2() : x(0), y(0) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}
    vec2(float _f) : x(_f), y(_f) {}
    vec2(const vec2i& v);
    
    vec2 operator +(const vec2& v) const { return vec2(x + v.x, y + v.y); }
    vec2 operator -(const vec2& v) const { return vec2(x - v.x, y - v.y); }
    vec2 operator *(const vec2& v) const { return vec2(x * v.x, y * v.y); }
    vec2 operator /(const vec2& v) const { return vec2(x / v.x, y / v.y); }
    
    float& operator[](size_t index)
    {
        if(index == 0)
            return x;
        else if(index == 1)
            return y;
        
        static float error = -1.0;
        return error;
    }
    
    float dot(const vec2& v) const { return x * v.x + y * v.y; }
    float cross(const vec2& v) const { return x * v.y - y * v.x; }
    
    float x, y;
};


class vec2i{
public:
    vec2i() : x(0), y(0) {}
    vec2i(int _x, int _y) : x(_x), y(_y) {}
    vec2i(int _f) : x(_f), y(_f) {}
    vec2i(const vec2& v);
    
    vec2i operator +(const vec2i& v) const { return vec2i(x + v.x, y + v.y); }
    vec2i operator -(const vec2i& v) const { return vec2i(x - v.x, y - v.y); }
    vec2i operator *(const vec2i& v) const { return vec2i(x * v.x, y * v.y); }
    
    int& operator[](size_t index)
    {
        if(index == 0)
            return x;
        else if(index == 1)
            return y;
        
        static int error = -1.0;
        return error;
    }
    
    int dot(const vec2i& v) const { return x * v.x + y * v.y; }
    int cross(const vec2i& v) const { return x * v.y - y * v.x; }
    
    int x, y;
};


class vec3{
public:
    vec3() : x(0), y(0), z(0) {}
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    vec3(float _f) : x(_f), y(_f), z(_f) {}
    vec3(const vec3i& v);
    
    vec3 operator +(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }
    vec3 operator -(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }
    vec3 operator *(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); }
    vec3 operator /(const vec3& v) const { return vec3(x / v.x, y / v.y, z / v.z); }
    
    float& operator[](size_t index)
    {
        if(index == 0)
            return x;
        else if(index == 1)
            return y;
        else if(index == 2)
            return z;
        
        static float error = -1.0;
        return error;
    }
    
    float dot(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    vec3 cross(const vec3& v) const { return vec3(y * v.z - z * v.y, z * v.x - x * v.y, x * v.y - y * v.x); }
    
    float x, y, z;
};


class vec3i{
public:
    vec3i() : x(0), y(0), z(0) {}
    vec3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    vec3i(int _f) : x(_f), y(_f), z(_f) {}
    vec3i(const vec3& v);
    
    vec3i operator +(const vec3i& v) const { return vec3i(x + v.x, y + v.y, z + v.z); }
    vec3i operator -(const vec3i& v) const { return vec3i(x - v.x, y - v.y, z - v.z); }
    vec3i operator *(const vec3i& v) const { return vec3i(x * v.x, y * v.y, z * v.z); }
    
    int& operator[](size_t index)
    {
        if(index == 0)
            return x;
        else if(index == 1)
            return y;
        else if(index == 2)
            return z;
        
        static int error = -1;
        return error;
    }
    
    int dot(const vec3i& v) const { return x * v.x + y * v.y + z * v.z; }
    vec3i cross(const vec3i& v) const { return vec3i(y * v.z - z * v.y, z * v.x - x * v.y, x * v.y - y * v.x); }
    
    int x, y, z;
};


class vec4{
public:
    vec4() : x(0), y(0), z(0), w(0) {}
    vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    vec4(float _f) : x(_f), y(_f), z(_f), w(_f) {}
    
    vec4 operator +(const vec4& v) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
    vec4 operator -(const vec4& v) const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
    vec4 operator *(const vec4& v) const { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
    vec4 operator /(const vec4& v) const { return vec4(x / v.x, y / v.y, z / v.z, w / v.w); }
    
    float& operator[](size_t index)
    {
        if(index == 0)
            return x;
        else if(index == 1)
            return y;
        else if(index == 2)
            return z;
        else if(index == 3)
            return w;
        
        static float error = -1.0;
        return error;
    }
    
    float dot(const vec4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
    
    float x, y, z, w;
};

#endif /* vec_h */
