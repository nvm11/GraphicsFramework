#version 330 core

out vec FragColor

uniform vec4 lightColor;

void main()
{
	FragColor = lightColor;
}