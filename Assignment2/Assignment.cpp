// Bai3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int		screenWidth = 800;
int		screenHeight= 600;

bool topView = false, drawWireFrame = false, turnOn2ndLight;

// fall between 0.2 and 0.8
float	chot2pos = 0.8, chot2posmin = 0.2, chot2posmax = 0.8;
// fall between 0.4 and 0.6
float	banhxepos = 0.55;
// chot co dinh 1
float	chot1pos = 0.15;

float camera_angle = 60;
float camera_height = 10;
float camera_dis = 60;
float camera_X, camera_Y, camera_Z;
// ban quay, static
Mesh	de, giado1, giado2;
Mesh	codinh1, codinh2;
Mesh	chot1;

// Chuyen dong tai cho
Mesh	banhxe;

// thanh phan chuyen dong
Mesh	chot2, chot3, boxchot2, boxchot3;
Mesh	contruot2, contruot3;
Mesh	thanhnoi1, thanhnoi2;
Mesh	tayquay;
Mesh	thanhtru;

// My light
GLfloat	lightDiffuse0[] = { .8f, .8f, .8f, .8f };
GLfloat	lightSpecular0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat	lightAmbient0[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat light_position0[] = { 10.0f, 5.0f, 15.0f, 0.0f };

GLfloat	lightDiffuse1[] = { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat	lightSpecular1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat	lightAmbient1[] = { 0.2f, 0.2f, 0.2, 1.0f };
GLfloat light_position1[] = { -40.0f, 50.0f, 20.0f, 1.0f };
void setupLight() {
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	if (turnOn2ndLight) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	glEnable(GL_NORMALIZE);
}
void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}
void myKeyboard(unsigned char key, int x, int y)
{
	float banhxeRotateStep = 5;
	float chot2Step = 0.02;
	switch (key)
	{
	case '1':
		banhxe.rotateY += banhxeRotateStep;
		if (banhxe.rotateY > 360)
			banhxe.rotateY -= 360;
		glutPostRedisplay();
		break;
	case '2':
		banhxe.rotateY -= banhxeRotateStep;
		if (banhxe.rotateY > 360)
			banhxe.rotateY -= 360;
		glutPostRedisplay();
		break;
	case '3':
		if(chot2pos <= chot2posmax)
			chot2pos += chot2Step;
		glutPostRedisplay();
		break;
	case '4':
		if (chot2pos >= chot2posmin)
			chot2pos -= chot2Step;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		drawWireFrame = !drawWireFrame;
		glutPostRedisplay();
		break;
	case 'v':
	case 'V':
		topView = !topView;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		turnOn2ndLight = !turnOn2ndLight;
		glutPostRedisplay();
		break;
	case '+':
		camera_dis += 0.2;
		glutPostRedisplay();
		break;
	case '-':
		camera_dis -= 0.2;
		glutPostRedisplay();
		break;
	default:
		break;
	}

}

// thong so
float	deHeight = 10, deWidth = 30, deThickness = 2;
float	giado1Height = 2, giado1Width = 3, giado1Thickness = 20;
float	giado2Height = 2, giado2Width = deWidth, giado2Thickness = 10;
float	codinhHeight = 6, codinhWidth = 4 , codinhThickness = 1, codinhfRadius = 0.8, codinhhRadius = 0.4;
int		codinhnSegment = 40;
float	banhxeRad = 1.5 * giado1Width, banhxeHeight = codinhThickness;
float	thanhtruHeight = deWidth * 1.5, thanhtruRad = codinhfRadius;
float	thanhnoi2Height = 10, thanhnoi2InnerHeight = 8, thanhnoi2InnerWidth = 0.75, thanhnoi2Thickness = 0.5, thanhnoi2Width = 2;
float	chot1Height = (banhxeHeight + giado1Height + codinhHeight) / 2, chot1Radius = 0.5;
float	tayquayHeight = 1, tayquayWidth = banhxeRad, tayquayThickness = 2;
float	boxchot2Size = tayquayHeight *0.5f, boxchot2Height = boxchot2Size, chot2Height = boxchot2Height + 0.1, chot2Radius = boxchot2Size / 2;
float	thanhnoi1Height = 3, thanhnoi1Width = 18, thanhnoi1InnerHeight = boxchot2Size * 2, thanhnoi1InnerWidth = thanhnoi1Width * 0.7, thanhnoi1Thickness = 1;
float	boxchot3Size = thanhnoi2InnerWidth, chot3Height = boxchot3Size * 2 + 0.1, chot3Radius = boxchot3Size / 2;

void createMeshes()
{
	de.CreateCuboid(deWidth, deThickness, deHeight);
	de.GenerateNormVector();

	giado1.CreateCuboid(giado1Width, giado1Thickness, giado1Height);
	giado1.GenerateNormVector();

	giado2.CreateCuboid(giado2Width, giado2Thickness, giado2Height);
	giado2.GenerateNormVector();

	codinh1.CreateS1(codinhnSegment, codinhHeight, codinhWidth, codinhThickness, codinhfRadius, codinhhRadius);
	codinh1.GenerateNormVector();

	codinh2.CreateS1(codinhnSegment, codinhHeight, codinhWidth, codinhThickness, codinhfRadius, codinhhRadius);
	codinh2.GenerateNormVector();

	banhxe.CreateCylinder(40, banhxeHeight, banhxeRad);
	banhxe.GenerateNormVector();

	thanhtru.CreateCylinder(40, thanhtruHeight, thanhtruRad);
	thanhtru.GenerateNormVector();

	chot1.CreateCylinder(40, chot1Height, chot1Radius);
	chot1.GenerateNormVector();
	
	thanhnoi2.CreateS4(thanhnoi2Width, thanhnoi2Height, thanhnoi2Thickness, thanhnoi2InnerHeight, thanhnoi2InnerWidth);
	thanhnoi2.GenerateNormVector();

	tayquay.CreateS2(tayquayWidth, tayquayHeight, tayquayThickness, 40);
	tayquay.GenerateNormVector();

	boxchot2.CreateCube(boxchot2Size);
	boxchot2.GenerateNormVector();
	chot2.CreateCylinder(40, chot2Height, chot2Radius);
	chot2.GenerateNormVector();

	thanhnoi1.CreateS3(thanhnoi1Width, thanhnoi1Thickness, thanhnoi1Height, thanhnoi1InnerWidth, thanhnoi1InnerHeight, 40);
	thanhnoi1.GenerateNormVector();

	boxchot3.CreateCube(boxchot3Size);
	boxchot3.GenerateNormVector();
	chot3.CreateCylinder(40, chot3Height, chot3Radius);
	chot3.GenerateNormVector();
}

void drawDe();
void drawGiado1();
void drawGiado2();
void drawCodinh1();
void drawCodinh2();
void drawBanhxe();
void drawThanhtru();
void drawChot1();
void drawThanhnoi2();
void drawTayquay();
void drawBoxchot2();
void drawChot2();
void drawThanhnoi1();
void drawBoxchot3();
void drawChot3();
void drawTruchetTiling();

void setColorLight(float r, float g, float b)
{
	float baseSpecular = 0.1, baseDiffuse = 0.3, factorSpecular = 0.5, factorDiffuse = 0.3;

	GLfloat ambient0[] = { r,g,b, 1.0f };
	GLfloat diffuse[] = {
		baseDiffuse + r * factorDiffuse,
		baseDiffuse + g * factorDiffuse,
		baseDiffuse + b * factorDiffuse,
		1.0f
	};
	GLfloat specular[] = { 
		baseSpecular + r * factorSpecular,
		baseSpecular + g * factorSpecular,
		baseSpecular + b * factorSpecular,
		1.0f
	};
	GLfloat	shiness = 100;
	setupMaterial(ambient0, diffuse, specular, shiness);
}

float beta()
{
	float alpha = PI / 2 + banhxe.rotateY * D2R;
	float r = chot2pos * tayquayWidth;

	float rfx = r * cos(alpha);
	float rfy = (banhxepos - chot1pos) * giado1Thickness + r * sin(alpha);
	return atan(rfx / rfy);
}
void calculateThanhtruSlideX();

void drawMeshes()
{
	calculateThanhtruSlideX();
	drawDe();
	drawGiado1();
	drawGiado2();
	drawCodinh1();
	drawCodinh2();
	drawBanhxe();
	drawThanhtru();
	drawChot1();
	drawThanhnoi2();
	drawTayquay();
	drawBoxchot2();
	drawChot2();
	drawThanhnoi1();
	drawBoxchot3();
	drawChot3();
	drawTruchetTiling();
}
void calculateThanhtruSlideX()
{
	float beta = ::beta();

	float l = thanhnoi1Width - thanhnoi1Height;
	float y0 = chot1pos * giado1Thickness + 0.5 * deThickness;

	thanhtru.slideX = -l * cos(beta + PI / 2);
	chot3.slideY = y0 + l * sin(beta + PI / 2);
	thanhnoi1.rotateY = -beta / (D2R);
	boxchot2.rotateY = -beta / (D2R);
}

void drawChot3()
{
	glPushMatrix();
	
	glTranslatef(
		thanhtru.slideX,
		chot3.slideY,
		giado1Height + boxchot2Height * 2 + thanhnoi1Thickness);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	if (drawWireFrame)
	{
		chot3.DrawWireframe();
	}
	else
	{
		setColorLight(.5, .5, .5);
		chot3.Draw();
	}
	glPopMatrix();
}

void drawBoxchot3()
{
	glPushMatrix();

	glTranslatef(
		thanhtru.slideX, 
		chot3.slideY, 
		giado1Height + boxchot2Height * 2 + thanhnoi1Thickness
	);

	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	if (drawWireFrame)
	{
		boxchot3.DrawWireframe();
	}
	else
	{
		setColorLight(1, 0, 0);
		boxchot3.Draw();
	}
	glPopMatrix();
}


void drawThanhnoi1()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	glTranslatef(
		deThickness + giado1Thickness * chot1pos,
		giado1Height + tayquayHeight + thanhnoi1Thickness / 2,
	0
	);

	glTranslatef(
		cos(D2R * thanhnoi1.rotateY) * (thanhnoi1Width - thanhnoi1Height) * 0.5,
		0,
		-sin(D2R * thanhnoi1.rotateY) * (thanhnoi1Width - thanhnoi1Height) * 0.5
	);
	glRotatef(thanhnoi1.rotateY, 0, 1, 0);
	
	if (drawWireFrame)
	{
		thanhnoi1.DrawWireframe();
	}
	else
	{
		setColorLight(0, .9, 0);
		thanhnoi1.Draw();
	}

	glPopMatrix();
}

