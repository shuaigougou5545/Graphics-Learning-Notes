#ifndef model_h
#define model_h

#include <vector>
#include "vec.h"

class model{
public:
    model(const char *filename);
    ~model();
    std::vector<vec3> verts;
    std::vector<std::vector<int>> faces;
};

#endif /* model_h */
