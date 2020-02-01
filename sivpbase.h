#include <assert.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "arrayutils.h"


typedef struct {
	size_t data[256];
} Histogram;


SDL_Surface * storeImage( const char * path );
Histogram storeHistogram( SDL_Surface * image );

void displayTexture( SDL_Texture * tex, const char * windowName, const int width, const int height ); //private
void displayImage( SDL_Surface * image );
void displayHistogram( Histogram * histogram );

void rgb2gray( SDL_Surface * image );


void initNSIVP();
void exitNSIVP();