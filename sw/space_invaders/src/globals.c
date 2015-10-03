
// Demonstrates one way to handle globals safely in C.
#include "globals.h"

// Here are the globals.
static unsigned short tankPosition;
static point_t tankBulletPosition;
static point_t alienBlockPosition;

// Here are the accessors.

void setTankPositionGlobal(unsigned short val) {
  tankPosition = val;
}

// return the poisition of the tank
unsigned short getTankPositionGlobal() {
  return tankPosition;
}


// set the starting point of newly-fired tank missile
void setTankBulletPosition(point_t val) {
  tankBulletPosition.x = val.x;
  tankBulletPosition.y = val.y;
}

// return the current position of the tank bullet
point_t getTankBulletPosition() {
  return tankBulletPosition;
}
