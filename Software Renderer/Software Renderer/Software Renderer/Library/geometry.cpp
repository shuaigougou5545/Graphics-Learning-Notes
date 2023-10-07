#include "geometry.h"


void draw_line(const vec2i& p0, const vec2i& p1, TGAImage& image, TGAColor color)
{
    int x0 = p0.x, y0 = p0.y;
    int x1 = p1.x, y1 = p1.y;
    
    bool steep = false;
    if(abs(x0 - x1) < abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
  
    if(x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
  
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for(int x = x0; x <= x1; x++)
    {
        if(steep)
            image.set(y, x, color);
        else
            image.set(x, y, color);
        
        error2 += derror2;
        if (error2 > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

bool is_point_in_triangle_2d(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary)
{
    // use 'cross product' to calculate barycentric coordinates
    float epsilon = 0.0001;
    bary = {-1.f, 1.f, 1.f};
    
    // AB AC PA
    vec3 a = {pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - p.x};
    vec3 b = {pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - p.y};
    
    vec3 u = a.cross(b);
    
    if (std::abs(u.z) < epsilon)
        return false;
    
    bary.x = 1.f - (u.x + u.y) / (float)u.z;
    bary.y = u.x / (float)u.z;
    bary.z = u.y / (float)u.z;
    
    if(bary.x < 0 ||
       bary.y < 0 ||
       bary.z < 0 ||
       std::abs(bary.x + bary.y + bary.z - 1.f) > epsilon)
        return false;
    return true;
}

bool is_point_in_triangle_2d_cramers_rule(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary)
{
    // use 'Cramer's Rule' to calculate barycentric coordinates
    float epsilon = 0.0001;
    bary = {-1.0, 1.0, 1.0};
    
    vec2 a = pts[0];
    vec2 b = pts[1];
    vec2 c = pts[2];
    
    vec2 ab = b - a;
    vec2 ac = c - a;
    vec2 ap = p - a;
    
    mat2 coords_matrix = { ab.x, ab.y, ac.x, ac.y };
    
    float D = coords_matrix.determinant();
    if(abs(D) < epsilon)
        return false;
    
    bary.y = mat2(ap.x, ap.y, ac.x, ac.y).determinant() / D;
    bary.z = mat2(ab.x, ab.y, ap.x, ap.y).determinant() / D;
    bary.x = 1.0 - (bary.y + bary.z);
    
    if(bary.x < 0 ||
       bary.y < 0 ||
       bary.z < 0 ||
       std::abs(bary.x + bary.y + bary.z - 1.f) > epsilon)
        return false;
    return true;
}

bool is_point_in_triangle_3d(const vec3& p, const std::array<vec3, 3>& pts, vec3& bary)
{
    // use 'subtriangle area' to calculate barycentric coordinates
    float epsilon = 0.0001;
    bary = {-1.0, 1.0, 1.0};
    
    vec3 a = pts[0];
    vec3 b = pts[1];
    vec3 c = pts[2];
    
    vec3 ab = b - a;
    vec3 bc = c - b;
    vec3 ca = a - c;
    
    float S = ab.cross(ca).norm() / 2.0;
    
    if(abs(S) < epsilon)
        return false;
    
    vec3 pbc = (p - b).cross(bc);
    vec3 pca = (p - c).cross(ca);
    vec3 pab = (p - a).cross(ab);
    
    if(pbc.dot(pca) * pbc.dot(pab) < 0.0)
        return false;
    
    float S_PBC = pbc.norm() / 2.0;
    float S_PCA = pca.norm() / 2.0;
    float S_PAB = pab.norm() / 2.0;
    
    bary.x = S_PBC / S;
    bary.y = S_PCA / S;
    bary.z = S_PAB / S;
    
    if(bary.x < 0 ||
       bary.y < 0 ||
       bary.z < 0 ||
       std::abs(bary.x + bary.y + bary.z - 1.f) > epsilon)
        return false;
    return true;
}


vec3 barycentric(const vec2& A, const vec2& B, const vec2& C, const vec2& P)
{
    // AB AC PA
    vec2 AB = B - A;
    vec2 AC = C - A;
    vec2 PA = A - P;
    
    vec3 u = vec3(AB.x, AC.x, PA.x).cross(vec3(AB.y, AC.y, PA.y));
    if(std::abs(u.z) < 1e-2)
        return vec3(-1.f, 1.f, 1.f);
    
    vec3 bary;
    bary.y = u.x / u.z;
    bary.z = u.y / u.z;
    bary.x = 1.f - (bary.y + bary.z);
    return bary;
}
