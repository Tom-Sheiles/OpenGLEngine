#pragma once

#include "Engine.h"
#include "Object.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Renderer{
private:
    static std::vector<Object*> objects;
    static Engine *s_engine;

public:
    static glm::mat4 projectionMatrix;
    static glm::mat4 viewMatrix;

    static void Init(int screenWidth, int screenHeight, Engine *engine);
    static void Register(Object *object);
    static void Draw();
};