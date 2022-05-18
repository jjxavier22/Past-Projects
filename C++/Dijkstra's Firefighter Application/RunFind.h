// Author: Sean Davis
#ifndef RUNFIND_H
#define	RUNFIND_H

struct Coordinate
{
  int x;
  int y;
};

struct StreetBlock
{
  int startX;
  int startY;
  int endX;
  int endY;
  int speed;
};

#endif	// RUNFIND_H

