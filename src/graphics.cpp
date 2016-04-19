#include "graphics.hpp"

Graphics::Graphics(){
	m_log = new Logger(m_logfile_name);
	if(init()){

		if(init_gl()){
			m_successful_init = true;
		}else{
			m_log->log("Could not initialize OpenGL.");
		}

	}else {
		m_log->log("Could not initialize SDL.");
	}
}

Graphics::~Graphics(){
}


bool Graphics::init(){


			m_log->log("Initializing of " + m_window_name);
			bool success = true;
			if(SDL_Init(SDL_INIT_VIDEO) < 0){
				m_log->log( "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()) );
				success = false;
			}else{

				if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				{
					m_log->log("Warning: Linear texture filtering not enabled!");
				}

				m_sdl_window = SDL_CreateWindow(
					m_window_name.c_str(),
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					m_screen_width,
					m_screen_height,
					SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
				if(m_sdl_window  == nullptr){
					m_log->log( "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()) );
					success = false;
				}else{
					m_sdl_glcontext = SDL_GL_CreateContext(m_sdl_window);
					if(m_sdl_glcontext == 0){
						m_log->log("OpenGL context could not be created! SDL Error: " + std::string(SDL_GetError()));
						success = false;
					}else{
						if(SDL_GL_SetSwapInterval(1) < 0){
							m_log->log("Warning: Unable to set VSync! SDL Error: " + std::string(SDL_GetError()) );
							success = false;
						}
						/*
						if(!init_gl()){
							m_log->log("Unable to initialize OpenGL!");
							success = false;
						}
						*/
						
					}
					m_sdl_surface = SDL_GetWindowSurface(m_sdl_window);

					m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
					if(m_sdl_renderer == nullptr){
						m_log->log("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()) );
						success = false;
					}else{
						SDL_SetRenderDrawColor(m_sdl_renderer, 0xff, 0xff, 0xff, 0xff);
						int img_flags = IMG_INIT_PNG;
						if(!(IMG_Init(img_flags) & img_flags)){
							m_log->log("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()) );
							success = false;
						}
						if (TTF_Init() == -1)
						{
							m_log->log("SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
							success = false;
						}
					}

				}
			}
		

			m_log->log("Done initializing of " + m_window_name);
			return success;
		}

bool Graphics::init_gl(){
	return true;
}

void Graphics::run(){
		bool running = true;
		SDL_Event events;
		SDL_StartTextInput();
		Texture texture(m_sdl_renderer);
		assert(texture.load_from_file("media\\test.png"));
		Texture illuminati(m_sdl_renderer);
		assert(illuminati.load_from_file("media\\illuminati.png"));
		Texture swords(m_sdl_renderer);
		assert(swords.load_from_file("media\\sword.png"));
		Texture text(m_sdl_renderer);
		SDL_Color col = { 0,0,0 };
		text.set_font("ARIALUNI.TTF");
		assert(text.load_from_rendered_text("Hello world", col));
		texture.set_blendmode(SDL_BLENDMODE_BLEND);
		illuminati.set_blendmode(SDL_BLENDMODE_BLEND);
		text.set_blendmode(SDL_BLENDMODE_BLEND);
		int x = 0; int y = 0;
		int counter = 0;
		while(running){	
			while(SDL_PollEvent(&events) != 0){ 
				switch(events.type){

					case SDL_QUIT:
					running = false;
					break; 

					case SDL_TEXTINPUT:
					    if(events.text.text[0] == 'q'){
					    	running = false;
					    }
					}
				}
				SDL_GetMouseState(&x, &y);
				SDL_SetRenderDrawColor(m_sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(m_sdl_renderer);
				SDL_Rect clipper = { 10, 10, 200, 200 };
				texture.set_alpha(x);
				texture.set_color(x, y, x);
				
				swords.render(0,0);
				texture.render(x - texture.get_width()/2, y - texture.get_height()/2, &clipper);
				illuminati.render(40, 40);
				counter++;
				text.load_from_rendered_text("Hello world: " + std::to_string(counter), col);
				text.render(50, 50);

				SDL_RenderPresent(m_sdl_renderer);
			}
			SDL_StopTextInput();
}