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





void displayTexture( SDL_Texture * tex, const char * windowName ) {
	SDL_CreateWindowAndRenderer( tex->w, tex->h, 0, &win, &r );
	SDL_SetWindowTitle( win, windowName );

	while( 1 ) {
		SDL_PollEvent( &ev );
		if( ev.type == SDL_QUIT )
			break;

		SDL_RenderCopy( r, tex, NULL, NULL);
		SDL_RenderPresent( r );
	}

	SDL_DestroyRenderer( r );
	SDL_DestroyWindow( win );
}


void displayImage( SDL_Surface * image ) {
	SDL_Texture * tex = SDL_CreateTextureFromSurface( r, image );
	displayTexture( tex, "NSVIP Picture Display" );
	SDL_DestroyTexture( tex );
}


void displayHistogram( Histogram * histogram ) {
	SDL_Texture * tex = SDL_CreateTexture( r, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 640, 480 );

	const size_t maxValue = maxArrayU8( tex->pixels, 921600 ); //640 * 480 * 3
	const double factorValue = 256.0 / 640.0;
	const double factorCount = 480.0 / maxValue;
	const size_t w = tex->w;
	const size_t h = tex->h;

	uint8_t texContent[ w * h * 3 ];
	bzero( texContent, sizeof( uint8_t ) * w * h * 3 ); //black out


	for( int i = 0; i < 640; ++i ) {
		size_t pos = i * 3 + ( h - ( histogram->data[ (int)(i * factorValue) ] * factorCount ) ) * w * 3;
		texContent[ pos ] = 255;
		texContent[ pos + 1 ] = 255;
		texContent[ pos + 2 ] = 255;
	}

	SDL_UpdateTexture( tex, NULL, texContent, 1 );
	displayTexture( tex, "NSVIP Histogram Display" );
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