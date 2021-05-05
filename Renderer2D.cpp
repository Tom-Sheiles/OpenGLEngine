#include "Renderer2D.h"
#include "GLDebug.h"

Shader *Renderer2D::s_UnlitShader;
glm::mat4 Renderer2D::s_ProjectionMatrix;
glm::mat4 Renderer2D::s_ViewMatrix;
Engine *Renderer2D::s_Engine;
RenderBatch2D Renderer2D::s_RenderBatches;

std::vector<float> Renderer2D::s_Verticies;
std::vector<uint32_t> Renderer2D::s_Indicies;
uint32_t Renderer2D::s_nIndicies;
uint32_t Renderer2D::s_nVerticies;

float vert[] = {
        -0.5f, -0.5f, 1.0, 0.0, 0.0,
         0.5f, -0.5f, 1.0, 0.0, 0.0,
         0.5f,  0.5f, 1.0, 0.0, 0.0,
        -0.5f, 0.5f,  1.0, 0.0, 0.0 };
    uint32_t ind[] = {0,1,2,2,3,0};

    float vert2[] = {
        -0.5f,  -2.0f,  0.0, 1.0, 0.0,
         0.5f,  -2.0f, 0.0, 1.0, 0.0,
         0.5f,  -1.0f, 0.0, 1.0, 0.0,
        -0.5f,  -1.0f,  0.0, 1.0, 0.0   };
    uint32_t ind2[] = {4,5,6,6,7,4};


void Renderer2D::Init(float screenWidth, float screenHeight, Engine *engine)
{
    StartGLDebug();
    glClearColor(0.23, 0.23, 0.23, 1.0f);

    s_Engine = engine;
    s_ProjectionMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, 0.3f, 10.0f);
    s_ViewMatrix = glm::translate(s_ProjectionMatrix, glm::vec3(screenWidth/2, screenHeight/2, 0));
    s_ViewMatrix = glm::scale(s_ViewMatrix, glm::vec3(50.0f));
    
    s_UnlitShader = new Shader("./res/Shaders/UnlitVertex.GLSL","./res/Shaders/UnlitFragment.GLSL");
    uint32_t ViewProjection = glGetUniformLocation(s_UnlitShader->GetShaderID(), "u_ViewProjection");

    if(ViewProjection == -1) { printf("Could not find View Projection Matrix!\n"); }
    glUniformMatrix4fv(ViewProjection, 1, GL_FALSE, &s_ViewMatrix[0][0]);

    glGenBuffers(1, &s_RenderBatches.VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, s_RenderBatches.VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, s_RenderBatches.MaxVerticies * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &s_RenderBatches.IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderBatches.IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_RenderBatches.MaxIndicies * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, tint));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int nReservedQuads = 20;

    s_Verticies.reserve(20*nReservedQuads);
    s_Indicies.reserve(6*nReservedQuads);

    Register(vert, ind);
    Register(vert2, ind2);
}

void Renderer2D::Register(float *verts, uint32_t* inds)
{
    s_Verticies.insert(s_Verticies.end(), verts, verts+20);
    s_Indicies.insert(s_Indicies.end(), inds, inds+6);
    return;
}

void Renderer2D::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, s_RenderBatches.VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderBatches.IndexBuffer);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_Verticies.size() * sizeof(float), s_Verticies.data());
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s_Indicies.size() * sizeof(uint32_t), s_Indicies.data());

    
    glDrawElements(GL_TRIANGLES, s_Indicies.size(), GL_UNSIGNED_INT, nullptr);

    s_Engine->SwapGLBuffers();
}