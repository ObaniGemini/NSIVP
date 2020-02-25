#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "arrayutils.h"

typedef struct {
	int w, h;
	int chans;
	int SDLmode;
	uint8_t * pixels;
} Image;

typedef struct {
	uint64_t data[256];
} Histogram;

void freeImage( Image * image );
Image allocImage( int width, int height, int chans );

Image storeImage( const char * path );
Histogram storeHistogram( Image image );

void displayImage( Image image );
void displayHistogram( Histogram * histogram );

Image rgb2gray( Image image );
Image imageMultiply( Image X, Image Y );

void initNSIVP();
void exitNSIVP();