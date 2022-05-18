// Author Sean Davis

#include "FindMax.h"
#include <iostream>
#include <cstdlib>
#include "BinaryHeap.h"

FindMax::FindMax(short int citySize, const StreetBlock *streets, int numStreets)
{
	interCount = 0;
	Vertex currentInput;
	for (int i = 0; i < numStreets; i++){
		currentInput.endx = streets[i].endX;
		currentInput.endy = streets[i].endY;

		currentInput.time = 3600 * 10000 * abs(streets[i].endX-streets[i].startX + streets[i].endY - streets[i].startY) / streets[i].speed;

		adjacencyMatrix[streets[i].startY][streets[i].startX].x = streets[i].startX;
		adjacencyMatrix[streets[i].startY][streets[i].startX].y = streets[i].startY;

		adjacencyMatrix[streets[i].startY][streets[i].startX].
		vertices[adjacencyMatrix[streets[i].startY][streets[i].startX].count] = currentInput;

		adjacencyMatrix[streets[i].startY][streets[i].startX].
		count ++;


		if(adjacencyMatrix[streets[i].startY][streets[i].startX].
		count == 1){
			interCount++;
		}

		////////////////////////////////

		currentInput.endx = streets[i].startX;
		currentInput.endy = streets[i].startY;

		adjacencyMatrix[streets[i].endY][streets[i].endX].x = streets[i].endX;
		adjacencyMatrix[streets[i].endY][streets[i].endX].y = streets[i].endY;

		adjacencyMatrix[streets[i].endY][streets[i].endX].
		vertices[adjacencyMatrix[streets[i].endY][streets[i].endX].count] = currentInput;

		adjacencyMatrix[streets[i].endY][streets[i].endX].
		count ++;

		if(adjacencyMatrix[streets[i].endY][streets[i].endX].
		count == 1){
			interCount++;
		}
	}
} // FindMax()

void FindMax::find(Coordinate fireHouses[4], Coordinate *furthest, int *time)
{
	BinaryHeap <Details> dijkstraHeap(100000);
	short int knownIntCount = 0;
	short int curX;
	short int curY;
	int bigMax = 0;
	short int xMax = 0;
	short int yMax = 0;

	for (short int i = 0; i < 4; i++){
		adjacencyMatrix[fireHouses[i].y][fireHouses[i].x].time = 0;
		dijkstraHeap.insert(adjacencyMatrix[fireHouses[i].y][fireHouses[i].x]);
	}


	while(!dijkstraHeap.isEmpty()){
		Details curDetail;
		int newTime;
		dijkstraHeap.deleteMin(curDetail);
		curX = curDetail.x;
		curY = curDetail.y;
		if (curDetail.known == true){
			continue;
		}
		if ( adjacencyMatrix[curY][curX].time > bigMax){
			bigMax = adjacencyMatrix[curY][curX].time;
			xMax = curX;
			yMax = curY;
		}
		adjacencyMatrix[curY][curX].known = true;
		knownIntCount++;
		for (short int i = 0; i < adjacencyMatrix[curY][curX].count; i++){
			newTime = adjacencyMatrix[curY][curX].vertices[i].time + adjacencyMatrix[curY][curX].time;
			if ( newTime < adjacencyMatrix[adjacencyMatrix[curY][curX].vertices[i].endy][adjacencyMatrix[curY][curX].vertices[i].endx].time) {
				adjacencyMatrix[adjacencyMatrix[curY][curX].vertices[i].endy][adjacencyMatrix[curY][curX].vertices[i].endx].time   = newTime;
				if (adjacencyMatrix[adjacencyMatrix[curY][curX].vertices[i].endy][adjacencyMatrix[curY][curX].vertices[i].endx].known != true){
					dijkstraHeap.insert(adjacencyMatrix[adjacencyMatrix[curY][curX].vertices[i].endy][adjacencyMatrix[curY][curX].vertices[i].endx]);
				}
			}
		}
	}
	furthest->x = xMax;
	furthest->y = yMax;
	*time = adjacencyMatrix[yMax][xMax].time / 100000;
} // find()
