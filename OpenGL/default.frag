#version 330 core

//outputs colors in RGBA
out vec4 FragColor;


//inputs the color from the vertex shader
in vec3 color;
//imports texture coordinates from vertex shader
in vec2 texCoord;
//gets the texture unit from main
uniform sampler2D tex0;

//imports the normal from vertex shader
in vec3 Normal;
//imports the current position from the vertex shader
in vec3 crntPos;

//gets the color of the light
uniform vec4 lightColor;
//gets the position of the light
uniform vec3 lightPos;

//gets the position of the camera
uniform vec3 camPos;

void main()
{
//ambient lighting
	float ambient = 0.20f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	//final color output
   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}