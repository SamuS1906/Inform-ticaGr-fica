//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"


//*************************************************************************
// _puntos3D
//*************************************************************************


_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}



//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*****************************************1.0,0.5,0.0,3********************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}



//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //cambiado por sólido
//glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //cambiado por sólido
//glLineWidth(grosor);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if(i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}



//*************************************************************************
// clase cubo 
//*************************************************************************

_cubo::_cubo(float tam)
{
// matriz de vertices
// definimos con resize (piramide tiene 5)
// Definimos los puntos en 3D ojo con los tam
// ojo orden contrario a las agujas del reloj en los vertices 
vertices.resize(8); 
vertices[0].x=0;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=0;
vertices[3].x=0;vertices[3].y=0;vertices[3].z=0; // El vertice 3 está en el (0,0,0)
vertices[4].x=0;vertices[4].y=tam;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=tam;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=0;
vertices[7].x=0;vertices[7].y=tam;vertices[7].z=0;
// matriz de triangulos

caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4; // la cara 0 esta formada por los vertices 0 1 y 4
caras[1]._0=1;caras[1]._1=5;caras[1]._2=4;
caras[2]._0=1;caras[2]._1=2;caras[2]._2=5;
caras[3]._0=2;caras[3]._1=6;caras[3]._2=5;
caras[4]._0=2;caras[4]._1=3;caras[4]._2=6; 
caras[5]._0=3;caras[5]._1=7;caras[5]._2=6; 
caras[6]._0=0;caras[6]._1=3;caras[6]._2=7; 
caras[7]._0=0;caras[7]._1=4;caras[7]._2=7;
caras[8]._0=4;caras[8]._1=5;caras[8]._2=6;
caras[9]._0=4;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=3;caras[10]._1=1;caras[10]._2=0; 
caras[11]._0=3;caras[11]._1=2;caras[11]._2=1; 

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4; // la cara 0 esta formada por los vertices 0 1 y 4
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0; // triangulo base
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1; // triangulo base
}

//*************************************************************************
// clase ovni
//*************************************************************************

_ovni::_ovni(float tam)
{
// matriz de vertices
// ojo orden contrario a las agujas del reloj en las caras

vertices.resize(16); 
vertices[0].x=0;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=0;
vertices[3].x=0;vertices[3].y=0;vertices[3].z=0; // El vertice 3 está en el (0,0,0)
vertices[4].x=0;vertices[4].y=tam;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=tam;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=0;
vertices[7].x=0;vertices[7].y=tam;vertices[7].z=0;
vertices[8].x=0;vertices[8].y=0;vertices[8].z=tam*2;
vertices[9].x=tam;vertices[9].y=0;vertices[9].z=tam*2;
vertices[10].x=tam*2;vertices[10].y=0;vertices[10].z=tam;
vertices[11].x=tam*2;vertices[11].y=0;vertices[11].z=0;
vertices[12].x=tam;vertices[12].y=0;vertices[12].z=-tam;
vertices[13].x=0;vertices[13].y=0;vertices[13].z=-tam;
vertices[14].x=-tam;vertices[14].y=0;vertices[14].z=0;
vertices[15].x=-tam;vertices[15].y=0;vertices[15].z=tam;
// matriz de triangulos

caras.resize(28);
caras[0]._0=4;caras[0]._1=8;caras[0]._2=5; 
caras[1]._0=5;caras[1]._1=8;caras[1]._2=9;
caras[2]._0=5;caras[2]._1=9;caras[2]._2=10;
caras[3]._0=5;caras[3]._1=10;caras[3]._2=11;
caras[4]._0=5;caras[4]._1=11;caras[4]._2=6; 
caras[5]._0=6;caras[5]._1=11;caras[5]._2=12; 
caras[6]._0=6;caras[6]._1=12;caras[6]._2=7; 
caras[7]._0=7;caras[7]._1=12;caras[7]._2=13;
caras[8]._0=7;caras[8]._1=13;caras[8]._2=14;
caras[9]._0=7;caras[9]._1=15;caras[9]._2=14;
caras[10]._0=7;caras[10]._1=4;caras[10]._2=15; 
caras[11]._0=4;caras[11]._1=15;caras[11]._2=8; 
caras[12]._0=4;caras[12]._1=5;caras[12]._2=6;
caras[13]._0=4;caras[13]._1=6;caras[13]._2=7;
// Base

caras[14]._0=0;caras[14]._1=8;caras[14]._2=9;
caras[15]._0=0;caras[15]._1=9;caras[15]._2=1;
caras[16]._0=9;caras[16]._1=10;caras[16]._2=1;
caras[17]._0=2;caras[17]._1=1;caras[17]._2=10;
caras[18]._0=2;caras[18]._1=10;caras[18]._2=11;
caras[19]._0=11;caras[19]._1=2;caras[19]._2=12;
caras[20]._0=2;caras[20]._1=12;caras[20]._2=13;
caras[21]._0=13;caras[21]._1=3;caras[21]._2=2;
caras[22]._0=3;caras[22]._1=13;caras[22]._2=14;
caras[23]._0=3;caras[23]._1=14;caras[23]._2=0;
caras[24]._0=14;caras[24]._1=15;caras[24]._2=0;
caras[25]._0=15;caras[25]._1=8;caras[25]._2=0;
caras[26]._0=0;caras[26]._1=1;caras[26]._2=3;
caras[27]._0=3;caras[27]._1=1;caras[27]._2=2;
}

