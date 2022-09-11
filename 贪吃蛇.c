#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<conio.h>
#define ROW 18
#define COL 26
void hidden_cursor();
struct Snake {
	int x;
	int y;
	int len;
} snakeH;
struct Food {
	int x;
	int y;
} food;
struct Body {
	int x;
	int y;
} body[ROW*COL];
char snake[ROW][COL],dire = 'd';
int i,j,isFirst = 1,k = 0,len_body = 2,isOutLoop = 0, isAteMyself = 0,numx,numy,f;
void main() {
	hidden_cursor();
	srand(time(0));
	char cl;
	food.x = 9;
	food.y = 9;
	for(;;) {
		if(isFirst == 1) {
			snakeH.x = COL/2;
			snakeH.y = ROW/2;
			for(;;) {
				numx = rand() % 40;
				numy = rand() % 26;
				if(numx < ROW - 2 && numx > 0  &&  numy < ROW - 2 && numy > 0
				        && numx != snakeH.x && numy != snakeH.y) {
					for(i = 0; i < ROW * COL; i++) {
						if(body[i].x != food.x && body[i].y != food.y) {
							food.x = numx;
							food.y = numy;
							isOutLoop = 1;
							break;
						}
					}
				}
				if(isOutLoop == 1) {
					break;
				}
			}
			for(i = 0; i < ROW; i++) {
				for(j = 0; j <COL; j++) {
					if((i >0 && i < ROW -1)&&(j > 0 && j < COL - 1)) {
						snake[i][j] = ' ';
					} else if (i == 0 || i == ROW - 1 || j  == 0 || j == COL - 1) { //二维数组的边缘
						snake[i][j] = '#';
					}
				}
			}
			snake[snakeH.y][snakeH.x] = 'H';
			for(i = 0; i <len_body; i++) {
				body[i].x = COL/2 - i - 1;
				body[i].y = ROW/2;
				snake[body[i].y][body[i].x] = 'B';
			}
			snake[food.x][food.y] = 'F';
			for(i = 0; i< ROW; i++) {
				for(j = 0; j < COL; j++) {
					printf("%c ",snake[i][j]);
				}
				printf("\n");
			}
			usleep(300000);
			isFirst = 0;
			system("CLS");
		}
		if (_kbhit() && (cl = _getch())) { //判断是否输入
			switch(cl) {
				case 'd':
				case 'D':
				case 77:

					if (dire != 'a') {
						dire = 'd';
					}
					break;
				case 's':
				case 'S':
				case 80:
					if (dire != 'w') {
						dire = 's';
					}
					break;
				case 'W':
				case 'w':
				case 72:
					if (dire != 's') {
						dire = 'w';
					}
					break;
				case 'a':
				case 'A':
				case 75:
					if (dire != 'd') {
						dire = 'a';
					}
					break;
			}
		}
		switch(dire) {
			case 'd':
				for(i = len_body; i > 0; i--) {
					body[i].x = body[i - 1].x;
					body[i].y = body[i - 1].y;
				}
				body[0].x = snakeH.x;
				body[0].y = snakeH.y;
				snakeH.x = snakeH.x + 1;
				break;
			case 's':
				for(i = len_body; i > 0; i--) {
					body[i].x = body[i - 1].x;
					body[i].y = body[i - 1].y;
				}
				body[0].x = snakeH.x;
				body[0].y = snakeH.y;
				snakeH.y = snakeH.y + 1;
				break;
			case 'w':
				for(i = len_body; i > 0; i--) {
					body[i].x = body[i - 1].x;
					body[i].y = body[i - 1].y;
				}
				body[0].x = snakeH.x;
				body[0].y = snakeH.y;
				snakeH.y = snakeH.y - 1;
				break;
			case 'a':
				for(i = len_body; i > 0; i--) {
					body[i].x = body[i - 1].x;
					body[i].y = body[i - 1].y;
				}
				body[0].x = snakeH.x;
				body[0].y = snakeH.y;
				snakeH.x = snakeH.x - 1;
				break;
		}
		if(isFirst == 0) {
			for(i = 0; i < ROW; i++) {
				for(j = 0; j <COL; j++) {
					if((i >0 && i < ROW -1)&&(j > 0 && j < COL - 1)) {
						snake[i][j] = ' ';
					} else if (i == 0 || i == ROW - 1 || j  == 0 || j == COL - 1) { //二维数组的边缘
						snake[i][j] = '#';
					}
				}
			}
			snake[snakeH.y][snakeH.x] = 'H';
			for(i = 0; i <len_body; i++) {
				snake[body[i].y][body[i].x] = 'B';
			}
			snake[food.x][food.y] = 'F';
			for(i = 0; i< ROW; i++) {
				for(j = 0; j < COL; j++) {
					printf("%c ",snake[i][j]);
				}
				printf("\n");
			}
			usleep(300000);
			system("CLS");
		}
		if(snake[snakeH.y][snakeH.x] == snake[food.x][food.y]) {
			for(;;) {
				numx = rand() % 40;
				numy = rand() % 26;
				if(numx < COL - 1 && numx > 0  &&  numy < ROW - 1 && numy > 0
				        && numx != snakeH.x && numy != snakeH.y) {
					for(i = 0; i < ROW * COL; i++) {
						if(body[i].x != food.x && body[i].y != food.y) {
							food.x = numx;
							food.y = numy;
							isOutLoop = 1;
							break;
						}
					}
				}
				if(isOutLoop == 1) {
					break;
				}
			}
			len_body = len_body + 1;
		}
		if(snakeH.x == COL -1 || snakeH.x == 0 || snakeH.y == ROW -1 || snakeH.y == 0) {
			break;
		}
		for(i = 0; i < len_body; i++) {
			if(body[i].x == snakeH.x && body[i].y == snakeH.y) {
				isAteMyself = 1;
			}
		}
		if(isAteMyself == 1) {
			break;
		}
	}
	printf("游戏结束！\n");
}
void hidden_cursor() { //隐藏光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;//赋1为显示，赋0为隐藏
	SetConsoleCursorInfo(hOut,&cci);
}
