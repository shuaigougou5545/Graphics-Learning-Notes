#include "geometry.h"


bool isPointInTriangle2D(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary)
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

bool isPointInTriangle2D_CramersRule(const vec2& p, const std::array<vec2, 3>& pts, vec3& bary)
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

bool isPointInTriangle3D(const vec3& p, const std::array<vec3, 3>& pts, vec3& bary)
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


