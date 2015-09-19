#include <stdio.h>

#include "globals.h"
int main() {
  point_t currentPosition;
  currentPosition.x = 99;
  currentPosition.y = 11;

  setTankPositionGlobal(14);
  xil_printf("tank position: %d\n\r", getTankPositionGlobal());

  setTankBulletPosition(currentPosition);
  xil_printf("tank x:%d tank y:%d\n\r", getTankBulletPosition().x, getTankBulletPosition().y);

  // What does this do?
  point_t anotherTankBulletPosition = getTankBulletPosition();
  anotherTankBulletPosition.x = 55;
  anotherTankBulletPosition.y = 44;
  // Does this affect the value of the global?
  xil_printf("tank x:%d tank y:%d\n\r", getTankBulletPosition().x, getTankBulletPosition().y);

}
