//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"


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
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
	r = 0.0;
	g = 0.5;
	b = 0.7;
  //color por defecto


	b_normales_caras=false;
	b_normales_vertices=false;

	ambiente_difusa=_vertex4f(0.2,0.4,0.9,1.0);  //coeficientes ambiente y difuso
	especular=_vertex4f(0.5,0.5,0.5,1.0);        //coeficiente especular
	brillo=40;  

}

//cambiar color
void _triangulos3D::change_color (vector<float> color, int size){
	r = color[size-3];
	g = color[size-2];
	b = color[size-1];
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido()
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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

void _triangulos3D::draw_solido_ajedrez(float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r,g,b);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}


//*************************************************************************
// calcular normales a caras
//*************************************************************************


void _triangulos3D::calcular_normales_caras()
{  

normales_caras.resize(caras.size());
for(unsigned long i=0; i<caras.size(); i++){
	// obtener dos vectores en el triángulo y calcular el producto vectorial
	_vertex3f 
        	 a1=vertices[caras[i]._1]-vertices[caras[i]._0],
       		 a2=vertices[caras[i]._2]-vertices[caras[i]._0],
         	 n=a1.cross_product(a2);
	// modulo
	float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
	// normalización
    	normales_caras[i]= _vertex3f(n.x/m, n.y/m, n.z/m);
	}
  
b_normales_caras=true;

}

//*************************************************************************
// calcular normales a vertices
//*************************************************************************


void _triangulos3D::calcular_normales_vertices()
{

 int i, n, m;
 n = vertices.size();
 m = caras.size();

 normales_vertices.resize(n);

 for (i = 0; i < n; i++)
 {
  	normales_vertices[i].x = 0.0;
  	normales_vertices[i].y = 0.0;
  	normales_vertices[i].z = 0.0;
 }

 for (i = 0; i < m; i++)
 {
  	normales_vertices[caras[i]._0] += normales_caras[i];
  	normales_vertices[caras[i]._1] += normales_caras[i];
  	normales_vertices[caras[i]._2] += normales_caras[i];
  
 }

 b_normales_caras = true;

}

//*************************************************************************
// iluninacion suave
//*************************************************************************


void _triangulos3D::draw_iluminacion_suave()
{
 if (b_normales_caras == false)
  	calcular_normales_caras();
 
 if (b_normales_vertices == false)
  	calcular_normales_vertices();

 glShadeModel(GL_SMOOTH);
 glEnable(GL_LIGHTING);
 glEnable(GL_NORMALIZE);

 glMaterialfv(GL_AMBIENT_AND_DIFFUSE, GL_FRONT, (GLfloat *)&ambiente_difusa);
 glMaterialfv(GL_SPECULAR, GL_FRONT, (GLfloat *)&especular);
 glMaterialf(GL_SHININESS, GL_FRONT, brillo);

 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 glBegin(GL_TRIANGLES);
 for (int i = 0; i < caras.size(); i++)
 {
  	glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
  	glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

  	glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
  	glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

  	glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
  	glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
 }
 glEnd();
 glDisable(GL_LIGHTING);

}

//*************************************************************************
// iluminacion plana
//*************************************************************************


void _triangulos3D::draw_iluminacion_plana()

{

	int i;
	if (b_normales_caras==false) calcular_normales_caras();

	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
	glMaterialf(GL_FRONT,GL_SHININESS,brillo);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
	glDisable(GL_LIGHTING);

}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************


void _triangulos3D::draw(_modo modo, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r2,g2,b2,grosor);break;
	case EDGES:draw_aristas(grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r2, g2, b2);break;
	case SOLID:draw_solido();break;
	case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
	case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
	case ALL: draw_puntos(r2, g2, b2, grosor); draw_aristas(grosor); draw_solido_ajedrez(r2, g2, b2); break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
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
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
   
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

// esfera
//************************************************************************

_esfera::_esfera()
{


}

