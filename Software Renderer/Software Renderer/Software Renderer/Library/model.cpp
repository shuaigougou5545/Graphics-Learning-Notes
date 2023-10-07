#include "model.h"
#include <string>
#include <fstream>
#include <sstream>


Model::Model(const char *filename)
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if(in.fail()) return;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0, 2, "v "))
        {
            // vertex
            iss >> trash;
            vec3 v;
            for(int i = 0; i < 3; i++)
                iss >> v[i];
            verts.push_back(v);
        }else if(!line.compare(0, 3, "vn ")){
            // normal
            iss >> trash >> trash;
            vec3 n;
            for(int i = 0; i < 3; i++)
                iss >> n[i];
            norms.push_back(n.normalize());
        }else if(!line.compare(0, 3, "vt ")){
            // texture coords - uv
            iss >> trash >> trash;
            vec2 uv;
            for(int i = 0; i < 2; i++)
                iss >> uv[i];
            tex_coords.push_back({uv.x, 1.f - uv.y}); // 上下颠倒
        }else if(!line.compare(0, 2, "f "))
        {
            int f, t, n;
            iss >> trash;
            int count = 0;
            while (iss >> f >> trash >> t >> trash >> n)
            {
                // 索引从1开始
                facet_vrt.push_back(--f);
                facet_tex.push_back(--t);
                facet_nrm.push_back(--n);
                count++;
            }
            
            if(count != 3)
            {
                // 只考虑以三角形为图元拓扑的obj
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                return;
            }
        }
    }
    std::cerr << "# v# " << verts.size() << " f# "  << facet_vrt.size() << " vt# " << tex_coords.size() << " vn# " << norms.size() << std::endl;
    
    load_texture(filename, "_diffuse.tga", diffuse_map);
//    load_texture(filename, "_nm_tangent.tga", normal_map);
//    load_texture(filename, "_spec.tga", specular_map);
}

Model::~Model()
{
      
}

void Model::load_texture(std::string filename, const std::string suffix, TGAImage &img)
{
    size_t dot = filename.find_last_of(".");
    if(dot == std::string::npos)
        return;
    
    std::string texfile = filename.substr(0, dot) + suffix;
    std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
}

vec2 Model::uv(int face_id, int vert_id)
{
    return tex_coords[facet_tex[face_id * 3 + vert_id]];
}

vec3 Model::normal(const vec2& uv)
{
    TGAColor c = normal_map.get(uv.x * normal_map.get_width(), uv.y * normal_map.get_height());
    return vec3(float(c[2]), float(c[1]), float(c[0])) * 2.f / 255.f - vec3(1.f);
}

vec3 Model::normal(int face_id, int vert_id)
{
    return norms[facet_nrm[face_id * 3 + vert_id]];
}
