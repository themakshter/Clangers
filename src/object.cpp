#include "object.h"

using namespace std;
using namespace glm;

Object::Object(const char * objFile,const char * imageFile)
{
    objPath = objFile;
    imagePath = imageFile;
    load();
    loadTexture();
}

void Object::load(void)
{
    bool success;
    success = loadOBJ(objPath,vertices,uvs,normals);
    if(success)
    {
        glGenBuffers(3, vbo);
        glGenVertexArrays(1, vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
        glBindVertexArray(vao[0]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (const GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (const GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (const GLvoid*)0);
    }
    else
    {
        printf("ERROR! Object was not loaded\n");
    }
}


GLuint Object::loadTexture()
{
    textureID = loadBMP_custom(imagePath);
    return textureID;
}

void Object::rotate(float rotation, vec3 axes)
{
    object = glm::rotate(object, rotation, axes);
}

void Object::translate(vec3 translations)
{
    object = glm::translate(object, translations);
}

void Object::scale(vec3 scales)
{
    object = glm::scale(object, scales);
}

void Object::render(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glDrawArrays(GL_QUADS, 0, vertices.size());
}

void Object::setMatrix(mat4 newMatrix)
{
    object = newMatrix;
}

mat4 Object::getMatrix(void)
{
    return object;
}
