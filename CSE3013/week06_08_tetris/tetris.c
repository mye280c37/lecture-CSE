#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);

	// create existed ranking
	createRankList();	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_REC_PLAY: 
			rec_flag = 1;
			recommendedPlay();
			break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	writeRankFile();

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for (j = 0; j < HEIGHT; j++) {
		for (i = 0; i < WIDTH; i++) {
			field[j][i] = 0;
			if(!rec_flag) recRoot->recField[j][i] = 0;
		}
	}

	// initialize nextBlock
	for(i=0; i<5; i++){
		nextBlock[i]=rand()%7;
	}

	if(rec_flag){
		for (i=0; i<WIDTH; i++){
			newRecRoot->height[i] = 0;
		}
		for (i=0; i<HEIGHT; i++){
			newRecRoot->hole[i][0] = 0;
			newRecRoot->hole[i][1] = 0b0;
		}
		newRecRoot->level = 0;
		newRecRoot->accumulatedScore = 0;
		newRecRoot->reward = 0;
		recommendR = 0;
		recommendY = -1;
		recommendX = WIDTH/2-2;

		modified_recommend(newRecRoot);
	}else{
		// initialize recRoot
		recRoot->level = 0;
		recRoot->accumulatedScore = 0;
		recommendR = 0;
		recommendY = -1;
		recommendX = WIDTH/2-2;

		recommend(recRoot);
	}

	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	if (rec_flag){
		DrawBlockWithFeatures(blockY, recommendX, nextBlock[0], recommendR);
	}else{
		DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
	}
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	for(i=0;i<BLOCK_NUM-1;i++){
		DrawBox(3+7*i,WIDTH+10,4,8);
	}
	
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(3+7*(BLOCK_NUM-1),WIDTH+10);
	printw("SCORE");
	DrawBox(4+7*(BLOCK_NUM-1),WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	int dropDownFlag=0;

	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	case ' ':
		while(CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)){
			if(!drawFlag){
				dropDownFlag=1;
			}
			if (dropDownFlag){
				DeleteBlock(blockY, blockX, nextBlock[0], blockRotate, '.');
				dropDownFlag=1;
			}
			blockY++;
			drawFlag=1;
		}
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(5+7*(BLOCK_NUM-1),WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for(int b=1; b<BLOCK_NUM; b++){
		for( i = 0; i < 4; i++ ){
			move(4+i+7*(b-1),WIDTH+13);
			for( j = 0; j < 4; j++ ){
				if( block[nextBlock[b]][0][i][j] == 1 ){
					attron(A_REVERSE);
					printw(" ");
					attroff(A_REVERSE);
				}
				else printw(" ");
			}
		}
	}

}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// 블록이 더 이상 내려갈 수 없는 위치 찾기
	int shadowY = GetShadowY(y, x, blockID, blockRotate);
	// shadow 그리기
	DrawBlock(shadowY, x, blockID, blockRotate, '/');
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	DrawBlock(y, x, blockID, blockRotate, 'R');
}

void DrawBlockWithFeatures(int y, int x, int blockID,int blockRotate){
	if (rec_flag){
		DrawShadow(recommendY, recommendX, blockID, recommendR);
		DrawBlock(y, recommendX, blockID, recommendR, ' ');
	}else{
		DrawShadow(y, x, blockID, blockRotate);
		DrawBlock(y, x, blockID, blockRotate, ' ');
		DrawRecommend(recommendY, recommendX, nextBlock[0], recommendR);
	}
}

void DeleteBlock(int y, int x, int blockID, int blockRotate, char tile){
	int i, j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j] == 1 && i+y>=0){
				move(i+y+1, j+x+1);
				printw("%c", tile);
			}
		}
	}
}


void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);

	recRoot = (RecNode*)malloc(sizeof(RecNode));

	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();
			newRank(score);

			return;
		}
	}while(!gameOver);

	free(recRoot);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block[currentBlock][blockRotate][i][j] == 1){
				int fieldY = blockY + i;
				int fieldX = blockX + j;
				if(f[fieldY][fieldX] == 1 || fieldY < 0 || fieldY >= HEIGHT || fieldX < 0 || fieldX >= WIDTH){
					return 0;
				}
			}
		}
	}
	return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	int preBlockRotate = blockRotate;
	int preBlockY = blockY;
	int preBlockX = blockX;

	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	switch(command){
	case KEY_UP:
		preBlockRotate = (blockRotate+3)%4;
		break;
	case KEY_DOWN:
		preBlockY = blockY-1;
		break;
	case KEY_RIGHT:
		preBlockX = blockX-1;
		break;
	case KEY_LEFT:
		preBlockX = blockX+1;
		break;
	default:
		break;
	}
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	int ShadowY = GetShadowY(preBlockY, preBlockX, currentBlock, preBlockRotate);
	DeleteBlock(ShadowY, preBlockX, currentBlock, preBlockRotate, '.');
	DeleteBlock(preBlockY, preBlockX, currentBlock, preBlockRotate, '.');

	//3. 새로운 블록 정보를 그린다.
	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate); 
}

