#pragma once

#define SHADED      0x01
#define WIREFRAME   0x02
#define CULLING     0x04

#include "Engine.h"
#include "Object.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Renderer{
private:
    static std::vector<Object*> objects;
    static Engine *s_engine;

    static Shader *s_StandardShader;

public:
    static glm::mat4 projectionMatrix;
    static glm::mat4 viewMatrix;

    static void Init(int screenWidth, int screenHeight, Engine *engine, unsigned int options);
    static void Register(Object *object);
    static void Draw();
    static void Resize(int width, int height);

    static inline Shader *GetStandardShader() { return s_StandardShader; }
};