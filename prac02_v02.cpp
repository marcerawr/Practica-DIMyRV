#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Audio/Sound.hpp>

float movcubox = 0.0f;
float movcubey = 0.0f;
float movespherex = 0.0f;
float movespherey = 0.0f;

void DibujaCubo()
{
	
	static const GLfloat cube[] =
	{
		// positions    // texture coordinates
		-20, -20, -20,  0, 0,
		-20,  20, -20,  1, 0,
		-20, -20,  20,  0, 1,
		-20, -20,  20,  0, 1,
		-20,  20, -20,  1, 0,
		-20,  20,  20,  1, 1,

		20, -20, -20,  0, 0,
		20,  20, -20,  1, 0,
		20, -20,  20,  0, 1,
		20, -20,  20,  0, 1,
		20,  20, -20,  1, 0,
		20,  20,  20,  1, 1,

		-20, -20, -20,  0, 0,
		20, -20, -20,  1, 0,
		-20, -20,  20,  0, 1,
		-20, -20,  20,  0, 1,
		20, -20, -20,  1, 0,
		20, -20,  20,  1, 1,

		-20,  20, -20,  0, 0,
		20,  20, -20,  1, 0,
		-20,  20,  20,  0, 1,
		-20,  20,  20,  0, 1,
		20,  20, -20,  1, 0,
		20,  20,  20,  1, 1,

		-20, -20, -20,  0, 0,
		20, -20, -20,  1, 0,
		-20,  20, -20,  0, 1,
		-20,  20, -20,  0, 1,
		20, -20, -20,  1, 0,
		20,  20, -20,  1, 1,

		-20, -20,  20,  0, 0,
		20, -20,  20,  1, 0,
		-20,  20,  20,  0, 1,
		-20,  20,  20,  0, 1,
		20, -20,  20,  1, 0,
		20,  20,  20,  1, 1
	};

	// Enable position and texture coordinates vertex components
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube); //Ubicación de las coordenadas de los vértices de la constante cube
	//glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3); //Ubicación de las coordenadas en la constante cube

					  /*   // Disable normal and color vertex components
						   glDisableClientState(GL_NORMAL_ARRAY);
						   glDisableClientState(GL_COLOR_ARRAY);
												   */
								   // Draw the cube
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

