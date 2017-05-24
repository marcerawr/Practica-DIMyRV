#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Audio/Sound.hpp>

/*
int dibujaCubo(float max_x, float max_y, float max_z, float min_x, float min_y, float min_z);
int dibujaEsfera(float radio, int meridianos, int paralelos);
bool AABB(float obj1_max_x, float obj1_max_y, float obj1_max_z, float obj1_min_x, float obj1_min_y, float obj1_min_z, float obj2_max_x, float obj2_max_y, float obj2_max_z, float obj2_min_x, float obj2_min_y, float obj2_min_z);
bool esferaAABB(float AABBmax_x, float AABBmax_y, float AABBmax_z, float AABBmin_x, float AABBmin_y, float AABBmin_z);
bool esferaEsfera(float EsfRadio2, float centro_x, float centro_y, float centro_z);
*/

// Declaración de vértices los cuales se usan para los cálculos de AABB
GLfloat VertexAABB[5][3] =
{
	{ 1, 1, 1 }, //Coordenadas del V0
	{ -0.5, 1, 3 }, //Coordenadas del V0
	{ -1, 0.5, -1 }, //Coordenadas del V0
	{ -2, 1.5, -1 }, //Coordenadas del V0
	{ -1.5, -1, 1 }, //Coordenadas del V0

};
// Declaración de vértices los cuales se usan para los cálculos de SBB
GLfloat VertexSBB[5][3] =
{
	{ 5, 5, 5 }, //Coordenadas del V0
	{ 4.5, 5, 8 }, //Coordenadas del V0
	{ 3, 4.5, 3 }, //Coordenadas del V0
	{ 2, 5.5, 3 }, //Coordenadas del V0
	{ 2.5, 3, 5 }, //Coordenadas del V0

};

// Variables default:
float MinX = 65000.0;
float MaxX = -65000.0;
float MinY = 65000.0;
float MaxY = -65000.0;
float MinZ = 65000.0;
float MaxZ = -65000.0;

// Variables para movimiento:
float MoveCubeX = 0.0f;
float MoveCubeY = 0.0f;
float MoveSphereX = 0.0f;
float MoveSphereY = 0.0f;

// Variables default para el SBB
float centro[] = { 0.0, 0.0, 0.0 };
float radio = 0.0;

// variables de coloreo
int red = 0;
int green = 0.8;
int blue = 1;

