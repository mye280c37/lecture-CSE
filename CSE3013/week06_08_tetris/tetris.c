#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	for(i=0; i<BLOCK_NUM; i++){
		nextBlock[i]=rand()%7;
	}
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
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
	char tile = '/';
	int shadowY = GetShadowY(y, x, blockID, blockRotate);
	DrawBlock(shadowY, x, blockID, blockRotate, '/');
}

void DrawBlockWithFeatures(int y, int x, int blockID,int blockRotate){
	DrawShadow(y, x, blockID, blockRotate);
	DrawBlock(y, x, blockID, blockRotate, ' ');
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

			return;
		}
	}while(!gameOver);

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
				if(f[fieldY][fieldX] == 1 | fieldY < 0 | fieldY >= HEIGHT | fieldX < 0 | fieldX >= WIDTH){
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
		AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		if(blockY == -1) gameOver = 1;
		else{
			score += DeleteLine(field);
			nextBlock[0] = nextBlock[1];
			for(int i=1; i<BLOCK_NUM; i++){
				nextBlock[i] = rand()%7;
			}
			DrawNextBlock(nextBlock);
			blockY = -1;
			blockX = WIDTH/2-2;
			blockRotate = 0;
			PrintScore(score);
		}
		DrawField();
	}
	timed_out = 0;
	//강의자료 p26-27의 플로우차트를 참고한다.
}

void AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int touched = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block[currentBlock][blockRotate][i][j] == 1){
				int fieldY = blockY + i;
				int fieldX = blockX + j; 
				if(0 <= fieldY && fieldY < HEIGHT && 0 <= fieldX && fieldX < WIDTH){
					f[fieldY][fieldX] = 1;
					if (fieldY == HEIGHT-1) touched++;
				}
			}
		}
	}
	score += touched*10;
	//Block이 추가된 영역의 필드값을 바꾼다.
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
	// user code
}

void rank(){
	// user code
}

void writeRankFile(){
	// user code
}

void newRank(int score){
	// user code
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay(){
	// user code
}

int GetShadowY(int y, int x, int blockID, int blockRotate){
	int shadowY = y;
	while(CheckToMove(field, nextBlock[0], blockRotate, shadowY+1, x)) shadowY++;
	return shadowY;
}
