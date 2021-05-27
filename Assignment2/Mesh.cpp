#include "Mesh.h"
#include <math.h>
float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };


void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	Mesh* myMesh = this;

	int i;

	myMesh->numVerts = 8;

	float realX, realY, realZ;
	realX = fSizeX / 2;
	realY = fSizeY / 2;
	realZ = fSizeZ / 2;

	myMesh->pt = new Point3[myMesh->numVerts];
	myMesh->pt[0].set(-realX, realY, realZ);
	myMesh->pt[1].set(realX, realY, realZ);
	myMesh->pt[2].set(realX, realY, -realZ);
	myMesh->pt[3].set(-realX, realY, -realZ);
	myMesh->pt[4].set(-realX, -realY, realZ);
	myMesh->pt[5].set(realX, -realY, realZ);
	myMesh->pt[6].set(realX, -realY, -realZ);
	myMesh->pt[7].set(-realX, -realY, -realZ);


	myMesh->numFaces = 6;
	myMesh->face = new Face[myMesh->numFaces];

	//Left face
	myMesh->face[0].nVerts = 4;
	myMesh->face[0].vert = new VertexID[myMesh->face[0].nVerts];
	myMesh->face[0].vert[0].vertIndex = 1;
	myMesh->face[0].vert[1].vertIndex = 5;
	myMesh->face[0].vert[2].vertIndex = 6;
	myMesh->face[0].vert[3].vertIndex = 2;
	for (i = 0; i < myMesh->face[0].nVerts; i++)
		myMesh->face[0].vert[i].colorIndex = 0;

	//Right face
	myMesh->face[1].nVerts = 4;
	myMesh->face[1].vert = new VertexID[myMesh->face[1].nVerts];
	myMesh->face[1].vert[0].vertIndex = 0;
	myMesh->face[1].vert[1].vertIndex = 3;
	myMesh->face[1].vert[2].vertIndex = 7;
	myMesh->face[1].vert[3].vertIndex = 4;
	for (i = 0; i < myMesh->face[1].nVerts; i++)
		myMesh->face[1].vert[i].colorIndex = 1;

	//top face
	myMesh->face[2].nVerts = 4;
	myMesh->face[2].vert = new VertexID[myMesh->face[2].nVerts];
	myMesh->face[2].vert[0].vertIndex = 0;
	myMesh->face[2].vert[1].vertIndex = 1;
	myMesh->face[2].vert[2].vertIndex = 2;
	myMesh->face[2].vert[3].vertIndex = 3;
	for (i = 0; i < myMesh->face[2].nVerts; i++)
		myMesh->face[2].vert[i].colorIndex = 2;

	//bottom face
	myMesh->face[3].nVerts = 4;
	myMesh->face[3].vert = new VertexID[myMesh->face[3].nVerts];
	myMesh->face[3].vert[0].vertIndex = 7;
	myMesh->face[3].vert[1].vertIndex = 6;
	myMesh->face[3].vert[2].vertIndex = 5;
	myMesh->face[3].vert[3].vertIndex = 4;
	for (i = 0; i < myMesh->face[3].nVerts; i++)
		myMesh->face[3].vert[i].colorIndex = 3;

	//near face
	myMesh->face[4].nVerts = 4;
	myMesh->face[4].vert = new VertexID[myMesh->face[4].nVerts];
	myMesh->face[4].vert[0].vertIndex = 4;
	myMesh->face[4].vert[1].vertIndex = 5;
	myMesh->face[4].vert[2].vertIndex = 1;
	myMesh->face[4].vert[3].vertIndex = 0;
	for (i = 0; i < myMesh->face[4].nVerts; i++)
		myMesh->face[4].vert[i].colorIndex = 4;

	//Far face
	myMesh->face[5].nVerts = 4;
	myMesh->face[5].vert = new VertexID[myMesh->face[5].nVerts];
	myMesh->face[5].vert[0].vertIndex = 3;
	myMesh->face[5].vert[1].vertIndex = 2;
	myMesh->face[5].vert[2].vertIndex = 6;
	myMesh->face[5].vert[3].vertIndex = 7;
	for (i = 0; i < myMesh->face[5].nVerts; i++)
		myMesh->face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateCylinderWithHole(int nSegment, float fHeight, float fRadius, float hRadius)
{
	Mesh* myMesh = this;

	myMesh->numVerts = nSegment * 4 + 4;
	myMesh->pt = new Point3[myMesh->numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	for (i = 0; i < nSegment; i++)
	{
		// outer top
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		myMesh->pt[i].set(x, y, z);
		//outer bottom
		y = -fHeight / 2;
		myMesh->pt[i + nSegment].set(x, y, z);


		// inner top
		x = hRadius * cos(fAngle * i);
		z = hRadius * sin(fAngle * i);
		y = fHeight / 2;
		myMesh->pt[i + 2 * nSegment].set(x, y, z);
		// inner bottom
		y = -fHeight / 2;
		myMesh->pt[i + 3 * nSegment].set(x, y, z);
	}

	myMesh->numFaces = nSegment * 4;
	myMesh->face = new Face[myMesh->numFaces];

	idx = 0;
	// Top surface
	for (i = 0; i < nSegment; i++)
	{
		myMesh->face[idx].nVerts = 4;
		myMesh->face[idx].vert = new VertexID[myMesh->face[idx].nVerts];

		if (i < nSegment - 1)
		{
			myMesh->face[idx].vert[0].vertIndex = i;
			myMesh->face[idx].vert[3].vertIndex = i + nSegment * 2;
			myMesh->face[idx].vert[1].vertIndex = i + 1;
			myMesh->face[idx].vert[2].vertIndex = i + 1 + nSegment * 2;
		}
		else
		{
			myMesh->face[idx].vert[0].vertIndex = i;
			myMesh->face[idx].vert[3].vertIndex = i + nSegment * 2;
			myMesh->face[idx].vert[1].vertIndex = 0;
			myMesh->face[idx].vert[2].vertIndex = nSegment * 2;
		}

		idx++;
	}

	// Around outer surface
	for (i = 0; i < nSegment; i++)
	{
		myMesh->face[idx].nVerts = 4;
		myMesh->face[idx].vert = new VertexID[myMesh->face[idx].nVerts];

		myMesh->face[idx].vert[0].vertIndex = i;
		if (i < nSegment - 1)
			myMesh->face[idx].vert[1].vertIndex = i + 1;
		else
			myMesh->face[idx].vert[1].vertIndex = 0;
		myMesh->face[idx].vert[2].vertIndex = myMesh->face[idx].vert[1].vertIndex + nSegment;
		myMesh->face[idx].vert[3].vertIndex = myMesh->face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	// Around inner surface
	for (i = 2 * nSegment; i < 3 * nSegment; i++)
	{
		myMesh->face[idx].nVerts = 4;
		myMesh->face[idx].vert = new VertexID[myMesh->face[idx].nVerts];

		myMesh->face[idx].vert[0].vertIndex = i;
		if (i < 3 * nSegment - 1)
			myMesh->face[idx].vert[1].vertIndex = i + 1;
		else
			myMesh->face[idx].vert[1].vertIndex = 2 * nSegment;
		myMesh->face[idx].vert[2].vertIndex = myMesh->face[idx].vert[1].vertIndex + nSegment;
		myMesh->face[idx].vert[3].vertIndex = myMesh->face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}


	// Bottom face
	for (i = 0; i < nSegment; i++)
	{
		myMesh->face[idx].nVerts = 4;
		myMesh->face[idx].vert = new VertexID[myMesh->face[idx].nVerts];

		if (i < nSegment - 1)
		{
			myMesh->face[idx].vert[0].vertIndex = i + nSegment;
			myMesh->face[idx].vert[3].vertIndex = i + nSegment * 3;
			myMesh->face[idx].vert[1].vertIndex = i + 1 + nSegment;
			myMesh->face[idx].vert[2].vertIndex = i + 1 + nSegment * 3;
		}
		else
		{
			myMesh->face[idx].vert[0].vertIndex = i + nSegment;
			myMesh->face[idx].vert[3].vertIndex = i + nSegment * 3;
			myMesh->face[idx].vert[1].vertIndex = nSegment;
			myMesh->face[idx].vert[2].vertIndex = nSegment * 3;
		}
		idx++;
	}
}


void Mesh::CreateS1(int nSegment, float height, float width, float thickness, float fRadius, float hRadius) {
	numVerts = (nSegment * 2 + 6) * 2;
	int halftVerts = numVerts / 2;
	pt = new Point3[numVerts];
	float radius_inside = (1 / (float)3) * (width / (float)2);
	float radius_outside = (2 / (float)3) * (width / (float)2);
	int index = 0;
	float x, y, z;

	// caculate points
	int centerPosition = height - radius_outside;
	float angle = 0;
	float alpha = 360 / (float)nSegment;

	for (int i = 0; i < nSegment; i++)
	{
		x = radius_inside * cos(D2R * angle);
		y = radius_inside * sin(D2R * angle) + centerPosition;
		z = thickness;
		pt[index].set(x, y, z);
		z = -z;
		pt[index + halftVerts].set(x, y, z);
		angle += alpha;
		index++;
	}

	angle = 0;
	alpha = 180 / (float)(nSegment / 2);
	for (int i = 0; i < nSegment / 2; i++)
	{
		x = radius_outside * cos(D2R * angle);
		y = radius_outside * sin(D2R * angle) + centerPosition;
		z = thickness;
		pt[index].set(x, y, z);
		z = -z;
		pt[index + halftVerts].set(x, y, z);
		angle += alpha;
		index++;
	}

	for (int i = 0; i < nSegment - nSegment / 2; i++)
	{
		x = pt[index - nSegment].x;
		y = thickness;
		z = thickness;
		pt[index].set(x, y, z);
		z = -z;
		pt[index + halftVerts].set(x, y, z);
		index++;
	}

	// bottom Support
	pt[index].set(width / (float)2, thickness, thickness);
	pt[index + halftVerts].set(width / (float)2, thickness, -thickness);
	index++;

	pt[index].set(-width / (float)2, thickness, thickness);
	pt[index + halftVerts].set(-width / (float)2, thickness, -thickness);
	index++;

	pt[index].set(-width / (float)2, 0, thickness);
	pt[index + halftVerts].set(-width / (float)2, 0, -thickness);
	index++;

	pt[index].set(width / (float)2, 0, thickness);
	pt[index + halftVerts].set(width / (float)2, 0, -thickness);
	index++;

	int remaining = index;
	pt[remaining].set(pt[nSegment].x, thickness, thickness);
	pt[remaining + halftVerts].set(pt[nSegment].x, thickness, -thickness);

	pt[remaining + 1].set(-pt[nSegment].x, thickness, thickness);
	pt[remaining + halftVerts + 1].set(-pt[nSegment].x, thickness, -thickness);

	// set faces

	numFaces = (nSegment * 4) + 6 - nSegment / 2 + 1;
	face = new Face[numFaces];
	int idx = 0;
	for (int i = 0; i < nSegment - 1; i++)
	{
		if (i != nSegment / 2 - 1) {

			// right face cyliner
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[4];
			face[idx].vert[3].vertIndex = i;
			face[idx].vert[2].vertIndex = i + 1;
			face[idx].vert[1].vertIndex = i + nSegment + 1;
			face[idx].vert[0].vertIndex = i + nSegment;
			idx++;

			// left face cylinder
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[4];
			face[idx].vert[0].vertIndex = i + halftVerts;
			face[idx].vert[1].vertIndex = i + 1 + halftVerts;
			face[idx].vert[2].vertIndex = i + nSegment + halftVerts + 1;
			face[idx].vert[3].vertIndex = i + nSegment + halftVerts;
			idx++;

			// inner cylinder
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[4];
			face[idx].vert[0].vertIndex = i;
			face[idx].vert[1].vertIndex = i + 1;
			face[idx].vert[2].vertIndex = i + halftVerts + 1;
			face[idx].vert[3].vertIndex = i + halftVerts;
			idx++;

			if (i < nSegment / 2) {
				// outer cylinder
				face[idx].nVerts = 4;
				face[idx].vert = new VertexID[4];
				face[idx].vert[3].vertIndex = i + nSegment;
				face[idx].vert[2].vertIndex = i + 1 + nSegment;
				face[idx].vert[1].vertIndex = i + nSegment + halftVerts + 1;
				face[idx].vert[0].vertIndex = i + nSegment + halftVerts;
				idx++;
			}
		}
	}

	int tmp = nSegment / 2 - 1;
	face[idx].nVerts = 5;
	face[idx].vert = new VertexID[5];
	face[idx].vert[4].vertIndex = tmp;
	face[idx].vert[3].vertIndex = tmp + 1;
	face[idx].vert[2].vertIndex = tmp + nSegment + 1;
	face[idx].vert[1].vertIndex = remaining + 1;
	face[idx].vert[0].vertIndex = tmp + nSegment;
	idx++;

	face[idx].nVerts = 5;
	face[idx].vert = new VertexID[5];
	face[idx].vert[0].vertIndex = tmp + halftVerts;
	face[idx].vert[1].vertIndex = tmp + 1 + halftVerts;
	face[idx].vert[2].vertIndex = tmp + nSegment + halftVerts + 1;
	face[idx].vert[3].vertIndex = remaining + 1 + halftVerts;
	face[idx].vert[4].vertIndex = tmp + nSegment + halftVerts;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[0].vertIndex = tmp;
	face[idx].vert[1].vertIndex = tmp + 1;
	face[idx].vert[2].vertIndex = tmp + halftVerts + 1;
	face[idx].vert[3].vertIndex = tmp + halftVerts;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[0].vertIndex = tmp + nSegment;
	face[idx].vert[1].vertIndex = remaining + 1;
	face[idx].vert[2].vertIndex = remaining + halftVerts + 1;
	face[idx].vert[3].vertIndex = tmp + nSegment + halftVerts;
	idx++;

	//==================
	tmp = nSegment - 1;
	face[idx].nVerts = 5;
	face[idx].vert = new VertexID[5];
	face[idx].vert[4].vertIndex = tmp;
	face[idx].vert[3].vertIndex = 0;
	face[idx].vert[2].vertIndex = nSegment;
	face[idx].vert[1].vertIndex = remaining;
	face[idx].vert[0].vertIndex = tmp + nSegment;
	idx++;

	face[idx].nVerts = 5;
	face[idx].vert = new VertexID[5];
	face[idx].vert[0].vertIndex = tmp + halftVerts;
	face[idx].vert[1].vertIndex = halftVerts;
	face[idx].vert[2].vertIndex = nSegment + halftVerts;
	face[idx].vert[3].vertIndex = remaining + halftVerts;
	face[idx].vert[4].vertIndex = tmp + nSegment + halftVerts;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[0].vertIndex = tmp;
	face[idx].vert[1].vertIndex = 0;
	face[idx].vert[2].vertIndex = halftVerts;
	face[idx].vert[3].vertIndex = tmp + halftVerts;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[0].vertIndex = nSegment;
	face[idx].vert[1].vertIndex = remaining;
	face[idx].vert[2].vertIndex = remaining + halftVerts;
	face[idx].vert[3].vertIndex = nSegment + halftVerts;
	idx++;

	tmp = remaining - 4;

	for (int i = 0; i < 3; i++)
	{
		// top support stand
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[4];
		face[idx].vert[3].vertIndex = tmp;
		face[idx].vert[2].vertIndex = tmp + 1;
		face[idx].vert[1].vertIndex = tmp + halftVerts + 1;
		face[idx].vert[0].vertIndex = tmp + halftVerts;
		idx++;
		tmp++;
	}
	// support stand far
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[3].vertIndex = tmp;
	face[idx].vert[2].vertIndex = remaining - 4;
	face[idx].vert[1].vertIndex = remaining - 4 + halftVerts;
	face[idx].vert[0].vertIndex = tmp + halftVerts;
	idx++;

	tmp = remaining - 4;
	//support stand right
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[0].vertIndex = tmp;
	face[idx].vert[1].vertIndex = tmp + 1;
	face[idx].vert[2].vertIndex = tmp + 2;
	face[idx].vert[3].vertIndex = tmp + 3;
	idx++;

	// support stand left
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[4];
	face[idx].vert[3].vertIndex = tmp + halftVerts;
	face[idx].vert[2].vertIndex = tmp + 1 + halftVerts;
	face[idx].vert[1].vertIndex = tmp + 2 + halftVerts;
	face[idx].vert[0].vertIndex = tmp + 3 + halftVerts;
	idx++;
}

void Mesh::CreateS2(float fSizeX, float fSizeY, float fSizeZ, int nSegment = 2)
{
	float fx = fSizeX / 2, fy = fSizeY /2 , fz = fSizeZ / 2;
	float radius = fz;
	// cube first
	numVerts = (1 + nSegment) * 4;
	pt = new Point3[numVerts];

	float end1 = fx - radius;
	int oppos = 1 + nSegment;
	int down = oppos*2;
	
	pt[0					].set(-end1, fy, fz);
	pt[1					].set(end1, fy, fz);
	

	pt[0 +				down].set(-end1, -fy, fz);
	pt[1 +				down].set(end1, -fy, fz);

	pt[0 + oppos			].set(end1, fy, -fz);
	pt[1 + oppos			].set(-end1, fy, -fz);

	pt[0 + oppos + down].set(end1, -fy, -fz);
	pt[1 + oppos + down].set(-end1, -fy, -fz);

	// two head
	float pAngle = D2R * 180 / nSegment;
	for (size_t i = 2; i < nSegment+1; i++)
	{	
		float tAngle = (i - 1) * pAngle;
		pt[i].set((end1 + radius * sin(tAngle)), fy, radius * cos(tAngle));
		pt[i + oppos].set(-pt[i].x, fy, -pt[i].z);
		
		pt[i + down].set(pt[i].x, -fy, pt[i].z);
		pt[i + oppos + down].set(-pt[i].x, -fy, -pt[i].z);
	}

	numFaces = 2 + 2 + nSegment * 2;
	face = new Face[numFaces];

	// Face top and bot	
	face[0].nVerts = (1 + nSegment) * 2;
	face[0].vert = new VertexID[face[0].nVerts];
	face[1].nVerts = (1 + nSegment) * 2;
	face[1].vert = new VertexID[face[1].nVerts];

	for (size_t i = 0; i < (1+nSegment)*2; i++)
	{
		face[0].vert[i].vertIndex = i;
		face[1].vert[i].vertIndex = i + down;
	}


	int idx = 2;
	// Around face
	for (size_t i = 0; i < (1 + nSegment) * 2; i++)
	{
		if (i == 2*nSegment+1)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = i;
			face[idx].vert[1].vertIndex = i + down;
			face[idx].vert[2].vertIndex = 0 + down;
			face[idx].vert[3].vertIndex = 0 ;
			idx++;
			continue;
		}

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + down;
		face[idx].vert[2].vertIndex = i + 1 + down;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;
	}
}

void Mesh::CreateS3(float fSizeX, float fSizeY, float fSizeZ, float hfSizeX, float hfSizeZ, int nSegment)
{
	float fx = fSizeX / 2, fy = fSizeY / 2, fz = fSizeZ / 2;
	float hfx = hfSizeX / 2, hfz = hfSizeZ / 2;
	float radius = fz;
	// cube first
	this->numVerts = (1 + nSegment) * 4 + 16;
	pt = new Point3[numVerts];
	int hole = numVerts - 8;
	Point3* hpt = pt + hole;

	float end1 = fx - radius;
	int oppos = 1 + nSegment + 2;
	int down = oppos * 2;
	
	pt[0].set(-end1, fy, fz);
	pt[0 + oppos].set(end1, fy, -fz);
	pt[0 + down].set(-end1, -fy, fz);
	pt[0 + oppos + down].set(end1, -fy, -fz);

	pt[1].set(-hfx, fy, fz);
	pt[1 + oppos].set(hfx, fy, -fz);
	pt[1 + down].set(-hfx, -fy, fz);
	pt[1 + down + oppos].set(hfx, -fy, -fz);

	pt[2].set(hfx, fy, fz);
	pt[2 + oppos].set(-hfx, fy, -fz);
	pt[2 + down].set(hfx, -fy, fz);
	pt[2 + down + oppos].set(-hfx, -fy, -fz);

	pt[3].set(end1, fy, fz);
	pt[3 + oppos].set(-end1, fy, -fz);
	pt[3 + down].set(end1, -fy, fz);
	pt[3 + oppos + down].set(-end1, -fy, -fz);

	// hole
	hpt[0].set(-hfx, fy, hfz);
	hpt[1].set(hfx, fy, hfz);
	hpt[2].set(hfx, fy, -hfz);
	hpt[3].set(-hfx, fy, -hfz);

	hpt[4].set(-hfx, -fy, hfz);
	hpt[5].set(hfx, -fy, hfz);
	hpt[6].set(hfx, -fy, -hfz);
	hpt[7].set(-hfx, -fy, -hfz);


	// two head
	float pAngle = D2R * 180 / nSegment;
	for (size_t i = 4; i < 2+nSegment + 1; i++)
	{
		float tAngle = (i - 3) * pAngle;
		pt[i].set((end1 + radius * sin(tAngle)), fy, radius * cos(tAngle));
		pt[i + oppos].set(-pt[i].x, fy, -pt[i].z);
		pt[i + down].set(pt[i].x, -fy, pt[i].z);
		pt[i + oppos + down].set(-pt[i].x, -fy, -pt[i].z);
	}

	numFaces = 8 + 2 + 6+2*nSegment;
	face = new Face[numFaces];
	face[0].nVerts = nSegment + 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[1].nVerts = nSegment + 3;
	face[1].vert = new VertexID[face[1].nVerts];

	for (size_t i = 0; i < nSegment + 1; i++)
	{
		face[0].vert[i].vertIndex = 2 + oppos + i;
		face[1].vert[i].vertIndex = face[0].vert[i].vertIndex - oppos;
	}

	face[0].vert[nSegment + 1].vertIndex = 0;
	face[1].vert[nSegment + 1].vertIndex = 0 + oppos;
	face[0].vert[nSegment + 2].vertIndex = 1;
	face[1].vert[nSegment + 2].vertIndex = 1 + oppos;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];

	face[2].vert[0].vertIndex = 1;
	face[3].vert[0].vertIndex = 1 + oppos;
	face[2].vert[1].vertIndex = 2;
	face[3].vert[1].vertIndex = 2 + oppos;
	face[2].vert[2].vertIndex = hole + 1;
	face[3].vert[2].vertIndex = hole + 3;
	face[2].vert[3].vertIndex = hole;
	face[3].vert[3].vertIndex = hole + 2;


	// bot

	face[4].nVerts = nSegment + 3;
	face[4].vert = new VertexID[face[4].nVerts];
	face[5].nVerts = nSegment + 3;
	face[5].vert = new VertexID[face[5].nVerts];

	for (size_t i = 0; i < nSegment + 1; i++)
	{
		face[4].vert[i].vertIndex = face[0].vert[i].vertIndex + down ;
		face[5].vert[i].vertIndex = face[4].vert[i].vertIndex - oppos;
	}

	face[4].vert[nSegment + 1].vertIndex = 0 + down;
	face[5].vert[nSegment + 1].vertIndex = 0 + oppos + down;
	face[4].vert[nSegment + 2].vertIndex = 1 + down ;
	face[5].vert[nSegment + 2].vertIndex = 1 + oppos + down;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];

	face[6].vert[0].vertIndex = 1 + down;
	face[7].vert[0].vertIndex = 1 + oppos + down;
	face[6].vert[1].vertIndex = 2 + down;
	face[7].vert[1].vertIndex = 2 + oppos + down;

	face[6].vert[2].vertIndex = hole + 1 + 4;
	face[7].vert[2].vertIndex = hole + 3 + 4;
	face[6].vert[3].vertIndex = hole + 4;
	face[7].vert[3].vertIndex = hole + 2 + 4;


	int idx = 8;
	// Around face
	// near
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 0 + down;
	face[idx].vert[2].vertIndex = 3 + down;
	face[idx].vert[3].vertIndex = 3;
	idx++;

	//  inner near
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = hole + 0;
	face[idx].vert[2].vertIndex = hole + 4;
	face[idx].vert[1].vertIndex = hole + 5;
	face[idx].vert[0].vertIndex = hole + 1;
	idx++;
	// inner left
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = hole + 5;
	face[idx].vert[1].vertIndex = hole + 6;
	face[idx].vert[2].vertIndex = hole + 2;
	face[idx].vert[3].vertIndex = hole + 1;
	idx++;
	// inner far

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = hole + 2;
	face[idx].vert[1].vertIndex = hole + 3;
	face[idx].vert[2].vertIndex = hole + 7;
	face[idx].vert[3].vertIndex = hole + 6;
	idx++;
	// inner right

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = hole + 3;
	face[idx].vert[1].vertIndex = hole + 0;
	face[idx].vert[2].vertIndex = hole + 4;
	face[idx].vert[3].vertIndex = hole + 7;
	idx++;
	//far
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0 + oppos;
	face[idx].vert[1].vertIndex = 0 + oppos + down;
	face[idx].vert[2].vertIndex = 3 + oppos + down;
	face[idx].vert[3].vertIndex = 3 + oppos;
	idx++;
	for (size_t i = 3; i <  3+nSegment; i++)
	{
		if (i == 2+nSegment)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = i;
			face[idx].vert[1].vertIndex = i + down;
			face[idx].vert[2].vertIndex = i + 1 + down;
			face[idx].vert[3].vertIndex = i + 1;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = i + oppos;
			face[idx].vert[1].vertIndex = i + oppos + down;
			face[idx].vert[2].vertIndex = 0 + down;
			face[idx].vert[3].vertIndex = 0;
			idx++;
			continue;
		}

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i + down;
		face[idx].vert[2].vertIndex = i + 1 + down;
		face[idx].vert[3].vertIndex = i + 1;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + oppos;
		face[idx].vert[1].vertIndex = i + oppos + down;
		face[idx].vert[2].vertIndex = i + 1 + oppos + down;
		face[idx].vert[3].vertIndex = i + 1 + oppos;
		idx++;
	}
}

