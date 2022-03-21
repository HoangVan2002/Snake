/* # Snake 
Ngôn ngữ C/C++ 
Tui viết có thể chưa được tốt, chưa được tối ưu, bạn có thêm chỉnh sửa chút xíu cho nó xịn xò con bò hơn nhí :3
*/

#pragma warning(disable : 4996)
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<Windows.h>
const int dx[4] = { -1,1,0,0 };
const int dy[4] = { 0,0,-1,1 };
struct Diem {
	int x, y;
}s[1000], f, db, tg;
FILE* h;
int opt, opt2, opt3, opt4, i, j, huongdichuyen, diem, soluongdotcuasnake, mapchoi, p, mapdangchoido, capdo, v, d1, ptr, diemcao[5],z = 1;
char a[10][18], t;
int stop, ps, reset_cfg[3];
void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void ancontrodi() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void textcolor(int x) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void XoaManHinh() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void hoan_doi(int& a, int& b) {
	int tg;
	tg = a;
	a = b;
	b = tg;
}
int empty_file(const char* x) {
	h = fopen(x, "r");
	if (h != NULL) {
		fseek(h, 0, SEEK_END);
		if (ftell(h) == 0) return 1;
		else return 0;
		fclose(h);
	}
	return 0;
}
int kt() {
	for (i = 0; i < soluongdotcuasnake; i++)
		if ((f.x == s[i].x) && (f.y == s[i].y)) {
			a[f.x][f.y] = 'O';
			return 0;
		}
	return 1;
}
int kt2() {
	for (i = 0; i < soluongdotcuasnake; i++) {
		if ((s[i].x == db.x) && (s[i].y == db.y)) {
			a[db.x][db.y] = 'O';
			return 0;
		}
	}
	return 1;
}
int kt22() {
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 15; j++) {
			if ((strncmp(&a[i + 1][j + 1], "  ", 2) == 0) && (strncmp(&a[i + 2][j + 1], "  ", 2) == 0)) return 1;
		}
	}
	return 0;
}
int kt2A() {
	for (i = 0; i < soluongdotcuasnake; i++) {
		if ((s[i].x == db.x) && (s[i].y == db.y)) {
			a[db.x][db.y] = 'O';
			return 0;
		}
		else if ((s[i].x == db.x + 1) && (s[i].y == db.y)) {
			a[db.x + 1][db.y] = 'O';
			return 0;
		}
		else if ((s[i].x == db.x) && (s[i].y == db.y + 1)) {
			a[db.x][db.y + 1] = 'O';
			return 0;
		}
		else if ((s[i].x == db.x + 1) && (s[i].y == db.y + 1)) {
			a[db.x + 1][db.y + 1] = '0';
			return 0;
		}
	}
	if ((a[db.x][db.y] == '+') || (a[db.x + 1][db.y] == '+') || (a[db.x][db.y + 1] == '+') || (a[db.x + 1][db.y + 1] == '+')) return 0;
	return 1;
}
int kt3() {
	if (((f.x == db.x) && (f.y == db.y)) || ((f.x == db.x + 1) && (f.y == db.y)) || ((f.x == db.x) && (f.y == db.y + 1)) || ((f.x == db.x + 1) && (f.y == db.y + 1))) return 1;
	else return 0;
}
void on_preload() {
	h = fopen("cfg.ini", "r");
	if (h == NULL) {
		h = fopen("cfg.ini", "w");
		fprintf(h, "%d %d %d", 1, 1, 0);
		fclose(h);
	}
	h = fopen("save.ini", "r");
	if (h == NULL) {
		h = fopen("save.ini", "w");
		fclose(h);
	}
	system("attrib -r cfg.ini");
	system("attrib -r save.ini");
	h = fopen("hi0.txt", "r");
	if (h == NULL) {
		h = fopen("hi0.txt", "w");
		fclose(h);
	}
	h = fopen("hi1.txt", "r");
	if (h == NULL) {
		h = fopen("hi1.txt", "w");
		fclose(h);
	}
	h = fopen("hi2.txt", "r");
	if (h == NULL) {
		h = fopen("hi2.txt", "w");
		fclose(h);
	}
	opt = 1;
	for (i = 0; i < 3; i++) { reset_cfg[i] = 0; }
}
void on_load() {	// mở map chơi trước đó
	h = fopen("cfg.ini", "r");
	fscanf(h, "%d %d %d", &capdo, &mapchoi, &mapdangchoido);

	fclose(h);
}
void doc_trang_thai(const char* x) {
	h = fopen(x, "r");
	fscanf(h, "%d %d %d", &capdo, &mapchoi, &mapdangchoido);
	fscanf(h, "%d %d", &diem, &soluongdotcuasnake);
	fscanf(h, "%d", &huongdichuyen);
	fscanf(h, "%d %d %d %d %d %d", &f.x, &f.y, &db.x, &db.y, &v, &d1);
	for (i = 0; i < soluongdotcuasnake; i++) fscanf(h, "%d %d", &s[i].x, &s[i].y);	// lưu lại tọa độ của con rắn
	fclose(h);
}
void ghi_trang_thai(const char* x) {
	h = fopen(x, "w");
	fprintf(h, "%d %d %d\n", capdo, mapchoi, mapdangchoido);
	fprintf(h, "%d %d\n", diem, soluongdotcuasnake);
	fprintf(h, "%d\n", huongdichuyen);
	fprintf(h, "%d %d %d %d %d %d\n", f.x, f.y, db.x, db.y, v, d1);
	for (i = 0; i < soluongdotcuasnake; i++) { fprintf(h, "%d %d\n", s[i].x, s[i].y); }
	fclose(h);
}
void doc_diem_cao(const char* x) {
	h = fopen(x, "r");
	for (i = 0; i < 5; i++) fscanf(h, "%d", &diemcao[i]);
	fclose(h);
}
void ghi_diem_cao(const char* x) {
	h = fopen(x, "w");
	for (i = 0; i < 5; i++) fprintf(h, "%d\n", diemcao[i]);
	fclose(h);
}
void on_exit() {
	h = fopen("cfg.ini", "w");
	fprintf(h, "%d %d %d", capdo, mapchoi, mapdangchoido);
	fclose(h);
}
void khung() {
	
	for (i = 0; i < 10; i++) {
		printf("\t");
		for (j = 0; j < 18; j++) {
			if ((i == 0) || (i == 9)) {
				a[i][j] = (char)196;
			}
			else if (j == 0 || j == 17) {
				a[i][j] = (char)179;
			}
			else
			{
				a[i][j] = ' ';
			}
		}

	}
}
void ve_me_cung() {	 // vẽ các map trong chế độ mê cung
	switch (mapdangchoido) {
	case 1:	// map trong hộp
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 16; j++) {
				if ((i == 0) || (i == 7) || (j == 0) || (j == 15)) {
					a[i + 1][j + 1] = '+';
				}
			}
		}
		break;
	case 2: {	// map đường hầm
		for (i = 0; i < 16; i++) {
			if (((i >= 0) && (i <= 2)) || ((i >= 13) && (i <= 15))) { a[1][i + 1] = '+'; }
		}
		for (i = 1; i < 7; i++) {
			if ((i == 1) || (i == 2) || (i == 5) || (i == 6)) {
				a[i + 1][1] = '+';
				a[i + 1][16] = '+';
			}
		}
		for (i = 0; i < 16; i++) {
			if (((i >= 0) && (i <= 2)) || ((i >= 13) && (i <= 15))) {
				a[8][i + 1] = '+';
			}
		}
		for (i = 4; i < 12; i++) {
			a[3][i + 1] = '+';
			a[6][i + 1] = '+';
		}
		break;
	}
	case 3: {	// map nhà máy
		for (i = 0; i < 5; i++) { a[i + 1][5] = '+'; }
		for (i = 10; i < 16; i++) { a[2][i + 1] = '+'; }
		for (i = 3; i < 8; i++) { a[i + 1][11] = '+'; }
		for (i = 0; i < 5; i++) { a[7][i + 1] = '+'; }
		break;
	}
	case 4: {	// map đường ray
		for (i = 0; i < 16; i++) { a[1][i + 1] = '+'; }
		for (i = 1; i < 7; i++) {
			if ((i == 1) || (i == 2) || (i == 5) || (i == 6)) {
				a[i + 1][1] = '+';
				a[i + 1][16] = '+';
			}
		}
		for (i = 0; i < 16; i++) { a[8][i + 1] = '+'; }
		for (i = 3; i < 13; i++) {
			a[3][i + 1] = '+';
			a[6][i + 1] = '+';
		}
		break;
	}
	case 5: {	// map căn hộ
		a[1][1] = '+';
		a[1][2] = '+';
		a[2][1] = '+';
		for (i = 4; i < 13; i++) { a[1][i + 1] = '+'; }
		a[2][7] = '+';
		a[3][7] = '+';
		for (i = 0; i < 16; i++) {
			if ((i != 7) && (i != 8)) { a[4][i + 1] = '+'; }
			a[6][i + 1] = '+';
		}
		a[7][10] = '+';
		a[8][10] = '+';
		break;
	}
	} 
	p = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 16; j++) {
			if (a[i + 1][j + 1] == '+') { p++; }
		}
	}
}
void in_mt() {	// in ra map chơi
	XoaManHinh();
	printf("\n\tDiem: %04d\n", diem);
	for (i = 0; i < 10; i++) {
		printf("\t");
		for (j = 0; j < 18; j++) {
			if ((s[soluongdotcuasnake - 1].x == i) && (s[soluongdotcuasnake - 1].y == j)) textcolor(14);
			if (f.x == i && f.y == j) {
				textcolor(z);
			}
			printf("%c", a[i][j]);
			textcolor(7);
		}
		printf("\n");
	}
	
}
void tao() {	
	
	do {
		f.x = rand() % 8 + 1;
		f.y = rand() % 16 + 1;
	} while ((kt() == 0) || (a[f.x][f.y] == '+') || (a[f.x][f.y] == '*'));
	a[f.x][f.y] = '@';
}
void tao_db() {	// tọa hoa quả đặc biệt
	do {
		db.x = rand() % 8 + 1;
		db.y = rand() % 16 + 1;
	} while ((kt2() == 0) || (a[db.x][db.y] == '+') || (a[db.x][db.y] == '@'));
	a[db.x][db.y] = '*';
}
void tao_db_2x2() {
	do {
		db.x = rand() % 7 + 1;
		db.y = rand() % 15 + 1;
	} while ((kt2A() == 0) || (kt22() == 0));
	if ((f.x == db.x) && (f.y == db.y)) a[db.x][db.y] = '*';
	else a[db.x][db.y] = '*';
	if ((f.x == db.x + 1) && (f.y == db.y)) a[db.x + 1][db.y] = '*';
	else a[db.x + 1][db.y] = '*';
	if ((f.x == db.x) && (f.y == db.y + 1)) a[db.x][db.y + 1] = '*';
	else a[db.x][db.y + 1] = '*';
	if ((f.x == db.x + 1) && (f.y == db.y + 1)) a[db.x + 1][db.y + 1] = '*';
	else a[db.x + 1][db.y + 1] = '*';
	v = 1;
}
void xoa_db() {
	if ((v == 1) && ((a[db.x][db.y] == '*') || (a[db.x + 1][db.y] == '*') || (a[db.x][db.y + 1] == '*') || (a[db.x + 1][db.y + 1] == '*'))) {
		a[db.x][db.y] = ' ';
		a[db.x + 1][db.y] = ' ';
		a[db.x][db.y + 1] = ' ';
		a[db.x + 1][db.y + 1] = ' ';
		if ((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y)) a[db.x][db.y] = 'O';
		else if ((s[soluongdotcuasnake - 1].x == db.x + 1) && (s[soluongdotcuasnake - 1].y == db.y)) a[db.x + 1][db.y] = 'o';
		else if ((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y + 1)) a[db.x][db.y + 1] = 'o';
		else if ((s[soluongdotcuasnake - 1].x == db.x + 1) && (s[soluongdotcuasnake - 1].y == db.y + 1)) a[db.x + 1][db.y + 1] = 'o';
	}
	else if ((v == 1) && ((a[db.x][db.y] == '*') || (a[db.x + 1][db.y] == '*') || (a[db.x][db.y + 1] == '*') || (a[db.x + 1][db.y + 1] == '*'))) {
		a[db.x][db.y] = ' ';
		a[db.x + 1][db.y] = ' ';
		a[db.x][db.y + 1] = ' ';
		a[db.x + 1][db.y + 1] = ' ';
		if ((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y)) a[db.x][db.y] = 'O';
		else if ((s[soluongdotcuasnake - 1].x == db.x + 1) && (s[soluongdotcuasnake - 1].y == db.y)) a[db.x + 1][db.y] = 'o';
		else if ((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y + 1)) a[db.x][db.y + 1] = 'o';
		else if ((s[soluongdotcuasnake - 1].x == db.x + 1) && (s[soluongdotcuasnake - 1].y == db.y + 1)) a[db.x + 1][db.y + 1] = 'o';
	}
	else if ((a[db.x][db.y] == '*')) a[db.x][db.y] = ' ';
	db.x = 0;
	db.y = 0;
	d1 = 0;
	v = 0;
}
void Loading() {
	char x = 196;
	Sleep(1000);
	gotoxy(28, 23);
	printf("Xin cho ");
	for (int i = 0; i < 100; i++)
	{
		textcolor(12);
		gotoxy(i, 22);
		printf("%c", x);
		gotoxy(36, 23);
		textcolor(7);
		printf("%d%c", i, 37);
		if (i < 15) Sleep(50);
		else if (i > 14 && i < 50) Sleep(10);
		else Sleep(1);
	}
}
void cap_nhat() {
	XoaManHinh();
	printf("\n\tDiem: %04d\n", diem);
	in_mt();
	for (i = 0; i < 4; i++) { printf("\n"); }
	printf("[%c] [%c] [%c] [%c]: Dieu khien \t [ESC]: Tam dung", 30, 31, 17, 16);
}
void luu_diem() {
	switch (mapchoi) {
	case 1:doc_diem_cao("hi0.txt"); break;
	case 2:doc_diem_cao("hi1.txt"); break;
	case 3:doc_diem_cao("hi2.txt"); break;
	}
	if (diem <= diemcao[4]) printf("\n\tDiem cua ban: %d", diem);
	else if ((diem > diemcao[4]) && (diem <= diemcao[0])) printf("\n\tDiem cao: %d", diem);
	else printf("\n\tDiem cao nhat: %d", diem);
	if (diem > diemcao[4]) { diemcao[4] = diem; }
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (diemcao[i] < diemcao[j]) {
				hoan_doi(diemcao[i], diemcao[j]);
			}
		}
	}
	switch (mapchoi) {
	case 1:ghi_diem_cao("hi0.txt"); break;
	case 2:ghi_diem_cao("hi1.txt"); break;
	case 3:ghi_diem_cao("hi2.txt"); break;
	}
}
void khoi_tao() {
	soluongdotcuasnake = 2;
	if (mapchoi == 1) mapdangchoido = 0;
	else if ((mapchoi == 3) && (mapdangchoido != 1)) mapdangchoido = 1;
	if (mapdangchoido == 3) s[0].x = 3;
	else s[0].x = 5;
	s[0].y = 8;
	if (mapdangchoido == 3) s[1].x = 3;
	else s[1].x = 5;
	s[1].y = 9;
	huongdichuyen = 3;
	a[s[0].x][s[0].y] = 'o';
	a[s[1].x][s[1].y] = 'o';
	stop = 0;
	ps = 0;
}
void hoan_thanh() {
	Sleep(1000);
	for (i = 0; i < 6; i++) {
		system("color 70");
		Sleep(100);
		system("color 07");
		Sleep(100);
	}
}
void tiep_theo() {
	hoan_thanh();
	system("cls");
	khung();
	soluongdotcuasnake = 2;
	mapdangchoido++;
	if (mapdangchoido == 3) s[0].x = 3;
	else s[0].x = 5;
	s[0].y = 8;
	if (mapdangchoido == 3) s[1].x = 3;
	else s[1].x = 5;
	s[1].y = 9;
	huongdichuyen = 3;
	a[s[0].x][s[0].y] = 'O';
	a[s[soluongdotcuasnake - 1].x][s[soluongdotcuasnake - 1].y] = 'o';
	stop = 0;
	ps = 1;
	ve_me_cung();
	tao();
	in_mt();
	for (i = 0; i < 4; i++)
	{
		printf("\n");
	}
	printf("[%c] [%c] [%c] [%c]: Dieu khien \t [ESC]: Tam dung", 30, 31, 17, 16);
	ghi_trang_thai("save.ini");
	Sleep(600 - 65 * capdo);
	while (ps == 1) {
		t = getch();
		if (t == 27) break;
		else if (t == -32) {
			t = getch();
			if ((t == 72) && (huongdichuyen != 1)) huongdichuyen = 0;
			else if ((t == 80) && (huongdichuyen != 0)) huongdichuyen = 1;
			else if ((t == 75) && (huongdichuyen != 3)) huongdichuyen = 2;
			else if ((t == 77) && (huongdichuyen != 2)) huongdichuyen = 3;
			ps = 0;
		}
		else ps = 1;
	}
}
void di_chuyen(int k) {
	if (d1 > 0) d1--;
	if (d1 == 0) xoa_db();
	tg = s[0];
	a[s[0].x][s[0].y] = ' ';
	for (i = 0; i < soluongdotcuasnake - 1; i++) {
		s[i] = s[i + 1];
		a[s[i].x][s[i].y] = 'o';
	}
	s[soluongdotcuasnake - 1].x = s[soluongdotcuasnake - 2].x + dx[k];
	s[soluongdotcuasnake - 1].y = s[soluongdotcuasnake - 2].y + dy[k];
	if (s[soluongdotcuasnake - 1].x == 0) s[soluongdotcuasnake - 1].x = 8;
	else if (s[soluongdotcuasnake - 1].x == 9) s[soluongdotcuasnake - 1].x = 1;
	if (s[soluongdotcuasnake - 1].y == 0) s[soluongdotcuasnake - 1].y = 16;
	else if (s[soluongdotcuasnake - 1].y == 17) s[soluongdotcuasnake - 1].y = 1;
	if (a[s[soluongdotcuasnake - 1].x][s[soluongdotcuasnake - 1].y] == '+') { stop = 1; }
	a[s[soluongdotcuasnake - 1].x][s[soluongdotcuasnake - 1].y] = 'O';	// đầu con rắn
	if ((s[soluongdotcuasnake - 1].x == f.x) && (s[soluongdotcuasnake - 1].y) == f.y) {	// nếu rắn ăn dược mồi:
		z++;
		if (z >= 15) {
			z = 1;
		}
		if ((mapchoi != 3) || ((mapchoi == 3) && (soluongdotcuasnake < 15))) diem += capdo;
		if (diem > 9999) diem = 9999;
		if ((((mapdangchoido == 0) || (mapdangchoido == 3)) && (soluongdotcuasnake < 100)) || ((mapdangchoido != 0) && (mapdangchoido != 3) && (soluongdotcuasnake < 126 - p))) {
			soluongdotcuasnake++;
			for (i = soluongdotcuasnake - 1; i >= 0; i--) { s[i + 1] = s[i]; }
			s[0] = tg;
			a[s[0].x][s[0].y] = '*';	// sau khi ăn được mồi thì in ra cái này ở phía sau đuôi
			if ((mapchoi != 3) || ((mapchoi == 3) && (soluongdotcuasnake < 15))) {
				tao();
			}
			if (soluongdotcuasnake % 5 == 2) {
				if (d1 > 0) xoa_db();
				if (kt22() == 1) tao_db_2x2();
				else tao_db();
				d1 = 14;
			}
			if ((mapchoi == 3) && (soluongdotcuasnake == 15)) xoa_db();
		}
		else tao();
	}
	if (v == 1)
		if (((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y)) || ((s[soluongdotcuasnake - 1].x == db.x + 1) && (s[soluongdotcuasnake - 1].y == db.y)) || ((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y + 1)) || ((s[soluongdotcuasnake - 1].x == db.x + 1) && (s[soluongdotcuasnake - 1].y == db.y + 1))) {
			diem += (d1 * 5 - rand() % 5) * capdo;
			xoa_db();
		}
		else if ((s[soluongdotcuasnake - 1].x == db.x) && (s[soluongdotcuasnake - 1].y == db.y)) {
			diem += (d1 * 5 - rand() % 5) * capdo;
			xoa_db();
		}
	if ((f.x != 0) && (f.y != 0) && (a[f.x][f.y] == ' ')) { a[f.x][f.y] = '@'; }
	for (i = 0; i < soluongdotcuasnake - 1; i++)
		for (j = i + 1; j < soluongdotcuasnake; j++)
			if ((s[i].x == s[j].x) && (s[i].y == s[j].y)) {
				stop = 1;
				break;
			}
	cap_nhat();
	if (stop == 1) Sleep(2000);
}
void van_moi() {
	system("cls 2>save.ini");
	diem = 0;
	khung();
	khoi_tao();
	ve_me_cung();
	tao();
	in_mt();
	for (i = 0; i < 4; i++) printf("\n");
	printf("[%c] [%c] [%c] [%c]: Dieu khien \t [ESC]: Tam dung", 30, 31, 17, 16);
	Sleep(600 - 65 * capdo);
	while (ps == 0) {
		if (kbhit()) {
			t = getch();
			if (t == -32) {
				t = getch();
				if ((t == 72) && (huongdichuyen != 1)) huongdichuyen = 0;
				else if ((t == 80) && (huongdichuyen != 0)) huongdichuyen = 1;
				else if ((t == 75) && (huongdichuyen != 3)) huongdichuyen = 2;
				else if ((t == 77) && (huongdichuyen != 2)) huongdichuyen = 3;
			}
			else if (t == 27) {
				if (stop == 0) {
					ghi_trang_thai("save.ini");
					ps = 1;
					opt--;
				}
				else {
					system("cls 2>save.ini");
					luu_diem();
				}
				opt = 1;
				break;
			}
		}
		if (stop == 0) {
			if ((kbhit() == 0) || !((t == -32) && ((t == 72) || (t == 80) || (t == 75) || (t == 77)))) {
				di_chuyen(huongdichuyen);
				Sleep(600 - 65 * capdo);
			}
			if ((mapchoi == 3) && (soluongdotcuasnake == 15))
				if (mapdangchoido < 5) tiep_theo();
				else {
					stop = 1;
					Sleep(1000);
				}
		}
		else {
			system("cls 2>save.ini");
			if ((mapchoi == 3) && (mapdangchoido == 5) && (soluongdotcuasnake == 15)) printf("\t---- CHIEN DICH DA HOAN THANH ----\n");
			else printf("\t---- GAME OVER ----\n");
			luu_diem();
			printf("\nXin vui long doi de quay lai menu");
			Sleep(2000);
			opt = 1;
			break;
		}
	}
}
void tiep_tuc() {
	Loading();
	system("cls");
	doc_trang_thai("save.ini");
	khung();
	ve_me_cung();
	for (i = 0; i < soluongdotcuasnake; i++) { a[s[i].x][s[i].y] = '*'; }
	if ((f.x != 0) && (f.y != 0)) a[f.x][f.y] = '@';
	if ((db.x != 0) && (db.y != 0)) {
		if (v == 1) {
			if ((f.x == db.x) && (f.y == db.y)) a[db.x][db.y] = '*';
			else a[db.x][db.y] = '*';
			if ((f.x == db.x + 1) && (f.y == db.y)) a[db.x + 1][db.y] = '*';
			else a[db.x + 1][db.y] = '*';
			if ((f.x == db.x) && (f.y == db.y + 1)) a[db.x][db.y + 1] = '*';
			else a[db.x][db.y + 1] = '*';
			if ((f.x == db.x + 1) && (f.y == db.y + 1)) a[db.x + 1][db.y + 1] = '*';
			else a[db.x + 1][db.y + 1] = '*';
		}
		else a[db.x][db.y] = '1';
	}
	stop = 0;
	ps = 1;
	cap_nhat();
	Sleep(600 - 65 * capdo);
	while (ps == 1) {
		t = getch();
		if (t == 27) break;
		else if (t == -32) {
			t = getch();
			if ((t == 72) && (huongdichuyen != 1)) huongdichuyen = 0;
			else if ((t == 80) && (huongdichuyen != 0)) huongdichuyen = 1;
			else if ((t == 75) && (huongdichuyen != 3)) huongdichuyen = 2;
			else if ((t == 77) && (huongdichuyen != 2)) huongdichuyen = 3;
			ps = 0;
		}
		else ps = 1;
	}
	while (ps == 0) {
		if (kbhit()) {
			t = getch();
			if (t == -32) {
				t = getch();
				if ((t == 72) && (huongdichuyen != 1)) huongdichuyen = 0;
				else if ((t == 80) && (huongdichuyen != 0)) huongdichuyen = 1;
				else if ((t == 75) && (huongdichuyen != 3)) huongdichuyen = 2;
				else if ((t == 77) && (huongdichuyen != 2)) huongdichuyen = 3;
			}
			else if (t == 27) {
				if (stop == 0) {
					ghi_trang_thai("save.ini");
					ps = 1;
				}
				else {
					system("cls 2>save.ini");
					luu_diem();
				}
				opt = 1;
				break;
			}
		}
		if (stop == 0) {
			if ((kbhit() == 0) || !((t == -32) && ((t == 72) || (t == 80) || (t == 75) || (t == 77)))) {
				di_chuyen(huongdichuyen);
				Sleep(600 - 65 * capdo);
			}
			if ((mapchoi == 3) && (soluongdotcuasnake == 15))
				if (mapdangchoido < 5) tiep_theo();
				else {
					stop = 1;
					Sleep(2000);
				}
		}
		else {
			system("cls 2>save.ini");
			if ((mapchoi == 3) && (mapdangchoido == 5) && (soluongdotcuasnake == 15)) printf("\t---- CHIEN DICH DA HOAN THANH ----\n");
			else printf("\t---- GAME OVER ----\n");
			luu_diem();
			printf("\n[ ] Xin vui long doi de quay lai menu");
			Sleep(2000);
			opt = 1;
			break;
		}
	}
}
void cap_do() {
	ptr = capdo;
	while (true) {
		system("cls");
		printf("\t---- SNAKE %c CAP DO ----\n", 16);
		for (i = 0; i < 4; i++) printf("\n");
		printf("\t  ");
		for (i = 0; i < 10; i++) printf("%c", 205);
		printf("\n");
		printf(" \t %c ", 186);
		for (i = 0; i < ptr; i++) {
			textcolor(110);
			printf(" \u001b[0m");
		}
		for (i = 0; i < 8 - ptr; i++) {
			textcolor(7);
			printf(" \u001b[0m");
		}
		printf(" %c\n", 186);
		printf("\t  ");
		for (i = 0; i < 10; i++) printf("%c", 205);
		for (i = 0; i < 4; i++) printf("\n");
		printf("[%c] [%c]: Thay doi tuy chon \t [Enter]: Xac nhan \t [ESC]: Quay lai menu", 17, 16);
		t = getch();
		if (t == -32) {
			t = getch();
			if ((t == 75) && (ptr > 1)) ptr--;
			else if ((t == 77) && (ptr < 8)) ptr++;
		}
		else if ((t == 13) || (t == 27)) break;
	}
	if (t == 13) {
		if ((capdo != ptr) && (empty_file("save.ini") == 0)) {
			system("cls 2>save.ini");
			opt--;
		}
		capdo = ptr;
		on_exit();
	}
}
void me_cung() {
	if (mapchoi == 3) opt3 = 0;
	else opt3 = mapdangchoido;
	while (true) {
		system("cls");
		printf("\t---- SNAKE %c CHE DO %c ME CUNG ----\n", 16, 16);
		if (opt3 == 0) {
			textcolor(110);
			
		}
		printf("[1] Khong co me cung%21s\u001b[0m\n", ""); // 17
		if (opt3 == 1) {
			textcolor(110);
		}
		printf("[2] Hop%34s\u001b[0m\n", "");	//	4
		if (opt3 == 2) {
			textcolor(110);
		}
		printf("[3] Duong ham%28s\u001b[0m\n", "");	// 10
		if (opt3 == 3) {
			textcolor(110);
		}
		printf("[4] Nha may%30s\u001b[0m\n", "");	//8
		if (opt3 == 4) {
			textcolor(110);
		}
		printf("[5] Duong ray%28s\u001b[0m\n", "");	//10
		if (opt3 == 5) {
			textcolor(110);
		}
		printf("[6] Can ho%31s\u001b[0m", "");//7
		for (i = 0; i < 4; i++) { printf("\n"); }
		printf("[%c] [%c] : Chon muc \t [Enter]: Xac nhan \t [ESC]: Quay lai che do", 30, 31);
		t = getch();
		if ((t == 13) || (t == 27)) break;
		else if (t == -32) {
			t = getch();
			if (t == 72) opt3--;
			else if (t == 80) opt3++;
		}
		if (opt3 < 0) opt3 = 5;
		else if (opt3 > 5) opt3 = 0;
	}
	if (t == 13) {
		if (((mapchoi == 1) || (mapchoi == 3) || ((mapchoi == 2) && (mapdangchoido != opt3))) && (empty_file("save.ini") == 0)) {
			system("cls 2>save.ini");
			opt--;
		}
		mapchoi = 2;
		mapdangchoido = opt3;
		on_exit();
	}
}
void che_do() {
	opt2 = mapchoi;
	while (true) {
		system("cls");
		printf("\t---- SNAKE %c CHE DO ----\n", 16);
		if (opt2 == 1) {
			textcolor(110);
			
		}
		printf("[1] Kinh dien%28s\u001b[0m\n", "");	// 10
		if (opt2 == 2) {
			textcolor(110);
		}
		printf("[2] Hien dai%29s\u001b[0m\n", "");	// 9
		if (opt2 == 3) {
			textcolor(110);
		}
		printf("[3] Chien dich%27s\u001b[0m", "");	// 11
		for (i = 0; i < 4; i++) printf("\n");
		printf("[%c] [%c] : Chon muc \t [Enter]: Xac nhan \t [ESC]: Quay lai menu", 30, 31);
		t = getch();
		if (t == 13) {
			if (opt2 == 2) me_cung();
			else break;
		}
		else if (t == 27) break;
		else if (t == -32) {
			t = getch();
			if (t == 72) opt2--;
			else if (t == 80) opt2++;
		}
		if (opt2 < 1) opt2 = 3;
		else if (opt2 > 3) opt2 = 1;
	}
	if (opt2 == 1) mapdangchoido = 0;
	else if (opt2 == 3) mapdangchoido = 1;
	if (t == 13) {
		if ((mapchoi != opt2) && (empty_file("save.ini") == 0)) {
			system("cls 2>save.ini");
			opt--;
		}
		mapchoi = opt2;
		on_exit();
	}
}
void huong_dan() {
	while (true) {
		system("cls");
		printf("\t---- SNAKE %c HUONG DAN ----\n", 16);
		printf("Su dung cac phim mui ten de dieu khien ran. An thuc an ma tranh cham cac chuong \n");
		printf("ngai vat va an thuc an dac biet nhanh chong de ghi them diem.");
		for (i = 0; i < 4; i++) printf("\n");
		printf("[ESC]: Quay lai menu");
		if (getch() == 27) break;
	}
}
void diem_cao() {
	switch (mapchoi) {
	case 1:doc_diem_cao("hi0.txt"); break;
	case 2:doc_diem_cao("hi1.txt"); break;
	case 3:doc_diem_cao("hi2.txt"); break;
	}
	while (true) {
		system("cls");
		printf("\t---- SNAKE %c DIEM CAO ----\n", 16);
		for (i = 0; i < 5; i++) { printf("[%d]: %d\n", i + 1, diemcao[i]); }
		for (i = 0; i < 4; i++) { printf("\n"); }
		printf("[ESC]: Quay lai menu");
		if (getch() == 27) break;
	}
}
void dat_lai() {
	opt4 = 1;
	while (true) {
		system("cls");
		printf("\t---- SNAKE %c DAT LAI ----\n", 16);
		if (opt4 == 1) {
			textcolor(110);
			
		}
		printf("[1] Thiet lap du lieu%60s\u001b[0m\n", "");
		if (opt4 == 2) {
			textcolor(110);
			
		}
		printf("[2] Diem cao%69s\u001b[0m\n", "");
		if (opt4 == 3) {
			textcolor(110);
			
		}
		printf("[3] Khoi tao tat ca%62s\u001b[0m", "");
		for (i = 0; i < 4; i++) printf("\n");
		printf("[%c] [%c] : Chon muc \t [Enter]: Xac nhan \t [ESC]: Quay lai menu", 30, 31);
		t = getch();
		if (t == 13) {
			switch (opt4) {
			case 1: {
				while (reset_cfg[0] == 0) {
					system("cls");
					printf("\t---- SNAKE %c DAT LAI %c XAC NHAN ----\n", 16, 16);
					printf("[?] Dong y cai dat lai?\n");
					printf("[ ]Thiet lap du lieu\n");
					printf("[Enter]\t\t: Xac nhan\n");
					printf("[ESC]\t\t: Huy");
					t = getch();
					if (t == 27) break;
					if (t == 13) {
						system("cls 2>cfg.ini");
						if (empty_file("save.ini") == 0) {
							system("cls 2>save.ini");
							opt--;
						}
						capdo = 1;
						mapchoi = 1;
						mapdangchoido = 0;
						on_exit();
						reset_cfg[0] = 1;
					}
					if ((t != 13) && (t != 27)) reset_cfg[0] = 0;
				}
				break;
			}
			case 2: {
				while (reset_cfg[1] == 0) {
					system("cls");
					printf("\t---- SNAKE %c DAT LAI %c XAC NHAN ----\n", 16, 16);
					printf("[?] Dong y cai dat lai?\n");
					printf("[ ] Diem cao\n");
					printf("[Enter]\t\t: Xac nhan\n");
					printf("[ESC]\t\t: Huy");
					t = getch();
					if (t == 27) break;
					if (t == 13) {
						for (i = 0; i < 5; i++) { diemcao[i] = 0; }
						ghi_diem_cao("hi0.txt");
						ghi_diem_cao("hi1.txt");
						ghi_diem_cao("hi2.txt");
						reset_cfg[1] = 1;
					}
					if ((t != 13) && (t != 27)) reset_cfg[1] = 0;
				}
				break;
			}
			case 3: {
				while (reset_cfg[2] == 0) {
					system("cls");
					printf("\t---- SNAKE %c DAT LAI %c XAC NHAN ----\n", 16, 16);
					printf("[?] Dong y cai dat lai?\n");
					printf("[ ]Khoi tao tat ca\n");
					printf("[Enter]\t\t: Xac nhan\n");
					printf("[ESC]\t\t: Huy");
					t = getch();
					if (t == 27) break;
					if (t == 13) {
						system("cls 2>cfg.ini");
						if (empty_file("save.ini") == 0) {
							system("cls 2>save.ini");
							opt--;
						}
						capdo = 1;
						mapchoi = 1;
						mapdangchoido = 0;
						for (i = 0; i < 5; i++) { diemcao[i] = 0; }
						ghi_diem_cao("hi0.txt");
						ghi_diem_cao("hi1.txt");
						ghi_diem_cao("hi2.txt");
						on_exit();
						reset_cfg[2] = 1;
					}
					if ((t != 13) && (t != 27)) reset_cfg[2] = 0;
				}
				break;
			}
			}
			for (i = 0; i < 3; i++) { reset_cfg[i] = 0; }
		}
		else if (t == 27) break;
		else if (t == -32) {
			t = getch();
			if (t == 72) opt4--;
			else if (t == 80) opt4++;
		}
		if (opt4 < 1) opt4 = 3;
		else if (opt4 > 3) opt4 = 1;
	}
}
void menu() {
	system("cls");
	printf("\t---- SNAKE ----\n");
	if (opt == 1) {
		textcolor(110);
	}
	printf("[1] Tro choi moi%25s\u001b[0m\n", "");//13
	if (opt == 2) {
		textcolor(110);
	}
	printf("[2] Cap do%31s\u001b[0m\n", "");	// 7
	if (opt == 3) {
		textcolor(110);
	}
	printf("[3] Che do%31s\u001b[0m\n", "");
	if (opt == 4) {
		textcolor(110);
	}
	printf("[4] Huong dan%28s\u001b[0m\n", "");//10
	if (opt == 5) {
		textcolor(110);
	}
	printf("[5] Diem cao%29s\u001b[0m\n", "");	//	 9
	if (opt == 6) {
		textcolor(110);
	}
	printf("[6] Dat lai%30s\u001b[0m\n", ""); // 8
	if (opt == 7) {
		textcolor(110);
	}
	printf("[7] Thoat%32s\u001b[0m", "");	// 6
	for (i = 0; i < 4; i++) printf("\n");
	printf("[%c] [%c]: Chon muc \t[Enter]: Xac nhan", 30, 31);
	t = getch();
	if (t == 13) {
		switch (opt) {
		case 1:van_moi(); break;
		case 2:cap_do(); break;
		case 3:che_do(); break;
		case 4:huong_dan(); break;
		case 5:diem_cao(); break;
		case 6:dat_lai(); break;
		case 7: {
			on_exit();
			system("cls");
			system("attrib +r cfg.ini");
			system("attrib +r save.ini");
			exit(0);
			break;
		}
		}
	}
	else if (t == -32) {
		t = getch();
		if (t == 72) opt--;
		else if (t == 80) opt++;
	}
	if (opt < 1) opt = 7;
	else if (opt > 7) opt = 1;
}
void menu_tiep_tuc() {
	system("cls");
	printf("\t---- SNAKE ----\n");
	if (opt == 1) {
		textcolor(110);
	}
	printf("[1] Tiep tuc%29s\u001b[0m\n", "");
	if (opt == 2) {
		textcolor(110);
	}
	printf("[2] Tro choi moi%25s\u001b[0m\n", "");//13
	if (opt == 3) {
		textcolor(110);
	}
	printf("[3] Cap do%31s\u001b[0m\n", "");	// 7
	if (opt == 4) {
		textcolor(110);
	}
	printf("[4] Che do%31s\u001b[0m\n", "");
	if (opt == 5) {
		textcolor(110);
	}
	printf("[5] Huong dan%28s\u001b[0m\n", "");//10
	if (opt == 6) {
		textcolor(110);
	}
	printf("[6] Diem cao%29s\u001b[0m\n", "");	//	 9
	if (opt == 7) {
		textcolor(110);
	}
	printf("[7] Dat lai%30s\u001b[0m\n", ""); // 8
	if (opt == 8) {
		textcolor(110);
	}
	printf("[8] Thoat%32s\u001b[0m", "");	// 6
	for (i = 0; i < 4; i++) printf("\n");
	printf("[%c] [%c]: Chon muc \t [Enter]: Xac nhan", 30, 31);
	t = getch();
	if (t == 13) {
		switch (opt) {
		case 1:tiep_tuc(); break;
		case 2:van_moi(); break;
		case 3:cap_do(); break;
		case 4:che_do(); break;
		case 5:huong_dan(); break;
		case 6:diem_cao(); break;
		case 7:dat_lai(); break;
		case 8: {
			on_exit();
			system("cls");
			system("attrib +r cfg.ini");
			system("attrib +r save.ini");
			exit(0);
			break;
		}
		}
	}
	else if (t == -32) {
		t = getch();
		if (t == 72) opt--;
		else if (t == 80) opt++;
	}
	if (opt < 1) opt = 8;
	else if (opt > 8) opt = 1;
}

