#pragma once

#include "Object.h"

class Quad: public Object
{
public:
    Quad(Material *material);
    ~Quad();

    void transformObject();

private:
    void RegisterObject();
};
