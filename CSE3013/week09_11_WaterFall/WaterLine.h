#ifndef WATER_LINE_H
#define WATER_LINE_H

#include "ofMain.h"

class WaterLine {
public:
	vector<pair<int, int>> path;
	int necessary_lines;
	int x;
	int y;
	int draw_lines;

	WaterLine();
	~WaterLine();

	void start(int start_x, int start_y);
	void reset();
	void draw();
	int calculatePath(int num_of_line, vector<pair<int, int>> lines);
};

#endif
