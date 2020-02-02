#include <assert.h>
#include <string.h>

#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "arrayutils.h"


typedef struct {
	int w, h;
	int chans;
	int SDLmode;
	uint8_t * pixels;
} Image;

typedef struct {
	size_t data[256];
} Histogram;


Image storeImage( const char * path );
Histogram storeHistogram( Image * image );

void displayTexture( SDL_Texture * tex, const char * windowName, const int width, const int height ); //private
void displayImage( Image * image );
void displayHistogram( Histogram * histogram );

void rgb2gray( Image * image );


void initNSIVP();
void exitNSIVP();