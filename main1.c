#include <stdbool.h>
#include "camera.h"
#include "ennemi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include "detectCollBB.h"
#include <math.h>
/*#include "alea.h"*/
#include <SDL/SDL_rotozoom.h>
 
#define TEMPS       30 // Le temps qu'il y a entre chaque augmentation de l'angle.
 
#define HAUT	0
#define DROITE	1
#define BAS	2
#define GAUCHE	3

#define AUCUNE_DIRECTION	0
#define DIRECTION_HAUT		1
#define DIRECTION_DROITE	2
#define DIRECTION_BAS		4
#define DIRECTION_GAUCHE	8

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 400


/*score initialiser_score();
vie initialiser_vie();
void afficher_score(score s);
void afficher_vie(vie v);
void update_score(score *s , int sens);
void update_vie(vie *v);*/
int main()
{

	SDL_Surface *background;
SDL_Surface *entite_secondaire ; 
	SDL_Surface *player;
	SDL_Surface *ecran;

int X_min;
int X_max;
Sprite *a ; 
SDL_Surface b ; 

	SDL_Event event;
	int bFin = 0;
int distEH;
	SDL_Rect position={24,300}; 
	Scroll cam={0,0};
	/* On déclare trois sprites, un que l'on controlera
	   et deux qui se déplacerons tout seul */
	Sprite spControlable, spAutonome1, spAutonome2;
	Initialisation_Scroll(&cam,position,800,400);
	SDL_Rect pos_real={0,0};
	SDL_Rect pos={0,0};
        //enigme e ;
 	//enigmeData ed ;
	background=IMG_Load("jeu.png");
SDL_Rect poscoin;
poscoin.x=310;
poscoin.y=200;
entite_secondaire=IMG_Load("coin.png") ;
int argc;
 char *argv[50];
	//e=initEnigme();
        
      
	
	/* initialisation de SDL_Video */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "Echec d'initialisation de SDL.\n");
		return 1;
	}
	printf("Bonjour le monde, SDL est initialisé avec succès.\n");
	
	
	/* On fixe le mode d'affichage à 640*480*16 plein ecran.*/
	ecran = SDL_SetVideoMode(640, 400, 16, SDL_FULLSCREEN);
	if ( ecran == NULL )
	{
		fprintf(stderr, "Echec de changement du mode video : %s.\n", SDL_GetError());
		return 1;
	}
	
	/* On charge le sprite controlable avec l'image pecheur.bmp */
	if ( !chargerSprite( &spControlable, "pecheur.bmp" ) )
	{
		SDL_Quit();
		return 1;
	}

	/* On charge le premier sprite autonome avec l'image bebe.bmp */
	if ( !chargerSprite( &spAutonome1, "bebe.bmp" ) )
	{
		supprimerSprite( &spControlable );
		SDL_Quit();
		return 1;
	}

	/* On charge le second sprite autonome avec l'image souris.bmp */
	if ( !chargerSprite( &spAutonome2, "souris.bmp" ) )
	{
		supprimerSprite( &spAutonome1 );
		supprimerSprite( &spControlable );
		SDL_Quit();
		return 1;
	}

	spControlable.dest.x = 1000;
	spControlable.dest.y =800;
	fixerDirectionSprite( &spControlable, DIRECTION_DROITE );
	fixerDirectionSprite( &spControlable, AUCUNE_DIRECTION );
        spAutonome1.dest.x = 420;
	spAutonome1.dest.y =420;
	

	while (!bFin)
	{       
                Scrolling(&cam,position,800,600);
		SDL_BlitSurface(background,&(cam.scroll),ecran,NULL);
SDL_BlitSurface(entite_secondaire,NULL,background,&poscoin) ; 
                
		spControlable.dest.x=position.x-cam.scroll.x;
		spControlable.dest.y=305;

		if (spControlable.dest.x>=800)
		{
			spControlable.dest.x=800-161;
		}
		else if (spControlable.dest.x <=0)
		{
			spControlable.dest.x=0;
		}
		//SDL_BlitSurface(&spControlable.image,NULL,ecran,&spControlable.dest);
		//

		SDL_EnableKeyRepeat(5,5);
while(SDL_PollEvent(&event))
{

		
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					bFin = 1;
					break;
					
				// on deplace le sprite au clavier
				case SDLK_UP:
     fixerDirectionSprite( &spControlable, DIRECTION_HAUT );
   position.y-=10;
					break;
				
				case SDLK_RIGHT:
             fixerDirectionSprite( &spControlable, DIRECTION_DROITE );
             position.x+=10;
					break;
				
				case SDLK_DOWN:
	  fixerDirectionSprite( &spControlable, DIRECTION_BAS );
          position.y+=10;
					break;
				
				case SDLK_LEFT:
	fixerDirectionSprite( &spControlable, DIRECTION_GAUCHE );
         position.x-=10;
					break;
				
				default:
					printf("Une touche à été pressée.\n");
				}
				break;
			
	
			

			case SDL_QUIT:
				bFin = 1;
				break;


case SDL_MOUSEBUTTONUP :
if (event.motion.x < spControlable.dest.x )
{
fixerDirectionSprite( &spControlable, DIRECTION_GAUCHE );



                   if(event.button.button == SDL_BUTTON_LEFT)
             
		
            position.x -=20  ;
         position.y = position.y;
}
if (event.motion.x > spControlable.dest.x )
{fixerDirectionSprite( &spControlable, DIRECTION_DROITE );
if(event.button.button == SDL_BUTTON_LEFT)
             
		
            position.x +=20  ;
         position.y = position.y;
}

break ;
}

