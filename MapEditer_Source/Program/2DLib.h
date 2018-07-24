#ifndef LIB_H
#define LIB_H
#include "CRectangle.h"

void AddY(CRectangle*rect, float i);
void AddX(CRectangle*rect, float i);
bool Collision(CRectangle *prect1, CRectangle *prect2);

#endif