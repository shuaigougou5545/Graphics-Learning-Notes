#ifndef math_h
#define math_h

#include <iostream>
#include <vector>
#include <array>


class vec2;
class vec2i;
class vec3;
class vec3i;
class vec4;

class mat2;
class mat3;
class mat4;


class vec2{
public:
    vec2() : x(0), y(0) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}
    vec2(float _f) : x(_f), y(_f) {}
    
    vec2(const vec2i& v);
    vec2(const vec3& v);
    vec2(const vec3i& v);
    vec2(const vec4& v);
    
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
    
    const float& operator[](size_t index) const
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
    vec2i(const vec3& v);
    vec2i(const vec3i& v);
    vec2i(const vec4& v);
    
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
    
    const int& operator[](size_t index) const
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
    
    vec3(const vec2& v);
    vec3(const vec2i& v);
    vec3(const vec3i& v);
    vec3(const vec4& v);
    
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
    
    const float& operator[](size_t index) const
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
    vec3 cross(const vec3& v) const { return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    vec3 normalize()
    {
        float div = sqrt(x * x + y * y + z * z);
        x /= div;
        y /= div;
        z /= div;
        return *this;
    }
    float norm() const { return sqrt(x * x + y * y + z * z); }
    
    vec3 max(const vec3& v) const
    {
        vec3 res;
        res.x = std::max(v.x, x);
        res.y = std::max(v.y, y);
        res.z = std::max(v.z, z);
        return res;
    }
    
    float x, y, z;
};


class vec3i{
public:
    vec3i() : x(0), y(0), z(0) {}
    vec3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    vec3i(int _f) : x(_f), y(_f), z(_f) {}
    
    vec3i(const vec2& v);
    vec3i(const vec2i& v);
    vec3i(const vec3& v);
    vec3i(const vec4& v);
    
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
    
    const int& operator[](size_t index) const
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
    vec3i cross(const vec3i& v) const { return vec3i(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    
    int x, y, z;
};


class vec4{
public:
    vec4() : x(0), y(0), z(0), w(0) {}
    vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    vec4(float _f) : x(_f), y(_f), z(_f), w(_f) {}
    
    vec4(const vec2& v) : x(v.x), y(v.y), z(0), w(0) {}
    vec4(const vec2i& v) : x(v.x), y(v.y), z(0), w(0) {}
    vec4(const vec3& v) : x(v.x), y(v.y), z(v.z), w(0) {}
    vec4(const vec3i& v) : x(v.x), y(v.y), z(v.z), w(0) {}
    
    vec4 operator +(const vec4& v) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
    vec4 operator -(const vec4& v) const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
    vec4 operator *(const vec4& v) const { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
    vec4 operator /(const vec4& v) const { return vec4(x / v.x, y / v.y, z / v.z, w / v.w); }
    
    vec4 operator *(const mat4& m) const;
    
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
    
    const float& operator[](size_t index) const
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


class mat2{
public:
    mat2()
    {
        *this = identity();
    }
    
    mat2(const vec2& v0, const vec2& v1)
    {
        cols = {v0, v1};
    }
    
    mat2(float x0, float y0,
         float x1, float y1)
    {
        cols = {{{x0, x1}, {y0, y1}}};
    }

    mat2 identity() const
    {
        return mat2(1.0, 0.0,
                    0.0, 1.0);
    }

    mat2 zero() const
    {
        return mat2(0.0, 0.0,
                    0.0, 0.0);
    }

    vec2& operator[](int row)
    {
        return cols[row];
    }
    
    const vec2& operator[](int row) const
    {
        return cols[row];
    }
    
    float determinant()
    {
        return cols[0][0] * cols[1][1] - cols[0][1] * cols[1][0];
    }
    
    std::array<vec2, 2> cols;
};


class mat3{
public:
    mat3()
    {
        *this = identity();
    }
    
    mat3(const vec3& v0, const vec3& v1, const vec3& v2)
    {
        cols = {v0, v1, v2};
    }
    
    mat3(float x0, float y0, float z0,
         float x1, float y1, float z1,
         float x2, float y2, float z2)
    {
        cols = {{{x0, x1, x2}, {y0, y1, y2}, {z0, z1, z2}}};
    }

    mat3 identity() const
    {
        return mat3(1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0);
    }

    mat3 zero() const
    {
        return mat3(0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0);
    }

    vec3& operator[](int row)
    {
        return cols[row];
    }
    
    const vec3& operator[](int row) const
    {
        return cols[row];
    }
    
    float determinant()
    {
        return cols[0][0] * (cols[1][1] * cols[2][2] - cols[2][1] * cols[1][2])
            - cols[1][0] * (cols[0][1] * cols[2][2] - cols[2][1] * cols[0][2])
            + cols[2][0] * (cols[0][1] * cols[1][2] - cols[1][1] * cols[0][2]);
    }
    
    mat3& setCol(int col, const vec3& v)
    {
        cols[col] = v;
        return *this;
    }
    
    mat3& setRow(int row, const vec3& v)
    {
        cols[0][row] = v.x;
        cols[1][row] = v.y;
        cols[2][row] = v.z;
        return *this;
    }
    
    std::array<vec3, 3> cols;
};


class mat4{
public:
    mat4()
    {
        *this = identity();
    }
    
    mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3)
    {
        cols = {v0, v1, v2, v3};
    }
    
    mat4(float x0, float y0, float z0, float w0,
         float x1, float y1, float z1, float w1,
         float x2, float y2, float z2, float w2,
         float x3, float y3, float z3, float w3)
    {
        cols = {{{x0, x1, x2, x3}, {y0, y1, y2, y3}, {z0, z1, z2, z3}, {w0, w1, w2, w3}}};
    }
    
    mat4 identity() const
    {
        return mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
    }
    
    mat4 zero() const
    {
        return mat4(0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0);
    }
    
    vec4& operator[](int row)
    {
        return cols[row];
    }
    
    const vec4& operator[](int row) const
    {
        return cols[row];
    }
    
    vec4 operator*(const vec4& v);
    mat4& operator*(const mat4& m);

    std::array<vec4, 4> cols;
};


#endif /* math_h */
