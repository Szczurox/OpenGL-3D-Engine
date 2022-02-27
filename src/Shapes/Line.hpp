#ifndef LINE_CLASS_H
#define LINE_CLASS_H

#include<glm/glm.hpp>
#include<cmath>
#include<cfloat>

class Line {
public:
	glm::vec3 start = glm::vec3(0.0f);
	glm::vec3 end = glm::vec3(0.0f);

	// Constructors
	Line() : start(0.0f, 0.0f, 0.0f), end(0.0f, 0.0f, 0.0f) {} // Empty
	Line(const glm::vec3 s, const glm::vec3 e) :
		start(s), end(e) {} // From start and end points
};


#endif