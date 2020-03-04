#include "vectors.h"



Vec2D makeVec2D( int x, int y ) {
	Vec2D vec;
	vec.x = x;
	vec.y = y;
	return vec;
}

Vec3D makeVec3D( int x, int y, int z ) {
	Vec3D vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}



double distanceVec2D( Vec2D A, Vec2D B ) {
	int tmp1 = A.x - B.x;
	int tmp2 = A.y - B.y;

	return sqrt( tmp1*tmp1 + tmp2*tmp2 );
}

double distanceVec3D( Vec3D A, Vec3D B ) {
	int tmp1 = A.x - B.x;
	int tmp2 = A.y - B.y;
	int tmp3 = A.z - B.z;

	return sqrt( tmp1*tmp1 + tmp2*tmp2 + tmp3*tmp3 );
}


double normVec2D( Vec2D A ) {
	return sqrt( A.x * A.x + A.y * A.y );
}

double normVec3D( Vec3D A ) {
	return sqrt( A.x * A.x + A.y * A.y + A.z * A.z );
}