#include "Renderer2D.h"

Shader *Renderer2D::s_UnlitShader;
glm::mat4 Renderer2D::s_ProjectionMatrix;
glm::mat4 Renderer2D::s_ViewMatrix;
Engine *Renderer2D::s_Engine;
uint32_t Renderer2D::s_nIndicies;
RenderBatch2D Renderer2D::s_RenderBatches;

void Renderer2D::Init(float screenWidth, float screenHeight, Engine *engine)
{
    glClearColor(0.23, 0.23, 0.23, 1.0f);

    s_Engine = engine;
    s_ProjectionMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, 0.3f, 10.0f);
    s_ViewMatrix = glm::translate(s_ProjectionMatrix, glm::vec3(screenWidth/2, screenHeight/2, 0));
    
    s_UnlitShader = new Shader("./res/Shaders/UnlitVertex.GLSL","./res/Shaders/UnlitFragment.GLSL");

    glGenBuffers(1, &s_RenderBatches.VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, s_RenderBatches.VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, s_RenderBatches.MaxVerticies * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &s_RenderBatches.IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderBatches.IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_RenderBatches.MaxIndicies * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &s_RenderBatches.VertexArray);
    glBindVertexArray(s_RenderBatches.VertexArray);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, tint));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Renderer2D::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, s_nIndicies, GL_FLOAT, nullptr);

    s_Engine->SwapGLBuffers();
}