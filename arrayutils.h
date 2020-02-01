#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define min( a, b ) ( a > b ? b : a )
#define max( a, b ) ( a > b ? a : b )


uint8_t maxArrayU8( uint8_t * array, size_t size );
uint16_t maxArrayU16( uint16_t * array, size_t size );
uint32_t maxArrayU32( uint32_t * array, size_t size );
uint64_t maxArrayU64( uint64_t * array, size_t size );

char maxArrayChar( char * array, size_t size );
int maxArrayInt( int * array, size_t size );
float maxArrayFloat( float * array, size_t size );
double maxArrayDouble( double * array, size_t size );


uint8_t minArrayU8( uint8_t * array, size_t size );
uint16_t minArrayU16( uint16_t * array, size_t size );
uint32_t minArrayU32( uint32_t * array, size_t size );
uint64_t minArrayU64( uint64_t * array, size_t size );

char minArrayChar( char * array, size_t size );
int minArrayInt( int * array, size_t size );
float minArrayFloat( float * array, size_t size );
double minArrayDouble( double * array, size_t size );



void printArrayU8( uint8_t * array, size_t size );
void printArrayU16( uint16_t * array, size_t size );
void printArrayU32( uint32_t * array, size_t size );
void printArrayU64( uint64_t * array, size_t size );

void printArrayChar( char * array, size_t size );
void printArrayInt( int * array, size_t size );
void printArrayFloat( float * array, size_t size );
void printArrayDouble( double * array, size_t size );