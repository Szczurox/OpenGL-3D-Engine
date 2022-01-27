#version 330 core

out vec4 FragColor;

uniform vec4 Color; 

void main() {
    vec4 color = Color;
	color.a = 0.7;
	FragColor = lightColor;
}