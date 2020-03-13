#include "sivpbase.h"


static int chooseSDLMode( int chans ) {
	switch( chans ) {
		case 1: return SDL_PIXELFORMAT_RGB332;
		case 3: return SDL_PIXELFORMAT_RGB24;
		case 4: return SDL_PIXELFORMAT_RGBA32;
		default: printf("Error loading image SDL mode\n"); return SDL_PIXELFORMAT_UNKNOWN;
	}
}


static void _drawVerticalLine( Image image, int X, int Y ) {
	for( int y = Y; y < image.h; y++ ) {
		image.pixels[ X + y * image.w ] = 255;
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


Histogram storeHistogram( Image image ) {
	Histogram histogram;
	bzero( histogram.data, sizeof( uint64_t ) * 256 );

	uint64_t imageSize = image.w * image.h;
	for( uint64_t i = 0; i < imageSize; i++ ) {
		histogram.data[ image.pixels[ i ] ]++;
	} return histogram;
}


void clearImage( Image * image ) {
	memset( image->pixels, 0, image->w * image->h * image->chans );
}


void clearHistogram( Histogram * histogram ) {
	memset( histogram->data, 0, 256 * sizeof( uint64_t ) );
}


int saveImage( const char * path, Image image ) {
	const char * format = path + strlen( path ) - 3;

	if( strcmp( format, "png" ) == 0 ) {
		return stbi_write_png( path, image.w, image.h, 3, image.pixels, image.w * 3 );
	} else if( strcmp( format, "bmp" ) == 0 ) {
		return stbi_write_bmp( path, image.w, image.h, 3, image.pixels );
	} else if( strcmp( format, "tga" ) == 0 ) {
		return stbi_write_tga( path, image.w, image.h, 3, image.pixels );
	} else if( strcmp( format, "jpg" ) == 0 ) {
		return stbi_write_jpg( path, image.w, image.h, 3, image.pixels, 100 );
	} else {
		printf("Unrecognized format %s\n", format);
	}
	
	return 0;
}




static void _displayImage( Image image, const char * windowName, const int width, const int height ) {
	if( image.pixels == NULL ) {
		printf("Image was empty and couldn't be displayed.\n");
		return;
	}

	SDL_Window * win = SDL_CreateWindow( windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0 );
	SDL_Renderer * r = SDL_CreateRenderer( win, -1, SDL_RENDERER_TARGETTEXTURE );
	SDL_Event ev;

	SDL_Texture * tex = SDL_CreateTexture( r, image.SDLmode, SDL_TEXTUREACCESS_STATIC, image.w, image.h );
	SDL_UpdateTexture( tex, NULL, image.pixels, sizeof( uint8_t ) * image.w * image.chans );

	SDL_RenderCopy( r, tex, NULL, NULL );
	SDL_RenderPresent( r );

	int imageSaved = 0;
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

		else if( ev.type == SDL_KEYDOWN && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_F12 && !imageSaved ) {
			time_t currTime = time( NULL );
			struct tm * t = gmtime( &currTime ); 
			char * fileName = malloc( sizeof( char ) * 24 );
			sprintf( fileName, "%d_%d_%d_%d-%d-%d.png", t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );


			if( saveImage( fileName, image ) ) {
				printf( "Saved image %s\n", fileName );
				imageSaved = 1;
			} else {
				printf( "Failed saving image %s\n", fileName );
			}
		}
	}

	SDL_DestroyTexture( tex );
	SDL_DestroyRenderer( r );
	SDL_DestroyWindow( win );
}


void displayImage( Image image ) {
	_displayImage( image, "NSVIP Image Display", image.w, image.h );
}



void displayHistogram( Histogram * histogram ) {
	const int w = 480;
	const int h = 360;
	const uint64_t maxValue = maxArrayU64( histogram->data, 256 );
	const double factorValue = w / 256.0;
	const double factorCount = h / (double)maxValue;

	Image image = allocImage( w, h, 1 );

	for( int x = 0; x < 256; x++ ) {
		_drawVerticalLine( image, (int)(x * factorValue), ( h - (int)( histogram->data[ x ] * factorCount ) ) );
	}

	_displayImage( image, "NSVIP Histogram Display", w, h );
	freeImage( &image );
}



Image rgb2gray( Image image ) {
	Image output = allocImage( image.w, image.h, 1 );
	size_t numPixels = image.w * image.h;
	int chans = image.chans;

	for( size_t i = 0; i < numPixels; i++ ) {
		output.pixels[ i ] = (	(size_t)image.pixels[ i*chans ] *
								(size_t)image.pixels[ i*chans + 1 ] *
								(size_t)image.pixels[ i*chans + 2 ] ) /
							    (size_t)( 255 * 255 );
	} return output;
}



/*
	it's the same that inlincomb you just have to add the count which is the number of argument
	only for double
*/
double imlincomb( int count, ... )
{	double sum = 0;
	va_list ap;
	va_start( ap, count );

	for( int i = 0; i < count; i += 2 ) {
		sum += va_arg( ap, double ) * va_arg( ap, double );
	}
	va_end( ap );
	return sum;
}


/*
	it's the same that inlincomb you just have to add the count which is the number of argument
	only for tab of double
	copie[0] is the size of each tab
	and the tab of return 
*/
void inlincombtab( double* copie, size_t count, ... )
{	double sum;
	va_list ap;
	int size = (int)copie[0];
	for( int i = 0; i < size; ++i ) {
		sum = 0;
		va_start( ap, count );
		for( size_t j = 0; j <= count/2; ++j ) {
			sum += va_arg( ap, double ) * va_arg( ap, double* )[j];
		}
		copie[i] = sum;
		va_end( ap );
	}
}




Image imageMultiply( Image X, Image Y )
{	Image image;
	int taille;

	if( ( X.w * X.h ) > ( Y.w * Y.h ) ) {
		taille = Y.w * Y.h ;
		image = allocImage( X.w, X.h, 1 );
		for( int i = 0; i < taille; ++i ) {
			image.pixels[i] = ( X.pixels[i] * Y.pixels[i] ) ;
		}

		for( int i = taille + 1; i < X.w * X.h; ++i ) {
			image.pixels[i] = X.pixels[i];
		}
	}
	else {
		taille = X.w * X.h ;
		image = allocImage( Y.w, Y.h, 1 );
		for( int i = 0; i < taille; ++i ) {
			image.pixels[i] = ( X.pixels[i] * Y.pixels[i] ) ;
		
		}
		for( int i = taille + 1; i < Y.w * Y.h; ++i ) {
			image.pixels[i] = Y.pixels[i];
		}
	} return image;
}




void initNSIVP() {
	SDL_Init( SDL_INIT_VIDEO );
}


void exitNSIVP() {
	SDL_Quit();
	exit(0);
}




/*int main( int argc, char *argv[] ) {
	if( argc < 2 ) {
		fprintf( stderr, "%s %d\n", "<image> not found", __LINE__ );
		exit(0);
	}

	initNSIVP(); //init the lib

	Image image = storeImage( argv[1] ); //store an image
	Image image2 = imageMultiply( image, image ); //store the multiplication of image by itself
	Image gray = rgb2gray( image ); //store the gray-colored version of the image
	
	displayImage( image ); //display the image
	displayImage( image2 ); //display the multiplied image
	displayImage( gray ); //display the gray image

	Histogram hist = storeHistogram( image ); //store the histogram of the image gray

	freeImage( &image ); //free the image 1
	freeImage( &image2 ); //free the image 2
	freeImage( &gray ); //free the image gray

	displayHistogram( &hist ); //display the histogram of the image gray

	exitNSIVP(); //exit the lib
}*/