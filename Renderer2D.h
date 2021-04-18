#pragma once

#include "Engine.h"
#include "Shader.h"
#include "OglMath.h"
#include <gl/glew.h>
#include <gl/GL.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

struct QuadVertex{
    Vector3 position;
    Vector3 tint;
};

struct RenderBatch2D{
    uint32_t VertexBuffer;
    uint32_t IndexBuffer;
    uint32_t VertexArray;
    const int MaxVerticies = 4000;
    const int MaxIndicies = 6000;
    int nObjectsInBatch = 0;
};

class Renderer2D
{
public:
    static Shader *s_UnlitShader;
    static void Init(float screenWidth, float screenHeight, Engine *engine);
    static void Draw();
    static void Register();

private:
    static Engine *s_Engine;

    static glm::mat4 s_ProjectionMatrix;
    static glm::mat4 s_ViewMatrix;
    
    static RenderBatch2D s_RenderBatches;

    static float *s_Verticies;
    static uint32_t *s_Indicies;
    static uint32_t s_nIndicies;
    static uint32_t s_nVerticies;
};

