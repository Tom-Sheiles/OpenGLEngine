#include "Renderer.h"

std::vector<Object*> Renderer::objects;
glm::mat4 Renderer::projectionMatrix;
glm::mat4 Renderer::viewMatrix;

Engine *Renderer::s_engine;
Shader *Renderer::s_StandardShader;

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

void Renderer::Init(int screenWidth, int screenHeight, Engine *engine, unsigned int options)
{
    glDebugMessageCallback(MessageCallback, 0); 
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    s_engine = engine;

    glClearColor(0.53f, 0.42f, 0.65f, 1);

    if((options & WIREFRAME) == WIREFRAME) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if((options & CULLING) == CULLING) glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    //projectionMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -5.0f, 5.0f);
    projectionMatrix = glm::perspective(45.0f, (float)screenWidth/screenHeight, 0.3f, 1000.0f);
    //viewMatrix = glm::translate(projectionMatrix, glm::vec3(screenWidth/2, screenHeight/2, 0));
    viewMatrix = glm::scale(projectionMatrix, glm::vec3(40.0f));

    //s_StandardShader = new Shader("./res/Shaders/StandardVertex.GLSL", "./res/Shaders/StandardFragment.GLSL");
}

void Renderer::Register(Object *object)
{
    objects.push_back(object);
}

void Renderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->transformObject();
        objects[i]->m_Material->Bind();
        glDrawElements(GL_TRIANGLES, objects[i]->GetNIndicies(), GL_UNSIGNED_INT, nullptr);
    }

    s_engine->SwapGLBuffers();
}

void Renderer::Resize(int width, int height)
{
   //projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f); 
   glViewport(0, 0, width, height);
}