void drawChot2()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	glTranslatef(
		cos(banhxe.rotateY * D2R) * (tayquayWidth - tayquayHeight + chot2Radius) * chot2pos + deThickness / 2 + giado1Thickness * banhxepos,
		giado1Height + tayquayHeight + boxchot2Height,
		-sin(banhxe.rotateY * D2R) * (tayquayWidth - tayquayHeight + chot2Radius) * chot2pos
	);


	if (drawWireFrame)
	{
		chot2.DrawWireframe();
	}
	else
	{
		setColorLight(.5, .5, .5);
		chot2.Draw();
	}

	glPopMatrix();
}

void drawBoxchot2()
{
	glPushMatrix();

	
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	

	glTranslatef(
		cos(banhxe.rotateY * D2R) * (tayquayWidth - tayquayHeight + chot2Radius) * chot2pos + deThickness / 2 + giado1Thickness * banhxepos - boxchot2Size / 2, // new Y
		giado1Height + tayquayHeight + boxchot2Height / 2,
		-sin(banhxe.rotateY * D2R) * (tayquayWidth - tayquayHeight + chot2Radius) * chot2pos // new X
	);

	glTranslatef(
		cos(D2R * thanhnoi1.rotateY) * boxchot2Size * 0.5,
		0,
		-sin(D2R * thanhnoi1.rotateY) * boxchot2Size * 0.5
	);
	glRotatef(thanhnoi1.rotateY, 0, 1, 0);

	if (drawWireFrame)
	{
		boxchot2.DrawWireframe();
	}
	else
	{
		setColorLight(1, 0, 0);
		boxchot2.Draw();
	}

	glPopMatrix();
}


