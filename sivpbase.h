#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include "arrayutils.h"
#include "vectors.h"

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

void clearImage( Image * image );
void clearHistogram( Histogram * histogram );

int saveImage( const char * path, Image image );

void displayImage( Image image );
void displayHistogram( Histogram * histogram );

Image rgb2gray( Image image );
Image imageMultiply( Image X, Image Y );

void initNSIVP();
void exitNSIVP();