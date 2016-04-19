#pragma once

#include <string>
#include <cassert>
#include "logger.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "texture.hpp"
//#include "SDL_opengl.h"
//#include "include/SDL2-2.0.4/include/SDL.h"
//#include "include/SDL2_image-2.0.1/include/SDL_image.h"

class Graphics{
public:
	Graphics();
	~Graphics();
	void run();
private:
	bool init();
	bool init_gl();
	int count_fps();
	Logger * m_log;
	std::string m_logfile_name = "Graphics.txt";
	std::string m_window_name = "A window";
	SDL_Window * m_sdl_window = nullptr;
	SDL_Surface * m_sdl_surface = nullptr;
	SDL_Renderer * m_sdl_renderer = nullptr;
	SDL_GLContext m_sdl_glcontext;

	int m_screen_height = 640;
	int m_screen_width = 480;
	bool m_successful_init = true;
};