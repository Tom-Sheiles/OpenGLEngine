#include "Renderer2D.h"

Shader *Renderer2D::s_UnlitShader;
glm::mat4 Renderer2D::s_ProjectionMatrix;
glm::mat4 Renderer2D::s_ViewMatrix;
Engine *Renderer2D::s_Engine;
RenderBatch2D Renderer2D::s_RenderBatches;

float *Renderer2D::s_Verticies;
uint32_t *Renderer2D::s_Indicies;
uint32_t Renderer2D::s_nIndicies;
uint32_t Renderer2D::s_nVerticies;

float vert[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f, 0.5f};
    uint32_t ind[] = {0,1,2,2,3,0};

 void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    printf("GL Error message = %s\n", message);
}

void Renderer2D::Init(float screenWidth, float screenHeight, Engine *engine)
{
    glDebugMessageCallback(MessageCallback, 0); 
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glClearColor(0.23, 0.23, 0.23, 1.0f);

    s_Engine = engine;
    s_ProjectionMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, 0.3f, 10.0f);
    s_ViewMatrix = glm::translate(s_ProjectionMatrix, glm::vec3(screenWidth/2, screenHeight/2, 0));
    s_ViewMatrix = glm::scale(s_ViewMatrix, glm::vec3(10.0f));
    
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, tint));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    s_Verticies = new float[4*2];
    s_Indicies = new uint32_t[6];
    Register();
}

void Renderer2D::Register()
{
    memcpy(s_Verticies, vert, sizeof(vert));
    memcpy(s_Indicies, ind, sizeof(ind));
    
    s_nIndicies += 6;
    s_nVerticies += (4*2);
}

void Renderer2D::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, s_RenderBatches.VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderBatches.IndexBuffer);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_nVerticies * sizeof(float), s_Verticies);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, s_nIndicies * sizeof(uint32_t), s_Indicies);

    
    glDrawElements(GL_TRIANGLES, s_nIndicies, GL_UNSIGNED_INT, nullptr);

    s_Engine->SwapGLBuffers();
}