void BlockDown(int sig){
	if(CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX)){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else{
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		if(blockY == -1) gameOver = 1;
		score += DeleteLine(field);
		// renew nextBlock
		for (int i = 0; i < 4; i++) nextBlock[i] = nextBlock[i + 1];
		nextBlock[4] = rand()%7;

		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				recRoot->recField[i][j] = field[i][j];
		recRoot->level = 0;
		recRoot->accumulatedScore = score;
		recommendR = 0;
		recommendY = -1;
		recommendX = WIDTH/2-2;
		recommend(recRoot);

		DrawNextBlock(nextBlock);
		blockY = -1;
		blockX = WIDTH/2-2;
		blockRotate = 0;
		PrintScore(score);
		DrawField();
	}
	timed_out = 0;
	//강의자료 p26-27의 플로우차트를 참고한다.
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int touched = 0;
	//Block이 추가된 영역의 필드값을 바꾼다.
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block[currentBlock][blockRotate][i][j] == 1){
				int fieldY = blockY + i;
				int fieldX = blockX + j; 
				if(0 <= fieldY && fieldY < HEIGHT && 0 <= fieldX && fieldX < WIDTH){
					f[fieldY][fieldX] = 1;
					// 필드와 맞닿아 있는 블록의 면적을 count
					if (fieldY == HEIGHT-1) touched++;
				}
			}
		}
	}
	return touched*10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
	int isFull = 1;
	int fullLine = 0;
	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			if(f[i][j] == 0){
				isFull = 0;
				break;
			}
		}
		if(isFull){
			fullLine++;
			for(int k = i-1; k >= 0; k--){
				for(int j = 0; j < WIDTH; j++){
					f[k+1][j] = f[k][j];
				}
			}
		}
		isFull = 1;
	}
	return fullLine*fullLine*100;
}


void createRankList(){
	FILE *fp;

    fp = fopen("rank.txt", "r");

    if (fp == NULL) {
        fp = fopen("rank.txt", "w");
        if (fp == NULL) {
            fprintf(stderr, "create ranking error!\n");
            exit(0);
        }
        fprintf(fp, "0\n");
        // create rankHead
		rankList = (RankNode*)malloc(sizeof(RankNode));
		rankList[0].score = 0;
    } else {
        int cnt, score;
        char name[NAMELEN];

		fscanf(fp, "%d", &cnt);

		// create rankList
		rankList = (RankNode*)malloc(sizeof(RankNode)*(cnt+1));
		if(rankList == NULL) {
			fprintf(stderr, "can't create rank list");
			exit(0);
		}
		

		// store rankSize in rankList[0]
		rankList[0].score = cnt;

		for (int i=1; i<=cnt; i++){
			fscanf(fp, "%s %d", rankList[i].name, &(rankList[i].score));
		}
    }

    fclose(fp);
}

void rank(){
	int command, x, y;
	int rankSize = rankList[0].score;
	char name[NAMELEN];
	int findName = 0;
	int delete_rank;

	do {
        clear();
        printw("1. list ranks from X to Y\n");
        printw("2. list ranks by a specific name\n");
        printw("3. delete a specific rank\n");
        command = wgetch(stdscr);
    } while (!('1' <= command && command <= '3'));

	echo();

	switch (command)
	{
	case '1':
		printw("X: ");
        scanw("%d", &x);
        printw("Y: ");
        scanw("%d", &y);

		if (1 > x || x > rankSize) {
			x = 1;
		}
		if (1 > y || y > rankSize) {
			y = rankSize;
		}

		printw("      name       |   score   \n");
        printw("------------------------------\n");

		if (x > y) {
            printw("\nsearch failure: no rank in the list\n");
        } else {
			for(int i=x; i<=y; i++){
				printw("%-17s| %-10d\n", rankList[i].name, rankList[i].score);
			}
		}

		break;
	case '2':
		printw("Input the name: ");
		scanw("%s", name);

		printw("      name       |   score   \n");
        printw("------------------------------\n");

		for(int i=1; i<=rankSize; i++){
			if(strcmp(rankList[i].name, name) == 0) {
				printw("%-17s| %-10d\n", rankList[i].name, rankList[i].score);
				findName=1;
			}
		}

		if(!findName) printw("\nsearch failure: no name in the list\n");
		break;
	case '3':
		printw("Input the rank: ");
		scanw("%d", &delete_rank);

		if(1 <= delete_rank && delete_rank <= rankSize){
			for(int i=delete_rank; i< rankSize; i++){
				strcpy(rankList[i].name, rankList[i+1].name);
				rankList[i].score = rankList[i+1].score;
			}
			rankList[0].score -= 1;
			rankList = (RankNode*)realloc(rankList, sizeof(RankNode)*(rankList[0].score + 1));
			printw("\nresult: the rank deleted\n");
		}else{
			printw("\nsearch failure: the rank not in the list\n");
		}
		break;
	default:
		break;
	}
	noecho();
    getch();
}

