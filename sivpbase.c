#include "sivpbase.h"


SDL_Window * win;
SDL_Renderer * r;
SDL_Event ev;


Image storeImage( const char * path ) {
	Image image;
	image.pixels = stbi_load( path, &image.w, &image.h, &image.chans, 0 );
	switch( image.chans ) {
		case 1: image.SDLmode = SDL_PIXELFORMAT_INDEX8; break;
		case 3: image.SDLmode = SDL_PIXELFORMAT_RGB888; break;
		case 4: image.SDLmode = SDL_PIXELFORMAT_RGBA8888; break;
		default: printf("Error loading image %s (unknown channels number)\n", path); exit(1); break;
	} return image;
}


Histogram storeHistogram( Image * image ) {
	Histogram histogram;
	bzero( histogram.data, sizeof( size_t ) * 256 );

	size_t imageSize = image->w * image->h;
	for( size_t i = 0; i < imageSize; i++ ) {
		histogram.data[ image->pixels[ i ] ]++;
	} return histogram;
}





void displayTexture( SDL_Texture * tex, const char * windowName, const int width, const int height ) {
	win = SDL_CreateWindow( windowName, 0, 0, width, height, 0 );
	r = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

	SDL_Rect rect = { 0, 0, width, height };
	SDL_RenderCopy( r, tex, NULL, &rect );

	while( 1 ) {
		SDL_PollEvent( &ev );
		if( ev.type == SDL_QUIT )
			break;

		SDL_RenderPresent( r );
	}

	SDL_DestroyRenderer( r );
	SDL_DestroyWindow( win );
}


void displayImage( Image * image ) {
	SDL_Texture * tex = SDL_CreateTexture( r, image->SDLmode, 0, image->w, image->h );
	SDL_UpdateTexture( tex, NULL, image->pixels, sizeof( uint8_t ) * image->chans );
	displayTexture( tex, "NSVIP Picture Display", image->w, image->h );
	SDL_DestroyTexture( tex );
}


void displayHistogram( Histogram * histogram ) {
	const int w = 640;
	const int h = 480;
	const uint64_t maxValue = maxArrayU64( histogram->data, 256 ); //640 * 480 * 3
	const double factorValue = 256.0 / w;
	const double factorCount = h / maxValue;

	SDL_Texture * tex = SDL_CreateTexture( r, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, w, h );

	uint8_t texContent[ w * h * 3 ];
	bzero( texContent, sizeof( uint8_t ) * w * h * 3 ); //black out


	for( int i = 0; i < w; ++i ) {
		size_t pos = i * 3 + ( h - ( histogram->data[ (size_t)(i * factorValue) ] * factorCount ) ) * ( w - 1 ) * 3;
		texContent[ pos ] = 255;
		texContent[ pos + 1 ] = 255;
		texContent[ pos + 2 ] = 255;
	}

	SDL_UpdateTexture( tex, NULL, texContent, sizeof( uint8_t ) * 3 );
	displayTexture( tex, "NSVIP Histogram Display", w, h );
	SDL_DestroyTexture( tex );
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