#version 330 core
//positions/coords
layout (location = 0) in vec3 aPos;
//colors
layout (location = 1) in vec3 aColor;
//texture coords
layout (location = 2) in vec2 aTex;
//normals
layout (location = 3) in vec3 aNormal;

//outputs color to fragment shader
out vec3 color;
//outputs texture coords to frag shader
out vec2 texCoord;

//outputs the normal to fragment shader
out vec3 Normal;
//outputs the current position of the fragment shader
out vec3 crntPos;

//imports the camera matrix from main
uniform mat4 camMatrix;
//imports the model matrix from main
uniform mat4 model;

void main()
{
//calculates the current position
	crntPos = vec3(model * vec4(aPos, 1.0f));

	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0f);

	//assigns the colors from the Vertex Data to "color"
	color = aColor;

	//assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	//assigns normal to uniform
	Normal = aNormal;
}