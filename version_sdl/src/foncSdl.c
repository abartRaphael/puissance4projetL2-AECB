#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../lib/foncSdl.h"



/**
 * \file foncSdl.h
 * \brief Corps des fonctions SDL
 * \version 0.1
 * \date {22/03/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/



/**
 * \fn int init(SDL_Window* * window, SDL_Renderer* * renderer, int width, int height)
 * \brief initialise les systèmes de SDL, crée le pointeur sur fenêtre et le renderer
 * \param window pointeur sur pointeur de SDL_Window, va être rempli (à free avec SDL_DestroyRenderer() )
 * \param renderer pointeur sur pointeur de SDL_Renderer, va être rempli (à free avec SDL_DestroyWindow() )
 * \param width la largeur de la fenêtre
 * \param height la hauteur de la fenêtre
 * \return retourne 0 en cas de succès, -1 en cas d'échec
 */
int init(SDL_Window* * window, SDL_Renderer* * renderer, int width, int height) {
	
	// Initialisation simple 
	if ( SDL_InitSubSystem(SDL_INIT_VIDEO) != 0 ) {
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return -1;
	} 

	if( SDL_CreateWindowAndRenderer(width, 
								height, 
								SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE, 
								window, 
								renderer) != 0 )
	{
		fprintf(stderr, "Erreur à la création de la fenetre et du renderer : %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}



/**
 * \fn SDL_Texture* loadImage(char* path, SDL_Renderer* renderer)
 * \brief charge une image depuis un chemin donné, retourne une texture créée à partir de cette image
 * \param path chemin d'accès, relatif ou absolu, vers le fichier BITMAP UNIQUEMENT (.bmp) à ouvrir
 * \param renderer pointeur de SDL_Renderer, nécessaire pour créer une texture depuis une surface
 * \return retourne l'adresse d'une SDL_Texture dynamique créée à partir de cette image (à free avec SDL_DestroyTexture() ), ou NULL en cas d'échec
 */
SDL_Texture* loadImage(char* path, SDL_Renderer* renderer) {

	SDL_Surface* tempSurface = NULL;
	SDL_Texture* tempTexture = NULL;
	
	tempSurface = SDL_LoadBMP(path);
	if(!tempSurface)
	{
		fprintf(stderr, "Erreur SDL_LoadBMP : %s\n", SDL_GetError());
		return NULL;
	}

	tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface); // On libère la surface, on n’en a plus besoin 

	if(!tempTexture)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
		return NULL;
	}

	return tempTexture;
}



/**
 * \fn int setDrawColor(SDL_Renderer *renderer, SDL_Color color)
 * \brief change la couleur utilisée pour dessiner avec un SDL_Color
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param color couleur de type SDL_color {rouge, vert, bleu[, alpha]}
 * \return retourne 0 pour un succès, -1 pour une erreur
 */
int setDrawColor(SDL_Renderer *renderer, SDL_Color color) {

	if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
		return -1;

	return 0;  
}



void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y) {
    
	Uint32 *pixels = surface->pixels; // Nos pixels sont sur 32 bits 
    Uint32 couleur = SDL_MapRGBA(surface->format, r, g, b, a);
    pixels[y * surface->w + x] = couleur;
}



SDL_Surface *createSurfaceFromTexture(SDL_Texture* texture)
{
    Uint32 format_pixels;
    SDL_Surface* surface = NULL;
    void* pixels = NULL;
    int pitch, w, h;

    if( SDL_QueryTexture(texture, &format_pixels, NULL, &w, &h) != 0 )
    {
        fprintf(stderr, "SDL_QueryTexture: %s.\n", SDL_GetError());
        goto query_texture_fail;
    }

    if( SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0 )
    {
        fprintf(stderr, "SDL_LockTexture: %s.\n", SDL_GetError());
        goto lock_texture_fail;
    }

    surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 32, w * sizeof(Uint32), 
                                                 format_pixels);
    if(NULL == surface)
        fprintf(stderr, "Erreur SDL_CreateRGBSurfaceWithFormatFrom : %s.\n", SDL_GetError());

    SDL_UnlockTexture(texture);
lock_texture_fail:
query_texture_fail:
    return surface;
}


