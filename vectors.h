#include <math.h>
#include <sys/types.h>

typedef struct { ssize_t x, y; } Vec2Di;
typedef struct { double x, y; } Vec2Df;

typedef struct { ssize_t x, y, z; } Vec3Di;
typedef struct { double x, y, z; } Vec3Df;

double distanceVec2Di( Vec2Di A, Vec2Di B );
double distanceVec2Df( Vec2Df A, Vec2Df B );
double distanceVec3Di( Vec3Di A, Vec3Di B );
double distanceVec3Df( Vec3Df A, Vec3Df B );

double normVec2Di( Vec2Di A );
double normVec2Df( Vec2Df A );
double normVec3Di( Vec3Di A );
double normVec3Df( Vec3Df A );