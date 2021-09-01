/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

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

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Open") {
		readFile();
	}
	if(title == "Exit") {
		freeMemory();
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			isdfs = true;
			isbfs = false;
			dfs_line.clear();
			main_dfs.clear();
			bfs_line.clear();
			main_bfs.clear();
			cout << DFS() << endl;
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		doTopmost(bChecked); // Use the checked value directly
		if (isOpen)
		{
			isbfs = true;
			isdfs = false;
			dfs_line.clear();
			main_dfs.clear();
			bfs_line.clear();
			main_bfs.clear();
			cout << BFS() << endl;
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;

	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);
	int i, j;
	
	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	if (isOpen) {
		wall_length = 50;
		ofSetLineWidth(5);
		// draw the box
		ofDrawLine(0, 0, wall_length * WIDTH, 0);
		ofDrawLine(0, HEIGHT * wall_length, wall_length * WIDTH, wall_length * HEIGHT);
		ofDrawLine(0, 0, 0, wall_length * HEIGHT);
		ofDrawLine(wall_length * WIDTH, 0, wall_length * WIDTH, wall_length * HEIGHT);
		// col_wall
		for (int i = 0; i < HEIGHT; i++) {//wall_ver
			for (int j = 0; j < WIDTH - 1; j++) {
				if (col_wall[i][j] == 1) {
					ofDrawLine((j + 1) * wall_length, i * wall_length, (j + 1) * wall_length, (i + 1) * wall_length);
				}
			}
		}
		// row_wall
		for (int i = 0; i < HEIGHT - 1; i++) {//wall_hor
			for (int j = 0; j < WIDTH; j++) {
				if (row_wall[i][j] == 1) {
					ofDrawLine(j * wall_length, (i + 1) * wall_length, (j + 1) * wall_length, (i + 1) * wall_length);
				}
			}
		}
	}


	if (isdfs)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	if (isbfs)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			bfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze.maz";
		printf("file name is %s\n", fileName);
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of col_wall input is progress.
			// If input_flag is one, then work of row_wall input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;
			
			
			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			if (isOpen) {
				int line_size = buffer.getLines().begin().asString().size();
				int total_lines = buffer.size() / line_size;
				WIDTH = (line_size - 1) / 2;
				HEIGHT = (total_lines - 1) / 2;
				// intialize col_wall & row_wall
				col_wall = (int**)malloc(sizeof(int*)*HEIGHT);
				row_wall = (int**)malloc(sizeof(int*)*(HEIGHT - 1));
				for (int i = 0; i < HEIGHT; i++) {
					col_wall[i] = (int*)malloc(sizeof(int)*(WIDTH-1));
					row_wall[i] = (int*)malloc(sizeof(int)*WIDTH);
				}
				// read lines
				for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
					string line = *it;
					cnt++;
					if (cnt == 1 || cnt == total_lines) continue;
					if (input_flag == 0) {
						// col_wall
						for (int i = 0; i < WIDTH - 1; i++) {
							if (line[(i + 1) * 2] == '|') col_wall[cnt/2-1][i] = 1;
							else col_wall[cnt/2-1][i] = 0;
						}
						input_flag = 1;
					}
					else {
						// row_wall
						for (int i = 0; i < WIDTH; i++) {
							if (line[i * 2 + 1] == '-') row_wall[cnt / 2 - 1][i] = 1;
							else row_wall[cnt / 2 - 1][i] = 0;
						}
						input_flag = 0;
					}
				}


				// create data for tree
				int total_ele = WIDTH * HEIGHT;
				maze_ele = (MazeEle*)malloc(sizeof(MazeEle)*total_ele);
				// initialize maze_ele
				for (int i = 0; i < total_ele; i++) {
					maze_ele[i].parent= -1;
					maze_ele[i].child_num = 0;
				}
				// initialize visited
				visited = (int*)malloc(sizeof(int)*(total_ele));
				for (int i = 0; i < total_ele; i++) {
					visited[i] = 0;
				}

				// find child_node
				queue<int> path;

				int node_ind = 0;
				path.push(0);
				visited[0] = 1;

				int N = WIDTH;
				int M = HEIGHT;

				while (!path.empty()) {
					node_ind = path.front();
					path.pop();
					maze_col = node_ind % N;
					maze_row = node_ind / N;
					// up
					if (0 <= maze_row - 1 && maze_row - 1 < M - 1 && 0 <= maze_col && maze_col < N) {
						if (row_wall[maze_row - 1][maze_col] == 0 && visited[node_ind - N] == 0) {
							path.push(node_ind - N);
							visited[node_ind - N] = 1;
							maze_ele[node_ind].child_list[maze_ele[node_ind].child_num] = node_ind - N;
							maze_ele[node_ind].child_num++;
							maze_ele[node_ind - N].parent = node_ind;
						}
					}
					// left
					if (0 <= maze_row && maze_row < M && 0 <= maze_col-1 && maze_col-1 < N-1) {
						if (col_wall[maze_row][maze_col - 1] == 0 && visited[node_ind - 1] == 0) {
							path.push(node_ind - 1);
							visited[node_ind - 1] = 1;
							maze_ele[node_ind].child_list[maze_ele[node_ind].child_num] = node_ind - 1;
							maze_ele[node_ind].child_num++;
							maze_ele[node_ind - 1].parent = node_ind;
						}
					}
					// right
					if (0 <= maze_row && maze_row < M && 0 <= maze_col && maze_col < N - 1) {
						if (col_wall[maze_row][maze_col] == 0 && visited[node_ind + 1] == 0) {
							path.push(node_ind + 1);
							visited[node_ind + 1] = 1;
							maze_ele[node_ind].child_list[maze_ele[node_ind].child_num] = node_ind + 1;
							maze_ele[node_ind].child_num++;
							maze_ele[node_ind + 1].parent = node_ind;
						}
					}
					// down
					if (0 <= maze_row && maze_row < M - 1 && 0 <= maze_col && maze_col < N) {
						if (row_wall[maze_row][maze_col] == 0 && visited[node_ind + N] == 0) {
							path.push(node_ind + N);
							visited[node_ind + N] = 1;
							maze_ele[node_ind].child_list[maze_ele[node_ind].child_num] = node_ind + N;
							maze_ele[node_ind].child_num++;
							maze_ele[node_ind + N].parent = node_ind;
						}
					}
				}

			}
			
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {

	//TO DO
	// malloc한 memory를 free해주는 함수
	// free the walls
	for (int i = 0; i < HEIGHT; i++) {
		free(col_wall[i]);
	}
	for (int i = 0; i < HEIGHT - 1; i++) {
		free(row_wall[i]);
	}
	free(maze_ele);
	free(visited);
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	int total_ele = WIDTH * HEIGHT;
	int path_found = 0;
	stack<int> path;
	Line partial_path;

	// initialize visited
	for (int i = 0; i < total_ele; i++) {
		visited[i] = 0;
	}

	visited[0] = 1;
	path.push(0);
	maze_col = 0;
	maze_row = 0;
	while (!path.empty()) {
		int top_ele = path.top();
		if (top_ele == WIDTH * HEIGHT - 1) {
			path_found = 1;
			break;
		}
		int child_num = maze_ele[top_ele].child_num;
		int not_end = 0;
		if (child_num != 0) {
			for (int i = 0; i < child_num; i++) {
				int child_index = maze_ele[top_ele].child_list[i];
				if (visited[child_index] == 0) {
					path.push(child_index);
					maze_col = top_ele / WIDTH;
					maze_row = top_ele % WIDTH;
					partial_path.x1 = maze_row * wall_length + wall_length / 2;
					partial_path.y1 = maze_col * wall_length + wall_length / 2;
					maze_col = child_index / WIDTH;
					maze_row = child_index % WIDTH;
					partial_path.x2 = maze_row * wall_length + wall_length / 2;
					partial_path.y2 = maze_col * wall_length + wall_length / 2;
					dfs_line.push_back(partial_path);
					main_dfs.push_back(partial_path);
					visited[child_index] = 1;
					not_end = 1;
					if (child_index == WIDTH * HEIGHT - 1) {
						path_found = 1;
					}
					break;
				}
			}
		}
		if (not_end == 0) {
			path.pop();
			main_dfs.pop_back();
		}
	}
	if(path_found)
		return true;
	else return false;
}

