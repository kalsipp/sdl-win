#include "texture.hpp"
#include <cassert>
#include <stdlib.h>
Texture::Texture(SDL_Renderer * rend) {
	m_log = new Logger(m_logfile_name + std::to_string(rand()%1000) + ".txt");
	m_log->log("Texture constructed");
	m_sdl_renderer = rend;
}
Texture::~Texture() {
	free();
	TTF_CloseFont(m_font);
	m_log->log("Texture destructed");
	delete m_log;
}

bool Texture::load_from_file(const std::string & path) {
	m_log->log("Loading new texture from file" + path); 
	free();
	SDL_Texture * new_texture = nullptr;
	m_surface = IMG_Load(path.c_str()); 
	m_log->log("Image size: " + std::to_string(m_surface->w) + "w, "+ std::to_string(m_surface->h) +"h.");
	if (m_surface == nullptr) {
		m_log->log("Unable to load image " + path + " SDL Error: " + SDL_GetError() + " (texture)"); 
	}
	else {

		SDL_PixelFormat * px = m_surface->format;
		SDL_Surface * loaded = m_surface;
		SDL_Surface *out = SDL_CreateRGBSurface(0, 1, 1, loaded->format->BitsPerPixel, loaded->format->Rmask, loaded->format->Gmask, loaded->format->Bmask, loaded->format->Amask);
		SDL_BlitScaled(m_surface, 0, out, 0);
		new_texture = SDL_CreateTextureFromSurface(m_sdl_renderer, out);

		if (new_texture == nullptr) {
			m_log->log("Unable to create texture from " + path + "! SDL Error: " + SDL_GetError());
		}
		else {
			m_width = m_surface->w;
			m_height = m_surface->h;
			
		}
		//SDL_FreeSurface(loaded_surface);
		m_texture = new_texture;
	}
	return m_texture != nullptr;
}

bool Texture::load_from_rendered_text(const std::string & texture_text, SDL_Color text_color) {
	free();

	SDL_Surface * textsurface = TTF_RenderText_Solid(m_font, texture_text.c_str(), text_color);
	if (textsurface == nullptr) {
		m_log->log("Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()));
	}
	else {
		m_texture = SDL_CreateTextureFromSurface(m_sdl_renderer, textsurface);
		if (m_texture == nullptr) {
			m_log->log("Unable to create texture from rendered text! SDL Error: " + std::string(SDL_GetError()));
		}
		else {
			m_width = textsurface->w;
			m_height = textsurface->h;
		}
		SDL_FreeSurface(textsurface);
	}
	return m_texture != nullptr;
}

void Texture::free() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect * clip) {
	SDL_Rect renderquad = { x,y,m_width, m_height };

	if (clip != nullptr) {
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}

	SDL_RenderCopy(m_sdl_renderer, m_texture, clip, &renderquad);
}

void Texture::resize(int x, int y){
	SDL_Rect stretchrect;
	stretchrect.x = 0;
	stretchrect.y = 0;
	stretchrect.w = x;
	stretchrect.y = y;
	//SDL_Surface * newsurf;
	SDL_BlitScaled(m_surface, 0, m_surface, &stretchrect);
	//SDL_FreeSurface(m_surface);
	//m_surface = newsurf;
	SDL_DestroyTexture(m_texture);
	m_texture = SDL_CreateTextureFromSurface(m_sdl_renderer, m_surface);
	m_width = m_surface->w;
	m_height = m_surface->h;

}

int Texture::get_height() {
	return m_height;
}
int Texture::get_width() {
	return m_width;
}

void Texture::set_color(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void Texture::set_alpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(m_texture, alpha);
}
void Texture::set_blendmode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(m_texture, blending);
}
void Texture::set_font(const std::string & path) {
	if (m_font != nullptr) {
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}
	m_font = TTF_OpenFont(("fonts\\" + path).c_str(), 28);
	if (m_font == nullptr)
	{
		m_log->log("Failed to load lazy font! SDL_ttf Error: " + std::string(TTF_GetError()));
	}
}