int dibujaEsfera()
{
	GLuint texture = 0;
	float radio = 30;
	int paralelos = 12;
	int meridianos = 10;
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

	float ang1, ang2;
	float a[3], b[3], c[3], d[3];
	float delta1, delta2, deltaT;
	float PI = 3.141516;

	delta1 = 180.0f / paralelos;
	delta2 = 360.0f / meridianos;
	deltaT = 1.0 / paralelos;
	float t1, t2, s1, s2;
	glEnable(GL_TEXTURE_2D);

	//Semiesfera superior
	for (int i = 0; i < paralelos / 2; i++)
	{
		t1 = 0.15 + i*deltaT;
		t2 = 0.15 + (i + 1.0)*deltaT;
		s1 = 0.0;
		s2 = 1.0;

		for (int j = 0; j <= meridianos; j++)
		{
			ang1 = i*delta1;
			ang2 = j*delta2;
			a[0] = radio*(float)cos(ang1*PI / 180.0f)*(float)cos(ang2*PI / 180.0f);
			a[1] = radio*(float)sin(ang1*PI / 180.0f);
			a[2] = radio*(float)cos(ang1*PI / 180.0f)*(float)sin(ang2*PI / 180.0f);

			ang1 = (i + 1)*delta1;
			ang2 = j*delta2;
			b[0] = radio*(float)cos(ang1*PI / 180.0f)*(float)cos(ang2*PI / 180.0f);
			b[1] = radio*(float)sin(ang1*PI / 180.0f);
			b[2] = radio*(float)cos(ang1*PI / 180.0f)*(float)sin(ang2*PI / 180.0f);
			ang1 = (i + 1)*delta1;
			ang2 = (j + 1)*delta2;
			c[0] = radio*(float)cos(ang1*PI / 180.0f)*(float)cos(ang2*PI / 180.0f);
			c[1] = radio*(float)sin(ang1*PI / 180.0f);
			c[2] = radio*(float)cos(ang1*PI / 180.0f)*(float)sin(ang2*PI / 180.0f);
			ang1 = i*delta1;
			ang2 = (j + 1)*delta2;
			d[0] = radio*(float)cos(ang1*PI / 180.0f)*(float)cos(ang2*PI / 180.0f);
			d[1] = radio*(float)sin(ang1*PI / 180.0f);
			d[2] = radio*(float)cos(ang1*PI / 180.0f)*(float)sin(ang2*PI / 180.0f);

			glBegin(GL_QUADS);
			glNormal3f(a[0], a[1], a[2]);
			glTexCoord2f(s1 * 2, t1);
			glVertex3f(a[0], a[1], a[2]);

			glNormal3f(b[0], b[1], b[2]);
			glTexCoord2f(s1 * 2, t2);
			glVertex3f(b[0], b[1], b[2]);

			glNormal3f(c[0], c[1], c[2]);
			glTexCoord2f(s2 * 2, t2);
			glVertex3f(c[0], c[1], c[2]);

			glNormal3f(d[0], d[1], d[2]);
			glTexCoord2f(s2 * 2, t1);
			glVertex3f(d[0], d[1], d[2]);

			glNormal3f(a[0], -a[1], a[2]);
			glTexCoord2f(s1*2,t1);
			glVertex3f(a[0], -a[1], a[2]);

			glNormal3f(d[0], -d[1], d[2]);
			glTexCoord2f(s2 * 2, t1);
			glVertex3f(d[0], -d[1], d[2]);

			glNormal3f(c[0], -c[1], c[2]);
			glTexCoord2f(s2 * 2, t1);
			glVertex3f(c[0], -c[1], c[2]);

			glNormal3f(b[0], -b[1], b[2]);
			glTexCoord2f(s1 * 2, t2);
			glVertex3f(b[0], -b[1], b[2]);
			glEnd();
		}
	}
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
	caja.setFillColor(sf::Color(255,0,0,255));
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
	static const GLfloat cube[] =
	{
		// positions    // texture coordinates
		-20, -20, -20,  0, 0,
		-20,  20, -20,  1, 0,
		-20, -20,  20,  0, 1,
		-20, -20,  20,  0, 1,
		-20,  20, -20,  1, 0,
		-20,  20,  20,  1, 1,

		20, -20, -20,  0, 0,
		20,  20, -20,  1, 0,
		20, -20,  20,  0, 1,
		20, -20,  20,  0, 1,
		20,  20, -20,  1, 0,
		20,  20,  20,  1, 1,

		-20, -20, -20,  0, 0,
		20, -20, -20,  1, 0,
		-20, -20,  20,  0, 1,
		-20, -20,  20,  0, 1,
		20, -20, -20,  1, 0,
		20, -20,  20,  1, 1,

		-20,  20, -20,  0, 0,
		20,  20, -20,  1, 0,
		-20,  20,  20,  0, 1,
		-20,  20,  20,  0, 1,
		20,  20, -20,  1, 0,
		20,  20,  20,  1, 1,

		-20, -20, -20,  0, 0,
		20, -20, -20,  1, 0,
		-20,  20, -20,  0, 1,
		-20,  20, -20,  0, 1,
		20, -20, -20,  1, 0,
		20,  20, -20,  1, 1,

		-20, -20,  20,  0, 0,
		20, -20,  20,  1, 0,
		-20,  20,  20,  0, 1,
		-20,  20,  20,  0, 1,
		20, -20,  20,  1, 0,
		20,  20,  20,  1, 1
	};

	// Enable position and texture coordinates vertex components
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube); //Ubicación de las coordenadas de los vértices de la constante cube
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3); //Ubicación de las coordenadas en la constante cube

																   // Disable normal and color vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

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
				movcubey = movcubey + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{
				movcubey = movcubey - 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			{
				movcubox = movcubox - 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				movcubox = movcubox + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			{
				movespherex = movespherex - 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
			{
				movespherex = movespherex + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
			{
				movespherey = movespherey + 2.0f;
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			{
				movespherey = movespherey - 2.0f;
			}

		}


		// Draw the background
		window.pushGLStates();
		window.draw(fondo);
		//window.draw(sphere);
		//window.draw(sphere2);
		//window.draw(caja);
		window.popGLStates();

		window.pushGLStates();
		glTranslatef(50, 0, 0);
		DibujaCubo();
		window.popGLStates();

		window.pushGLStates();
		glTranslatef(0, 100, 0);
		dibujaEsfera();
		window.popGLStates();

		// Clear the depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
			// We get the position of the mouse cursor, so that we can move the box accordingly
			//float x = sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
			//float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;

			//Salvamos las coordenadas.
		//	float x1 = x;
	//			printf("x = %f  - y = %d ", x1, y1); //Ver las coordenadas.

	

			// Apply some transformations
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(movcubox, movcubey, -100.f);	

			// Draw the cube
			glDrawArrays(GL_TRIANGLES, 0, 36);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(movespherex, movespherey, 0);
		dibujaEsfera();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(90, -40, 0);
		DibujaCubo();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-80, 55, 0);
		dibujaEsfera();
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