void _esfera::parametros(int n,int m, double radio)
{

	//n numero de puntos del perfil
	//m numeros caras de la esfera
	r = radio;
	//radio = sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux; 
	num = m;


	for(i=1; i<n; i++){
		vertice_aux.x = radio*cos(M_PI*i/n-M_PI/2.0);
		vertice_aux.y= radio*sin(M_PI*i/n-M_PI/2.0);
		vertice_aux.z=0;
		perfil.push_back(vertice_aux);
	}
	//solo PI porque queremos generar la mitad

	//perfil lo generas tu con el radio
	num_aux=perfil.size();
	vertices.resize(num_aux*num+2);


	//realmente quieres generar num puntos
	for (j=0;j<num;j++){
		for (i=0;i<num_aux;i++){
			vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
							perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
			vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
							perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
			vertice_aux.y=perfil[i].y;
			vertices[i+j*num_aux]=vertice_aux;
		}
	}


	caras.resize((num_aux-1)*2*num+2*num);

	int c=0;

	for (j=0;j<num;j++){
		for(i=0; i<num_aux-1;i++){
			cara_aux._0 = i+1+j*num_aux;
			cara_aux._1 = i+1+((j+1)%num)*num_aux;
			cara_aux._2 = i+((j+1)%num)*num_aux;
			caras.push_back(cara_aux);

			cara_aux._0 = i+1+j*num_aux;
			cara_aux._1 = i+j*num_aux;
			cara_aux._2 = i+((j+1)%num)*num_aux;
			caras.push_back(cara_aux);
		}
	}



	// tapa inferior
	if (fabs(perfil[0].x)>0.0){

		vertices[num_aux*num].x=0.0; 
		vertices[num_aux*num].y=-radio; 
		vertices[num_aux*num].z=0.0;

	for (j=0;j<num;j++){
			caras[c]._0=num_aux*num;
			caras[c]._1=j*num_aux;
			caras[c]._2=((j+1)%num)*num_aux;
			c=c+1;
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0){

	vertices[num_aux*num+1].x=0.0; 
	vertices[num_aux*num+1].y=radio;
	vertices[num_aux*num+1].z=0.0;

		for (j=0;j<num;j++){

			caras[c]._0=num_aux*num+1;
			caras[c]._1=j*num_aux+num_aux-1;
			caras[c]._2=((j+1)%num)*num_aux+num_aux-1;

			c=c+1;
		}

	}
}


// cono
//************************************************************************

_cono::_cono()
{

}

void _cono::parametros(vector<_vertex3f> perfil, int num, double altura)
{

	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;
	
	h = altura;

	//num numero de lados
	//num_aux es el numero de puntos del perfil y en el cono es 1
	num_aux=1;
	vertices.resize(num_aux*num+2);


	for (j=0;j<num;j++)
	{
		for (i=0;i<num_aux;i++){
			vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
							perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
			vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
							perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
			vertice_aux.y=perfil[i].y;
			vertices[i+j*num_aux]=vertice_aux;
		}
	}

	

	// tratamiento de las caras 

	caras.resize((num_aux-1)*2*num+2*num);


	int c=0;
	// tapa inferior
	if (fabs(perfil[0].x)>0.0){

			vertices[num_aux*num].x=0.0; 
			vertices[num_aux*num].y=perfil[0].y; 
			vertices[num_aux*num].z=0.0;


		for (j=0;j<num;j++){
			caras[c]._0=num_aux*num;
			caras[c]._1=j*num_aux;
			caras[c]._2=((j+1)%num)*num_aux;
			c=c+1;
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0)
	{
			vertices[num_aux*num+1].x=0.0; 
			vertices[num_aux*num+1].y=h;
			vertices[num_aux*num+1].z=0.0;

		for (j=0;j<num;j++){	
			caras[c]._0=num_aux*num+1;
			caras[c]._1=j*num_aux+num_aux-1;
			caras[c]._2=((j+1)%num)*num_aux+num_aux-1;
			c=c+1;
		}
	}
 
}



// cilindro
//************************************************************************

_cilindro::_cilindro()
{

}

void _cilindro::parametros(vector<_vertex3f> perfil, int num)
{
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	num_aux=perfil.size();
	vertices.resize(num_aux*num+2);

	//Permitir que se pueda meter el vector de puntos de la generatriz en cualquier sentido
	//si se introduce de arriba a abajo, lo cambiamos de orden para que sea de abajo a arriba.
	j=num_aux-1;
	for(i=0; i<num_aux/2; i++){
		vertice_aux = perfil[i];
		perfil[i]=perfil[j];
		perfil[j]=vertice_aux;
		j--;
	}


	for (j=0;j<num;j++){
		for (i=0;i<num_aux;i++){
		vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
						perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
						perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=perfil[i].y;
		vertices[i+j*num_aux]=vertice_aux;
		}
	}

	caras.resize((num_aux-1)*2*num+2*num);

	int c=0;
	for (j=0;j<num-1;j++){
		caras[c]._0=j*num_aux;
		caras[c]._1=j*num_aux+1;
		caras[c]._2=(j+1)*num_aux+1;
		c=c+1; 

		caras[c]._0=(j+1)*num_aux+1;	
		caras[c]._1=(j+1)*num_aux;	
		caras[c]._2=j*num_aux;		
		c=c+1;
	}

	//cierre de la ultima cara del ultimo lado del cilindro

		caras[c]._0=num_aux*num -2; 
		caras[c]._1=num_aux*num -1; 
		caras[c]._2=1;

		c=c+1; 
		caras[c]._0=1; 
		caras[c]._1=0 ;
		caras[c]._2=num_aux*num-2;
	
		c=c+1;

	// tapa inferior
	if (fabs(perfil[0].x)>0.0){
		vertices[num_aux*num].x=0.0; 
		vertices[num_aux*num].y=perfil[0].y; 
		vertices[num_aux*num].z=0.0;

		for (j=0;j<num-1;j++){
			caras[c]._0=num_aux*num;
			caras[c]._1=j*num_aux;
			caras[c]._2=(j+1)*num_aux;

			c=c+1;
		}

		//enganchar la ultima cara del ultimo lado de la tapa inferior
		caras[c]._0=num_aux*num;
		caras[c]._1= 0;
		caras[c]._2=num_aux*num-2;
		c=c+1;
	}

	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0){

		vertices[num_aux*num+1].x=0.0; 
		vertices[num_aux*num+1].y=perfil[num_aux-1].y; 
		vertices[num_aux*num+1].z=0.0;

		for (j=0;j<num-1;j++){
			caras[c]._0=num_aux*num+1; 
			caras[c]._1=j*2+1;
			caras[c]._2=(j+1)*2+1;

			c=c+1;
		}

		caras[c]._0=num_aux*num+1;
		caras[c]._1=1; 
		caras[c]._2=num_aux*num-1; 
	}
		
}

// objeto revolución dado fichero ply
//************************************************************************

_revolucionPly::_revolucionPly(){

}

void _revolucionPly::parametros(char *file){

	int n_ver,n_car;
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	vector<_vertex3f> perfil;
	int num_aux, num;

	vector<float> ver_ply ;
	vector<int>   car_ply ;
	
	_file_ply::read(file, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;
	num = car_ply[0];
	//cojo el numero de lados del archivo ply en la ultiam linea de la cara que no se usa, el segundo valor de esta ultima linea que es 8.


	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	perfil.resize(n_ver);
	num_aux = perfil.size();

	vertices.resize(num_aux*num+2);


	for (int i=0; i<n_ver; i++){
	perfil[i].x=ver_ply[3*i];
	perfil[i].y=ver_ply[3*i+1];
	perfil[i].z=ver_ply[3*i+2];
	}

     
  
	for (j=0;j<num;j++){
		for (i=0;i<num_aux;i++){
		vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
						perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
						perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=perfil[i].y;
		vertices[i+j*num_aux]=vertice_aux;
		}
	}

	caras.resize((num_aux-1)*2*num+2*num);

	int c = 0;
	for (j=0;j<num;j++){
		for(i=0; i<num_aux-1;i++){
			cara_aux._0=i+((j+1)%num)*num_aux;
			cara_aux._1=i+1+((j+1)%num)*num_aux;
			cara_aux._2=i+1+j*num_aux;
			caras.push_back(cara_aux);

			cara_aux._0 = i+1+j*num_aux;
			cara_aux._1 = i+j*num_aux;
			cara_aux._2 = i+((j+1)%num)*num_aux;
			caras.push_back(cara_aux);
		}
	}


	if (fabs(perfil[0].x)>0.0){
		vertices[num_aux*num].x=0.0; 
		vertices[num_aux*num].y=perfil[0].y; 
		vertices[num_aux*num].z=0.0;

		for (j=0;j<num;j++){
			caras[c]._0=num_aux*num;
			caras[c]._1=j*num_aux;
			caras[c]._2=((j+1)%num)*num_aux;
			c=c+1;
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0){

		vertices[num_aux*num+1].x=0.0; 
		vertices[num_aux*num+1].y=perfil[num_aux-1].y;
		vertices[num_aux*num+1].z=0.0;

		for (j=0;j<num;j++){	
			caras[c]._0=num_aux*num+1;
			caras[c]._1=j*num_aux+num_aux-1;
			caras[c]._2=((j+1)%num)*num_aux+num_aux-1;

			c=c+1;
		}
	}
}


_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, char eje)
{
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;
	bool ejez = false;

	//num numero de lados
	//num_aux es el numero de puntos del perfil
	num_aux=perfil.size();
	vertices.resize(num_aux*num+2);


	//Permitir que se pueda meter el vector de puntos de la generatriz en cualquier sentido
	//si se introduce de arriba a abajo, lo cambiamos de orden para que sea de abajo a arriba.
	if(perfil[num_aux].y < perfil[0].y) {
		//lo que hacemos es cambiar de orden el perfil, para que sea de abajo a arriba
		
		j=num_aux-1;
		for(i=0; i<num_aux/2; i++){
			vertice_aux = perfil[i];
			perfil[i]=perfil[j];
			perfil[j]=vertice_aux;
			j--;
		}
	}
	
	/* 
	tal y como tengo el codigo no es necesario comprobar si en el eje y o z metes lo puntos de izquierda a derecha o de derecha a izquierda, funciona bien de igual FORMA.
	*/


	/* tratamiento de los vértice*/

	//vas a tener vertices segun: num_aux*num, numero de lados * numero de puntos perfil
	//+2 para las tapas, un punto para la tapa de arriba y otro para la tapa de abajo. Esos puntos centrales de las tapas.

	//aqui comprobamos si es sobre x, y o z

	if(eje == 'y'){
		for (j=0;j<num;j++){
			for (i=0;i<num_aux;i++){
				vertice_aux.x=perfil[i].x;
				vertice_aux.z=-perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+
								perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
				vertice_aux.y=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))+
								perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
				vertices[i+j*num_aux]=vertice_aux;
			}
		}
	}
	else if(eje == 'x'){
		for (j=0;j<num;j++)
		{
			for (i=0;i<num_aux;i++){
				vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
								perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
				vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
								perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
				vertice_aux.y=perfil[i].y;
				vertices[i+j*num_aux]=vertice_aux;
			}
		}
	}
	else if(eje == 'z'){
		for (j=0;j<num;j++)
		{
			for (i=0;i<num_aux;i++){
				vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))-
								perfil[i].y*sin(2.0*M_PI*j/(1.0*num));
				vertice_aux.z=-perfil[i].z;
				vertice_aux.y=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))+
								perfil[i].x*sin(2.0*M_PI*j/(1.0*num));
				vertices[i+j*num_aux]=vertice_aux;
			}
		}
		
		ejez = true;
	}

	// tratamiento de las caras 

	caras.resize((num_aux-1)*2*num+2*num);


	int c=0;
	for (j=0;j<num;j++)
		{
			for(i=0; i<num_aux-1;i++){
				cara_aux._0=i+((j+1)%num)*num_aux;
				cara_aux._1=i+1+((j+1)%num)*num_aux;
				cara_aux._2=i+1+j*num_aux;
				caras.push_back(cara_aux);

				cara_aux._0 = i+1+j*num_aux;
				cara_aux._1 = i+j*num_aux;
				cara_aux._2 = i+((j+1)%num)*num_aux;
				caras.push_back(cara_aux);
			}
		}



	// tapa inferior
	if (fabs(perfil[0].x)>0.0 || ejez){
		if(eje == 'y'){
			vertices[num_aux*num].x=perfil[0].x;
			vertices[num_aux*num].y=0.0; 
			vertices[num_aux*num].z=0.0;
		}
		else if(eje == 'x'){
			vertices[num_aux*num].x=0.0; 
			vertices[num_aux*num].y=perfil[0].y; 
			vertices[num_aux*num].z=0.0;
		}
		else if (eje == 'z'){
			vertices[num_aux*num].x=0.0; 
			vertices[num_aux*num].y=0.0; 
			vertices[num_aux*num].z=perfil[num_aux-1].z;
			//esto es debido a que es en el eje z
		}

		for (j=0;j<num;j++){
			caras[c]._0=num_aux*num;
			caras[c]._1=j*num_aux;
			caras[c]._2=((j+1)%num)*num_aux;
			c=c+1;
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0 || ejez)
	{
		if(eje == 'y'){
			vertices[num_aux*num+1].x=perfil[num_aux-1].x; 
			vertices[num_aux*num+1].y=0.0;
			vertices[num_aux*num+1].z=0.0;
		}else if( eje == 'x'){
			vertices[num_aux*num+1].x=0.0; 
			vertices[num_aux*num+1].y=perfil[num_aux-1].y;
			vertices[num_aux*num+1].z=0.0;
		}
		else if( eje == 'z'){
			vertices[num_aux*num+1].x=0.0; 
			vertices[num_aux*num+1].y=0.0;
			vertices[num_aux*num+1].z=perfil[0].z;
		}

		for (j=0;j<num;j++){	
			caras[c]._0=num_aux*num+1;
			caras[c]._1=j*num_aux+num_aux-1;
			caras[c]._2=((j+1)%num)*num_aux+num_aux-1;
			c=c+1;
		}
	}
}





