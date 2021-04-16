#ifndef UNICODE
#define UNICODE
#endif

#include "Engine.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include "Quad.h"
#include "Renderer.h"
#include "Material.h"

#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include<array>

struct Vertex{
    Vector3 positions;
    Vector3 color;
};

struct MaterialS{
    Shader *shader;
    Vector3 color;
};

std::array<Vertex, 4> CreateQuad(float x, float y, float scale, MaterialS mat)
{
    Vertex v0;
    v0.positions = {x, y, 0.0f};
    v0.color = {mat.color.x, mat.color.y, mat.color.z}; //{0.78, 0.19, 0.19}

    Vertex v1;
    v1.positions = {x + scale, y, 0.0f};
    v1.color = {mat.color.x, mat.color.y, mat.color.z}; //{0.78, 0.19, 0.19}

    Vertex v2;
    v2.positions = { x + scale, y + scale, 0.0f};
    v2.color = {mat.color.x, mat.color.y, mat.color.z}; //{0.78, 0.19, 0.19}

    Vertex v3;
    v3.positions = {x, y+scale, 0.0f};
    v3.color = {mat.color.x, mat.color.y, mat.color.z}; //{0.78, 0.19, 0.19}

    return {v0, v1, v2, v3};
}

std::array<unsigned int, 6> CreateQuadIndexBuffer(unsigned int i)
{
    i *= 4;
    return {i, i+1, i+2, i+2, i+3, i};
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 800;
    float screenHeight = 600;
    float nearPlane = -0.3f;
    float farPlane = 1000.0f;

    float fov = 45.0f;

    bool isPerspective = false;

    Engine *engine = new Engine(L"APP", 200, 50, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    Renderer::Init(screenWidth, screenHeight, engine, SHADED | CULLING);

    Shader *shader = new Shader("./res/Shaders/StandardVertex.GLSL", "./res/Shaders/StandardFragment.GLSL");

    MaterialS red    {shader, {1, 0, 0}};
    MaterialS blue   {shader, {0, 0, 1}};
    MaterialS green  {shader, {0, 1, 0}};
    MaterialS yellow {shader, {1, 1, 0}};

    glm::mat4 proj;
    glm::mat4 view;

    if(!isPerspective){
        proj = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, nearPlane, farPlane);
        view= glm::translate(proj, glm::vec3(screenWidth/2, screenHeight/2, 0));
        view = glm::scale(view, glm::vec3(50, 50, 0));
    }else{
        proj = glm::perspective(fov,(float)(screenWidth/screenHeight), nearPlane, farPlane);
        view = glm::scale(proj, glm::vec3(40.0f));
    }
    
    GLint vp = glGetUniformLocation(shader->GetShaderID(), "u_ViewProjection");
    glUniformMatrix4fv(vp, 1, GL_FALSE, &view[0][0]);

    const int maxQuads = 1000;
    const int maxVerts = maxQuads * 4;
    const int maxIndicies = maxQuads * 6;

    unsigned int vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, maxVerts * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, positions));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));


    unsigned int ind[maxIndicies];
    auto ind0 = CreateQuadIndexBuffer(0);
    auto ind1 = CreateQuadIndexBuffer(1);
    auto ind2 = CreateQuadIndexBuffer(2);
    auto ind3 = CreateQuadIndexBuffer(3);


    memcpy(ind, ind0.data(), 6 * sizeof(unsigned int));
    memcpy(ind + 6, ind1.data(), 6 * sizeof(unsigned int));
    memcpy(ind + 12, ind2.data(), 6 * sizeof(unsigned int));
    memcpy(ind + 12+6, ind3.data(), 6 * sizeof(unsigned int));

    unsigned int ib;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);


    float cameraX = screenWidth/2;
    float cameraY = screenHeight/2;
    float cameraZoom = 50;

    Vertex verts[maxVerts];
    while(engine->EngineRunning())
    {

        if(Keys['A']) cameraX -= 150.0f * Engine::deltaTime;
        if(Keys['D']) cameraX += 150.0f * Engine::deltaTime;
        if(Keys['W']) cameraY += 150.0f * Engine::deltaTime;
        if(Keys['S']) cameraY -= 150.0f * Engine::deltaTime;

        if(Keys['Q']) cameraZoom += 100.0f * Engine::deltaTime;
        if(Keys['E']) cameraZoom -= 100.0f * Engine::deltaTime;

        view = glm::translate(proj, glm::vec3(cameraX, cameraY, 0));
        view = glm::scale(view, glm::vec3(cameraZoom, cameraZoom, 0));

        glUseProgram(shader->GetShaderID());

        glUniformMatrix4fv(vp, 1, GL_FALSE, &view[0][0]);

        auto quad0 = CreateQuad(-0.6, 0.6, 1, red);
        auto quad1 = CreateQuad(0.6, 0.6, 1, green);
        auto quad2 = CreateQuad(-0.6, -0.6, 1, blue);
        auto quad3 = CreateQuad(0.6, -0.6, 1, yellow);

        memcpy(verts, quad0.data(), quad0.size() * sizeof(Vertex));
        memcpy(verts + quad0.size(), quad1.data(), quad1.size() * sizeof(Vertex));
        memcpy(verts + quad0.size() + quad1.size(), quad2.data(), quad2.size() * sizeof(Vertex));
        memcpy(verts + quad0.size() + quad1.size() + quad2.size(), quad3.data(), quad3.size() * sizeof(Vertex));


        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        glDrawElements(GL_TRIANGLES, 12+6+6, GL_UNSIGNED_INT, nullptr);

        engine->SwapGLBuffers();
    }

    delete engine;

    return 0;
}