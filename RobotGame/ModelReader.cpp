#include "stdafx.h"
#include "ModelReader.h"

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


// return model data

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