int siwar;
						
			siwar=collision_back ( &spControlable,  background);
			printf(siwar,"%d");
//****************************************************************************************************



/*SDL_Surface *ecran = NULL, *image = NULL, *rotation = NULL;
    SDL_Rect rect;
    SDL_Event event;
    double angle = 0;
    double zoom = 1;
    int sens = 1;
 
    int continuer = 1;
    int tempsPrecedent = 0, tempsActuel = 0;

 
    SDL_Init(SDL_INIT_VIDEO);

 
    ecran = SDL_SetVideoMode(1200, 800, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Faire des rotations avec SDL_gfx", NULL);
 
    image =IMG_Load("coin.png");
 
    while(continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }
 
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > TEMPS)
        {
            angle += 2; //On augmente l'angle pour que l'image tourne sur elle-même.
 
            tempsPrecedent = tempsActuel;
        }
        else
        {
            SDL_Delay(TEMPS - (tempsActuel - tempsPrecedent));
        }
 
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
 
        rotation = rotozoomSurface(image, angle, zoom, 0); //On transforme la surface image.
        
        //On repositionne l'image en fonction de sa taille.
        rect.x =  event.button.x - rotation->w / 2;
        rect.y =  event.button.y - rotation->h / 2;
 
        SDL_BlitSurface(rotation , NULL, ecran, &rect); //On affiche la rotation de la surface image.
        SDL_FreeSurface(rotation); //On efface la surface rotation car on va la redéfinir dans la prochaine boucle. Si on ne le fait pas, cela crée une fuite de mémoire. 
 
        if(zoom >= 2){sens = 0;}
        else if(zoom <= 0.5){sens = 1;}
 
        if(sens == 0){zoom -= 0.02;}
        else{zoom += 0.02;}
 
        SDL_Flip(ecran);
    }
 */




//**********************************************************************************************





/*SDL_Surface *image = NULL, *rotation = NULL;
SDL_Rect rect;
    SDL_Event event;
 SDL_Init(SDL_INIT_VIDEO );
    ecran=SDL_SetVideoMode(1000,500,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    int hh=0 , healthejja=100;
    
    
    int prev_time = 0, actual_time = 0;
    double zoom = 1;
 double angle = 0;
    int sens = 1;


 image = SDL_LoadBMP("But.bmp");

    //init_stage1(&hero , tab,hajjoura,&background,black_background,&frametime);
    //init_stage2(&hero2 , tab,hajjoura,&background,black_background,&frametime,tab_coin);
    
    
        // menu
           
            
            
                SDL_PollEvent(&event);

                actual_time = SDL_GetTicks();

                if (actual_time - prev_time > 30)
                {
                    angle += 2; 

                    prev_time = actual_time;
                }
            

                rotation = rotozoomSurface(image, angle, zoom, 0);
                

                rect.x = event.button.x - rotation->w / 2;
                rect.y = event.button.y - rotation->h / 2;
                
                SDL_BlitSurface(rotation, 0, ecran, &rect);

                if (zoom >= 2)
                {
                    sens = 0;
                }
                else if (zoom <= 0.5)
                {
                    sens = 1;
                }

                if (sens == 0)
                {
                    zoom -= 0.02;
                }
                else
                {
                    zoom += 0.02;
                }
                SDL_Flip(ecran);*/
             
               
            
//*****************************************************************************
/*rotoo(argc,&argv);*/
 /*mvt_alea_entite_secondaire(&ent ,X_min,X_max);*/
	
		if (detectCollBB(&spControlable,&spAutonome1,spControlable.dest,spAutonome1.dest)==false)
 { 
printf("collesion \n");


	 }
/*int anim;
		anim=movmntalea(&spAutonome1,&spControlable , background );
if (anim==2)
printf("siwar\n");
else if (anim==3)
printf("siwar3\n");*/
}
			/*rotoo(argc,&argv);*/
			/* On dessine la scene */
			/* On dessine les sprites à l'écran */

			dessinerSprite( &spControlable, ecran );
			dessinerSprite( &spAutonome1,background );
                    
                       miseAJourSprite( &spControlable );
			miseAJourSprite( &spAutonome1 );
			//miseAJourSprite( &spAutonome2 );

						
			/* On met à jour de la zone d'affichage de la fenetre */
			SDL_UpdateRect(ecran, 0, 0, 0, 0); 
                        SDL_Flip(ecran);

		
		
	} 	
 if (collision_back (&spControlable,  background)==0)
{
printf ("collback\n");
}
else 
{
printf("sssss\n") ;
}






	
	supprimerSprite(&spControlable);
        supprimerSprite(&spAutonome1);
     //   SDL_Delay(3000);
	SDL_Quit();
	return 0;
}