void writeRankFile(){
	FILE *fp;
	int rankSize = rankList[0].score;

	fp = fopen("rank.txt", "wt");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open rank file");
        exit(0);
    } else {
        fprintf(fp, "%d\n", rankList[0].score);
        for (int i = 1; i <= rankSize; i++) {
            fprintf(fp, "%s %d\n", rankList[i].name, rankList[i].score);
        }

        free(rankList);
        fclose(fp);
    }
}

void newRank(int score){
	char name[NAMELEN];
	int rankSize = rankList[0].score;
	int i;

    clear();
    echo();
    printw("Input your name: ");
    scanw("%s", name);
    noecho();

	if (name[0] == '\0') {
        return;
    }

	for(i=1; i<=rankSize; i++){
		if(score >= rankList[i].score) break;
	}

	rankList = (RankNode*)realloc(rankList, sizeof(RankNode)*(++rankSize + 1));

	// renew rankSize
	rankList[0].score = rankSize;

	// renew rankList
	for(int j=rankSize; j>=i+1; j--){
		strcpy(rankList[j].name, rankList[j-1].name);
		rankList[j].score =  rankList[j-1].score;
	}
	strcpy(rankList[i].name, name);
	rankList[i].score = score;

}

int recommend(RecNode *root){
	int MAX_LEVEL = 3;
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
	int childBlockId = nextBlock[root->level];
	// int level = root->level + 1;
	for (int rotate = 0; rotate < 4; rotate++) {
		for (int x = -2; x < WIDTH; x++) {
			if (CheckToMove(root->recField, childBlockId, rotate, 0, x)) {
				int h = 0;
				while (CheckToMove(root->recField, childBlockId, rotate, h+1, x)) {
					h++;
				}
				root->child = (RecNode*)malloc(sizeof(RecNode));
				
				for (int i = 0; i < HEIGHT; i++) {
					for (int j = 0; j < WIDTH; j++) {
						root->child->recField[i][j] = root->recField[i][j];
					}
				}
				root->child->level = root->level + 1;
				root->child->accumulatedScore = root->accumulatedScore + AddBlockToField(root->child->recField, childBlockId, rotate, h, x);
				root->child->accumulatedScore += DeleteLine(root->child->recField);
				if (root->child->level < MAX_LEVEL) {
					int temp = recommend(root->child);
					if(max == temp){
						if(root->child->level == 1 && recommendY < h){
							recommendR = rotate;
							recommendX = x;
							recommendY = h;
						}
					} else if(max < temp){
						max = temp;
						if (root->child->level == 1) {
							recommendR = rotate;
							recommendX = x;
							recommendY = h;
						}
					}
				}else{
					if (max < root->child->accumulatedScore)
						max = root->child->accumulatedScore;
				}
				free(root->child);
			}
		}
	}
	return max;
}

int modifiedCheckToMove(int height[WIDTH], int currentBlock,int blockRotate, int y, int x){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block[currentBlock][blockRotate][i][j] == 1){
				int fieldY = y + i;
				int fieldX = x + j;
				if(HEIGHT-fieldY <= height[fieldX] || fieldY < 0 || fieldY >= HEIGHT || fieldX < 0 || fieldX >= WIDTH){
					return 0;
				}
			}
		}
	}
	return 1;
}


