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

unsigned short getTankPositionGlobal() {
  return tankPosition;
}

void setTankBulletPosition(point_t val) {
  tankBulletPosition.x = val.x;
  tankBulletPosition.y = val.y;
}

point_t getTankBulletPosition() {
  return tankBulletPosition;
}
