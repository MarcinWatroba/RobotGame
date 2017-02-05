#ifndef MODELREADER_H
#define MODELREADER_H


#include "stdafx.h"
#include "drawable.h"

using namespace std;

class ModelReader : public Drawable
{
	private:
		
		// need to know ascii for forward slash
		static const int forwardSlash = 0x2F;

		// this is the data read from the OBJ file....
		vector<float> _vertices;					// v
		vector<float> _vertexNormals;				// vn
		vector<float> _vertexTextureCoordinates;	// vt only U V

		// f   v/vt/vn  (vt and vn optional)
		vector<unsigned int> _faceVertexIndices;
		vector<unsigned int> _faceTextureIndices;
		vector<unsigned int> _faceNormalIndices;   

		string _modelName;

		 
		vector<float> _vertexTriplets;	
		vector<float> _vertexNormalTriplets; 
		vector<float> _vertexTexturePairs;

	public:
		ModelReader(string filename);
		~ModelReader(void);

		//read model data from the obj file
		void ModelReader::ReadModelObjData(string filename);

		//process data from the file
		void ProcessVertexLine(istringstream& iss);
		void ProcessVertexNormalLine(istringstream& iss);
		void ProcessVertexTextureLine(istringstream& iss);
		void ProcessFaceLine(istringstream& iss);

		//create vectors to be used by buffers
		void CreateExpandedVertices();
		void CreateExpandedNormals();
		void CreateExpandedTextureCoordinates();
		
		//getters
		vector<float>& GetVertices();
		vector<float>& GetNormals();
		vector<float>& GetTextureCoordinates();

};

#endif