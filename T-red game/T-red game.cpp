#include <iostream>
#include "mylib.h"
#include <string>
using namespace std;

int h = 5;
int xdino = 25, ydino = 17;
int xdat = 10, ydat = ydino + h;
int jump = 14;
bool kt_jump = false;
char ground[3][91];
string space = "               ";
string dino[7] =
{
"           o-o ",
"         /(\\_/)",
".___.___' /`-' ",
" `-._.  )/,,   ",
"     //        ",
"    ^^         ",
};
string tree[5] =
{
"  *  ",
" *** ",
"*****",
"  *  ",
"  *  "
};
string die = { "           x-x " };
void play();
void draw_dino(int x, int y);
void tao_dat(int i);
void khoitaomatdat();
void draw_dat();
void dichuyenmatdat();
void draw_tree(int x);
void clear_tree(int x);
bool kt_vacham(int xtree, int x, int y);
void xoa(int a[], int &n, int vt);
void dichuyentree(int t[], int &nt);
bool game_over(int x, int y, int t[], int nt);
void draw_wall();
int main()
{
	srand(time(NULL));
	ShowCur(0);
	play();
	_getch();
}
void play() {
	int score = 0;
	int t[1000]; int nt = 0; int count = 0;
	draw_dino(xdino, ydino);
	draw_wall();
	khoitaomatdat();
	draw_dat();
	int x = xdino; int y = ydino;
	int check = 2; // 2 dung yen,1 di len, 0 di xuong
	while (true) {
		gotoXY(50, 1);
		cout << "SCORE: " << score++;
		if (count == 0) {
			t[nt++] = 95;
			count = rand() % (65 - 35 + 1) + 35; //[35,65]
		}
		//xoa du lieu man hinh
		if (check != 2) {
			draw_dino(x, y);
		}
		if (game_over(x, y, t, nt) == true) {
			break;
		}
		dichuyentree(t, nt);
		/*draw_tree(xtree);
		clear_tree(xtree);
		//kiem tra va cham
		if (kt_vacham(xtree, x, y) == true) {
			gotoXY(x, y);
			cout << die;
			break;
		}
		xtree--;*/
		draw_dino(x, y);
		dichuyenmatdat();
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
				if (c == 72 && check == 2) {
					check = 1; kt_jump = true;
				}
			}
		}
		//di chuyen
		if (check == 1) {
			gotoXY(x, y + h);
			cout << space;
			y--;
		}
		else if (check == 0) {
			gotoXY(x, y);
			cout << space;
			y++;
		}
		//kiem tra bien
		if (y == ydino - jump) {
			check = 0;
		}
		else if (y == ydino) {
			draw_dino(x, y);
			check = 2; kt_jump = false;
		}
		count--;
		Sleep(30);
	}
}
void draw_dino(int x, int y) {
	for (int i = 0; i < 6; i++) {
		gotoXY(x, y);
		cout << dino[i];
		y++;
	}
}
void tao_dat(int i) {
	int v = rand() % (15 - 1 + 1) + 1; //random 1-> 15
	switch (v) 
	{
	case 1: {
		ground[1][i] = '.'; ground[2][i] = ' '; break;
	}
	case 2: {
		ground[1][i] = '-'; ground[2][i] = ' '; break;
	}
	case 3: {
		ground[1][i] = '`'; ground[2][i] = ' '; break;
	}
	case 4: {
		ground[1][i] = 248; ground[2][i] = ' '; break;
	}
	case 5: {
		ground[1][i] = ' '; ground[2][i] = '.'; break;
	}
	case 6: {
		ground[1][i] = ' '; ground[2][i] = '-'; break;
	}
	case 7: {
		ground[1][i] = ' '; ground[2][i] = '`'; break;
	}
	default: {
		ground[1][i] = ' '; ground[2][i] = ' '; break;
	}
	}
}
void khoitaomatdat() {
	for (int i = 0; i < 90; i++) {
		ground[0][i] = '_';
		tao_dat(i);
	}
	ground[0][90] = '\0';
	ground[1][90] = '\0';
	ground[2][90] = '\0';
}
void draw_dat() {
	if (kt_jump = false) {
		ground[0][xdino + 4 - xdat] = '^';
		ground[0][xdino + 5 - xdat] = '^';
	}
	else {
		ground[0][xdino + 4 - xdat] = '_';
		ground[0][xdino + 5 - xdat] = '_';
	}
	for (int i = 0; i < 3; i++) {
		gotoXY(xdat, ydat + i);
		cout << ground[i];
	}
}
void dichuyenmatdat() {
	//doi vi tri
	for (int i = 0; i < 90 - 1; i++) {
		ground[1][i] = ground[1][i + 1];
		ground[2][i] = ground[2][i + 1];
	}
	//chen vi tri
	tao_dat(90 - 1);
	//draw
	draw_dat();
}
void draw_tree(int x) {
	int y = ydat - h;
	for (int i = 0; i < 5; i++) {
		gotoXY(x, y + i);
		cout << tree[i];
	}
}
void clear_tree(int x) {
	int y = ydat - 5;
	for (int i = 0; i < 5; i++) {
		gotoXY(x + 5, y + i);
		cout << " ";
	}
}
bool kt_vacham(int xtree, int x, int y) {
	//khung long
	int x_trai = x + 5; int x_phai = x + 9;
	int y_chan = y + 5;
	//tree
	int x_treemax = xtree + 5;
	int y_treemax = ydat;
	int y_tree = ydat - 5;
	if ((x_phai >= xtree && x_phai <= x_treemax)||(x_trai >= xtree && x_trai <= x_treemax)) {
		if (y_chan >= y_tree && y_chan <= y_treemax) {
			return true;
		}
	}return false;
}
void xoa(int a[], int &n, int vt) {
	for (int i = vt; i < n - 1; i++) {
		a[i] = a[i + 1];
	}
	n--;
}
void dichuyentree(int t[], int &nt) {
	if (t[0] == xdat) {
		xoa(t, nt, 0);
		clear_tree(xdat);
		clear_tree(xdat - 1);
		clear_tree(xdat - 2);
		clear_tree(xdat - 3);
		clear_tree(xdat - 4);
	}
	for (int i = 0; i < nt; i++) {
		draw_tree(t[i]);
		clear_tree(t[i]);
		t[i]--;
	}
}
bool game_over(int x, int y, int t[], int nt) {
	for (int i = 0; i < nt; i++) {
		if (kt_vacham(t[i], x, y) == true) {
			gotoXY(x, y);
			cout << die;
			return true;
		}
	}return false;
}
void draw_wall() {
	for (int y = 2; y < ydat + 4; y++) {
		gotoXY(xdat - 2, y);
		cout << "|";
		gotoXY(xdat + 92, y);
		cout << "|";
	}
	for (int x = xdat; x < xdat + 92; x++) {
		gotoXY(x-1, 2);
		cout << "-";
		gotoXY(x-1, ydat + 3);
		cout << "-";
	}
}
