//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor); //rgb es color y el entero grosor

vector<_vertex3f> vertices;
// Se podría poner así en lugar que en el draw_puntos (Igual que en triangulos de abajo por ejemplo)
//vector<_vertex3f> color;
//int grosor
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo lo tenemos que hacer (hereda de triángulo)
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide lo tenemos que hacer (hereda de triángulo)
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};


//*************************************************************************
// clase ovni lo tenemos que hacer (hereda de triángulo)
//*************************************************************************

class _ovni: public _triangulos3D
{
public:

	_ovni(float tam=0.5);
};





