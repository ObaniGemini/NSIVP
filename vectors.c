#include "vectors.h"



Vec2Di makeVec2Di( ssize_t x, ssize_t y ) {
	Vec2Di vec = { x, y };
	return vec; }
Vec2Df makeVec2Df( double x, double y ) {
	Vec2Df vec = { x, y };
	return vec; }

Vec3Di makeVec3Di( ssize_t x, ssize_t y, ssize_t z ) {
	Vec3Di vec = { x, y, z };
	return vec; }
Vec3Df makeVec3Df( double x, double y, double z ) {
	Vec3Df vec = { x, y, z };
	return vec; }





double distanceVec2Di( Vec2Di A, Vec2Di B ) {
	ssize_t tmp1 = A.x - B.x;
	ssize_t tmp2 = A.y - B.y;
	return sqrt( tmp1*tmp1 + tmp2*tmp2 ); }
double distanceVec2Df( Vec2Df A, Vec2Df B ) {
	ssize_t tmp1 = A.x - B.x;
	ssize_t tmp2 = A.y - B.y;
	return sqrt( tmp1*tmp1 + tmp2*tmp2 ); }

double distanceVec3Di( Vec3Di A, Vec3Di B ) {
	ssize_t tmp1 = A.x - B.x;
	ssize_t tmp2 = A.y - B.y;
	ssize_t tmp3 = A.z - B.z;
	return sqrt( tmp1*tmp1 + tmp2*tmp2 + tmp3*tmp3 ); }
double distanceVec3Df( Vec3Df A, Vec3Df B ) {
	ssize_t tmp1 = A.x - B.x;
	ssize_t tmp2 = A.y - B.y;
	ssize_t tmp3 = A.z - B.z;
	return sqrt( tmp1*tmp1 + tmp2*tmp2 + tmp3*tmp3 ); }




double normVec2Di( Vec2Di A ) { return sqrt( A.x * A.x + A.y * A.y ); }
double normVec3Di( Vec3Di A ) { return sqrt( A.x * A.x + A.y * A.y + A.z * A.z ); }

double normVec2Df( Vec2Df A ) { return sqrt( A.x * A.x + A.y * A.y ); }
double normVec3Df( Vec3Df A ) { return sqrt( A.x * A.x + A.y * A.y + A.z * A.z ); }