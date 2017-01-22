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

void Drawable::VBOobject()
{

	unsigned int handle[2];
	gl::GenBuffers(2, handle);

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


}

void Drawable::render() const
{
	gl::BindVertexArray(_vaoHandle);
	//gl::DrawElements(gl::TRIANGLES, m_faceVertexIndices.size(), gl::UNSIGNED_INT, ((GLubyte *)NULL + (0)));
	gl::DrawArrays(gl::TRIANGLES, 0, _vertices.size() / 3);
}