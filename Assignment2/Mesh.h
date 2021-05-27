#ifndef _MESH_CLASS
#define _MESH_CLASS

#include "supportClass.h"

#define PI			3.1415926
#define	COLORNUM		14
#define D2R PI / 180.0f



class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	Vector3 norm;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	// Use for translate, scale, rotate function
	float		slideX, slideY, slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;

	int		numVerts;
	Point3*		pt;	
	int		numFaces;
	Face*		face;
public:
	Mesh() : scaleX(1), scaleY(1), scaleZ(1),
		rotateX(0), rotateY(0), rotateZ(0),
		slideX(0), slideY(0), slideZ(0)
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void Draw();

	void GenerateNormVector()
	{
		float	mx, my, mz;
		int		idx, next;

		for (int f = 0; f < numFaces; f++)
		{
			mx = 0;
			my = 0;
			mz = 0;
			for (int v = 0; v < face[f].nVerts; v++)
			{
				idx = v;
				next = (idx + 1) % face[f].nVerts;

				int		p1 = face[f].vert[idx].vertIndex;
				int		p2 = face[f].vert[next].vertIndex;

				mx = mx + (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
				my = my + (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
				mz = mz + (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);

			}
			face[f].norm.set(mx, my, mz);
			face[f].norm.normalize();
		}
	}

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCuboid(float fxsize, float fysize, float fzsize);
	void CreateCylinderWithHole(int nSegment, float fHeight, float fRadius, float hRadius);
	void CreateS1(int nSegment, float height, float width, float supThickness, float fRadius, float hRadius);
	
	void CreateS2(float fxsize, float fysize, float fzsize, int nSegment);
	void CreateS3(float fxsize, float fysize, float fzsize, float hfxsize, float, int nSegment);
	void CreateS4(float fx, float outerh, float fz, float innerh, float innerw);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
};

#endif