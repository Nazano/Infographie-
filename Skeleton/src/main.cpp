//SDL Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

//OpenGL Libraries
#include <GL/glew.h>
#include <GL/gl.h>

//GML libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Objloader.h"

#include "logger.h"

#define WIDTH     800
#define HEIGHT    600
#define FRAMERATE 60
#define TIME_PER_FRAME_MS  (1.0f/FRAMERATE * 1e3)
#define INDICE_TO_PTR(x) ((void*)(x))


Shader* loadShader(std::string name) {
	FILE* vertFile = fopen(("bin\\Shaders\\" +  name + ".vert").c_str(), "r");
	FILE* fragFile = fopen(("bin\\Shaders\\" + name + ".frag").c_str(), "r");

	if (vertFile == NULL) { ERROR("Erreur vertex file"); }
	if (fragFile == NULL) { ERROR("Erreur fragment file"); }

	auto shader = Shader::loadFromFiles(vertFile, fragFile);

	fclose(vertFile);
	fclose(fragFile);

	return shader;
}

int main(int argc, char *argv[])
{
	////////////////////////////////////////
	//SDL2 / OpenGL Context initialization : 
	////////////////////////////////////////

	//Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		ERROR("The initialization of the SDL failed : %s\n", SDL_GetError());
		return 0;
	}

	//Create a Window
	SDL_Window* window = SDL_CreateWindow("VR Camera",                           //Titre
		SDL_WINDOWPOS_UNDEFINED,               //X Position
		SDL_WINDOWPOS_UNDEFINED,               //Y Position
		WIDTH, HEIGHT,                         //Resolution
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); //Flags (OpenGL + Show)

//Initialize OpenGL Version (version 3.0)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//Initialize the OpenGL Context (where OpenGL resources (Graphics card resources) lives)
	SDL_GLContext context = SDL_GL_CreateContext(window);

	//Tells GLEW to initialize the OpenGL function with this version
	glewExperimental = GL_TRUE;
	glewInit();


	//Start using OpenGL to draw something on screen
	glViewport(0, 0, WIDTH, HEIGHT); //Draw on ALL the screen

	//The OpenGL background color (RGBA, each component between 0.0f and 1.0f)
	glClearColor(0.35, 0.67, 0.81, 1.0); //Full Black

	glEnable(GL_DEPTH_TEST); //Active the depth test

	//TODO
	//From here you can load your OpenGL objects, like VBO, Shaders, etc.
	//TODO

	auto shader = loadShader("color");
	auto cam = Camera(shader->getProgramID());
	
	Objloader obj_filets("..\\filets.obj");
	Shape filets = obj_filets.getShape();
	filets.init(shader->getProgramID());
	filets.load_texture("..\\net.png");
	

	Objloader obj_cage("..\\cage.obj");
	Shape cage = obj_cage.getShape();
	cage.init(shader->getProgramID(), cam.getViewMat());
	cage.load_texture("..\\cage.jpg");
	

	Objloader obj_terrain("..\\terrain.obj");
	Shape terrain = obj_terrain.getShape();
	terrain.init(shader->getProgramID());
	terrain.load_texture("..\\fussballfeld_03_c.jpg");
	
	
	

	
	bool isOpened = true;
	auto cpt = 0.0f;

	//Main application loop
	while (isOpened)
	{
		//Time in ms telling us when this frame started. Useful for keeping a fix framerate
		uint32_t timeBegin = SDL_GetTicks();

		//Fetch the SDL events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					isOpened = false;
					break;
				default:
					break;
				}
				break;
				//We can add more event, like listening for the keyboard or the mouse. See SDL_Event documentation for more details
			}
		}

		//Clear the screen : the depth buffer and the color buffer
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//TODO rendering

		glUseProgram(shader->getProgramID());
		
		filets.show();
		terrain.show();
		cage.anim(1);
		cage.show();

		//cam.move(cpt);
		cpt += 0.1;
	
		glUseProgram(0);

		//Display on screen (swap the buffer on screen and the buffer you are drawing on)
		SDL_GL_SwapWindow(window);

		//Time in ms telling us when this frame ended. Useful for keeping a fix framerate
		uint32_t timeEnd = SDL_GetTicks();

		//We want FRAMERATE FPS
		if (timeEnd - timeBegin < TIME_PER_FRAME_MS)
			SDL_Delay(TIME_PER_FRAME_MS - (timeEnd - timeBegin));
	}

	//Free everything
	if (context != NULL)
		SDL_GL_DeleteContext(context);
	if (window != NULL)
		SDL_DestroyWindow(window);

	delete shader;

	return 0;
}
