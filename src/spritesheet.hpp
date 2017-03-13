#pragma once
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <chrono>
#include <vector>
#include <cassert>
#include "texture.hpp"

/*
	Texture container. Loads a full spritesheet, splits into into each sprite and places them in separate textures. 
	Also deals with animation. 
*/

class Spritesheet{
public:
	Spritesheet(const SDL_Renderer *);
	~Spritesheet();
	int size(); //Returns m_size which is the size of each image
	void scale(const int &);
	bool load_from_file(const std::string &, int size);	//size of each sprite. currently only 32. Currenly locked to 8x8 spritesheets. 
	void set_pattern(const std::vector<int> &); //Set current animation pattern. 
	Texture * get_text(const int &);
	void update_anim();
	Texture * get_next_anim();
	void set_anim_duration(const int &);
private:
	SDL_Renderer const * m_main_renderer;
	Texture * m_sheet;
	unsigned int m_size;
	unsigned int m_original_size;
	std::vector<int> m_pattern = {0};
	unsigned int m_current_anim = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_last_anim;
	double m_anim_duration = 1;
	std::map<std::pair<int,int>,SDL_Rect*> m_rects;
	std::vector<Texture*> m_textures;
};