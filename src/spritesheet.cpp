#include "spritesheet.hpp"


Spritesheet::Spritesheet(const SDL_Renderer * main_renderer): m_main_renderer(main_renderer){
	//m_main_renderer = main_renderer;

}

Spritesheet::~Spritesheet(){
	for(unsigned int i = 0; i < m_textures.size(); ++i){
		delete m_textures[i];
	}
}



int Spritesheet::size(){
	return m_size;
}

void Spritesheet::scale(const int & x){
	for(unsigned int i = 0; i < m_textures.size(); ++i){
		m_textures[i]->scale(x,x);
		m_size = m_original_size*x;
	}
}

bool Spritesheet::load_from_file(const std::string & path, int sprite_size){ 
	SDL_Surface * full_sheet = NULL;
	m_size = sprite_size;
	m_original_size = m_size;
	full_sheet = IMG_Load(path.c_str());
	bool success = true;
	if(full_sheet == NULL){
		std::cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << "." << std::endl;
		success = false;
	}else{
		//std::cout << "Image is " <<  std::to_string(full_sheet->w) << "w, " << std::to_string(full_sheet ->h) << "h." << std::endl;
		int pos = 0;
		for(int y = 0; y < 8; ++y){
			for(int x = 0; x < 8; ++x){
				SDL_Rect srcrect = {x*size(), y*size(), size(), size()};

				SDL_Surface * tmp = SDL_CreateRGBSurface(
					full_sheet->flags, 
					size(), 
					size(),
					32, 
					full_sheet->format->Rmask, 
					full_sheet->format->Gmask, 
					full_sheet->format->Bmask, 
					full_sheet->format->Amask
					);
				SDL_BlitSurface(full_sheet, &srcrect, tmp, NULL); 
				Texture * new_text = new Texture(m_main_renderer);
				new_text->load_image_from_surface(tmp);
				m_textures.push_back(new_text);
				pos++;

			}
		}
	}
	return success;
}

void Spritesheet::set_anim_duration(const int & n){
	m_anim_duration = n;
}

void Spritesheet::set_pattern(const std::vector<int> & nv){
	if(m_pattern != nv){
		m_pattern = nv;
		m_current_anim = 0;
	}
}

void Spritesheet::update_anim(){
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = now-m_last_anim;
	std::chrono::milliseconds diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

	if(diff_ms.count() > m_anim_duration){
		m_last_anim = now;
		++m_current_anim;
		if(m_current_anim >= m_pattern.size()) m_current_anim = 0;
	}
	
}

Texture * Spritesheet::get_next_anim(){;
	return m_textures[m_pattern[m_current_anim]];
}

Texture * Spritesheet::get_text(const int & n){
	if(n > size()*size()-1){
		std::cout << "Warning out of bounds in spritesheet: " << n << std::endl;
	}
	return m_textures[n];
}