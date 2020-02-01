#include "arrayutils.h"


uint8_t maxArrayU8( uint8_t * array, size_t size ) {
	uint8_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }
uint16_t maxArrayU16( uint16_t * array, size_t size ) {
	uint16_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }
uint32_t maxArrayU32( uint32_t * array, size_t size ) {
	uint32_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }
uint64_t maxArrayU64( uint64_t * array, size_t size ) {
	uint64_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }


char maxArrayChar( char * array, size_t size ) {
	char m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }
int maxArrayInt( int * array, size_t size ) {
	int m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }
float maxArrayFloat( float * array, size_t size ) {
	float m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }
double maxArrayDouble( double * array, size_t size ) {
	double m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m < array[i] ) m = array[i];
	return m; }




uint8_t minArrayU8( uint8_t * array, size_t size ) {
	uint8_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }
uint16_t minArrayU16( uint16_t * array, size_t size ) {
	uint16_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }
uint32_t minArrayU32( uint32_t * array, size_t size ) {
	uint32_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }
uint64_t minArrayU64( uint64_t * array, size_t size ) {
	uint64_t m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }


char minArrayChar( char * array, size_t size ) {
	char m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }
int minArrayInt( int * array, size_t size ) {
	int m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }
float minArrayFloat( float * array, size_t size ) {
	float m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }
double minArrayDouble( double * array, size_t size ) {
	double m = array[0];
	if( size <= 1 ) return m;
	for( size_t i = 1; i < size; ++i ) if( m > array[i] ) m = array[i];
	return m; }




void printArrayU8( uint8_t * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%hhu%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }
void printArrayU16( uint16_t * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%hu%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }
void printArrayU32( uint32_t * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%u%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }
void printArrayU64( uint64_t * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%lu%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }


void printArrayChar( char * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%c%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }
void printArrayInt( int * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%d%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }
void printArrayFloat( float * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%F%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }
void printArrayDouble( double * array, size_t size ) {
	printf("[ "); for( size_t i = 0; i < size; ++i ) printf("%F%s", array[i], i != size-1 ? ", " : " "); printf("]\n"); }