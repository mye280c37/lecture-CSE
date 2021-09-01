/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/

	#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon

typedef struct _mazeEle {
	int parent;
	int child_num;
	int child_list[4];
}MazeEle;

typedef struct _Line {
	int x1;
	int y1;
	int x2;
	int y2;
}Line;

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool readFile();
		void freeMemory();
		bool DFS();
		bool BFS();
		void dfsdraw();
		void bfsdraw();
		int HEIGHT;//�̷��� ���� M
		int WIDTH;//�̷��� �ʺ� N
		int wall_length;
		char** input;//�ؽ�Ʈ ������ ��� ������ ��� ������ �迭�̴�.
		MazeEle *maze_ele; //�̷��� �� ĭ�� ���� ������ ��� 1���� �迭�̴�.
		int **col_wall;
		int **row_wall;
		int *visited;
		int maze_col;//�̷�ĭ�� ���� �ε����� ����Ų��.
		int maze_row;//�̷�ĭ�� ���� �ε����� ����Ų��.
		int k;
		int isOpen; //������ ���ȴ����� �Ǵ��ϴ� ����. 0�̸� �ȿ��Ȱ� 1�̸� ���ȴ�.
		int isDFS;//DFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
		int isBFS;//BFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
		vector<Line>dfs_line;
		vector<Line>main_dfs;
		vector<Line>bfs_line;
		vector<Line>main_bfs;
		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		bool isdfs;
		bool isbfs;
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);

};
