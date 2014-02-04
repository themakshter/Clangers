#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util.h"

class Object {
	private:
		GLuint vao[1];
		GLuint vbo[3];
		GLuint textureID;
		const char * objPath;
		const char * imagePath;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;

		glm::mat4 object;

	public:
		Object(const char * objFile,const char * imageFile);
		void load(void);
		GLuint loadTexture(void);
		void rotate(float rotation, glm::vec3 axes);
		void translate(glm::vec3 translations);
		void scale(glm::vec3 scales);
		void render(void);
		void setMatrix(glm::mat4 newMatrix);
		glm::mat4 getMatrix(void);
};