void Mesh::CreateS4(float fx, float outerh, float fz, float innerh, float innerw)
{
	numVerts = 16;
	pt = new Point3[numVerts];
	int oppos = 4;
	int up = 2 * oppos;

	float realOuterh = outerh / 2;
	float realInnerh = innerh / 2;

	pt[0].set(-fx, 0, fz);
	pt[1].set(-innerw, 0, fz);
	pt[2].set(innerw, 0, fz);
	pt[3].set(fx, 0, fz);

	pt[0 + oppos].set(fx, 0, -fz);
	pt[1 + oppos].set(innerw, 0, -fz);
	pt[2 + oppos].set(-innerw, 0, -fz);
	pt[3 + oppos].set(-fx, 0, -fz);
	
	pt[0 + up].set(-fx, outerh, fz);
	pt[1 + up].set(-innerw, innerh, fz);
	pt[2 + up].set(innerw, innerh, fz);
	pt[3 + up].set(fx, outerh, fz);

	pt[0 + oppos + up].set(fx, outerh, -fz);
	pt[1 + oppos + up].set(innerw, innerh, -fz);
	pt[2 + oppos + up].set(-innerw, innerh, -fz);
	pt[3 + oppos + up].set(-fx, outerh, -fz);

	numFaces = 14;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 1 + up;
	face[0].vert[3].vertIndex = 0 + up;
	
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 2;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 3 + up;
	face[1].vert[3].vertIndex = 2 + up;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0 + oppos;
	face[2].vert[1].vertIndex = 1 + oppos;
	face[2].vert[2].vertIndex = 1 + oppos + up;
	face[2].vert[3].vertIndex = 0 + oppos + up;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 2 + oppos;
	face[3].vert[1].vertIndex = 3 + oppos;
	face[3].vert[2].vertIndex = 3 + oppos + up;
	face[3].vert[3].vertIndex = 2 + oppos + up;

	// forehead face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0 + up;
	face[4].vert[1].vertIndex = 1 + up;
	face[4].vert[2].vertIndex = 2 + up;
	face[4].vert[3].vertIndex = 3 + up;

	// forehead back
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0 + up + oppos;
	face[5].vert[1].vertIndex = 1 + up + oppos;
	face[5].vert[2].vertIndex = 2 + up + oppos;
	face[5].vert[3].vertIndex = 3 + up + oppos;


	// outer top
	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 0 + up;
	face[6].vert[1].vertIndex = 3 + up;
	face[6].vert[2].vertIndex = 0 + up + oppos;
	face[6].vert[3].vertIndex = 3 + up + oppos;
	// inner top
	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 1 + up;
	face[7].vert[1].vertIndex = 2 + up;
	face[7].vert[2].vertIndex = 1 + up + oppos;
	face[7].vert[3].vertIndex = 2 + up + oppos;

	// inner left
	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 1;
	face[8].vert[1].vertIndex = 2 + oppos;
	face[8].vert[2].vertIndex = 2 + up + oppos;
	face[8].vert[3].vertIndex = 1 + up;

	// outer left
	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[3].vertIndex = 0;
	face[9].vert[2].vertIndex = 3 + oppos;
	face[9].vert[1].vertIndex = 3 + up + oppos;
	face[9].vert[0].vertIndex = 0 + up;

	// outer right
	face[10].nVerts = 4;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 3;
	face[10].vert[1].vertIndex = 0 + oppos;
	face[10].vert[2].vertIndex = 0 + up + oppos;
	face[10].vert[3].vertIndex = 3 + up;
	
	// inner right
	face[11].nVerts = 4;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[3].vertIndex = 2;
	face[11].vert[2].vertIndex = 1 + oppos;
	face[11].vert[1].vertIndex = 1 + up + oppos;
	face[11].vert[0].vertIndex = 2 + up;

	// bot right
	face[12].nVerts = 4;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 2;
	face[12].vert[1].vertIndex = 3;
	face[12].vert[2].vertIndex = 0 + oppos;
	face[12].vert[3].vertIndex = 1 + oppos;

	// bot left
	face[13].nVerts = 4;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 0;
	face[13].vert[1].vertIndex = 1;
	face[13].vert[2].vertIndex = 2 + oppos;
	face[13].vert[3].vertIndex = 3 + oppos;
}


void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].norm.x, face[f].norm.y, face[f].norm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}



