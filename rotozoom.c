#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include "rotozoom.h"
 
#define TEMPS       30 // Le temps qu'il y a entre chaque augmentation de l'angle.

void rotozoom()
{
    SDL_Surface *ecran = NULL, *image = NULL, *rotation = NULL;
    SDL_Rect rect;
    SDL_Event event;
    int angle = 0;
    int zoom = 2;

 
    int continuer = 1;
    int tempsa = 0, tempsm= 0;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    ecran = SDL_SetVideoMode(1200, 800, 32, SDL_HWSURFACE);
 
    image = SDL_LoadBMP("image.bmp");
 
    while(continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        
		 case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
                {
		case SDLK_ESCAPE: 
			continuer=0;

		break;
		}
}
 
        tempsm = SDL_GetTicks();
        if (tempsm - tempsa > TEMPS)
        {
            angle += 2; //On augmente l'angle pour que l'image tourne sur elle-même.
 
            tempsa = tempsm;
        }
        else
        {
            SDL_Delay(TEMPS - (tempsm - tempsa));
        }
 
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
 
        rotation = rotozoomSurface(image, angle, zoom, 0); //On transforme la surface image.
        
        //On repositionne l'image en fonction de sa taille.
        rect.x =  event.button.x - rotation->w / 2;
        rect.y =  event.button.y - rotation->h / 2;
 
        SDL_BlitSurface(rotation , NULL, ecran, &rect); //On affiche la rotation de la surface image.
        SDL_FreeSurface(rotation); //On efface la surface rotation car on va la redéfinir dans la prochaine boucle. Si on ne le fait pas, cela crée une fuite de mémoire. 
 
      
 
        SDL_Flip(ecran);
    }
 
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(image);
    SDL_Quit();
 
   
}