void drawTayquay()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	glTranslatef(
		cos(banhxe.rotateY * D2R) * tayquayWidth / 2 + deThickness /2 + giado1Thickness * banhxepos,
		giado1Height + tayquayHeight / 2, 
		-sin(banhxe.rotateY * D2R) * tayquayWidth / 2
	);
	glRotatef(banhxe.rotateY, 0, 0.5, 0);
	if (drawWireFrame)
	{
		tayquay.DrawWireframe();
	}
	else
	{
		setColorLight(1, 174 / 255.0, 201 / 255.0);
		tayquay.Draw();
	}

	glPopMatrix();
}

void drawThanhnoi2()
{
	glPushMatrix();
	glTranslatef(
		thanhtru.slideX, 
		deThickness / 2 + giado1Thickness - thanhnoi2Height / 2 + codinhhRadius,
		giado1Height + codinhHeight / 2 - codinhhRadius
	);

	if (drawWireFrame)
	{
		thanhnoi2.DrawWireframe();
	}
	else
	{
		setColorLight(0, 0, 0);
		thanhnoi2.Draw();
	}

	glPopMatrix();
}

void drawChot1()
{
	glPushMatrix();
	glTranslatef(0, deThickness + chot1pos * giado1Thickness, giado1Height);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);

	if (drawWireFrame)
	{
		chot1.DrawWireframe();
	}
	else
	{
		setColorLight(.5, .5, .5);
		chot1.Draw();
	}

	glPopMatrix();

}

