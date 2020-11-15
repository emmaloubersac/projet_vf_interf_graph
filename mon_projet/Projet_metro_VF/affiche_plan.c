#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **agrv){

    SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

    //lancement SDL

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0){     
		SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	} 
    
    //creation fenetre + rendu

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
	    SDL_Log("ERREUR : creation fenetre et rendu echoue %s\n", SDL_GetError()); 
	    exit(EXIT_FAILURE);
    }

    //gestion d'evenement 
	SDL_bool program_launched = SDL_TRUE;

	while(program_launched){
		SDL_Event event; 

		while(SDL_PollEvent(&event)){   
			switch (event.type)    //evenement quitter le programme
			{
			case SDL_QUIT:
				program_launched = SDL_FALSE;
				break;
			
			default:
				break;
			}

		}
	}

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_VideoQuit(); //ne pas oublier de quitter en fct de ce qu'on a ouvert
	SDL_Quit();
    return EXIT_SUCCESS;
}