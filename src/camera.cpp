#include "camera.h"

using namespace glm;

Camera::Camera() {
	position = vec3(0.0f, 0.00f, 0.0f);
	yawRotation = 180.6f;
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	speed = 0.f;
	projection = perspective(45.0f, 1.0f, 0.0001f, 100.0f);
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::left(float rotation) {
	yawRotation -= rotation;
	if (yawRotation > 360.f) {
		yawRotation = 0.f;
	}
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::right(float rotation) {
	yawRotation += rotation;
	if (yawRotation > 360.f) {
		yawRotation = 0.f;
	}
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::raise(float delta) {
	float height = position.y + delta;
	if (height > 2.8f) {
		height = 2.8f;
	}
	position = vec3(position.x, height, position.z);
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::lower(float delta) {
	float height = position.y - delta;
	if (height < 0.f) {
		height = 0.f;
	}
	position= vec3(position.x, height, position.z);
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::increaseSpeed(float difference) {
	difference /= 10;
	if (speed + difference > 1) {
		speed = 1;
	}
	else {
		speed += difference;
	}
}

void Camera::decreaseSpeed(float difference) {
	difference /= 10;
	if (speed - difference < 0.0) {
		speed = 0.0;
	}
	else {
		speed -= difference;
	}
}

void Camera::resetSpeed() {
	speed = 0.f;
}

void Camera::move(float delta) {
	position = position + vec3(direction.x*speed*delta, direction.y*speed*delta, direction.z*speed*delta);
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::jumpTo(vec3 vertex) {
	position = vertex;
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

void Camera::lookAt(float rotation) {
	yawRotation = rotation;
	direction = vec3(glm::cos(yawRotation), 0, glm::sin(yawRotation));
	target = position + direction;
	view = glm::lookAt(position, target, vec3(0,1,0));
}

glm::mat4 Camera::getMVP(mat4 model) {
	mvp = projection * view * model;
	return mvp;
}
