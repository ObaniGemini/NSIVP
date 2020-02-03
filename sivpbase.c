#include "sivpbase.h"


static int chooseSDLMode( int chans ) {
	switch( chans ) {
		case 1: return SDL_PIXELFORMAT_INDEX8;
		case 3: return SDL_PIXELFORMAT_RGB888;
		case 4: return SDL_PIXELFORMAT_RGBA8888;
		default: printf("Error loading image SDL mode\n"); return SDL_PIXELFORMAT_UNKNOWN;
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
	
	SDL_Window * win = SDL_CreateWindow( windowName, 0, 0, width, height, 0 );
	SDL_Renderer * r = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );
	SDL_Event ev;

	SDL_Texture * tex = SDL_CreateTexture( r, image->SDLmode, 0, image->w, image->h );
	SDL_UpdateTexture( tex, NULL, image->pixels, sizeof( uint8_t ) * image->chans * image->w );

	SDL_RenderCopy( r, tex, NULL, NULL );

	while( 1 ) {
		SDL_PollEvent( &ev );
		if( ev.type == SDL_QUIT )
			break;

		SDL_RenderPresent( r );
	}

	SDL_DestroyTexture( tex );
	SDL_DestroyRenderer( r );
	SDL_DestroyWindow( win );


}


void displayImage( Image * image ) {
	_displayImage( image, "NSVIP Image Display", image->w, image->h );
}



void displayHistogram( Histogram * histogram ) {
	const int w = 640;
	const int h = 480;
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
	initNSIVP();
	Image image = storeImage( "testimg.jpg" );
	Histogram hist = storeHistogram( &image );
	displayImage( &image );
	displayHistogram( &hist );
	exitNSIVP();
}