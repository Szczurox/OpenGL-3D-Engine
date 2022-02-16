#include"Line.hpp"

// Useful for later, currently stored here
//#define CMP(x, y) \
// (fabsf((x)–(y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

float Line::Length() {
	return glm::length(start - end);
}

float Line::LengthSq() {
	return glm::dot(start - end, start - end);
}