void drawThanhtru()
{
	glPushMatrix();

	glTranslatef(
		thanhtru.slideX,
		deThickness / 2 + giado1Thickness + giado2Thickness / 2,
		giado1Height + codinhHeight / 2 - codinhhRadius
	);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);

	if (drawWireFrame)
	{
		thanhtru.DrawWireframe();
	}
	else
	{
		setColorLight(0, 0, 0);
		thanhtru.Draw();
	}

	glPopMatrix();
}

void drawBanhxe()
{
	glPushMatrix();

	glTranslatef(
		0, 
		deThickness / 2 + giado1Thickness * banhxepos, 
		giado1Height - banhxeHeight / 2
	);
	glRotatef(90, 1, 0, 0);
	glRotatef(banhxe.rotateY, 0, 1, 0);

	if (drawWireFrame)
	{
		banhxe.DrawWireframe();
	}
	else
	{
		setColorLight(1, 0, 0);
		banhxe.Draw();
	}

	glPopMatrix();
}

void drawCodinh2()
{
	glPushMatrix();
	glTranslatef(-giado2Width / 2 + 0.5 * codinhWidth, deThickness / 2 + giado1Thickness + giado2Thickness / 2, codinhThickness / 2);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);

	if (drawWireFrame)
	{
		codinh2.DrawWireframe();
	}
	else
	{
		setColorLight(1, 0, 0);
		codinh2.Draw();
	}

	glPopMatrix();

}

void drawCodinh1()
{
	glPushMatrix();
	glTranslatef(giado2Width / 2 - 0.5 * codinhWidth, deThickness / 2 + giado1Thickness + giado2Thickness / 2, codinhThickness / 2);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	
	if (drawWireFrame)
	{
		codinh1.DrawWireframe();
	}
	else
	{
		setColorLight(1, 0, 0);
		codinh1.Draw();
	}

	glPopMatrix();

}

void drawGiado2()
{
	glPushMatrix();

	glTranslatef(0, deThickness / 2 + giado1Thickness + giado2Thickness / 2, 0);
	if (drawWireFrame)
	{
		giado2.DrawWireframe();
	}
	else
	{
		setColorLight(0, 0, .5);
		giado2.Draw();
	}

	glPopMatrix();
}

