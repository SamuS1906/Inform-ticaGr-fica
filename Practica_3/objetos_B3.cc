//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"


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
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
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

void _triangulos3D::draw_solido(float r, float g, float b)
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

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
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

//
// Cilindro para paso de rueda
//


//
// Chasis parte frontal derecha (con paso de rueda) 
//
_paso_de_rueda_der::_paso_de_rueda_der(){

}

void _paso_de_rueda_der(_modo modo, float r2, float g2, float b2, float grosor){

}