//******************************************************************************************
// UMBRELA
//******************************************************************************************



_umbrela::_umbrela(){
	
	vector<_vertex3f>  perfil;
	_vertex3f aux;

	//puntos rotacion
	int i;
	double n=10, radio=100;
	for(i=1; i<n; i++){
		aux.x = i;
		aux.y= sqrt(radio-(pow(i,2)));
		aux.z=0;
		perfil.push_back(aux);
		
	}

	aux.x=10;
	aux.y=2.492798;
	aux.z=0;
	perfil.push_back(aux);
	aux.x=11;
	aux.y=0.381697;
	aux.z=0;
	perfil.push_back(aux);
	aux.x=10;
	aux.y=-2;
	aux.z=0;
	perfil.push_back(aux);
	
	semiesfera.parametros(perfil, 60, 'x');

}
void _umbrela::draw(_modo modo, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	glTranslatef(0,0,0);
	semiesfera.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();
	
}

//******************************************************************************************
// Tentaculos orales
//******************************************************************************************
_tentaculos_orales::_tentaculos_orales(){

	vector<_vertex3f> perfil2,perfil1;
	_vertex3f aux;

	//puntos cilindro
	aux.x=1.0; aux.y=1.0; aux.z=0.0;
	perfil1.push_back(aux);
	aux.x=1.0; aux.y=-1.0; aux.z=0.0;
	perfil1.push_back(aux);

	cilindro1.parametros(perfil1,20);
	cilindro2.parametros(perfil1,20);
	cilindro3.parametros(perfil1,20);


	//puntos cono
	aux.x=1.0; aux.y=-1.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1; aux.y=0.5; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0; aux.y=1.0; aux.z=0.0;
	perfil2.push_back(aux);

	cono1.parametros(perfil2,16,2);
	cono2.parametros(perfil2,16,2);	
	cono3.parametros(perfil2,16,2);


	n = 15;
	m = 15;
	radio = 2;
	
	esfera1.parametros(n,m,radio);
	esfera2.parametros(n,m,radio);
}

