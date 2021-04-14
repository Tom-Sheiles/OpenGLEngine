#include "Quad.h"
#include "Renderer.h"

Quad::Quad(Material *material)
{
    position = {0, 0, 0};
    rotation = {0, 0, 0};
    scale =    {1, 1, 1};

    m_VertexPositions = new float[] {
         -1.000000f, -1.000000f, 1.000000f,
         -1.000000f, 1.000000f, 1.000000f,
         -1.000000f, -1.000000f, -1.000000f,
         -1.000000f, 1.000000f, -1.000000f,
         1.000000f, -1.000000f, 1.000000f,
         1.000000f, 1.000000f, 1.000000f,
         1.000000f, -1.000000f, -1.000000f,
         1.000000f, 1.000000f, -1.000000f

    };

    m_Indicies = new unsigned int[] {
         1, 2, 0, 3, 6, 2, 7, 4, 6, 5, 0, 4, 6, 0, 2, 3, 5, 7, 1, 3, 2, 3, 7, 6, 7, 5, 4, 5, 1, 0, 6, 4, 0, 3, 1, 5
    };

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), m_VertexPositions, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), m_Indicies, GL_DYNAMIC_DRAW);

    m_nIndicies = 36;

    m_Material = material;
    u_MVP = glGetUniformLocation(m_Material->GetShader()->GetShaderID(), "u_MVP");

    RegisterObject();
}

Quad::~Quad()
{
    delete m_VertexPositions;
    delete m_Indicies;
}

void Quad::RegisterObject()
{
    Renderer::Register(this);
}

void Quad::transformObject()
{
    m_modelMatrix = glm::translate(Renderer::viewMatrix, glm::vec3(position.x, position.y, position.z));

    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.x, glm::vec3(1,0,0));
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.y, glm::vec3(0,1,0));
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.z, glm::vec3(0,0,1));

    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(scale.x, scale.y, scale.z));

    //glUniform4f(glGetUniformLocation(Renderer::GetStandardShader()->GetShaderID(), "u_Color"), 1.0f, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(u_MVP, 1, GL_FALSE, &m_modelMatrix[0][0]);
}