void AABB(float x, float y, float z) //
{
	int i;

	//Recorrer el arreglo en X
	for (i = 0; i<5; i++)
	{
		if (VertexAABB[i][0] < MinX)
			MinX = VertexAABB[i][0];
		if (VertexAABB[i][0] > MaxX)
			MaxX = VertexAABB[i][0];
	}
	//Recorrer el arreglo en Y
	for (i = 0; i<5; i++)
	{
		if (VertexAABB[i][1] < MinY)
			MinY = VertexAABB[i][1];
		if (VertexAABB[i][1] > MaxY)
			MaxY = VertexAABB[i][1];
	}

	//Recorre el arreglo en Z
	for (i = 0; i<5; i++)
	{
		if (VertexAABB[i][2] < MinZ)
			MinZ = VertexAABB[i][2];
		if (VertexAABB[i][2] > MaxZ)
			MaxZ = VertexAABB[i][2];
	}

	GLfloat NewVertexAABB[8][3] = {
		{ MinX,MinY,MinZ },
		{ MinX,MinY,MaxZ },
		{ MinX,MaxY,MinZ },
		{ MinX,MaxY,MaxZ },
		{ MaxX,MinY,MinZ },
		{ MaxX,MinY,MaxZ },
		{ MaxX,MaxY,MinZ },
		{ MaxX,MaxY,MaxZ }
	};

	glBegin(GL_POLYGON); //LEFT
	glColor3f(1, 1, 1); //Hago que el cuadro de caja de colisión sea blanco, una vez que detecta colisión este color cambiará
	glVertex3fv(NewVertexAABB[0]);
	glVertex3fv(NewVertexAABB[1]);
	glVertex3fv(NewVertexAABB[3]);
	glVertex3fv(NewVertexAABB[2]);
	glEnd();

	glBegin(GL_POLYGON); //FRONT
	glColor3f(1, 1, 1); //glColor3f(red, green, blue);
	glVertex3fv(NewVertexAABB[1]);
	glVertex3fv(NewVertexAABB[5]);
	glVertex3fv(NewVertexAABB[8]);
	glVertex3fv(NewVertexAABB[3]);
	glEnd();

	glBegin(GL_POLYGON); //RIGHT
	glColor3f(1, 1, 1); //glColor3f(red, green, blue);
	glVertex3fv(NewVertexAABB[5]);
	glVertex3fv(NewVertexAABB[4]);
	glVertex3fv(NewVertexAABB[6]);
	glVertex3fv(NewVertexAABB[8]);
	glEnd();

	glBegin(GL_POLYGON); //BACK
	glColor3f(1, 1, 1); //glColor3f(red, green, blue);
	glVertex3fv(NewVertexAABB[4]);
	glVertex3fv(NewVertexAABB[0]);
	glVertex3fv(NewVertexAABB[2]);
	glVertex3fv(NewVertexAABB[6]);
	glEnd();

	glBegin(GL_POLYGON); //UP
	glColor3f(1, 1, 1); //glColor3f(red, green, blue);
	glVertex3fv(NewVertexAABB[3]);
	glVertex3fv(NewVertexAABB[7]);
	glVertex3fv(NewVertexAABB[6]);
	glVertex3fv(NewVertexAABB[2]);
	glEnd();

	glBegin(GL_POLYGON); //DOWN
	glColor3f(1, 1, 1); //glColor3f(red, green, blue);
	glVertex3fv(NewVertexAABB[5]);
	glVertex3fv(NewVertexAABB[1]);
	glVertex3fv(NewVertexAABB[0]);
	glVertex3fv(NewVertexAABB[4]);
	glEnd();


	//Con esto se haría la caja de colisión y se dibuja, tal vez sería quitarle la textura yo sólo ponerle un color de fondo 
	//el cual se modifique siempre y cuando haya colisión
}

