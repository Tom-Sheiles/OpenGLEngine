#include "Renderer.h"

std::vector<Object*> Renderer::objects;
glm::mat4 Renderer::projectionMatrix;
glm::mat4 Renderer::viewMatrix;

Engine *Renderer::s_engine;

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

void Renderer::Init(int screenWidth, int screenHeight, Engine *engine)
{
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );  

    s_engine = engine;

    glClearColor(0.91f, 0.67f, 0.33f, 1.0f);

    projectionMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    viewMatrix = glm::translate(projectionMatrix, glm::vec3(screenWidth/2, screenHeight/2, 0));
    viewMatrix = glm::scale(viewMatrix, glm::vec3(100.0f));
}

void Renderer::Register(Object *object)
{
    objects.push_back(object);
}

void Renderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0; i < objects.size(); i++)
    {
        //objects[i]->BindObject();
        objects[i]->transformObject();
        glDrawElements(GL_TRIANGLES, objects[i]->GetNIndicies(), GL_UNSIGNED_INT, nullptr);
    }

    s_engine->SwapGLBuffers();
}