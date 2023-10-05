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
};

#endif /* model_h */
