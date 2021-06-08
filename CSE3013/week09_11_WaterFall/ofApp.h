#pragma once

#include "WaterLine.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	/* WaterFall-related member variables Regions */

	// flag variables
	int draw_flag;
	int load_flag;
	int waterfall_flag;
	int get_path;

	// Line segment and dot related variables
	int num_of_line, num_of_dot;
	float dot_diameter;
	vector<pair<int, int>> dots;
	vector<pair<int, int>> lines;
	WaterLine water_fall;
	int selected_dot = 0;

	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.

};