void drawDe()
{
	glPushMatrix();
	glTranslated(0, 0.5 * deThickness, 0);
	if (drawWireFrame)
	{
		de.DrawWireframe();
	}
	else
	{
		setColorLight(0, 0, .5);
		de.Draw();
	}

	glPopMatrix();
}

void drawGiado1()
{
	glPushMatrix();

	glTranslatef(0, deThickness / 2 + giado1Thickness / 2, 0);
	if (drawWireFrame)
	{
		giado1.DrawWireframe();
	}
	else
	{
		setColorLight(0, 0, .5);
		giado1.Draw();
	}
	glPopMatrix();
}

void drawTile(float len, int nSegment, int pattern, float pathWidth)
{
	GLfloat colorvBackground[3] = {153/255.0,217/255.0,234/255.0};
	GLfloat colorvForeground[3] = {127/255.0,127/255.0,127/255.0};
	float eps = 0.001;
	setColorLight(colorvBackground[0], colorvBackground[1], colorvBackground[2]);
	// background
	glBegin(GL_POLYGON);
		glNormal3b(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(len, 0, 0);
		glVertex3f(len, 0, len);
		glVertex3f(0, 0, len);
	glEnd();

	float pathSize = pathWidth / len;
	// Set these values avg 0.5 to make sure it can connect to other tiles properly 
	float innerRadius = 0.5 - pathSize / 2, outerRadius = 0.5 + pathSize / 2;

	float x, y;
	float radius;
	float angle, alpha;
	
	switch (pattern)
	{
	case 1:
	{
		setColorLight(colorvForeground[0], colorvForeground[1], colorvForeground[2]);
		glLineWidth(1);
		glBegin(GL_POLYGON);
		{
			glNormal3b(0, 1, 0);
			radius = outerRadius * len;
			alpha = 0;
			angle = 90.0f / ((float)nSegment - 1);
			for (int i = 0; i < nSegment; i++)
			{
				x = radius * cos(alpha * D2R);
				y = radius * sin(alpha * D2R);
				glVertex3f(x, eps, y);
				alpha += angle;
			}
			glVertex3f(0, eps, 0);
		}
		glEnd();

		setColorLight(colorvBackground[0], colorvBackground[1], colorvBackground[2]);
		glBegin(GL_POLYGON);
		{
			glNormal3b(0, 1, 0);
			radius = innerRadius * len;
			alpha = 0;
			angle = 90.0f / (nSegment - 1);
			for (int i = 0; i < nSegment; i++)
			{
				x = radius * cos(alpha * D2R);
				y = radius * sin(alpha * D2R);
				glVertex3f(x, eps * 2, y);
				alpha += angle;
			}
			glVertex3f(0, eps * 2, 0); 
		}
		glEnd();

		setColorLight(colorvForeground[0], colorvForeground[1], colorvForeground[2]);
		glBegin(GL_POLYGON);
		{
			glNormal3b(0, 1, 0);
			radius = outerRadius * len;
			alpha = 180;
			angle = 90.0f / (nSegment - 1);
			for (int i = 0; i < nSegment; i++)
			{

				x = radius * cos(alpha * D2R) + len;
				y = radius * sin(alpha * D2R) + len;
				glVertex3f(x, eps, y);
				alpha += angle;
			}
			glVertex3f(len, eps, len);
		}
		glEnd();

		setColorLight(colorvBackground[0], colorvBackground[1], colorvBackground[2]);
		glBegin(GL_POLYGON);
		{
			glNormal3b(0, 1, 0);
			radius = innerRadius * len;
			alpha = 180;
			angle = 90.0f / (nSegment - 1);
			for (int i = 0; i < nSegment; i++)
			{
				x = radius * cos(alpha * D2R) + len;
				y = radius * sin(alpha * D2R) + len;
				glVertex3f(x, eps * 2, y);
				alpha += angle;
			}
			glVertex3f(len, eps * 2, len);
		}
		glEnd();
		break;
	}
	case 2:
	{
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(len, 0, 0);
			drawTile(len, nSegment, 1, pathWidth);
		glPopMatrix();
		break;
	}
	case 3:
	{
		setColorLight(colorvForeground[0], colorvForeground[1], colorvForeground[2]);
		// Vertical path
		glBegin(GL_POLYGON);
		glNormal3b(0, 1, 0);
		glVertex3f(innerRadius * len, eps, 0);
		glVertex3f(outerRadius * len, eps, 0);
		glVertex3f(outerRadius * len, eps, len);
		glVertex3f(innerRadius * len, eps, len);
		glEnd();

		// Horizontal path
		glBegin(GL_POLYGON);
		glNormal3b(0, 1, 0);
		glVertex3f(0, eps, innerRadius * len);
		glVertex3f(0, eps, outerRadius * len);
		glVertex3f(len, eps, outerRadius * len);
		glVertex3f(len, eps, innerRadius * len);
		glEnd();
		break;
	}
	case 4:
	{
		setColorLight(colorvForeground[0], colorvForeground[1], colorvForeground[2]);
		
		drawTile(len, nSegment, 3, pathWidth);

		radius = innerRadius * len;
		alpha = 0;
		angle = 360.f / (nSegment - 1);
		glBegin(GL_POLYGON);
		glNormal3b(0, 1, 0);
		for (int i = 0; i < nSegment; i++)
		{
			x = radius * cos(alpha * D2R) + len / 2.0;
			y = radius * sin(alpha * D2R) + len / 2.0;
			glVertex3f(x, eps * 2, y);
			alpha += angle;
		}
		glEnd();

		setColorLight(colorvBackground[0], colorvBackground[1], colorvBackground[2]);
		radius = (outerRadius - innerRadius) * len;
		alpha = 0;
		angle = 360.f / nSegment;
		glBegin(GL_POLYGON);
		glNormal3b(0, 1, 0);
		for (int i = 0; i < nSegment; i++)
		{
			x = radius * cos(alpha * D2R) + len / 2;
			y = radius * sin(alpha * D2R) + len / 2;
			glVertex3f(x, eps * 3, y);
			alpha += angle;
		}
		glEnd();
		break;
	}
	default:
		break;
	}
}

int dota2id;
int getInt1to4()
{
	if (dota2id == 0)
	{
		dota2id = 368468556;
	}
	dota2id /= 4;
	return dota2id % 4 + 1;
}
void drawTruchetTiling()
{
	float len = 5;
	float pathWidth = 0.2 * len;
	int count = 23;
	int ic = 0;
	dota2id = 0;
	glPushMatrix();
		glTranslatef(-len * count + 1, 0, -len * count);
		for (int x = 0; x < 2*count; x++)
		{
			ic = 0;
			for (int y = 0; y < 2*count; y++)
			{
				ic++;
				int tilePattern = getInt1to4();
				if (tilePattern == 2)
				{
					glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glTranslatef(-len, 0, 0);
					drawTile(len, 80, 1, pathWidth);
					glPopMatrix();
				}
				else
					drawTile(len, 80, tilePattern, pathWidth);
				glTranslatef(len, 0, 0);
			}
			glTranslatef(0, 0, len);
			glTranslatef(-ic * len, 0, 0);
		}
	glPopMatrix();
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = -camera_dis * cos(camera_angle / 180 * PI);
	camera_Y = camera_height;
	camera_Z = camera_dis * sin(camera_angle / 180 * PI);
	if (topView) {
		gluLookAt(0, 60, 0, 0, 0, 0, 0, 0, -1);
	}
	else {
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, 0, 1, 0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth, screenHeight);
	setupLight();

	drawMeshes();

	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	gluPerspective(20.0, screenWidth / screenHeight, -1000, 1000.0);
}
void mySpecialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		camera_angle -= 10;
		if (camera_angle < 0)
			camera_angle += 360;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 10;
		if (camera_angle > 0)
			camera_angle -= 360;
		break;
	case GLUT_KEY_UP:
		camera_height += 0.1;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.1;
		break;
	}
	glutPostRedisplay();
}
int main(int argc, const char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Le Huu Vo Long - 1812883"); // open the screen window

	createMeshes();

	myInit();
    glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKey);
	glutMainLoop();
	return 0;
}