void _tentaculos_orales::draw(_modo modo, float r2, float g2, float b2, float grosor){
	

		glPushMatrix();
		glTranslatef(0,-5.0,0);
		glScalef(2.0,3.0,2);
		cilindro1.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();
		
	glPushMatrix();
	glRotatef(giroOrales, 0, 1, 0);

		glPushMatrix();	
		glTranslatef(0.0,-8.8,0.0);
		glRotatef(180.0,0,0,1);
		glScalef(2.0,0.8,2.0);		
		cono1.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.8,-9.8,0);
		glRotatef(-50,0,0,1);
		glScalef(1.3,1.0,1.3);
		cilindro2.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.8,-9.8,0);
		glRotatef(50,0,0,1);
		glScalef(1.3,1.0,1.3);
		cilindro3.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();

		glPushMatrix();	
		glTranslatef(-3.4,-11,0.0);
		glRotatef(-230.0,0,0,1);
		glScalef(0.5,0.5,0.5);	
		esfera1.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();
		
		glPushMatrix();	
		glTranslatef(3.4,-11,0.0);
		glRotatef(230.0,0,0,1);
		glScalef(0.5,0.5,0.5);	
		esfera2.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();

		glPushMatrix();	
		glTranslatef(3.7,-15.4,0.0);
		glRotatef(180.0,0,0,1);
		glScalef(1.4,3.4,1.4);		
		cono3.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();

		glPushMatrix();	
		glTranslatef(-3.7,-15.4,0.0);
		glRotatef(180.0,0,0,1);
		glScalef(1.4,3.4,1.4);		
		cono2.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();


	glPopMatrix();

}