int modified_recommend(NewRecNode *root){
	int MAX_LEVEL = 3;
	int reward = -999999999;
	int total_hole = 0;
	int emptyFloor = 0;
	int tmp_reward = -999999999;
	int childBlockId = nextBlock[root->level];

	for (int r=0; r<4; r++){
		for(int x=-4; x<WIDTH+4; x++){
			if(modifiedCheckToMove(root->height, childBlockId, r, 0, x)){
				int y=0;
				while(modifiedCheckToMove(root->height, childBlockId, r, y+1, x)){
					y++;
				}
				root->child = (NewRecNode*)malloc(sizeof(NewRecNode));
				root->child->level = root->level+1;
				root->child->accumulatedScore = root->accumulatedScore;
			
				int hole;
				
				// copy height
				for(int i=0; i<WIDTH; i++){
					root->child->height[i] = root->height[i];
				}
				// copy origin hole info
				for(int i=0; i<HEIGHT; i++){
					root->child->hole[i][0] = root->hole[i][0];
					root->child->hole[i][1] = root->hole[i][1];
				}

				int min_h, floor, new_hole, max_h, origin_y, emptySide, variance_h, touched;
				int cnt = 0;

				// add block
				floor=0;
				touched=0;
				for(int i=3; i>=0; i--){
					for(int j=0; j<4; j++){
						if(block[childBlockId][r][i][j] == 1){
							int new_y=y+i;
							int w=x+j;
							if(0 <= new_y && new_y < HEIGHT && 0 <= w && w < WIDTH){
								if (new_y == HEIGHT-1) floor++;
								int h = HEIGHT-new_y;

								// renew height
								root->child->height[w] = h;
								
								if(h-root->height[w] > 1){
									// renew hole
									origin_y = HEIGHT-root->height[w];
									new_hole = h-root->height[w]-1;
									if(new_hole > 0){
										for(int k=new_y+1; k<origin_y; k++){
											root->child->hole[k][0]++;
											touched--;
											int add_bit = 0b1;
											add_bit <<= (WIDTH-w-1);
											root->child->hole[k][1] += add_bit;
										}
									}
								}else{
									touched++;
								}
								int check_bit=1;
								check_bit <<= (WIDTH-w-1+1);
								if(root->child->height[w+1] >= h && (check_bit & root->child->hole[new_y][1])>>(WIDTH-w-1+1) != 1) touched++;
								check_bit = 1;
								check_bit <<= (WIDTH-w-1-1);
								if(root->child->height[w-1] >= h && (check_bit & root->child->hole[new_y][1])>>(WIDTH-w-1-1) != 1) touched++;
							}
						}
					}
				}

				// add score of floor
				root->child->accumulatedScore += 10*floor;

				// check line
				min_h = root->child->height[0];
				for(int i=1; i<WIDTH; i++){
					if(min_h > root->child->height[i]){
						min_h = root->child->height[i];
					}
				}
				// check hole
				cnt = min_h;
				for(int k=HEIGHT-min_h; k<HEIGHT; k++){
					if(root->child->hole[k][0] != WIDTH) cnt--;
				}
				
				
				// renew info of child
				if(cnt > 0){
					//add score
					root->child->accumulatedScore += 100*cnt*cnt;

					for(int i=0; i<WIDTH; i++){
						// renew height info
						root->child->height[i] -= (cnt-1);
						// check there is hole at height of width
						int check_y = HEIGHT-root->child->height[i];
						int check_bit=1;
						check_bit <<= (WIDTH-i-1);
						for(int j=check_y; j<HEIGHT; j++){
							if((check_bit | root->child->hole[j][1])>>(WIDTH-i-1) ==1){
								root->child->hole[j][0]--;
								root->child->hole[j][1] -= check_bit;
								root->child->height[i]--;
							}else{
								break;
							}
						}
					}
				}	

				// emptyFloor
				emptyFloor=0;
				for(int i=0; i<WIDTH; i++){
					if(root->child->height[i] == 0) emptyFloor++;
					else{
						int check_bit=1;
						check_bit <<= (WIDTH-i-1);
						if((check_bit & root->child->hole[HEIGHT-1][1])>>(WIDTH-i-1) ==1){
							emptyFloor++;
						}
					}
				}

				// total_hole
				total_hole = 0;
				for(int i=0; i<HEIGHT; i++){
					total_hole += root->child->hole[i][0]*(i+1);
					if(i<HEIGHT-1){
						if(root->child->hole[i][1] & root->child->hole[i+1][1]){
							total_hole*10;
						}
					}
				}
				
				// max_h, min_h
				min_h = root->child->height[0];
				max_h = root->child->height[0];
				int root_max_h = root->height[0];
				for(int i=0; i<WIDTH; i++){
					if(max_h < root->child->height[i]) max_h = root->child->height[i];
					if(min_h > root->child->height[i]) min_h = root->child->height[i];
					if(root_max_h < root->height[i]) root_max_h = root->height[i];
				}

				// emptySide
				emptySide = 0;
				for(int i=0; i<HEIGHT; i++){
					int check_bit = 1;
					if(root->child->hole[i][1] & check_bit == 1) emptySide++;
					check_bit <<= (WIDTH-1);
					if((root->child->hole[i][1] & check_bit)>>(WIDTH-1) == 1) emptySide++;
				}

				//variance_h
				variance_h = 0;
				int avg_h=0;
				for(int i=0; i<WIDTH; i++){
					avg_h += root->child->height[i];
				}
				avg_h /= WIDTH;
				for(int i=0; i<WIDTH; i++){
					variance_h += (root->child->height[i]-avg_h)*(root->child->height[i]-avg_h);
				}

				// child를 고려하지 않은 reward
				root->child->reward = 150000;
				root->child->reward = root->child->reward - 40*max_h - 15*total_hole - 100*(max_h-min_h) - 40*emptySide + 50*(root->child->accumulatedScore-score) + floor*10 - emptyFloor*20 - 150*variance_h + 100*touched + cnt*cnt*100;
				if(tmp_reward <= root->child->reward){
					tmp_reward = root->child->reward;
				}
				if (root->child->level < MAX_LEVEL) {
					// child를 고려여부 결정
					if(tmp_reward <= root->child->reward*MAX_LEVEL){
						root->child->reward += modified_recommend(root->child);
					}
					// 최종 reward 비교
					if(reward <= root->child->reward){
						reward = root->child->reward;
						if (root->child->level == 1) {
							recommendR = r;
							recommendX = x;
							recommendY = y;
						}
					}	
				}
				else{
					if(reward < root->child->reward)
						reward=root->child->reward;
				}
				// free child
				free(root->child);
			}
		}
	}
	return reward;
}

