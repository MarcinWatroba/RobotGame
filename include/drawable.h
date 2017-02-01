#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <Bitmap.h>
#include "texture.h"
using namespace std;

class Drawable
{
private:

	vector<float> _vertices;
	vector<float> _normals;
	vector<float> _textures;
	unsigned int _vaoHandle;
	GLuint textureID;

public:
    Drawable();

	void setVertices(vector<float>& vertices);
	void setNormals(vector<float>& normals);
	void setTextures(vector<float>& textures);
	void VBOobject();
	void applyTexture(Texture* tex);
	GLuint getTexture();
	void render() const;
};

#endif // DRAWABLE_H
