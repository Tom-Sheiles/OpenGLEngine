#pragma once

#include "OglMath.h"
#include "Material.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <gl/glew.h>
#include <gl/GL.h>

class Object{
protected:
    float *m_VertexPositions;
    unsigned int *m_Indicies;

    unsigned int m_VertexBuffer;
    unsigned int m_IndexBuffer;
    unsigned int m_nIndicies;

    glm::mat4 m_modelMatrix;
    int u_MVP;

public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Material *m_Material;

    unsigned int GetNIndicies() { return m_nIndicies; }
    virtual void transformObject() = 0;

private:
    virtual void RegisterObject() = 0;
};