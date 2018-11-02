// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>
using namespace std;

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	double sin_d = sin(degrees * pi / 180.0);
	double cos_d = cos(degrees * pi / 180.0);
	mat3 mymat1 = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
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

void Transform::left(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HEREvec3 axis = glm::normalize(up);
	vec3 axis = glm::normalize(up);
	eye = rotate(degrees, axis) * eye;
	//up = rotate(-degrees, axis) * up;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE 
	vec3 axis = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, axis) * eye;
	up = rotate(degrees, axis) * up;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	// YOUR CODE FOR HW2 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 R(u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		0, 0, 0, 1);

	mat4 T(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1);
	return R * T;
	// Likely the same as in HW 1.  
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	fovy = fovy * pi / 180;
	float a = -(zFar + zNear) / (zFar - zNear);
	float b = -(2 * zFar * zNear) / (zFar - zNear);
	float d = cos(fovy / 2.0) / sin(fovy / 2.0);

	ret = mat4(d / aspect, 0, 0, 0,
		0, d, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0);
	// New, to implement the perspective transform as well.  
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret = mat4(sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
	// YOUR CODE FOR HW2 HERE
	// Implement scaling 
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret = mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		tx, ty, tz, 1);
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
