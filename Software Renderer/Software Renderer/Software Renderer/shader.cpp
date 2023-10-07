#include "shader.h"
#include "geometry.h"


mat4 model_matrix = mat4().identity();
mat4 view_matrix = mat4().identity();
mat4 projection_matrix = mat4().identity();
mat4 viewport_matrix = mat4().identity();


void viewport(int x, int y, int w, int h)
{
    viewport_matrix = mat4().identity();
    viewport_matrix[0][0] = w / 2.f;
    viewport_matrix[3][0] = x + w / 2.f;
    
    viewport_matrix[1][1] = h / 2.f;
    viewport_matrix[3][1] = y + w / 2.f;
    
    // min_depth: 0.0 ; max_depth: 255.0
    viewport_matrix[2][2] = 255.f / 2.f;
    viewport_matrix[3][2] = 255.f / 2.f;
}

void projection(float n, float f, float alpha, float aspect_ratio)
{
    projection_matrix = mat4().identity();
    projection_matrix[0][0] = 1.f / (aspect_ratio * tan(alpha / 2.f));
    projection_matrix[1][1] = 1.f / tan(alpha / 2.f);
    projection_matrix[2][2] = (f + n) / (f - n);
    projection_matrix[3][2] = -2.f * n * f / (f - n);
    projection_matrix[2][3] = 1;
    projection_matrix[3][3] = 0;
}

void lookat(const vec3& eye, const vec3& center, const vec3& up)
{
    vec3 z = (eye - center).normalize();
    vec3 x = up.cross(z).normalize();
    vec3 y = z.cross(x).normalize();
    
    view_matrix = mat4().identity();
    view_matrix[0][0] = x[0];
    view_matrix[0][1] = x[1];
    view_matrix[0][2] = x[2];
    view_matrix[1][0] = y[0];
    view_matrix[1][1] = y[1];
    view_matrix[1][2] = y[2];
    view_matrix[2][0] = z[0];
    view_matrix[2][1] = z[1];
    view_matrix[2][2] = z[2];
    view_matrix[0][3] = -x.dot(eye);
    view_matrix[1][3] = -y.dot(eye);
    view_matrix[2][3] = -z.dot(eye);
}


void triangle(const std::vector<vec4>& pts, Shader& shader, TGAImage &image, TGAImage &zbuffer)
{
    vec2 bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    vec2 bboxmax(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
    
    for(int i = 0; i < 3; i++)
    {
        // z != 0
        bboxmin.x = std::min(bboxmin.x, pts[i].x / pts[i].z);
        bboxmin.y = std::min(bboxmin.y, pts[i].y / pts[i].z);
        bboxmax.x = std::max(bboxmax.x, pts[i].x / pts[i].z);
        bboxmax.y = std::max(bboxmax.y, pts[i].y / pts[i].z);
    }
    
    vec2i P;
    TGAColor color;
    for(P.x = bboxmin.x; P.x <= bboxmax.x; P.x++)
    {
        for(P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
        {
            
            vec3 bary = barycentric(vec2(pts[0]), vec2(pts[1]), vec2(pts[2]), P);
            
            // interpolation
            float z = pts[0].z * bary[0] + pts[1].z * bary[1] + pts[2].z * bary[2];
            float w = pts[0].w * bary[0] + pts[1].w * bary[1] + pts[2].w * bary[2];
            
            int frag_depth = std::max(0, std::min(255, int(z / w + 0.5)));
            
            if(bary.x < 0.f || bary.y < 0.f || bary.z < 0.f || zbuffer.get(P.x, P.y)[0] > frag_depth)
                continue;
            
            bool discard = !shader.fragment(bary, color);
            if(discard)
            {
                zbuffer.set(P.x, P.y, TGAColor(frag_depth));
                image.set(P.x, P.y, color);
            }
        }
    }
}