void hinhnen() {
	printf("\n");
	printf( "\n             /^\\/^\\                                            ");
	printf( "\n           _|_o|  O|                                             ");
	printf( "\n \\/     /~     \\_/ \\                                          ");
	printf( "\n  \\____|__________/  \\                                         ");
	printf(" \n         \\_______      \\                                       ");
	printf(" \n                 `\\     \\                  \\                  ");
	printf(" \n                   |     |                   \\                  ");
	printf(" \n                  /      /                    \\                 ");
	printf(" \n                 /     /                       \\\\              ");
	printf(" \n               /      /                         \\ \\            ");
	printf(" \n              /     /                            \\  \\          ");
	printf(" \n            /     /             _----_            \\   \\        ");
	printf(" \n           /     /           _-~      ~-_         |   |          ");
	printf(" \n          (      (        _-~    _--_    ~-_     _/   |          ");
	printf(" \n           \\      ~-____-~    _-~    ~-_    ~-_-~    /          ");
	printf(" \n             ~-_           _-~          ~-_       _-~            ");
	printf(" \n                ~--______-~                ~-___-~             \n\n");
	Loading();
}
int main() {
	ancontrodi();
	hinhnen();
	srand(time(0));
	on_preload();
	on_load();
	while (true) {
		if (empty_file("save.ini") == 0) menu_tiep_tuc();
		else menu();
	}
	on_exit();
	return 0;
}
