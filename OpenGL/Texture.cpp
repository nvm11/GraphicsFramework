#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	//assigns the type of the texture ot the texture object
	type = texType;

	//stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	//flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	//reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	//generates an OpenGL Texture object
	glGenTextures(1, &ID);
	//assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	//configures the type of algorithm that is used to make the image smaller/bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//configures the way texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//extra lines in case you choose to use GL_CLAMP_TO_BORDER
	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//assigns the image to Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	//generates MipMaps (smaller versions of textures)
	glGenerateMipmap(texType);

	//deletes the image data as it is already in Texture object
	stbi_image_free(bytes);

	//unbinds the OpenGL Texture obj so it can't be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	//gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//shader needs to be activated before changing value of uniform
	shader.Activate();
	//sets the value of uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}