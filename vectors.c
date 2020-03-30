#include "vectors.h"



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