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

std::array<Vertex, 4> CreateQuad(float x, float y, float scale, float r, float g, float b)
{
    Vertex v0;
    v0.positions = {x, y, 0.0f};
    v0.color = {r,g,b}; //{0.78, 0.19, 0.19}

    Vertex v1;
    v1.positions = {x + scale, y, 0.0f};
    v1.color = {r, g, b};

    Vertex v2;
    v2.positions = { x + scale, y + scale, 0.0f};
    v2.color = {r, g, b};

    Vertex v3;
    v3.positions = {x, y+scale, 0.0f};
    v3.color = {r,g,b};

    return {v0, v1, v2, v3};
}

std::array<unsigned int, 6> CreateQuadIndexBuffer(unsigned int i)
{
    i *= 4;
    return {i, i+1, i+2, i+2, i+3, i};
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    float screenWidth = 600;
    float screenHeight = 600;

    Engine *engine = new Engine(L"APP", 200, 50, screenWidth, screenHeight, hInstance, CREATE_CONSOLE);
    Renderer::Init(screenWidth, screenHeight, engine, SHADED | CULLING);

    Shader *shader = new Shader("./res/Shaders/StandardVertex.GLSL", "./res/Shaders/StandardFragment.GLSL");

    /*float ver[] = {
        -0.2, -0.2, 0.0,  0.78, 0.19, 0.19,
         0.2, -0.2, 0.0,  0.78, 0.19, 0.19,
         0.2,  0.2, 0.0,  0.78, 0.19, 0.19,
        -0.2,  0.2, 0.0,  0.78, 0.19, 0.19,
    };*/

    /*unsigned int indcies[] = {
        0, 1, 2,
        2, 3, 0,
    };*/

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


    unsigned int ind[12+6];
    auto ind0 = CreateQuadIndexBuffer(0);
    auto ind1 = CreateQuadIndexBuffer(1);
    auto ind2 = CreateQuadIndexBuffer(2);

    memcpy(ind, ind0.data(), 6 * sizeof(unsigned int));
    memcpy(ind + 6, ind1.data(), 6 * sizeof(unsigned int));
    memcpy(ind + 12, ind2.data(), 6 * sizeof(unsigned int));

    unsigned int ib;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);


    float speed = 5;
    while(engine->EngineRunning())
    {

        Vertex verts[12];
        auto quad0 = CreateQuad(-0.2, 0, 0.3, 0.78, 0.19, 0.19);
        auto quad1 = CreateQuad(0.2, 0, 0.3, 0.19, 0.78, 0.19);
        auto quad2 = CreateQuad(0.2, -0.5, 0.3, 0.19, 0.19, 0.78);

        memcpy(verts, quad0.data(), quad0.size() * sizeof(Vertex));
        memcpy(verts + quad0.size(), quad1.data(), quad1.size() * sizeof(Vertex));
        memcpy(verts + quad0.size() + + quad1.size(), quad2.data(), quad2.size() * sizeof(Vertex));


        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        glDrawElements(GL_TRIANGLES, 12+6 , GL_UNSIGNED_INT, nullptr);

        engine->SwapGLBuffers();
    }

    delete engine;

    return 0;
}