void SBB(int meridianos, int paralelos) //quité float radio porque la declaré global y aquí se modifica varias veces
{
	//PRUEBA: hacerla global **revisar al inicio
	//float centro[] = {0.0, 0.0, 0.0};
	// **************************************************************************************************************************
	int k, l;

	for (l = 0; l < 5; l++) {
		//Centro en X
		centro[0] = centro[0] + VertexSBB[l][0];
		//Centro en Y
		centro[1] = centro[1] + VertexSBB[l][1];
		//CEntro en Z
		centro[2] = centro[2] + VertexSBB[l][2];
	}
	// Esto dejaría listo el centro de los vértices declarados globalmente

	//float radio = 0.0; Se prueba como global
	for (k = 0; k<5; k++)
	{
		float temp = sqrt(((centro[0] - VertexSBB[k][0])*(centro[0] - VertexSBB[k][0])) + ((centro[1] - VertexSBB[k][1])*(centro[1] - VertexSBB[k][1])) + ((centro[2] - VertexSBB[k][2])*(centro[2] - VertexSBB[k][2])));
		if (temp > radio)
			radio = temp;
	}
	// **************************************************************************************************************************

	GLuint texture = 0;

	{
		sf::Image image;
		if (!image.loadFromFile("resources/blue_marble.jpg"))
			//return EXIT_FAILURE;
			glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	double theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	//glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			//glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			//glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			//glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			//glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

int dibujaCubo(float max_x, float max_y, float max_z, float min_x, float min_y, float min_z)
{

	glBegin(GL_POLYGON);	//Front
	glColor3f(red, green, blue);			//glColor3f(1.0*color1, 0.0, 0.0);
	glVertex3f(max_x, min_y, max_z);
	glVertex3f(max_x, max_y, max_z);
	glVertex3f(min_x, max_y, max_z);
	glVertex3f(min_x, min_y, max_z);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glColor3f(red, green, blue);						//glColor3f(0.0, 0.0, 1.0*color1);
	glVertex3f(max_x, min_y, max_z);
	glVertex3f(max_x, min_y, min_z);
	glVertex3f(max_x, max_y, min_z);
	glVertex3f(max_x, max_y, max_z);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glColor3f(red, green, blue);							//glColor3f(0.0, 1.0, 0.0);
	glVertex3f(min_x, max_y, min_z);
	glVertex3f(max_x, max_y, min_z);
	glVertex3f(max_x, min_y, min_z);
	glVertex3f(min_x, min_y, min_z);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glColor3f(red, green, blue);				  //glColor3f(1.0*color1, 1.0*color1, 1.0*color1);
	glVertex3f(min_x, min_y, max_z);
	glVertex3f(min_x, max_y, max_z);
	glVertex3f(min_x, max_y, min_z);
	glVertex3f(min_x, min_y, min_z);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glColor3f(red, green, blue);			  //glColor3f(0.4*color1, 0.2*color1, 0.6*color1);
	glVertex3f(max_x, min_y, max_z);
	glVertex3f(min_x, min_y, max_z);
	glVertex3f(min_x, min_y, min_z);
	glVertex3f(max_x, min_y, min_z);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glColor3f(red, green, blue);						  //glColor3f(0.8*color1, 0.2*color1, 0.4*color1);
	glVertex3f(max_x, max_y, max_z);
	glVertex3f(max_x, max_y, min_z);
	glVertex3f(min_x, max_y, min_z);
	glVertex3f(min_x, max_y, max_z);
	glEnd();
	return 0;
}

int dibujaEsfera(float radio, int meridianos, int paralelos)
{
	GLuint texture = 0;

	{
		sf::Image image;
		if (!image.loadFromFile("resources/blue_marble.jpg"))
			return EXIT_FAILURE;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	double theta, phi;

	float ctext_s = 1.0 / meridianos;
	float ctext_t = 1.0 / paralelos;

	//glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	float v1[] = { 0.0, 0.0, 0.0 };
	float v2[] = { 0.0, 0.0, 0.0 };
	float v3[] = { 0.0, 0.0, 0.0 };
	float v4[] = { 0.0, 0.0, 0.0 };
	int i, j;
	float angulom, angulop;
	angulom = 2 * 3.141592654 / meridianos;
	angulop = 3.141592654 / paralelos;
	for (i = 0; i<meridianos; i++)
	{
		for (j = 0; j<paralelos; j++)
		{
			v1[0] = radio*cos(angulom*i)*sin(angulop*j);
			v1[1] = radio*cos(angulop*j);
			v1[2] = radio*sin(angulom*i)*sin(angulop*j);

			v2[0] = radio*cos(angulom*i)*sin(angulop*(j + 1));
			v2[1] = radio*cos(angulop*(j + 1));
			v2[2] = radio*sin(angulom*i)*sin(angulop*(j + 1));

			v3[0] = radio*cos(angulom*(i + 1))*sin(angulop*(j + 1));
			v3[1] = radio*cos(angulop*(j + 1));
			v3[2] = radio*sin(angulom*(i + 1))*sin(angulop*(j + 1));

			v4[0] = radio*cos(angulom*(i + 1))*sin(angulop*j);
			v4[1] = radio*cos(angulop*j);
			v4[2] = radio*sin(angulom*(i + 1))*sin(angulop*j);

			glBegin(GL_POLYGON);
			glNormal3fv(v1);
			glColor3f(red, green, blue);//glTexCoord2f(ctext_s*i, -ctext_t*j);
			glVertex3fv(v1);
			glNormal3fv(v2);
			glColor3f(red, green, blue);//glTexCoord2f(ctext_s*i, -ctext_t*(j + 1));
			glVertex3fv(v2);
			glNormal3fv(v3);
			glColor3f(red, green, blue);//glTexCoord2f(ctext_s*(i + 1), -ctext_t*(j + 1));
			glVertex3fv(v3);
			glNormal3fv(v4);
			glColor3f(red, green, blue);//glTexCoord2f(ctext_s*(i + 1), -ctext_t*j);
			glVertex3fv(v4);
			glEnd();
		}
	}
}

// ************************************************** Se puede usar
int ColAABB(float obj1_max_x, float obj1_max_y, float obj1_max_z, float obj1_min_x, float obj1_min_y, float obj1_min_z, float obj2_max_x, float obj2_max_y, float obj2_max_z, float obj2_min_x, float obj2_min_y, float obj2_min_z)
{
	bool colision_x, colision_y, colision_z;
	//////////////////EN X/////////////////////////
	if (obj2_max_x < obj1_min_x)//no hay colision 
		colision_x = false;
	if (obj1_min_x <= obj2_max_x && obj1_min_x >= obj2_min_x)//si hay colison
		colision_x = true;
	if (obj1_min_x <= obj2_min_x && obj2_min_x <= obj1_max_x)//si hay colison
		colision_x = true;
	if (obj1_max_x < obj2_min_x)// no hay colision
		colision_x = false;
	//////////////////EN Y/////////////////////////
	if (obj2_max_y < obj1_min_y)//no hay colision 
		colision_y = false;
	if (obj1_min_y <= obj2_max_y && obj1_min_y >= obj2_min_y)//si hay colison
		colision_y = true;
	if (obj1_min_y <= obj2_min_y && obj2_min_y <= obj1_max_y)//si hay colison
		colision_y = true;
	if (obj1_max_y < obj2_min_y)// no hay colision
		colision_y = false;
	/////////////////EN Z//////////////////
	if (obj2_max_z < obj1_min_z)//no hay colision 
		colision_z = false;
	if (obj1_min_z <= obj2_max_z && obj1_min_z >= obj2_min_z)//si hay colison
		colision_z = true;
	if (obj1_min_z <= obj2_min_z && obj2_min_z <= obj1_max_z)//si hay colison
		colision_z = true;
	if (obj1_max_z < obj2_min_z)// no hay colision
		colision_z = false;

	if (colision_x == true && colision_y == true && colision_z == true)
	{
		printf("AABB vs AABB: Si \t");

		return true;
	}
	else
	{
		printf("AABB vs AABB: No \t");

		return false;
	}

}

int ColEsferaAABB(float AABBmax_x, float AABBmax_y, float AABBmax_z, float AABBmin_x, float AABBmin_y, float AABBmin_z)
{

	float d = 0, s = 0;

	float DistanciaM = 0;
	float temp;
	float radio;
	int i, numeroV = 4;
	float centrox[] = { 0, 0 };
	float centroy[] = { 0, 0 };
	float centroz[] = { 0, 0 };

	float EsfRadio, EsfCentro_x, EsfCentro_y, EsfCentro_z;
	
	for (i = 0; i < numeroV; i++)
	{
		centrox[0] += VertexSBB[i][0];
		centroy[0] += VertexSBB[i][1];
		centroz[0] += VertexSBB[i][2];
	}

	centrox[0] /= numeroV;
	centroy[0] /= numeroV;
	centroz[0] /= numeroV;


	for (i = 0; i < numeroV; i++)
	{
		temp = sqrt((VertexSBB[i][0] - centrox[0])*(VertexSBB[i][0] - centrox[0]) + (VertexSBB[i][1] - centroy[0])*(VertexSBB[i][1] - centroy[0]) + (VertexSBB[i][2] - centroz[0])*(VertexSBB[i][2] - centroz[0]));

		if (DistanciaM < temp)
		{
			DistanciaM = temp;
		}
	}
	radio = DistanciaM;
	EsfRadio = radio;

	EsfCentro_x = centrox[0]+MoveSphereX;
	EsfCentro_y = centroy[0]+MoveSphereY; 
	EsfCentro_z = centroz[0];

	// Comprobamos si el centro de la esfera está dentro del AABB
	if (EsfCentro_x > AABBmin_x+MoveCubeX && EsfCentro_x < AABBmax_x+MoveCubeX+25) {
		if (EsfCentro_y > AABBmin_y+MoveCubeY && EsfCentro_y < AABBmax_y+MoveCubeY+25) {
			if (EsfCentro_z > AABBmin_z && EsfCentro_z < AABBmax_z) {
				return true;
			}
		}
	}

	// Comprobamos si la esfera y el AABB se intersectan
	if (EsfCentro_x < AABBmin_x+MoveCubeX) {
		s = EsfCentro_x - AABBmin_x+MoveCubeX;
		d += s * s;
	}
	else if (EsfCentro_x > AABBmax_x+MoveCubeX+50) {
		s = EsfCentro_x - AABBmax_x+MoveCubeX+50;
		d += s * s;
	}

	if (EsfCentro_y < AABBmin_y+MoveCubeY-15) {
		s = EsfCentro_y - AABBmin_y+MoveCubeY-15;
		d += s * s;
	}
	else if (EsfCentro_y > AABBmax_y+MoveCubeY+28) {
		s = EsfCentro_y - AABBmax_y+MoveCubeY+28;
		d += s * s;
	}

	if (EsfCentro_z < AABBmin_z) {
		s = EsfCentro_z - AABBmin_z;
		d += s * s;
	}
	else if (EsfCentro_z > AABBmax_z) {
		s = EsfCentro_z - AABBmax_z;
		d += s * s;
	}

	if (d <= EsfRadio * EsfRadio) {
		return true;
	}
	else
	{
		return false;
	}
}

int ColSBB(float EsfRadio2, float centro_x, float centro_y, float centro_z)
{

	float d = 0, s = 0;
	/*glPushMatrix();
	glTranslatef(centro_x, centro_y, centro_z);
	dibujaEsfera(25, 10, 10);
	glPopMatrix();*/

	///calculo esfera////

	float x[2][30];
	float y[2][30];
	float z[2][30];
	x[0][0] = 0;
	y[0][0] = 0;
	z[0][0] = 0;
	x[0][1] = 100;
	y[0][1] = 0;
	z[0][1] = 200;
	x[0][2] = 200;
	y[0][2] = 0;
	z[0][2] = 0;
	x[0][3] = 100;
	y[0][3] = 200;
	z[0][3] = 100;
	x[1][0] = 0;
	y[1][0] = 0;
	z[1][0] = 0;
	x[1][1] = 100;
	y[1][1] = 0;
	z[1][1] = 200;
	x[1][2] = 200;
	y[1][2] = 0;
	z[1][2] = 0;
	x[1][3] = 100;
	y[1][3] = 200;
	z[1][3] = 100;


	float DistanciaM = 0;
	float temp;
	float radio;
	int i, numeroV = 4;
	float centrox[] = { 0, 0 };
	float centroy[] = { 0, 0 };
	float centroz[] = { 0, 0 };

	float EsfRadio, EsfCentro_x, EsfCentro_y, EsfCentro_z;

	for (i = 0; i < numeroV; i++)
	{
		centrox[0] += x[0][i];
		centroy[0] += y[0][i];
		centroz[0] += z[0][i];
	}
	centrox[0] /= numeroV;
	centroy[0] /= numeroV;
	centroz[0] /= numeroV;


	for (i = 0; i < numeroV; i++)
	{
		temp = sqrt((x[0][i] - centrox[0])*(x[0][i] - centrox[0]) + (y[0][i] - centroy[0])*(y[0][i] - centroy[0]) + (z[0][i] - centroz[0])*(z[0][i] - centroz[0]));
		if (DistanciaM < temp)
		{
			DistanciaM = temp;
		}
	}
	radio = DistanciaM;
	EsfRadio = radio / 8;

	EsfCentro_x = centrox[0];
	EsfCentro_y = centroy[0]; //+ mov_esfera;
	EsfCentro_z = centroz[0];

	///calculo esfera///

	glPushMatrix();
	//glTranslatef(EsfCentro_x, EsfCentro_y, EsfCentro_z);
	//glTranslatef(MoveSphereX, MoveSphereY, 0);
	//dibujaEsfera(EsfRadio, 10, 10);
	glPopMatrix();


	float distancia = sqrt(((EsfCentro_x - centro_x) * (EsfCentro_x - centro_x)) + ((EsfCentro_y - centro_y)*(EsfCentro_y - centro_y)) + ((EsfCentro_z - centro_z)*(EsfCentro_z - centro_z)));
	float distanciaminima = EsfRadio + EsfRadio2;
	if (distancia < distanciaminima) {
		printf("SBB vs SBB: Si		");
		return true;
	}
	else
		printf("SBB vs SBB: No		");
	return false;

}

int main()
{

	// **** Buffer de profundidad ****
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// **** Creación de ventana principal ****
	sf::RenderWindow window(sf::VideoMode(800, 600), "DIMRV", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	// **** Imagen de fondo ****
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("resources/LandscapeMountains_01.jpg"))
		return EXIT_FAILURE;
	sf::Sprite background(backgroundTexture);

	// **** Imagen de fondo 2****
	sf::Texture backgroundTexture2;
	if (!backgroundTexture2.loadFromFile("resources/castle.jpg"))
		return EXIT_FAILURE;
	sf::Sprite background2(backgroundTexture2);

	//Variable para cambio de fondo

	sf::Sprite fondo(background);


	// **** Texto en la ventana ****
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;
	sf::Text text("DIMRV / PRACTICA 02", font);
	text.setFillColor(sf::Color(255, 255, 255, 255));
	text.setPosition(250.f, 550.f);

	//********Figuras para colisión*******
	sf::CircleShape sphere;
	sphere.setRadius(100);
	sphere.setPosition(4, 0);
	sphere.setFillColor(sf::Color(255, 0, 255, 200));

	sf::CircleShape sphere2;
	sphere2.setRadius(100);
	sphere2.setPosition(580, 400);
	sphere2.setFillColor(sf::Color(255, 255, 0, 200));

	sf::RectangleShape caja;
	caja.setSize(sf::Vector2f(100, 100));
	caja.setFillColor(sf::Color(255, 0, 0, 255));
	caja.setPosition(520, 5);

	//********Implementación de audio**********
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("cuboHielo.wav"))
		return -1;
	//return 0;
	sf::Sound cuboHielo;
	cuboHielo.setBuffer(buffer);

	sf::Music music;
	if (!music.openFromFile("bow.ogg"))
		return -1; // error
	music.play();


	sf::Music music2;
	if (!music2.openFromFile("bow2.ogg"))
		return -1; // error


	sf::Music music3;
	if (!music3.openFromFile("bow3.ogg"))
		return -1; // error




				   // Make the window the active target for OpenGL calls
	window.setActive();

	// Load an OpenGL texture.
	// We could directly use a sf::Texture as an OpenGL texture (with its Bind() member function),
	// but here we want more control on it (generate mipmaps, ...) so we create a new one from an image
	GLuint texture = 0;

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);

	// Disable lighting
	glDisable(GL_LIGHTING);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

	// Bind the texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Definición de un cubo (3D = 6 caras hechas por 2 triángulos cada uno compuesto de 3 vertices)
	//Arreglo de vértices y coordenadas de texturizado de un cubo:


	// Enable position and texture coordinates vertex components
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube); //Ubicación de las coordenadas de los vértices de la constante cube
	//glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3); //Ubicación de las coordenadas en la constante cube

	//															   // Disable normal and color vertex components
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	// Create a clock for measuring the time elapsed
	sf::Clock clock;

	// Start game loop
	while (window.isOpen())
	{

		// Process events
		sf::Event event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			music.play();
			music2.stop();
			music3.stop();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			music2.play();
			music.stop();
			music3.stop();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
		{
			music3.play();
			music2.stop();
			music.stop();
		}

		while (window.pollEvent(event))
		{

			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			// Escape key: exit
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();


			// Adjust the viewport when the window is resized
			if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);

			//
			if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Left))
			{
				cuboHielo.play();
				//glTranslatef(0.0f, 10.0f, 0.0f);
			}

			if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Right))
			{
				printf("*************************************************************\n");
				printf("********************** PRACTICA 02 **************************\n");
				printf("****************** Programa elaborado por: ******************\n");
				printf("****************** - Alcántara Reséndiz Liliana *************\n");
				printf("****************** - Arreola Camacho Marcela ****************\n");
				printf("****************** - Garduño Magaña Mauricio ****************\n");
				printf("****************** - Rosales Pérez Iván *********************\n");
				printf("**** Diseño de Interfaces, Multimedia y Realidad Virtual ****\n");
				printf("********************** Semestre 2017-2 **********************\n");
				printf("*************************************************************\n");
				printf("\n");

			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
			{
				fondo = background2;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
			{
				fondo = background;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			{
				MoveCubeY = MoveCubeY + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{
				MoveCubeY = MoveCubeY - 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			{
				MoveCubeX = MoveCubeX - 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				MoveCubeX = MoveCubeX + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			{
				MoveSphereX = MoveSphereX - 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
			{
				MoveSphereX = MoveSphereX + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
			{
				MoveSphereY = MoveSphereY + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			{
				MoveSphereY = MoveSphereY - 2.0f;
			}

		}


		// Draw the background
		window.pushGLStates();
		window.draw(fondo);
		//window.draw(sphere);
		//window.draw(sphere2);
		//window.draw(caja);
		window.popGLStates();

		// Clear the depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);


		// ***********************************************************************************************************
		//Figuras estáticas
		glPushMatrix();
		glTranslatef(60, -23, 0);
		glColor3f(1, 0, 0);
		dibujaCubo(25, 25, 25, 0, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-80, 55, 0);
		dibujaEsfera(25, 25, 25);
		glPopMatrix();
		// ***********************************************************************************************************

		glPushMatrix();
		// Apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(MoveCubeX, MoveCubeY, -100.f);
		dibujaCubo(25, 25, 25, 0, 0, 0);
		//AABB(25, 25, 25);
		//ColAABB(25,25,25,0,0,0,MoveCubeX+25,MoveCubeY+25,25,MoveCubeX,MoveCubeY,0);
		ColAABB(85, 2, 25, 60, -23, 0, MoveCubeX + 25, MoveCubeY + 25, 25, MoveCubeX, MoveCubeY, 0);
		glPopMatrix();


		glPushMatrix();
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(MoveSphereX-30, MoveSphereY, 0);
		dibujaEsfera(25,10,10);
		glPopMatrix();
		ColSBB(25, -45, 55, 0);
		
		glPopMatrix();

		//Comprobamoos la colision de Esfera y caja
		glPushMatrix();
		if (ColEsferaAABB(25, 25, 25, 0, 0, 0) == true) {
			printf("SBB vs AABB: Si\t \n");
		}
		else {
			printf("SBB vs AABB: No\t \n");
		}
		glPopMatrix();



		// Draw some text on top of our OpenGL object
		window.pushGLStates();
		window.draw(text);
		window.popGLStates();



		// Finally, display the rendered frame on screen
		window.display();
	}

	// Don't forget to destroy our texture
	glDeleteTextures(1, &texture);

	return EXIT_SUCCESS;
}