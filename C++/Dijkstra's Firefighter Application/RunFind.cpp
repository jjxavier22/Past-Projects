//* Author: Sean Davis
#include <iostream>
#include <fstream>
#include "RunFind.h"
#include "CPUTimer.h"
#include "FindMax.h"

using namespace std;

void readFile(Coordinate fireHouses[4], StreetBlock *streets, int numStreets,
  Coordinate *maxCoord, int *maxTime, ifstream &inf)
{
  for(int i = 0; i < 4; i++)
    inf >> fireHouses[i].x >> fireHouses[i].y;

  inf >> maxCoord->x >> maxCoord->y >> *maxTime;

  for(int i = 0; i < numStreets; i++)
    inf >> streets[i].startX >> streets[i].startY >> streets[i].endX
      >> streets[i].endY >> streets[i].speed;

  inf.close();
}  // readFile

int main(int argc, char** argv)
{
  int citySize, numStreets, maxTime, worstTime;
  Coordinate fireHouses[4], maxCoord, worstCoord;
  ifstream inf(argv[1]);
  inf >> citySize >> numStreets;
  StreetBlock *streets = new StreetBlock[numStreets];
  readFile(fireHouses, streets, numStreets, &maxCoord, &maxTime, inf);
  CPUTimer ct;
  ct.reset();
  FindMax *findMax = new FindMax(citySize, streets, numStreets);
  delete [] streets;
  findMax->find(fireHouses, &worstCoord, &worstTime);

  if(maxCoord.x != worstCoord.x || maxCoord.y != worstCoord.y)
    cout << "Coordinates do not match.  Solution: ("  << maxCoord.x << ", "
      << maxCoord.y << ") Yours: (" << worstCoord.x << ", " << worstCoord.y
      << ")\n";

  if(worstTime < maxTime - 1 || worstTime > maxTime + 1)
    cout << "Times do not match. Solution: "  << maxTime << " Yours: "
      << worstTime << endl;

  cout << "CPU Time: " << ct.cur_CPUTime() << endl;
  return 0;
} // main()

