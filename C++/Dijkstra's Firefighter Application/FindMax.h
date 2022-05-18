#ifndef _FINDMAX_H
#define	_FINDMAX_H
#include "RunFind.h"



class Vertex
{
public:
	Vertex():endx(0),endy(0),time(0){}
  short int endx;
  short  int endy;
  int time;
};

class Details
{
public:
	Details():known(false),time(2147483646),count(0),x(0),y(0){}
	bool known;
	int time;
	short int count;
	short int x;
	short int y;
	Vertex vertices[4];

};



class FindMax {
public:
	Details adjacencyMatrix[1000][1000];
  FindMax(short int citySize, const StreetBlock *streets,int numStreets);
  short int interCount;
  void find(Coordinate fireHouses[4], Coordinate *furthest, int *time);
}; // class FindMax

#endif	/* _FINDMAX_H */
