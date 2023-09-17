#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<float, 3> vec3;
typedef array<float, 4> vec4;
typedef array<array<float, 3>, 3> mat3;
typedef array<array<float, 4>, 4> mat4;

// 基于DirectX
void input(vec3& v)
{
    cin >> v[0] >> v[1] >> v[2];
}

void input(vec4& v, int w = 1)
{
    cin >> v[0] >> v[1] >> v[2];
    v[3] = w;
}

void input(mat4& m)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
                cin >> m[i][j];
}

void prt(const vec4& v)
{
    cout << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3] << "\n" << endl;
}

void prt(const mat4& m)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
                cout << m[i][j] << ' ';
        cout << "\n";
    }
    cout << endl;
}

vec3 normalize(const vec3& v)
{
    vec3 res;
    float sum = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    res[0] = v[0] / sum;
    res[1] = v[1] / sum;
    res[2] = v[2] / sum;
    return res;
}

vec4 zeroVec4()
{
    /*
        0 0 0 0
    */
    vec4 res;
    res[0] = res[1] = res[2] = 0;
    return res;
}

mat3 zeroMat3()
{
    /*
        0 0 0
        0 0 0
        0 0 0
    */
    mat3 res;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            res[i][j] = 0;
    return res;
}

mat4 zeroMat4()
{
    /*
        0 0 0 0
        0 0 0 0
        0 0 0 0
        0 0 0 0
    */
    mat4 res;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            res[i][j] = 0;
    return res;
}

mat4 identityMat4()
{
    /*
        1 0 0 0
        0 1 0 0
        0 0 1 0
        0 0 0 1
    */
    mat4 res = zeroMat4();
    res[0][0] = 1;
    res[1][1] = 1;
    res[2][2] = 1;
    res[3][3] = 1;   
    return res;
}

mat4 transposition(const mat4& m)
{
    mat4 res;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            res[i][j] = m[j][i];
    return res;
}

mat4 matrixMultiply(const mat4& m1, const mat4& m2)
{
    mat4 res = zeroMat4();

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                res[i][j] += m1[i][k] * m2[k][j];
    
    return res;
}

vec4 transform(const vec4& v, const mat4& m)
{
    vec4 res;
    for(int i = 0; i < 4; i++)
    {
        res[i] = 0;
        for(int j = 0; j < 4; j++)
            res[i] += v[j] * m[j][i];
    }
    return res;
}

mat4 getScaleMatrix(const vec3& scale)
{
    mat4 res = identityMat4();

    res[0][0] = scale[0];
    res[1][1] = scale[1];
    res[2][2] = scale[2];
    return res;
}

float angleToRadius(const float angle)
{
    const float pi = 3.1415926;
    return angle / 180.0 * pi;
}

mat4 getRotationMatrix(const vec3& rotation_axis, const float angle)
{
    mat4 res = identityMat4();
    
    float radius = angleToRadius(angle);
    float c = cos(radius);
    float s = sin(radius);
    vec3 axis = normalize(rotation_axis);
    float x = axis[0];
    float y = axis[1];
    float z = axis[2];

    /*
        罗德里格旋转公式:
        v' = cosθv + (1-cosθ)(n·v)n + sinθ(n×v)
    */

    res[0][0] = c + (1 - c) * x * x;
    res[0][1] = (1 - c) * x * y + s * z;
    res[0][2] = (1 - c) * x * z - s * y;
    res[1][0] = (1 - c) * x * y - s * z;
    res[1][1] = c + (1 - c) * y * y;
    res[1][2] = (1 - c) * y * z + s * x;
    res[2][0] = (1 - c) * x * z + s * y;
    res[2][1] = (1 - c) * y * z - s * x;
    res[2][2] = c + (1 - c) * z * z;

    return res;
}

mat4 getTranslationMatrix(const vec3& trans)
{
    mat4 res = identityMat4();
    res[3][0] = trans[0];
    res[3][1] = trans[1];
    res[3][2] = trans[2];
    return res;
}

mat4 getModelMatrix(const vec3& scale, const vec3& rotation_axis, const float angle, const vec3& trans)
{
    mat4 res = identityMat4();

    mat4 S = getScaleMatrix(scale);
    mat4 R = getRotationMatrix(rotation_axis, angle);
    mat4 T = getTranslationMatrix(trans);
    
    prt(S);
    prt(R);
    prt(T);

    res = matrixMultiply(res, S);
    res = matrixMultiply(res, R);
    res = matrixMultiply(res, T);
    
    return res;
}

mat4 getViewMatrix(const vec3& right, const vec3& up, const float forward, const vec3& cameraW)
{
    mat4 res = identityMat4();

    res[0] = 
}

int main()
{
    // local
    vec4 posL;
    input(posL);

    // model - function 1
    mat4 model;
    input(model);

    // model - function 2
    // vec3 scale = { 1,1,1 };
    // vec3 axis = { 0,0,1 };
    // float angle = 30.0;
    // vec3 trans = { 0,0,0 };
    // model = getModelMatrix(scale, axis, angle, trans);

    vec4 posW;
    posW = transform(posL, model);

    // view
    mat4 view;
    vec3 cameraW;
    vec3 right, up, forward;
    input(cameraW);
    input(right);
    input(up);
    input(forward);
    

    

    return 0;
}
