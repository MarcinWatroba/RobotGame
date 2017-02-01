#include "stdafx.h"
#include "drawable.h"

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

	//Bitmap _bmp = bmp;
	////bmp.flipVertically();
	//gl::ActiveTexture(gl::TEXTURE0);
	//gl::GenTextures(1, &textureID);
	//Set texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, tex->object());
	//gl::TexImage2D(gl::TEXTURE_2D,
	//	0, gl::RGB,
	//	bmp.width(), bmp.height(), 0,
	//	gl::RGB, gl::UNSIGNED_BYTE,
	//	bmp.pixelBuffer());

	//gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	//gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	//gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	//gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	//gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);


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
	//gl::BufferData(gl::ARRAY_BUFFER, m_vertexNormalTriplets.size() * sizeof(float), m_vertexNormalTriplets.data(), gl::STATIC_DRAW);
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
	//gl::DrawElements(gl::TRIANGLES, m_faceVertexIndices.size(), gl::UNSIGNED_INT, ((GLubyte *)NULL + (0)));
	gl::DrawArrays(gl::TRIANGLES, 0, _vertices.size() / 3);
}