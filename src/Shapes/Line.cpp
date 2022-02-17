#include"Line.hpp"

float Line::Length() {
	return glm::length(start - end);
}

float Line::LengthSq() {
	return glm::dot(start - end, start - end);
}