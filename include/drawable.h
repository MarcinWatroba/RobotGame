#ifndef DRAWABLE_H
#define DRAWABLE_H

using namespace std;

class Drawable
{
private:

	vector<float> _vertices;
	vector<float> _normals;

	unsigned int _vaoHandle;

public:
    Drawable();

	void setVertices(vector<float>& vertices);
	void setNormals(vector<float>& normals);
	void VBOobject();
	void render() const;
};

#endif // DRAWABLE_H
