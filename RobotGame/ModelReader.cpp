#include "stdafx.h"
#include "ModelReader.h"

//#include <glm/gtc/matrix_transform.hpp>

ModelReader::ModelReader(string filename)
{
	ReadModelObjData(filename);

	//expand the data suitable for lDrawArrays()
	CreateExpandedVertices();
	CreateExpandedNormals();
	CreateExpandedTextureCoordinates();
}

ModelReader::~ModelReader(void)
{
}

void ModelReader::ReadModelObjData(string filename)
{
	std::fstream modelfile(filename, std::ios_base::in);

	if(!modelfile.is_open())
	{
		std::cerr << "File " << filename << " not found.";
		//DebugBreak();
		throw std::invalid_argument( "File not found" );
		return;	//ERROR!!!
	}

	string line;
	string token = "";
	while (getline(modelfile, line))
	{
		istringstream iss(line);

		// process the line
		token = "";

		iss >> token; // read to first whitespace
	
		if (token == "#")
		{
			// ignore rest of line
			// iss >> s;
		}
		else if (token == "g")
		{
			// read the model name
			iss >> _modelName;
			// ignore rest of line
		}
		else if (token == "v")
		{
			ProcessVertexLine(iss);
		}
		else if (token == "vn")
		{
			ProcessVertexNormalLine(iss);
		}
		else if (token == "vt")
		{
			ProcessVertexTextureLine(iss);
		}
		else if (token == "f")
		{
			ProcessFaceLine(iss);
		}
		else
		{
			// ignore any line without these qualifiers
			// ignore rest of line
		}
	}
	modelfile.close();

}

void ModelReader::ProcessVertexLine(istringstream& iss)
{

	//store 3 floats in m_vertices vector
	float value;
	while (iss >> value)
	{	
		_vertices.push_back(value);
	}
}

void ModelReader::ProcessVertexNormalLine(istringstream& iss)
{
	//store 3 floats in m_vertexNormals vector
	float value;
	while (iss >> value)
	{	
		_vertexNormals.push_back(value);
		//std::cout << m_vertexNormals.back() << std::endl;
	}
}

void ModelReader::ProcessVertexTextureLine(istringstream& iss)
{
	//store 2 floats in m_vertexTextureCoordinates vector
	float value;
	while (iss >> value)
	{	
		_vertexTextureCoordinates.push_back(value);
	}
}


void ModelReader::ProcessFaceLine(istringstream& iss)
{
	static const int forwardSlash = 0x2F;

	float value;
	while (iss >> value)
	{

		value = abs(value);
		value--;
		_faceVertexIndices.push_back(value);	//process vertex indices
		int lookAhead = iss.peek();
		if (lookAhead == forwardSlash)
		{
			iss.get();
			lookAhead = iss.peek();
			if (lookAhead == forwardSlash)
			{
				iss.get();
				iss >> value;
				value = abs(value);
				value--;
				_faceNormalIndices.push_back(value);	//process normal indices if no textures
			}

			else
			{
				iss >> value;
				value = abs(value);
				value--;
				_faceTextureIndices.push_back(value);	//proces texture indices
				lookAhead = iss.peek();
				if (lookAhead == forwardSlash)
				{
					iss.get();
					iss >> value;
					value = abs(value);
					value--;
					_faceNormalIndices.push_back(value);	//process normal indices after textures

				}
			}

		}


	}

}


void ModelReader::CreateExpandedVertices()
{
	for (std::vector<unsigned int>::iterator it = _faceVertexIndices.begin() ; it != _faceVertexIndices.end(); ++it)
	{
		int vertexNumber = (*it) * 3;
		// 3 floats per triangular face
		for (int i = 0; i < 3; i++)
		{
		_vertexTriplets.push_back(_vertices.at(vertexNumber + i));
		}
		//index and copy 3 floats to the m_vertexTriplets vector

	}

}
void ModelReader::CreateExpandedNormals()
{
	// create a list of normal triplets for each face (with duplicates)

	for (std::vector<unsigned int>::iterator it = _faceNormalIndices.begin() ; it != _faceNormalIndices.end(); ++it)
	{
		int vertexNormalNumber = (*it) * 3;

		for (int i = 0; i < 3; i++)
		{
			_vertexNormalTriplets.push_back(_vertexNormals.at(vertexNormalNumber + i));
			//std::cout << m_vertexNormalTriplets.back() << std::endl;

		}
		//index and copy 3 floats to the m_vertexTriplets vector

	}

}
void ModelReader::CreateExpandedTextureCoordinates()
{

	// index and copy 2 floats to the m_vertexTexturePairs vector
	for (std::vector<unsigned int>::iterator it = _faceTextureIndices.begin() ; it != _faceTextureIndices.end(); ++it)
	{
		int vertexTextureNumber = (*it) * 2;

		for (int i = 0; i < 2; i++)
		{
			_vertexTexturePairs.push_back(_vertexTextureCoordinates.at(vertexTextureNumber + i));
		}

	}

}


// Get methods gove access to the vector data

vector<float>& ModelReader::GetVertices()
{
	return _vertexTriplets;
}
vector<float>& ModelReader::GetNormals()
{
	return _vertexNormalTriplets;
}
vector<float>& ModelReader::GetTextureCoordinates()
{
	return _vertexTexturePairs;
}

void ModelReader::VBOobject()
{

	unsigned int handle[2];
	gl::GenBuffers(2, handle);

	gl::GenVertexArrays(1, &_vaoHandle);
	gl::BindVertexArray(_vaoHandle);

	gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
	gl::BufferData(gl::ARRAY_BUFFER, _vertexTriplets.size() * sizeof(float), _vertexTriplets.data(), gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(0);  // Vertex position

	gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
	//gl::BufferData(gl::ARRAY_BUFFER, m_vertexNormalTriplets.size() * sizeof(float), m_vertexNormalTriplets.data(), gl::STATIC_DRAW);
	gl::BufferData(gl::ARRAY_BUFFER, _vertexNormalTriplets.size() * sizeof(float), _vertexNormalTriplets.data(), gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(1);  // Vertex normal

	////for (auto it = m_vertexNormalTriplets.begin(); it != m_vertexNormalTriplets.end(); it++) {
	////	std::cout << *it << std::endl;
	////}

	//gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
	//gl::BufferData(gl::ARRAY_BUFFER, m_vertexTexturePairs.size() * sizeof(float), m_vertexTexturePairs.data(), gl::STATIC_DRAW);
	//gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	//gl::EnableVertexAttribArray(2);  // Texture coords

	//gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, handle[3]);
	//gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, m_faceVertexIndices.size() * sizeof(unsigned int), m_faceVertexIndices.data(), gl::STATIC_DRAW);

	//gl::BindVertexArray(0);

}

void ModelReader::render() const
{
	gl::BindVertexArray(_vaoHandle);
	//gl::DrawElements(gl::TRIANGLES, m_faceVertexIndices.size(), gl::UNSIGNED_INT, ((GLubyte *)NULL + (0)));
	gl::DrawArrays(gl::TRIANGLES, 0, _vertexTriplets.size() / 3);
}
