#ifndef model_h
#define model_h

#include <vector>
#include "vec.h"

class Model{
public:
    Model(const char *filename);
    ~Model();
    std::vector<vec3> verts;
    std::vector<std::vector<int>> faces;
};

#endif /* model_h */
