#include "stdafx.h"
#include "drawable.h"

//This class populated VBO with data and draws the objects
Drawable::Drawable()
{
}


void Drawable::setVertices(vector<float>& vertices)
{
	_vertices = vertices;
}

void Drawable::setNormals(vector<float>& normals)
{
	_normals = normals;
}

void Drawable::setTextures(vector<float>& textures)
{
	_textures = textures;
}

void Drawable::applyTexture(Texture* tex)
{
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, tex->object());
}

GLuint Drawable::getTexture()
{
	return textureID;
}

void Drawable::VBOobject()
{

	unsigned int handle[3];
	gl::GenBuffers(3, handle);

	gl::GenVertexArrays(1, &_vaoHandle);
	gl::BindVertexArray(_vaoHandle);

	gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
	gl::BufferData(gl::ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(0);  // Vertex position

	gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
	gl::BufferData(gl::ARRAY_BUFFER, _normals.size() * sizeof(float), _normals.data(), gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(1);  // Vertex normal

	gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);	//binding UV buffer
	gl::BufferData(gl::ARRAY_BUFFER, _textures.size() * sizeof(float), _textures.data(), gl::STATIC_DRAW);	//specify size, data, and drawing mode
	gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(2);

}

void Drawable::render() const
{
	gl::BindVertexArray(_vaoHandle);
	gl::DrawArrays(gl::TRIANGLES, 0, _vertices.size() / 3);
}