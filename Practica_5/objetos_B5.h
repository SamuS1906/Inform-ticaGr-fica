//**************************************************************************
// Práctica 4 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,ALL,SOLID_ILLUMINATED_FLAT,SOLID_ILLUMINATED_GOURAUD, SELECT} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(int grosor);
void    draw_solido();
void 	draw_solido_ajedrez(float r2, float g2, float b2);
void 	draw(_modo modo,float r2, float g2, float b2, float grosor);

void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );

void 	change_color (vector<float> color, int size);

void	calcular_normales_caras();
void 	calcular_normales_vertices();
void   draw_seleccion(int r, int g, int b);

vector<_vertex3i> caras;
float r,g,b;


vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

class _revolucionPly: public _triangulos3D
{
public:
       _revolucionPly();
void  parametros(char *file);

void  revolucionPly(char *file);


vector<_vertex3f> perfil; 
int num;
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil, int num, char eje);


vector<_vertex3f> perfil; 
int num;
};


class _cono: public _triangulos3D
{
public:
       _cono();
void  parametros(vector<_vertex3f> perfil1,int num1, double altura);

vector<_vertex3f> perfil; 
int num;
int num_aux; //siempre será 1 el número de puntos que tiene el perfil para un cono.
double h;
};

class _cilindro: public _triangulos3D
{
public:
       _cilindro();
void  parametros(vector<_vertex3f> perfil1, int num1);

vector<_vertex3f> perfil; 
int num;
};

class _esfera: public _triangulos3D
{
public:
       _esfera();
void  parametros(int n,int m, double radio);

vector<_vertex3f> perfil; 
int num;
int num_aux; 
double r;
};



//************************************************************************
// Práctica3: medusa
//************************************************************************
//     Umbrela
class _umbrela: public _triangulos3D
{
public:
       _umbrela();

void 	draw(_modo modo, float r2, float g2, float b2, float grosor);

protected:
_rotacion semiesfera;

};


//     Tentaculos orales

class _tentaculos_orales: public _triangulos3D
{
public:
       _tentaculos_orales();

void draw(_modo modo, float r2, float g2, float b2, float grosor);

float getGiro();
void setGiro(float valor);

float giroOrales;

int n,m;
float radio;

protected:
_cilindro  cilindro1;

_cono cono1;
_cono cono2;
_cono cono3;


_cilindro  cilindro2;
_cilindro  cilindro3;

_esfera esfera1;
_esfera esfera2;


};

//     Tentaculos venenosos

class _tentaculos_venenosos: public _triangulos3D
{
public:
       _tentaculos_venenosos();

void draw(_modo modo, float r2, float g2, float b2, float grosor);

float getFlexion1();
float getFlexion2();
float getFlexion3();
float getFlexion4();

float getMAXFlexion1();
float getMINFlexion1();
float getMAXFlexion2();
float getMINFlexion2();
float getMAXFlexion3();
float getMINFlexion3();
float getMAXFlexion4();
float getMINFlexion4();

void setFlexion1(float valor);
void setFlexion2(float valor);
void setFlexion3(float valor);
void setFlexion4(float valor);

float flexion1, flexion2, flexion3, flexion4;
float flexion1Max, flexion1Min,flexion2Max, flexion2Min,flexion3Max, flexion3Min,flexion4Max, flexion4Min;

int n,m;
float radio;

protected:
_cilindro  cilindro1;
_cilindro  cilindro2;
_cilindro  cilindro3;

_cono cono1;

_esfera esfera1;
_esfera esfera2;
_esfera esfera3;
_esfera esfera4;



};


//     Medusa
class _medusa: public _triangulos3D
{
public:
       _medusa();

void 	draw(_modo modo, float r2, float g2, float b2, float grosor);
float getGiroTentaculosOrales();
void setGiroTentaculosOrales(float valor);
void seleccion();

int piezas;
int activo[3];
int color_selec[3][3];
int color_pick[3];

float getFlexion11();
float getFlexion12();
float getFlexion13();
float getFlexion14();

float getFlexion21();
float getFlexion22();
float getFlexion23();
float getFlexion24();

float getFlexion31();
float getFlexion32();
float getFlexion33();
float getFlexion34();

float getFlexion41();
float getFlexion42();
float getFlexion43();
float getFlexion44();

float getFlexion15();
float getFlexion16();
float getFlexion17();
float getFlexion18();

float getFlexion25();
float getFlexion26();
float getFlexion27();
float getFlexion28();

float getFlexion35();
float getFlexion36();
float getFlexion37();
float getFlexion38();

float getFlexion45();
float getFlexion46();
float getFlexion47();
float getFlexion48();

void setFlexion1(float valor);
void setFlexion2(float valor);
void setFlexion3(float valor);
void setFlexion4(float valor);


protected:
_umbrela umbrela;
_tentaculos_orales tentaculos_orales;
_tentaculos_venenosos tentaculos_venenosos1;
_tentaculos_venenosos tentaculos_venenosos2;
_tentaculos_venenosos tentaculos_venenosos3;
_tentaculos_venenosos tentaculos_venenosos4;
_tentaculos_venenosos tentaculos_venenosos5;
_tentaculos_venenosos tentaculos_venenosos6;
_tentaculos_venenosos tentaculos_venenosos7;
_tentaculos_venenosos tentaculos_venenosos8;
};