float _tentaculos_orales::getGiro(){
	return giroOrales;
}

void _tentaculos_orales::setGiro(float valor){
	giroOrales += valor;
}

//******************************************************************************************
// Tentaculos venenosos
//******************************************************************************************
_tentaculos_venenosos::_tentaculos_venenosos(){
	
	vector<_vertex3f> perfil2,perfil1;
	_vertex3f aux;

	flexion1Max=45;
	flexion1Min=-20;

	flexion2Max=20;
	flexion2Min=-20;

	flexion3Max=10;
	flexion3Min=-15;

	flexion4Max=5;
	flexion4Min=-15;

	//puntos cilindro
	aux.x=1.0; aux.y=0.0; aux.z=0.0;
	perfil1.push_back(aux);
	aux.x=1.0; aux.y=-1.0; aux.z=0.0;
	perfil1.push_back(aux);

	cilindro1.parametros(perfil1,20);
	cilindro2.parametros(perfil1,20);
	cilindro3.parametros(perfil1,20);
	
	//puntos cono
	aux.x=1.0; aux.y=-1.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1; aux.y=0.5; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0; aux.y=1.0; aux.z=0.0;
	perfil2.push_back(aux);

	cono1.parametros(perfil2,16,2);

	n = 15;
	m = 15;
	radio = 2;
	
	esfera1.parametros(n,m,radio);
	esfera2.parametros(n,m,radio);
	esfera3.parametros(n,m,radio);
	esfera4.parametros(n,m,radio);
}

