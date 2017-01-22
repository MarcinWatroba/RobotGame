#ifndef MODELREADER_H
#define MODELREADER_H


#include "stdafx.h"


using namespace std;

class ModelReader
{
	private:
		
		// need to know ascii for forward slash
		static const int forwardSlash = 0x2F;

		//
		// this is the data read from the OBJ file....
		//

		vector<float> _vertices;					// v
		vector<float> _vertexNormals;				// vn
		vector<float> _vertexTextureCoordinates;	// vt only U V

		// f   v/vt/vn  (vt and vn optional)
		// these are unsigned as opengl expected unsigned data
		vector<unsigned int> _faceVertexIndices;
		vector<unsigned int> _faceTextureIndices;
		vector<unsigned int> _faceNormalIndices;   

		string _modelName;

		// because maya output indices that don't necessarily match for
		// faces normals and textures we have two options
		// 1. rebalance the texture and normal indices to match the face indices - then draw with glDrawElements
		// 2. Create buffers with duplicated vertices, texture coordinates and normals and use glDrawArrays
		//
		// 1 is probably more efficient but 2 is perhaps a little clearer...

		// to simply test we generate a set of vertex triplets that repeat vertices
		// but which ww can simply pass to open gl in sequence to draw each triangle
		// in the model

		vector<float> _vertexTriplets;	// v
		vector<float> _vertexNormalTriplets; 
		vector<float> _vertexTexturePairs;

		unsigned int _vaoHandle;

	public:
		ModelReader(string filename);
		~ModelReader(void);

		void ModelReader::ReadModelObjData(string filename);

		void ProcessVertexLine(istringstream& iss);
		void ProcessVertexNormalLine(istringstream& iss);
		void ProcessVertexTextureLine(istringstream& iss);
		void ProcessFaceLine(istringstream& iss);
		void VBOobject();
		void render() const;

		void CreateExpandedVertices();
		void CreateExpandedNormals();
		void CreateExpandedTextureCoordinates();

		vector<float>& GetVertices();
		vector<float>& GetNormals();
		vector<float>& GetTextureCoordinates();

};

#endif