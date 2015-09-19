// Demonstrates one way to handle globals safely in C.
#include "globals.h"

// Here are the globals.
static unsigned short tankPosition;
static point_t tankBulletPosition;
static point_t alienBlockPosition;

int alien_lives_matter[64] = {0};

int* getAlienLives(){
	return alien_lives_matter;
}

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

//////////////// Another way to do this without structs ////////////////
unsigned short tankBulletPositionX;
unsigned short tankBulletPositionY;

void setTankBulletPositionX(unsigned short val) {tankBulletPositionX = val;}
void setTankBulletPositionY(unsigned short val) {tankBulletPositionY = val;}

unsigned short getTankBulletPositionX(){return tankBulletPositionX;}
unsigned short getTankBulletPositionY(){return tankBulletPositionY;}