void _tentaculos_venenosos::draw(_modo modo, float r2, float g2, float b2, float grosor){
	


		glPushMatrix();
		glTranslatef(0,-2.4,0);
		glScalef(0.2,0.2,0.2);
		esfera1.draw(modo, r2, g2, b2, grosor);
		glPopMatrix();

		glTranslatef(0,-2.8,0);
// UNO		
		glPushMatrix();
		glRotatef(flexion1,1,0,0);			
			glPushMatrix();
			
			glScalef(0.3,8.0,0.3);
			cilindro1.draw(modo, r2, g2, b2, grosor);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0,-8.4,0);
			glScalef(0.2,0.2,0.2);
			esfera2.draw(modo, r2, g2, b2, grosor);
			glPopMatrix();

			glTranslatef(0,-8.8,0);
// DOS
			glPushMatrix();
			glRotatef(flexion2,1,0,0);
				glPushMatrix();
				
				glScalef(0.3,8.0,0.3);
				cilindro2.draw(modo, r2, g2, b2, grosor);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0,-8.4,0);
				glScalef(0.2,0.2,0.2);
				esfera3.draw(modo, r2, g2, b2, grosor);
				glPopMatrix();

				glTranslatef(0,-8.8,0);
// TRES
				glPushMatrix();
				glRotatef(flexion3,1,0,0);
					glPushMatrix();
					
					glScalef(0.3,8.0,0.3);
					cilindro3.draw(modo, r2, g2, b2, grosor);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(0,-8.4,0);
					glScalef(0.2,0.2,0.2);
					esfera4.draw(modo, r2, g2, b2, grosor);
					glPopMatrix();

                 glTranslatef(0,-8.8,0);
// CUATRO           
					
						glPushMatrix();
						
						glRotatef(flexion4,1,0,0);
						glTranslatef(0,-4,0);
						glRotatef(180.0,0,0,1);
						glScalef(0.3,4.0,0.3);
						cono1.draw(modo, r2, g2, b2, grosor);
					
					    glPopMatrix();//CUATRO
				glPopMatrix();//TRES
			glPopMatrix();// DOS
		glPopMatrix(); //UNO
}