void ofApp::dfsdraw()
{
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
	for (int i = 0; i < dfs_line.size(); i++) {
		ofSetColor(255, 0, 0);
		ofDrawLine(dfs_line[i].x1, dfs_line[i].y1, dfs_line[i].x2, dfs_line[i].y2);
	}
	for (int i = 0; i < main_dfs.size(); i++) {
		ofSetColor(0, 0, 255);
		ofDrawLine(main_dfs[i].x1, main_dfs[i].y1, main_dfs[i].x2, main_dfs[i].y2);
	}
}


bool ofApp::BFS()
{
	int total_ele = WIDTH * HEIGHT;
	int path_found = 0;
	int front_ind;
	queue<int> path;
	Line partial_path;

	// initialize visited
	for (int i = 0; i < total_ele; i++) {
		visited[i] = 0;
	}

	visited[0] = 1;
	path.push(0);

	while (!path.empty()) {
		front_ind = path.front();
		path.pop();
		if (front_ind == WIDTH * HEIGHT - 1) {
			path_found = 1;
			break;
		}
		if (maze_ele[front_ind].child_num != 0) {
			int child_num = maze_ele[front_ind].child_num;
			for (int i = 0; i < child_num; i++) {
				int child_ind = maze_ele[front_ind].child_list[i];
				if (visited[child_ind] == 0) {
					path.push(child_ind);
					visited[child_ind] = 1;
					// push child_in to bfs_line
					maze_col = front_ind / WIDTH;
					maze_row = front_ind % WIDTH;
					partial_path.x1 = maze_row * wall_length + wall_length / 2;
					partial_path.y1 = maze_col * wall_length + wall_length / 2;
					maze_col = child_ind / WIDTH;
					maze_row = child_ind % WIDTH;
					partial_path.x2 = maze_row * wall_length + wall_length / 2;
					partial_path.y2 = maze_col * wall_length + wall_length / 2;
					bfs_line.push_back(partial_path);
				}
			}
		}
	}

	while (front_ind != 0) {
		int parent_ind = maze_ele[front_ind].parent;
		maze_col = parent_ind / WIDTH;
		maze_row = parent_ind % WIDTH;
		partial_path.x1 = maze_row * wall_length + wall_length / 2;
		partial_path.y1 = maze_col * wall_length + wall_length / 2;
		maze_col = front_ind / WIDTH;
		maze_row = front_ind % WIDTH;
		partial_path.x2 = maze_row * wall_length + wall_length / 2;
		partial_path.y2 = maze_col * wall_length + wall_length / 2;
		main_bfs.push_back(partial_path);
		front_ind = parent_ind;
	}

	if(path_found) return true;
	else return false;
}

void ofApp::bfsdraw() {
	for (int i = 0; i < bfs_line.size(); i++) {
		ofSetColor(255, 0, 0);
		ofDrawLine(bfs_line[i].x1, bfs_line[i].y1, bfs_line[i].x2, bfs_line[i].y2);
	}
	for (int i = 0; i < main_bfs.size(); i++) {
		ofSetColor(0, 0, 255);
		ofDrawLine(main_bfs[i].x1, main_bfs[i].y1, main_bfs[i].x2, main_bfs[i].y2);
	}
}