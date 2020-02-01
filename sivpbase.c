#include "sivpbase.h"


SDL_Window * win;
SDL_Renderer * r;
SDL_Event ev;


SDL_Surface * storeImage( const char * path ) {
	SDL_Surface * surface = IMG_Load( path );
	assert( surface );
	return surface;
}


Histogram storeHistogram( SDL_Surface * image ) {
	Histogram histogram;
	bzero( histogram.data, sizeof( size_t ) * 256 );

	size_t imageSize = image->w * image->h;
	for( size_t i = 0; i < imageSize; i++ ) {
		histogram.data[ ( ( uint8_t * )image->pixels )[ i ] ]++;
	} return histogram;
}





void displayTexture( SDL_Texture * tex, const char * windowName, const int width, const int height ) {
	SDL_CreateWindowAndRenderer( width, height, 0, &win, &r );
	SDL_SetWindowTitle( win, windowName );

	SDL_RenderCopy( r, tex, NULL, NULL);

	while( 1 ) {
		SDL_PollEvent( &ev );
		if( ev.type == SDL_QUIT )
			break;

		SDL_RenderPresent( r );
	}

	SDL_DestroyRenderer( r );
	SDL_DestroyWindow( win );
}


void displayImage( SDL_Surface * image ) {
	SDL_Texture * tex = SDL_CreateTextureFromSurface( r, image );
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

	SDL_UpdateTexture( tex, NULL, texContent, 1 );
	displayTexture( tex, "NSVIP Histogram Display", w, h );
	SDL_DestroyTexture( tex );
}





void initNSIVP() {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
	IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF );
}


void exitNSIVP() {
	IMG_Quit();
	exit(0);
}


int main() {
	initNSIVP();
	SDL_Surface * image = storeImage( "testimg.jpg" );
	Histogram hist = storeHistogram( image );
	displayImage( image );
	displayHistogram( &hist );
	exitNSIVP();
}