float _tentaculos_venenosos::getFlexion1(){
		return flexion1;
}
float _tentaculos_venenosos::getFlexion2(){
		return flexion2;
}
float _tentaculos_venenosos::getFlexion3(){
		return flexion3;
}
float _tentaculos_venenosos::getFlexion4(){
		return flexion4;
}
float _tentaculos_venenosos::getMAXFlexion1(){
		return flexion1Max;
}
float _tentaculos_venenosos::getMINFlexion1(){
		return flexion1Min;
}
float _tentaculos_venenosos::getMAXFlexion2(){
		return flexion2Max;
}
float _tentaculos_venenosos::getMINFlexion2(){
		return flexion2Min;
}
float _tentaculos_venenosos::getMAXFlexion3(){
		return flexion3Max;
}
float _tentaculos_venenosos::getMINFlexion3(){
		return flexion3Min;
}
float _tentaculos_venenosos::getMAXFlexion4(){
		return flexion4Max;
}
float _tentaculos_venenosos::getMINFlexion4(){
		return flexion4Min;
}

void _tentaculos_venenosos::setFlexion1(float valor){

	if(flexion1 + valor > flexion1Max){
		flexion1 = flexion1Max;
	}else if(flexion1 + valor < flexion1Min){
		flexion1 = flexion1Min;
	}
	flexion1+=valor;

}
void _tentaculos_venenosos::setFlexion2(float valor){
	
	if(flexion2 + valor > flexion2Max){
		flexion2 = flexion2Max;
	}else if(flexion2 + valor < flexion2Min){
		flexion2 = flexion2Min;
	}
	flexion2+=valor;

}
void _tentaculos_venenosos::setFlexion3(float valor){

	if(flexion3 + valor > flexion3Max){
		flexion3 = flexion3Max;
	}else if(flexion3 + valor < flexion3Min){
		flexion3 = flexion3Min;
	}
	flexion3+=valor;

}
void _tentaculos_venenosos::setFlexion4(float valor){
	
	if(flexion4 + valor > flexion4Max){
		flexion4 = flexion4Max;
	}else if(flexion4 + valor < flexion4Min){
		flexion4 = flexion4Min;
	}
	flexion4+=valor;

}



//************************************************************************
// MEDUSA
//************************************************************************
_medusa::_medusa(){


}

float _medusa::getGiroTentaculosOrales(){
	return tentaculos_orales.getGiro();
}

void _medusa::setGiroTentaculosOrales(float valor){
	tentaculos_orales.setGiro(valor);
}


//Primer bloque
float _medusa::getFlexion11(){
	return tentaculos_venenosos1.getFlexion1();
}
float _medusa::getFlexion12(){
	return tentaculos_venenosos2.getFlexion1();
}
float _medusa::getFlexion13(){
	return tentaculos_venenosos3.getFlexion1();
}
float _medusa::getFlexion14(){
	return tentaculos_venenosos4.getFlexion1();
}
float _medusa::getFlexion15(){
	return tentaculos_venenosos5.getFlexion1();
}
float _medusa::getFlexion16(){
	return tentaculos_venenosos6.getFlexion1();
}
float _medusa::getFlexion17(){
	return tentaculos_venenosos7.getFlexion1();
}
float _medusa::getFlexion18(){
	return tentaculos_venenosos8.getFlexion1();
}

//Segundo bloque
float _medusa::getFlexion21(){
	return tentaculos_venenosos1.getFlexion2();
}
float _medusa::getFlexion22(){
	return tentaculos_venenosos2.getFlexion2();
}
float _medusa::getFlexion23(){
	return tentaculos_venenosos3.getFlexion2();
}
float _medusa::getFlexion24(){
	return tentaculos_venenosos4.getFlexion2();
}
float _medusa::getFlexion25(){
	return tentaculos_venenosos5.getFlexion2();
}
float _medusa::getFlexion26(){
	return tentaculos_venenosos6.getFlexion2();
}
float _medusa::getFlexion27(){
	return tentaculos_venenosos7.getFlexion2();
}
float _medusa::getFlexion28(){
	return tentaculos_venenosos8.getFlexion2();
}
//Tercer bloque
float _medusa::getFlexion31(){
	return tentaculos_venenosos1.getFlexion3();
}
float _medusa::getFlexion32(){
	return tentaculos_venenosos2.getFlexion3();
}
float _medusa::getFlexion33(){
	return tentaculos_venenosos3.getFlexion3();
}
float _medusa::getFlexion34(){
	return tentaculos_venenosos4.getFlexion3();
}
float _medusa::getFlexion35(){
	return tentaculos_venenosos5.getFlexion3();
}
float _medusa::getFlexion36(){
	return tentaculos_venenosos6.getFlexion3();
}
float _medusa::getFlexion37(){
	return tentaculos_venenosos7.getFlexion3();
}
float _medusa::getFlexion38(){
	return tentaculos_venenosos8.getFlexion3();
}

