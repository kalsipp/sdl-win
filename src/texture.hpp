#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "logger.hpp"
class Texture {
public:
	Texture(SDL_Renderer *);
	~Texture();
	bool load_from_file(const std::string & path);
	bool load_from_rendered_text(const std::string & texture_text, SDL_Color text_color);
	void free();
	void render(int x, int y, SDL_Rect * clip = nullptr);
	void set_color(Uint8 red, Uint8 green, Uint8 blue);
	void set_blendmode(SDL_BlendMode blending);
	void set_font(const std::string & path);
	void set_alpha(Uint8 alpha);
	void resize(int x, int y);
	int get_width();
	int get_height();

private:
	SDL_Texture * m_texture = nullptr;
	SDL_Surface * m_surface = nullptr;
	TTF_Font * m_font = nullptr;
	int m_width = 0;
	int m_height = 0;
	int m_scale_x = 1;
	int m_scale_y = 1;
	Logger * m_log = nullptr;
	SDL_Renderer * m_sdl_renderer;
	std::string m_logfile_name = "log_Texture";

};