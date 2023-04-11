#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>


// La largeur et la hauteur de la fenêtre du menu
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// La couleur du texte pour les boutons
const SDL_Color TEXT_COLOR = {255, 255, 255};


SDL_Rect SDL_CreerRect(int x, int y, int w, int h){
    SDL_Rect rectangle;
    rectangle.x = x ;///Coordonnées x de l'angle haut gauche
    rectangle.y = y ;///Corddonnées y de l'angle haut gauche 
    rectangle.w = w ;///Longueur du rectangle
    rectangle.h = h ;///Hauteur
    return rectangle ;
    /**
    \return rectangle
    */
}

int main(int argc, char* argv[])
{
    

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de la police de caractères
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de la bibliothèque SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    // Création de la fenêtre du menu
    SDL_Window* window = SDL_CreateWindow("Puissance4++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return 1;
    }

    // Création du rendu pour dessiner le menu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        printf("Erreur lors de la création du rendu : %s\n", SDL_GetError());
        return 1;
    }
// Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    Mix_Music* musique = Mix_LoadMUS("musique.mp3");
    if (musique == NULL) {
        printf("Erreur de chargement de la musique : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    Mix_PlayMusic(musique, -1);
    
    
    // Chargez l'image de fond d'écran
    SDL_Surface* backgroundSurface = SDL_LoadBMP("../img/imageMenu/tache_bleue.bmp");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);

    // Dessinez la texture de fond d'écran
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    

    // Création du texte pour le bouton "Jouer"
    SDL_Surface* play_button_surface = IMG_Load("../img/imageMenu/bouton_jouer.bmp");
    if (play_button_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_jouer.bmp : %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* play_button_texture = SDL_CreateTextureFromSurface(renderer, play_button_surface);
    SDL_Rect play_button_rect = SDL_CreerRect(SCREEN_WIDTH/4, 80, SCREEN_WIDTH/2, SCREEN_HEIGHT/3);
    SDL_RenderCopy(renderer, play_button_texture, NULL, &play_button_rect);
    
    // Création du texte pour le bouton "Quitter"
    SDL_Surface* quit_button_surface = IMG_Load("../img/imageMenu/bouton_quitter.bmp");
    if (quit_button_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_quitter.bmp : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* quit_button_texture = SDL_CreateTextureFromSurface(renderer, quit_button_surface);
    SDL_Rect quit_button_rect = SDL_CreerRect(SCREEN_WIDTH/4, 160, SCREEN_WIDTH/2, SCREEN_HEIGHT/3);    
    SDL_RenderCopy(renderer, quit_button_texture, NULL, &quit_button_rect);

    // Création du texte pour le bouton "regles"
    SDL_Surface* regles_button_surface = IMG_Load("../img/imageMenu/bouton_regles.bmp");
    if (regles_button_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_regles.bmp : %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* regles_button_texture = SDL_CreateTextureFromSurface(renderer, regles_button_surface);
    SDL_Rect regles_button_rect = SDL_CreerRect(SCREEN_WIDTH/4, 240, SCREEN_WIDTH/2, SCREEN_HEIGHT/3);
    SDL_RenderCopy(renderer, regles_button_texture, NULL, &regles_button_rect);
     
    // Chargement de l'icône pour couper la musique
    SDL_Surface* bouton_sound_on_surface = SDL_LoadBMP("../img/imageMenu/bouton_sound_on.bmp");
    SDL_Surface* bouton_sound_off_surface = SDL_LoadBMP("../img/imageMenu/bouton_sound_off.bmp");

    if (bouton_sound_on_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_sound_on.bmp : %s\n", SDL_GetError());
        return 1;
    }
     if (bouton_sound_off_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_sound_off.bmp : %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* bouton_sound_on_texture = SDL_CreateTextureFromSurface(renderer, bouton_sound_on_surface);
    SDL_Texture* bouton_sound_off_texture = SDL_CreateTextureFromSurface(renderer, bouton_sound_off_surface);
    SDL_Rect bouton_sound_on_rect = SDL_CreerRect(580, 420, 50, 50); // Position de l'icône en bas à droite de la fenêtre
    SDL_Rect bouton_sound_off_rect = SDL_CreerRect(580, 420, 50, 50); // Position de l'icône en bas à droite de la fenêtre
    SDL_RenderCopy(renderer, bouton_sound_on_texture, NULL, &bouton_sound_on_rect);

    // Chargement de l'icône pour revenir en arriere 
    SDL_Surface* bouton_back_surface = SDL_LoadBMP("../img/imageMenu/bouton_back.bmp");
    if (bouton_back_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_back.bmp : %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* bouton_back_texture = SDL_CreateTextureFromSurface(renderer, bouton_back_surface);
  
    SDL_Rect bouton_back_rect = SDL_CreerRect(10, 10, 40, 40); // Position de l'icône en hautb à gauche de la fenêtre
   

     // Création du texte pour du contenu des "regles"
    SDL_Surface* regles_surface = IMG_Load("../img/imageMenu/regles.bmp");
    if (regles_surface == NULL) {
        printf("Erreur lors du chargement de l'image regles.bmp : %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* regles_texture = SDL_CreateTextureFromSurface(renderer, regles_surface);
    SDL_Rect regles_rect = SDL_CreerRect(0,0,640,480);
    
     // Création du texte pour le bouton "Contre un joueur"
    SDL_Surface* contre_joueur_button_surface = IMG_Load("../img/imageMenu/bouton_contre_joueur.bmp");
    if (contre_joueur_button_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_contre_joueur.bmp : %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* contre_joueur_button_texture = SDL_CreateTextureFromSurface(renderer, contre_joueur_button_surface);
    SDL_Rect contre_joueur_button_rect = SDL_CreerRect(SCREEN_WIDTH/4, 100, SCREEN_WIDTH/2, SCREEN_HEIGHT/3);
    
    
    // Création du texte pour le bouton "contre l'ordinateur"
    SDL_Surface* contre_ordinateur_button_surface = IMG_Load("../img/imageMenu/bouton_contre_ordinateur.bmp");
    if (contre_ordinateur_button_surface == NULL) {
        printf("Erreur lors du chargement de l'image bouton_contre_ordinateur.bmp : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* contre_ordinateur_button_texture = SDL_CreateTextureFromSurface(renderer, contre_ordinateur_button_surface);
    SDL_Rect contre_ordinateur_button_rect = SDL_CreerRect(SCREEN_WIDTH/4, 200, SCREEN_WIDTH/2, SCREEN_HEIGHT/3); 
    



    // Mise à jour de l'affichage
    SDL_RenderPresent(renderer);

    typedef enum {principal=1, regles, mode} menu_t;

    // Boucle principale du menu
    int continuer = 1;
    int musique_active = 1;
    menu_t menu_actuel = 1; 
    SDL_Event event;
    while (continuer) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // L'utilisateur a cliqué sur le bouton de fermeture de la fenêtre
                continuer = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) 
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                switch(menu_actuel) {

                    case principal:
                        // menu principal à l'écran

                        if (mouseX >= quit_button_rect.x && mouseX <= quit_button_rect.x + quit_button_rect.w &&
                            mouseY >= quit_button_rect.y && mouseY <= quit_button_rect.y + quit_button_rect.h) {
                            // Le bouton "Quitter" a été cliqué
                            continuer = 0;
                        }
                        if (mouseX >= play_button_rect.x && mouseX <= play_button_rect.x + play_button_rect.w &&
                            mouseY >= play_button_rect.y && mouseY <= play_button_rect.y + play_button_rect.h) {
                            // Le bouton "Jouer" a été cliqué
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
                            SDL_RenderCopy(renderer, contre_joueur_button_texture, NULL, &contre_joueur_button_rect);
                            SDL_RenderCopy(renderer, contre_ordinateur_button_texture, NULL, &contre_ordinateur_button_rect);
                            SDL_RenderCopy(renderer, bouton_back_texture, NULL, &bouton_back_rect);
                            SDL_RenderPresent(renderer);
                            menu_actuel = mode;

                            
                        }
                        if (mouseX >= regles_button_rect.x && mouseX <= regles_button_rect.x + regles_button_rect.w &&
                            mouseY >= regles_button_rect.y && mouseY <= regles_button_rect.y + regles_button_rect.h) {
                            // Le bouton "Regles" a été cliqué
                            SDL_RenderCopy(renderer, regles_texture, NULL, &regles_rect);
                            SDL_RenderCopy(renderer, bouton_back_texture, NULL, &bouton_back_rect);
                            SDL_RenderPresent(renderer);
                            menu_actuel = regles;
                        }
                        break;
                    
                    
                    case regles:
                        if(mouseX >= bouton_back_rect.x && mouseX <= bouton_back_rect.x + bouton_back_rect.w &&
                            mouseY >= bouton_back_rect.y && mouseY <= bouton_back_rect.y + bouton_back_rect.h){
                            // Le bouton "Back" a été cliqué
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
                            SDL_RenderCopy(renderer, play_button_texture, NULL, &play_button_rect);
                            SDL_RenderCopy(renderer, quit_button_texture, NULL, &quit_button_rect);
                            SDL_RenderCopy(renderer, regles_button_texture, NULL, &regles_button_rect);
                            
                            SDL_RenderPresent(renderer);
                            menu_actuel = principal;
                        }
                        break;
                        
                    case mode:
                        if(mouseX >= bouton_back_rect.x && mouseX <= bouton_back_rect.x + bouton_back_rect.w &&
                            mouseY >= bouton_back_rect.y && mouseY <= bouton_back_rect.y + bouton_back_rect.h){
                            // Le bouton "Back" a été cliqué
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
                            SDL_RenderCopy(renderer, play_button_texture, NULL, &play_button_rect);
                            SDL_RenderCopy(renderer, quit_button_texture, NULL, &quit_button_rect);
                            SDL_RenderCopy(renderer, regles_button_texture, NULL, &regles_button_rect);
                            
                            SDL_RenderPresent(renderer);
                            menu_actuel = principal;
                        }

                        break;
                }
                
            
                // dans tous les cas
                if(event.button.x >= bouton_sound_on_rect.x && event.button.x <= bouton_sound_on_rect.x + bouton_sound_on_rect.w &&
                           event.button.y >= bouton_sound_on_rect.y && event.button.y <= bouton_sound_on_rect.y + bouton_sound_on_rect.h) 
                {
                    // Le bouton "mute" à été cliqué
                    if (musique_active)
                    {
                        Mix_HaltMusic(); // Si la musique est active, on la coupe
                        musique_active = 0;
                    }
                    else
                    {
                        Mix_PlayMusic(musique, -1); // Si la musique est inactive, on la joue en boucle
                        musique_active = 1;
                    }
                }

                if (musique_active)
                {
                    SDL_RenderCopy(renderer, bouton_sound_on_texture, NULL, &bouton_sound_off_rect);
                    SDL_RenderPresent(renderer);
                }
                else
                {
                    SDL_RenderCopy(renderer, bouton_sound_off_texture, NULL, &bouton_sound_on_rect);
                    SDL_RenderPresent(renderer);
                }
            } 
        }  
    }

    

    
    

    // Libération des ressources
    SDL_DestroyTexture(play_button_texture);
    SDL_DestroyTexture(quit_button_texture);
    SDL_FreeSurface(play_button_surface);
    SDL_FreeSurface(quit_button_surface);
    SDL_DestroyTexture(backgroundTexture);
    SDL_FreeSurface(backgroundSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(musique);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