//Cuarto bloque
float _medusa::getFlexion41(){
	return tentaculos_venenosos1.getFlexion4();
}
float _medusa::getFlexion42(){
	return tentaculos_venenosos2.getFlexion4();
}
float _medusa::getFlexion43(){
	return tentaculos_venenosos3.getFlexion4();
}
float _medusa::getFlexion44(){
	return tentaculos_venenosos4.getFlexion4();
}
float _medusa::getFlexion45(){
	return tentaculos_venenosos5.getFlexion4();
}
float _medusa::getFlexion46(){
	return tentaculos_venenosos6.getFlexion4();
}
float _medusa::getFlexion47(){
	return tentaculos_venenosos7.getFlexion4();
}
float _medusa::getFlexion48(){
	return tentaculos_venenosos8.getFlexion4();
}

void _medusa::setFlexion1(float valor){

	tentaculos_venenosos1.setFlexion1(valor);
	tentaculos_venenosos2.setFlexion1(valor);
	tentaculos_venenosos3.setFlexion1(valor);
	tentaculos_venenosos4.setFlexion1(valor);
	tentaculos_venenosos5.setFlexion1(valor);
	tentaculos_venenosos6.setFlexion1(valor);
	tentaculos_venenosos7.setFlexion1(valor);
	tentaculos_venenosos8.setFlexion1(valor);

}
void _medusa::setFlexion2(float valor){

	tentaculos_venenosos1.setFlexion2(valor);
	tentaculos_venenosos2.setFlexion2(valor);
	tentaculos_venenosos3.setFlexion2(valor);
	tentaculos_venenosos4.setFlexion2(valor);
	tentaculos_venenosos5.setFlexion2(valor);
	tentaculos_venenosos6.setFlexion2(valor);
	tentaculos_venenosos7.setFlexion2(valor);
	tentaculos_venenosos8.setFlexion2(valor);
	
}
void _medusa::setFlexion3(float valor){

	tentaculos_venenosos1.setFlexion3(valor);
	tentaculos_venenosos2.setFlexion3(valor);
	tentaculos_venenosos3.setFlexion3(valor);
	tentaculos_venenosos4.setFlexion3(valor);
	tentaculos_venenosos5.setFlexion3(valor);
	tentaculos_venenosos6.setFlexion3(valor);
	tentaculos_venenosos7.setFlexion3(valor);
	tentaculos_venenosos8.setFlexion3(valor);	

}
void _medusa::setFlexion4(float valor){

	tentaculos_venenosos1.setFlexion4(valor);
	tentaculos_venenosos2.setFlexion4(valor);
	tentaculos_venenosos3.setFlexion4(valor);
	tentaculos_venenosos4.setFlexion4(valor);
	tentaculos_venenosos5.setFlexion4(valor);
	tentaculos_venenosos6.setFlexion4(valor);
	tentaculos_venenosos7.setFlexion4(valor);
	tentaculos_venenosos8.setFlexion4(valor);

}


void _medusa::draw(_modo modo, float r2, float g2, float b2, float grosor){
	
	glPushMatrix();
	glTranslatef(0,0,0);
	umbrela.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,0);
	tentaculos_orales.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.5,0,0);
	glRotatef(-90, 0, 1, 0);
	tentaculos_venenosos1.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9.5,0,0);
	glRotatef(90, 0, 1, 0);
	tentaculos_venenosos2.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,9.5);
	glRotatef(180, 0, 1, 0);	
	tentaculos_venenosos3.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,0,-9.5);
	tentaculos_venenosos4.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.71,0,6.71);
	glRotatef(-135, 0, 1, 0);
	tentaculos_venenosos5.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.71,0,6.71);
	glRotatef(135, 0, 1, 0);
	tentaculos_venenosos6.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.71,0,-6.71);
	glRotatef(45, 0, 1, 0);
	tentaculos_venenosos7.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.71,0,-6.71);
	glRotatef(-45, 0, 1, 0);	
	tentaculos_venenosos8.draw(modo, r2, g2, b2, grosor);
	glPopMatrix();
}