//gcc .\Projet_metro_VF\*.c -o .\bin\main -I include -L lib -lmingw32 -lSDL2main -lSDL2
//commande pour compiler avec la SDL
//lien pour telercharger un menmento avec toute les commandes et protoypes : https://mega.nz/file/AYtXxQ6D#VIdMcHx0HxOOkrC7gSPgDSAtg1WZUc-z3PEgTPyqMQM
//Attention : Pour la plupart des fct, comme tu vas le remarquer, la valeur retour est 0 quand elle fct, et il est important de tester tte les fct (pour quitter si il y a une erreur)
//pour trouver les commandes et nom des constantes a utliser, ne pas hesiter à aller sur SDL wiki

/*fct qui permet de creer une fenetre et un rendu en mm temp:
if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
	SDL_Log("ERREUR : creation fenetre et rendu echoue %s\n", SDL_GetError()); 
	exit(EXIT_FAILURE);
}*/

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **agrv){
    SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	//lancement SDL
	SDL_version nb;
	SDL_VERSION(&nb);
	printf("Bienvenue sur la SDL %d.%d.%d !\n", nb.major,nb.minor,nb.patch);

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0){     //argm : Un drapeau(comment d'ouvre une fenetre), '|' permet d'ouvrir plusieurs SDL_INIT
		SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	} 

	//Ouverture d'un fenêtre
	window = SDL_CreateWindow("Première fenêtre SDL 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600,0);    
 		//creation d'une fenêtre   argm : le deuxieme  et troisieme (x,y) correspondent au coord de la fenetre, on utilise une constance pour la centré automatiquement
		 //puis 4eme et 5eme : nb de pixel, ici 800 fois 600 //0 par défaut, sinon mettre les SDL_ mode d'affichage
	if (window == NULL){     //si il y a une erreur d'alloc pointeur recup erreur et quitte
		SDL_Log("ERREUR : Creation fenetre echoue > %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//Ouverture rendu
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //permet de creer un rendu (qui sera afficher dans la fenetre creer)
	if (renderer == NULL){  //verifie que le rendu a bien ete cree, quitte sinon
		SDL_Log("ERREUR : Creation rendu echoue \n", SDL_GetError());
		exit(EXIT_FAILURE);
	}



	//dessiner sur un rendu 
	if (SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0){   //renderer le rendu ou l'on change la couleur, ensuite on a RRR/VVV/BBB puis l'opacite du trait (ici 100%, le trait nest pas transparent)
		SDL_Log("ERREUR : Impossible de changer couleur rendu\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//dessin point

	if (SDL_RenderDrawPoint(renderer, 100, 400) != 0){   //affiche un point au coord 100,400 (il est tout petit)
		SDL_Log("ERREUR : Impossible de dessiner le point\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//dessin ligne

	if (SDL_RenderDrawLine(renderer, 50, 50, 100, 100) != 0){   
		SDL_Log("ERREUR : Impossible de dessiner la ligne\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//dessin rectangle

	SDL_Rect rectangle;
	rectangle.x = 300;  
	rectangle.y = 300;  //x,y coord en haut a gauche
	rectangle.h	= 100; // hauteur
	rectangle.w = 200; // largeur
	
	//contour du rect seulement
	if (SDL_RenderDrawRect(renderer, &rectangle) != 0){  
		SDL_Log("ERREUR : Impossible de dessiner le rectangle\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//rectangle plein
	/*if (SDL_RenderFillRect(renderer, &rectangle) != 0){   
		SDL_Log("ERREUR : Impossible de dessiner le rectangle\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}*/
	SDL_RenderPresent(renderer); //affiche le rendu creer

	if (SDL_RenderClear(renderer) != 0){    //efface un rendu (pour pvr en afficher un nouveau apres pas ex) et test en mm temps si l'effacement a bien eu lieu, quitte sinon
		SDL_Log("ERREUR : effacement rendu echoue > %s\n", SDL_GetError()); 
		exit(EXIT_FAILURE);
	}

	//commande qui va permettre d'ouvrir le fichier et de le garder ouvert tant que l'utilisateur n'a pas decider de fermer la page 
	SDL_bool program_launched = SDL_TRUE;

	while(program_launched){
		SDL_Event event; //creation evenement

		while(SDL_PollEvent(&event)){   //gestion des evenements : tous les evenements sont a mettre à l'interieur (un seul while pour tous les evenements)
			
			
			
			switch (event.type)    
			{	
				case SDL_MOUSEMOTION:   //gestion evenement mouvement souris
					printf("%d / %d\n", event.motion.x, event.motion.y );   //affiche coord de la souris
					break;

				case SDL_MOUSEBUTTONDOWN:   //gestion evenemnt cliquer avec la souris
					printf("Click en : %d / %d\n", event.button.x, event.button.y);
					break;

				case SDL_KEYDOWN:    //gestion evenement du clavier
					switch (event.key.keysym.sym)
					{
						case SDLK_b:    //quand on appuie sur la touche b
							printf("appuie sur b");   //on decide d'afficher 'appuie sur b'
							break;
					
						default:
							break;
					}
			
				case SDL_QUIT:    //comment quitter un programe proprement (par l'utilisateur) imperatif, il faut tjs le mettre
					program_launched = SDL_FALSE;
					break;
				default:
					break;
			}
		}
	}

	//SDL_Delay(5000);  //temp d'ouverture : 5000 en ms seconde (c'est mieux d'uliser la gestion d'evement comme ça le programme reste ouvert jusk la fermeture)


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_VideoQuit(); //ne pas oublier de quitter en fct de ce qu'on a ouvert
	SDL_Quit();

    return EXIT_SUCCESS;
}