void recBlockDown(int sig){
	if(CheckToMove(field, nextBlock[0], recommendR, blockY+1, recommendX)){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], recommendR, blockY, recommendX);
	}
	else{
		score += AddBlockToField(field, nextBlock[0], recommendR, blockY, recommendX);
		if(blockY == -1) gameOver = 1;
		score += DeleteLine(field);
		// renew nextBlock
		for (int i = 0; i < 4; i++) nextBlock[i] = nextBlock[i + 1];
		nextBlock[4] = rand()%7;

		for(int i=0; i<HEIGHT; i++){
			newRecRoot->hole[i][0] = 0;
			newRecRoot->hole[i][1] = 0b0;
		}

		for(int i=0; i<WIDTH; i++){
			newRecRoot->height[i] = 0;
			int is_height = 0;
			int j = 0;
			// check height
			for(j=0; j<HEIGHT; j++){
				if(field[j][i]) {
					newRecRoot->height[i] = HEIGHT-j;
					is_height = 1;
					break;
				}
			}
			if(is_height){
				// check hole
				int add_bit = 1;
				add_bit <<= (WIDTH-i-1);
				j++;
				for(j; j<HEIGHT; j++){
					if(!field[j][i]){
						newRecRoot->hole[j][0]++;
						newRecRoot->hole[j][1] += add_bit;
					}
				}
			}
		}
		newRecRoot->level = 0;
		newRecRoot->accumulatedScore = score;
		newRecRoot->reward = 0;
		int min_h = newRecRoot->height[0];
		int max_h = newRecRoot->height[0];
		for(int i=1; i<WIDTH; i++){
			if(min_h > newRecRoot->height[i]) min_h = newRecRoot->height[i];
			if(max_h < newRecRoot->height[i]) max_h = newRecRoot->height[i];
		}
		recommendR = 0;
		recommendY = -1;
		recommendX = WIDTH/2-2;
		modified_recommend(newRecRoot);

		DrawNextBlock(nextBlock);
		blockY = -1;
		blockX = WIDTH/2-2;
		blockRotate = 0;
		PrintScore(score);
		DrawField();
	}
	timed_out = 0;
}

void recommendedPlay(){
	int command;
	clear();
	act.sa_handler = recBlockDown;
	sigaction(SIGALRM,&act,&oact);

	newRecRoot = (NewRecNode*)malloc(sizeof(NewRecNode));

	InitTetris();
	do{
		if(timed_out==0){
			ualarm( 100000,0 );
			timed_out=1;
		}

		// don't get command except QUIT
		if(GetCommand()==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();
			newRank(score);

			return;
		}
	}while(!gameOver);

	free(recRoot);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

int GetShadowY(int y, int x, int blockID, int blockRotate){
	int shadowY = y;
	while(CheckToMove(field, nextBlock[0], blockRotate, shadowY+1, x)) shadowY++;
	return shadowY;
}
