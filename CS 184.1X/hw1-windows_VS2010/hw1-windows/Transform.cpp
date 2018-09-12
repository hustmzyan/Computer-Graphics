// Transform.cpp: implementation of the Transform class.

#include <iostream>
#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	float sin_d = sin(degrees * pi / 180.0);
	float cos_d = cos(degrees * pi / 180.0);
	mat3 mymat1 = mat3(1,0,0,0,1,0,0,0,1);
	mat3 mymat2 = mat3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		               axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		               axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);
	mat3 mymat3 = mat3(0, axis.z, -axis.y,
		               -axis.z, 0, axis.x,
		               axis.y, -axis.x, 0);
	mymat1 = cos_d * mymat1;
	mymat2 = (1 - cos_d) * mymat2;
	mymat3 = sin_d * mymat3;
  // You will change this return call
  return mymat1 + mymat2 + mymat3;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(up);
	eye = rotate(-degrees, axis) * eye;
	up = rotate(-degrees, axis) * up;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 axis = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, axis) * eye;
	up = rotate(degrees, axis) * up;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 w = eye / glm::length(eye);
	vec3 u = glm::cross(up, w) / glm::length(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	mat4 m1 = mat4(u.x, u.y, u.z, 0,
		           v.x, v.y, v.z, 0,
		           w.x, w.y, w.z, 0,
		           0, 0, 0, 1);
	
	mat4 m2 = mat4(1, 0, 0, -eye.x,
		0, 1, 0, -eye.y,
		0, 0, 1, -eye.z,
		0, 0, 0, 1);
	m1 = glm::transpose(m1);
	m2 = glm::transpose(m2);
  // You will change this return call
  return m1 * m2;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
