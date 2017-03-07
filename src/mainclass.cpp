#include "mainclass.hpp"
#include "player.hpp"
#include "actor.hpp"
Mainclass::Mainclass(){
	std::cout << "Init main" << std::endl;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout <<  "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
		m_init_ok = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}
		//Create window
		m_main_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
		if( m_main_window == NULL )
		{
			std::cout <<  "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
			m_init_ok = false;
		}else{
			m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			m_main_surface = SDL_GetWindowSurface( m_main_window );
			if(m_main_renderer == NULL){
				std::cout << "Renderer could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
				m_init_ok = false;
			}else
			{
				SDL_SetRenderDrawColor(m_main_renderer, 0x0, 0x0, 0x0, 0x0);
				int img_flags = IMG_INIT_PNG;
				if(!(IMG_Init(img_flags) & img_flags)){
					std::cout << "SDL_image could not initialize! SDL_image Error: " << std::string(IMG_GetError()) << std::endl;
					m_init_ok = false;
				}
				if (TTF_Init() == -1)
				{
					std::cout <<"SDL_ttf could not initialize! SDL_ttf Error: " << std::string(TTF_GetError())<<std::endl;
					m_init_ok = false;
				}
			}
		}
	}


	setup_keys();
	setup_gameobjects();
	//Destroy window


}
Mainclass::~Mainclass(){ 
	std::cout << "Destruct main" << std::endl;

	//Remove all gameobjects
	for(std::vector<Gameobject*>::iterator it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it ){
		delete (*it);
	}
	m_gameobjects.clear();

	//Close down SDL
	SDL_DestroyRenderer(m_main_renderer);
	SDL_FreeSurface(m_main_surface);
	SDL_DestroyWindow( m_main_window );
	SDL_Quit();
}
void Mainclass::run(){
	std::cout << "Run main" << std::endl;
	while(m_running){
		//Player Update
		update_keys();
		update_player();

		if(m_keys[SDLK_p]){
			debug_show_colliders = !debug_show_colliders;
			m_keys[SDLK_p] = false;
		}
		std::sort(m_gameobjects.begin(), m_gameobjects.end());

		//Rendering
		SDL_SetRenderDrawColor(m_main_renderer, 0, 0, 0, 1);
		SDL_RenderClear(m_main_renderer);

		for (std::vector<Gameobject*>::iterator it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it)
		{

			(*it)->update(); //Update gameobjects

			if(debug_show_colliders){
				SDL_SetRenderDrawColor(m_main_renderer, 255, 255, 255, 255);
				(*it)->collider().render(m_main_renderer);
			}else{
				(*it)->render();
			}	
		}
		SDL_RenderPresent(m_main_renderer);
	}
}


void Mainclass::update_player(){
	/*
	std::pair<float,float> player_movement = {0,0};
	if(m_keys[SDLK_a]) player_movement = {-m_player->move_speed(),0}; //m_player->move(-m_player->move_speed(),0);
	if(m_keys[SDLK_s]) player_movement = {player_movement.first, player_movement.second + m_player->move_speed()};// m_player->move(0,m_player->move_speed());
	if(m_keys[SDLK_w]) player_movement = {player_movement.first, player_movement.second - m_player->move_speed()};//m_player->move(0, -m_player->move_speed());
	if(m_keys[SDLK_d]) player_movement = {player_movement.first + m_player->move_speed(), player_movement.second};//m_player->move(m_player->move_speed(), 0);
	dyn_movement(m_player, player_movement);
	*/
}
/*
void Mainclass::dyn_movement(Gameobject * mover, const std::pair<float, float> & movement){

	mover->move(movement.first, movement.second);
	for(auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it){
		if((*it) != mover){
			if((*it)->collider().collision_check(mover->collider())){ //If we have collision
				mover->move(-movement.first, 0); 
				if((*it)->collider().collision_check(mover->collider())){ //If we go back x and it's not ok
					mover->move(movement.first, -movement.second); //We reset x and try going back y
					if((*it)->collider().collision_check(mover->collider())){ //If this didn't work just back both
						mover->move(-movement.first, 0);
					}
				}
			}
		}
	}

}
*/

void Mainclass::setup_gameobjects(){
	Gameobject * g = new Player(this);
	g->position().z() = 1;
	g->load_from_file("media\\player_new.png");
	g->move_to(100, 100);
	g->scale(3.0f);
	g->collider().set_size(96,96);
	m_gameobjects.push_back(g);

	 g = new Gameobject(this);
	g->scale(0.5f);
	g->move_to(40,40);
	g->collider().set_size(32, 32);
	//g->load_from_file("media\\32_temp.png");
	m_gameobjects.push_back( g);

	
}


void Mainclass::setup_keys(){
	m_keys[SDLK_a] = false;
	m_keys[SDLK_w] = false;
	m_keys[SDLK_s] = false;
	m_keys[SDLK_d] = false;
	m_keys[SDLK_RIGHT] = false;
	m_keys[SDLK_LEFT] = false;
	m_keys[SDLK_UP] = false;
	m_keys[SDLK_DOWN] = false;
	m_keys[SDLK_p] = false;
}
void Mainclass::update_keys(){
	while(SDL_PollEvent(&m_main_event) != 0){ 
		switch(m_main_event.type){
			case SDL_QUIT:
			m_running = false;
			break; 

			case SDL_TEXTINPUT:
			if(m_main_event.text.text[0] == 'q'){
				m_running = false;
			}
			case SDL_KEYUP:
			if(m_keys.count(m_main_event.key.keysym.sym) > 0){
				m_keys[m_main_event.key.keysym.sym] = false;
			}
			break;
			case SDL_KEYDOWN:
			if(m_keys.count(m_main_event.key.keysym.sym) > 0){
				m_keys[m_main_event.key.keysym.sym] = true;
			}
			break;
		}
	}
}


const std::vector<Gameobject*> & Mainclass::gameobjects()const{
	return m_gameobjects;
}
bool Mainclass::key(int n)const{
	return m_keys.at(n);
}
const SDL_Renderer * Mainclass::main_renderer()const{
	return m_main_renderer;
}