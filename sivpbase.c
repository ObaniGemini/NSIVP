#include "sivpbase.h"


static int chooseSDLMode( int chans ) {
	switch( chans ) {
		case 1: return SDL_PIXELFORMAT_INDEX8;
		case 3: return SDL_PIXELFORMAT_RGB888;
		case 4: return SDL_PIXELFORMAT_RGBA8888;
		default: printf("Error loading image SDL mode\n"); return SDL_PIXELFORMAT_UNKNOWN;
	}
}

void freeImage( Image * image ) {
	if( image->w || image->h ) {
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
	image.pixels = calloc( image.chans * image.w * image.h, sizeof( uint8_t ) );
	return image;
}


Image storeImage( const char * path ) {
	Image image;
	image.pixels = stbi_load( path, &image.w, &image.h, &image.chans, 0 );
	image.SDLmode = chooseSDLMode( image.chans );
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
	const double factorCount = h / maxValue;

	Image image = allocImage( w, h, 3 );


	for( int i = 0; i < w; ++i ) {
		size_t pos = i * 3 + ( h - ( histogram->data[ (size_t)(i * factorValue) ] * factorCount ) ) * ( w - 1 ) * 3;
		image.pixels[ pos ] = 255;
		image.pixels[ pos + 1 ] = 255;
		image.pixels[ pos + 2 ] = 255;
	}

	_displayImage( &image, "NSVIP Histogram Display", w, h );
}





void initNSIVP() {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
}


void exitNSIVP() {
	SDL_Quit();
	exit(0);
}



int main() {
	initNSIVP(); //init the lib

	Image image = storeImage( "testimg.jpg" ); //store an image
	Histogram hist = storeHistogram( &image ); //store the histogram of the image

	displayImage( &image ); //display the image
	freeImage( &image ); //free the image if we don't have enough memory

	displayHistogram( &hist ); //display the histogram of the image

	exitNSIVP(); //exit the lib
}