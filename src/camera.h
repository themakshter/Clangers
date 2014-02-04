#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>


class Camera {
	private:
		glm::mat4 projection, view, mvp;
		glm::vec3 position, target, direction;
		float yawRotation;
		double speed;
	public:
		Camera();
		void left(float rotation);
		void right(float rotation);
		void raise(float delta);
		void lower(float delta);
		void increaseSpeed(float difference);
		void decreaseSpeed(float difference);
		void resetSpeed();
		void move(float delta);
		void jumpTo(glm::vec3 vertex);
		void lookAt(float rotation);
		glm::mat4 getMVP(glm::mat4 model);
};
