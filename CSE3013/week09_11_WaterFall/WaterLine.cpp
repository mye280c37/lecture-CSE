#include "WaterLine.h"

WaterLine::WaterLine(){

}

WaterLine::~WaterLine() {

}

void WaterLine::start(int start_x, int start_y) {
	path.push_back({ start_x, start_y });
	x = start_x;
	y = start_y;
	necessary_lines = 0;
	draw_lines = 0;
}

void WaterLine::reset() {
	path.clear();
}

void WaterLine::draw() {
	ofSetColor(0, 0, 255);
	for (int i = 0; i < draw_lines; i++) {
		ofDrawLine((float)path[i].first, (float)path[i].second, (float)path[i + 1].first, (float)path[i + 1].second);
	}
	if (draw_lines < necessary_lines) draw_lines++;
}

int WaterLine::calculatePath(int num_of_line, vector<pair<int, int>> lines) {
	int cur_x = path[0].first;
	int cur_y = path[0].second;
	int past_line = -1;

	while (cur_y < ofGetHeight()-50) {
		pair<int, int> next = { cur_x, ofGetHeight()-50 };

		int tmp_x = cur_x;
		int tmp_y = cur_y;
		int line_index = -1;
		double slope = 0;

		for (int i = 0; i < num_of_line; i++) {
			if (past_line == i * 2 || past_line == i * 2 + 1) continue;

			pair<int, int> line_start = lines[i * 2], line_end = lines[i * 2 + 1];

			if (cur_y >= line_start.second && cur_y >= line_end.second)  continue;
			if (line_start.first > cur_x || cur_x > line_end.first) continue;

			slope = (double)(line_end.second - line_start.second) / (double)(line_end.first - line_start.first);

			tmp_y = line_start.second + slope * (cur_x - line_start.first);

			if (tmp_y < next.second) {
				next.second = tmp_y;
				if (slope < 0) line_index = i * 2;
				else line_index = i * 2 + 1;
			}

		}

		for (int i = 5+cur_y; i < next.second; ) {
			path.push_back({ cur_x, i });
			necessary_lines++;
			i += 5;
		}
		path.push_back({ next.first, next.second });
		necessary_lines++;
		cur_x = next.first;
		cur_y = next.second;
		if (line_index != -1) {
			next.first = lines[line_index].first;
			next.second = lines[line_index].second;
			for (int i = 3 + cur_y; i < next.second; ) {
				path.push_back({ cur_x + (i-cur_y)/slope, i });
				necessary_lines++;
				i += 3;
			}
			path.push_back({ next.first, next.second });
			necessary_lines++;
			past_line = line_index;
			cur_x = next.first;
			cur_y = next.second;
		}
	}
	
	return 1;
}
