#ifndef model_h
#define model_h

#include <vector>
#include "tgaimage.h"
#include "math.h"

class Model{
public:
    Model(const char *filename);
    ~Model();
    
    std::vector<vec3> verts;
    std::vector<vec2> tex_coords;
    std::vector<vec3> norms;
    
    std::vector<int> facet_vrt;
    std::vector<int> facet_tex;
    std::vector<int> facet_nrm;
    
    TGAImage diffuse_map;
    TGAImage normal_map;
    TGAImage specular_map;
    
    void load_texture(std::string filename, const std::string suffix, TGAImage &img);
    
    size_t nfaces() { return verts.size(); }
    
    vec2 uv(int face_id, int vert_id);
    vec3 normal(const vec2& uv);
    vec3 normal(int face_id, int vert_id);
};

#endif /* model_h */
