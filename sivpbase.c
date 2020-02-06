#include "sivpbase.h"


static int chooseSDLMode( int chans ) {
	switch( chans ) {
		case 1: return SDL_PIXELFORMAT_RGB332;
		case 3: return SDL_PIXELFORMAT_RGB24;
		case 4: return SDL_PIXELFORMAT_RGBA32;
		default: printf("Error loading image SDL mode\n"); return SDL_PIXELFORMAT_UNKNOWN;
	}
}


void freeImage( Image * image ) {
	if( image->pixels != NULL ) {
		image->w = 0;
		image->h = 0;
		image->chans = 0;
		image->SDLmode = SDL_PIXELFORMAT_UNKNOWN;
		stbi_image_free( image->pixels );
	}
}


Image allocImage( const int width, const int height, const int chans ) {
	Image image;
	image.w = width;
	image.h = height;
	image.chans = chans;
	image.SDLmode = chooseSDLMode( chans );
	image.pixels = calloc( width * height * chans, sizeof( uint8_t ) );
	printf("Allocated space for an image of format %dx%d with %d channels\n\n", image.w, image.h, image.chans );
	return image;
}


Image storeImage( const char * path ) {
	Image image;
	image.pixels = stbi_load( path, &image.w, &image.h, &image.chans, 0 );
	image.SDLmode = chooseSDLMode( image.chans );
	if( image.w || image.h ) {
		printf("Stored image %s with format %dx%d and %d channels\n\n", path, image.w, image.h, image.chans );
	} else {
		stbi_image_free( image.pixels );
		image.pixels = NULL;
		printf("There was an error storing image %s. Perhaps it doesn't exist ?\n\n", path );
	}

	return image;
}


Histogram storeHistogram( Image * image ) {
	Histogram histogram;
	bzero( histogram.data, sizeof( uint64_t ) * 256 );

	uint64_t imageSize = image->w * image->h;
	for( uint64_t i = 0; i < imageSize; i++ ) {
		histogram.data[ image->pixels[ i ] ]++;
	} return histogram;
}





static void _displayImage( Image * image, const char * windowName, const int width, const int height ) {
	if( image->pixels == NULL ) {
		printf("Image was empty and couldn't be displayed.\n");
		return;
	}

	SDL_Window * win = SDL_CreateWindow( windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0 );
	SDL_Renderer * r = SDL_CreateRenderer( win, -1, SDL_RENDERER_TARGETTEXTURE );
	SDL_Event ev;

	SDL_Texture * tex = SDL_CreateTexture( r, image->SDLmode, SDL_TEXTUREACCESS_STATIC, image->w, image->h );
	SDL_UpdateTexture( tex, NULL, image->pixels, sizeof( uint8_t ) * image->w * image->chans );

	SDL_RenderCopy( r, tex, NULL, NULL );
	SDL_RenderPresent( r );

	while( 1 ) {
		SDL_PollEvent( &ev );
		if( ev.type == SDL_QUIT ) {
			break;
		}

		else if( ev.type == SDL_WINDOWEVENT &&
		  	   ( ev.window.event == SDL_WINDOWEVENT_SHOWN ||
				 ev.window.event == SDL_WINDOWEVENT_EXPOSED ) ) {
			SDL_RenderCopy( r, tex, NULL, NULL );
			SDL_RenderPresent( r );
		}
	}

	SDL_DestroyTexture( tex );
	SDL_DestroyRenderer( r );
	SDL_DestroyWindow( win );
}


void displayImage( Image * image ) {
	_displayImage( image, "NSVIP Image Display", image->w, image->h );
}



void displayHistogram( Histogram * histogram ) {
	const int w = 480;
	const int h = 360;
	const uint64_t maxValue = maxArrayU64( histogram->data, 256 );
	const double factorValue = 256.0 / w;
	const double factorCount = h / (double)maxValue;
	printf("%f\n", factorCount);

	Image image = allocImage( w, h, 1 );

	for( int x = 0; x < w; ++x ) {
		size_t pos = x * 3 + ( h - ( histogram->data[ (size_t)(x * factorValue) ] * factorCount ) ) * w;
		image.pixels[ pos ] = 255;
	}

	_displayImage( &image, "NSVIP Histogram Display", w, h );
	freeImage( &image );
}





void initNSIVP() {
	SDL_Init( SDL_INIT_VIDEO );
}


void exitNSIVP() {
	SDL_Quit();
	exit(0);
}



int main( int argc, char *argv[] ) {
	initNSIVP(); //init the lib

	Image image = storeImage( argv[1] ); //store an image
	Histogram hist = storeHistogram( &image ); //store the histogram of the image

	displayImage( &image ); //display the image
	freeImage( &image ); //free the image if we don't have enough memory

	displayHistogram( &hist ); //display the histogram of the image

	exitNSIVP(); //exit the lib
}