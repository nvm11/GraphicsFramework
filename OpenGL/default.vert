#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

//frag shader color
out vec3 color;
//outputs texture coords to frag shader
out vec2 texCoord;

//controls scale of vertices
uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
// Outputs the positions/coordinates of all vertices
gl_Position = proj * view * model * vec4(aPos, 1.0);
//assigns the colors from the Vertex Data to "color"
color = aColor;
//assigns the texture coordinates from the Vertex Data to "texCoord"
texCoord = aTex;

}