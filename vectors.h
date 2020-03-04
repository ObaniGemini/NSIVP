#include <math.h>

typedef struct {
	int x;
	int y;
} Vec2D;

typedef struct {
	int x;
	int y;
	int z;
} Vec3D;

Vec2D makeVec2D( int x, int y );
Vec3D makeVec3D( int x, int y, int z );
double distanceVec2D( Vec2D A, Vec2D B );
double distanceVec3D( Vec3D A, Vec3D B );
