#include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <math.h>
  #include "ennemi.h"
  #include <SDL/SDL.h>
  #include <SDL/SDL_image.h>
  #include <SDL/SDL_ttf.h>
  #include<SDL/SDL_mixer.h>
  

SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y)
{

  SDL_Color color;
  Uint32 col= 0;
  char* pPosition = (char*) pSurface->pixels;
  pPosition += (pSurface->pitch * y);
  pPosition += (pSurface->format->BytesPerPixel * x);
  memcpy (&col,pPosition,pSurface->format->BytesPerPixel);
  SDL_GetRGB (col,pSurface->format,&color.r,&color.g,&color.b);
 return (color);
}

int collision_back (Sprite *a, SDL_Surface b)
{
SDL_Surface *surf= IMG_Load("jeu.png");
SDL_Surface *surfM= IMG_Load("jeumasque.png") ; 
int X,Y,W,H;
/* X=a.dest.x;
 Y=a.dest.y;
 W=a.dest.w=a->largeur;
 H=a.dest.h=a->hauteur;*/


	X=a->dest.x ;
	Y=a->dest.y ;
	H=a->dest.w = a->largeur;
	W=a->dest.h = a->hauteur;

	

  SDL_Rect point[8];
  SDL_Color color[8];

point[0].x=X;
point[0].y=Y;

point[1].x=X+W/2;
point[1].y=Y;

point[2].x=X+W;
point[2].y=Y;

point[3].x=X;
point[3].y=Y+H/2;

point[4].x=X;
point[4].y=Y+H;

point[5].x=X+W/2;
point[5].y=Y+H;

point[6].x=X+W;
point[6].y=Y+H;

point[7].x=X+W;
point[7].y=Y+H/2;


color[0]=GetPixel (&surfM, point[0].x, point[0].y);
color[1]=GetPixel (&surfM, point[1].x, point[1].y);
color[2]=GetPixel (&surfM, point[2].x, point[2].y);
color[3]=GetPixel (&surfM, point[3].x, point[3].y);
color[4]=GetPixel (&surfM, point[4].x, point[4].y);
color[5]=GetPixel (&surfM, point[5].x, point[5].y);
color[6]=GetPixel (&surfM, point[6].x, point[6].y);
color[7]=GetPixel (&surfM, point[7].x, point[7].y);

 if 
  (  (color[1].r==0 && color[1].g==0 && color[1].b==0)||
    (color[3].r==0 && color[3].g==0 && color[3].b==0)||
    (color[2].r==0 && color[2].g==0 && color[2].b==0)||

         (color[6].r==0 && color[6].g==0 && color[6].b==0)||
         (color[7].r==0 && color[7].g==0 && color[7].b==0)||

         (color[0].r==0 && color[0].g==0 && color[0].b==0)||
         (color[4].r==0 && color[4].g==0 && color[4].b==0)||
         (color[5].r==0 && color[5].g==0 && color[5].b==0))
 {  

return 1;
printf("frfrfrfr") ;
 }

else return 0;
}



