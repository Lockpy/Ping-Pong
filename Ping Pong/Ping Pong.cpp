#include "iostream"
#include "windows.h"
#include "conio.h"
#include "ctime"

using namespace std;
#pragma warning(disable : 4996)
HANDLE HC = GetStdHandle(STD_OUTPUT_HANDLE);

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Menu {
public:
	bool select;
	Menu() { select = true; }
	bool eng(bool type) {
		char key;
		print(true, type);
		key = getch();
		if (key == -32) {
			key = getch();
			if (key == 72) { select = true; }
			if (key == 80) { select = false; }
		}
		if (key == 13) {
			print(false, type);
			return select;
		}
		eng(type);
	}
	void print(bool check, bool type) {
		COORD pos;
		if (select) {
			pos.Y = 12;
			pos.X = 33;
			SetConsoleCursorPosition(HC, pos);
			cout << "  ";
			pos.Y = 11;
			SetConsoleCursorPosition(HC, pos);
			if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Green));
			else SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
			cout << ">>";
		}
		pos.X = 35;
		pos.Y = 11;
		if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightMagenta));
		else SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
		SetConsoleCursorPosition(HC, pos);
		if (type)cout << "Play";
		else cout << "Play Again";
		if (!select) {
			pos.Y = 11;
			pos.X = 33;
			SetConsoleCursorPosition(HC, pos);
			cout << "  ";
			pos.Y = 12;
			SetConsoleCursorPosition(HC, pos);
			if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Green));
			else SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
			cout << ">>";
		}
		pos.X = 35;
		pos.Y = 12;
		SetConsoleCursorPosition(HC, pos);
		if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightMagenta));
		else SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
		cout << "Exit";
		pos.X = 30;
		pos.Y = 9;
		SetConsoleCursorPosition(HC, pos);
		if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightGreen));
		else SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
		if (type)for (int i = 0;i < 13;i++)cout << (char)177;
		else for (int i = 0;i < 15;i++)cout << (char)177;
		for (int i = 0;i < 5;i++, pos.Y++, SetConsoleCursorPosition(HC, pos))cout << (char)177;
		if (type)for (int i = 0;i < 14;i++)cout << (char)177;
		else for (int i = 0;i < 16;i++)cout << (char)177;
		if (type)pos.X += 14;
		else pos.X += 16;
		SetConsoleCursorPosition(HC, pos);
		for (int i = 0;i < 6;i++, pos.Y--, SetConsoleCursorPosition(HC, pos))cout << (char)177;
	}


};

class Ball {
public:
	COORD pos;
	int middle;
	int move_type;
	int up, down;
	int move_speed = 50;
	Ball() {
		pos.X = pos.Y = middle = 0;
	}

	void move_cord(int x, int y) {
		print(false);
		pos.X = x;
		pos.Y = y;
		print(true);
	}
	void start_random() {
		move_type = 1 + (rand() % 4);
	}
	void rekoshet() {
		if (move_type == 1) {
			move_type = 2;
			move();
			return;
		}
		if (move_type == 2) {
			move_type = 1;
			move();
			return;
		}
		if (move_type == 3) {
			move_type = 4;
			move();
			return;
		}
		if (move_type == 4) {
			move_type = 3;
			move();
			return;
		}
	}
	void racket_rekoshet() {
		if (move_type == 1) { //Влево вверх 
			move_type = 4;
			move();
			return;
		}
		if (move_type == 2) { //Влево вниз
			move_type = 3;
			move();
			return;
		}
		if (move_type == 3) { //Вправо вниз
			move_type = 2;
			move();
			return;
		}
		if (move_type == 4) { //Вправо вверх
			move_type = 1;
			move();
			return;
		}

		if (move_type == 5) { //Тестовое направление прямо влево!
			move_type = 6;
			move();
			return;
		}

		if (move_type == 6) { //Тестовое направление прямо влево!
			move_type = 5;
			move();
			return;
		}
	}
	void move() {
		int x = pos.X, y = pos.Y;
		if (move_type == 1) {  //Влево вверх 
			if (pos.Y + 1 > up&& pos.X - 1 > 0) {
				x--;
				y--;
				move_cord(x, y);
			}
		}

		if (move_type == 2) { //Влево вниз
			if (pos.Y - 3 < down && pos.X - 1 > 0) {
				x--;
				y++;
				move_cord(x, y);
			}

		}

		if (move_type == 3) { //Вправо вниз
			if (pos.Y - 3 < down && pos.X + 2 < middle * 2) {
				x++;
				y++;
				move_cord(x, y);
			}

		}

		if (move_type == 4) { //Вправо вверх
			if (pos.Y + 1 > up&& pos.X + 2 < middle * 2) {
				x++;
				y--;
				move_cord(x, y);
			}
		}

		if (move_type == 5) { //Тестовое направление прямо влево!
			if (pos.X + 2 < middle * 2) {
				x++;
				//y--;
				move_cord(x, y);
			}
		}

		if (move_type == 6) { //Тестовое направление прямо влево!
			if (pos.X - 1 > 0) {
				x--;
				//y--;
				move_cord(x, y);
			}
		}

		Sleep(move_speed); //Скорость шарика
	}
	bool bord() {
		return (pos.Y + 1 > up) && (pos.Y - 3 < down);
	}
	void print(bool check) {
		SetConsoleTextAttribute(HC, (WORD)((Blue << 4) | LightMagenta));
		SetConsoleCursorPosition(HC, pos);
		//SetConsoleCP(1251);
		//SetConsoleOutputCP(1251);
		if (pos.X > middle)SetConsoleTextAttribute(HC, (WORD)((Red << 4) | LightMagenta));
		if (pos.X < middle)SetConsoleTextAttribute(HC, (WORD)((Blue << 4) | LightMagenta));
		if (check)cout << (char)254;
		else cout << (char)255;
		SetConsoleCP(866);
		SetConsoleOutputCP(866);
	}

};

class Racket {
public:
	COORD pos;
	int score = 0;
	Racket() {
		pos.X = pos.Y = 0;
	}
	void print(bool check, bool p) {
		COORD temp = pos;
		temp.Y -= 2;
		SetConsoleCursorPosition(HC, temp);
		if (check) {
			SetConsoleTextAttribute(HC, (WORD)((White << 4) | White));
			cout << (char)219;
		}
		else {
			if (p)SetConsoleTextAttribute(HC, (WORD)((Blue << 4) | Blue));
			else SetConsoleTextAttribute(HC, (WORD)((Red << 4) | Red));
			cout << (char)255;
		}

		for (int i = 0; i < 4; i++) {
			temp.Y += 1;
			SetConsoleCursorPosition(HC, temp);
			if (check)cout << (char)219;
			else cout << (char)255;
		}
	}
};


class Pong {
private:
	Ball ball;
	Racket p1, p2;
	Menu menu;
	char** pole;
	int pole_weight = 72, pole_height = 23, up = 3, down = pole_height - 4;
	int win_score = 5;
public:
	Pong() { //Конструктор без параметров
		iniz();
		fill();
	}
	Pong(int w, int h) { //Конструктор с параметрами
		pole_weight = w;
		pole_height = h;
		iniz();
		fill();
	}
	void iniz() { //Инициализация
		ball.up = up;
		ball.down = down;
		ball.middle = pole_weight / 2;
		pole = new char* [pole_height]; //Инициализация массива поле
		for (int i = 0; i < pole_height; i++)pole[i] = new char[pole_weight]; //Инициализация массива поле
		p1.pos.X = 1; //Начальные корды ракетки
		p1.pos.Y = p2.pos.Y = (down + 6) / 2; //Начальные корды ракетки
		p2.pos.X = pole_weight - 2; //Начальные корды ракетки

	}
	void fill() { //Заполнение поля
		for (int i = 0; i < pole_height; i++) {

			for (int j = 0; j < pole_weight; j++) {
				if (i == 0 || i == pole_height - 1)pole[i][j] = (char)205;
				else if (j == 0 || j == pole_weight - 1)pole[i][j] = (char)186;
				else pole[i][j] = ' ';
			}

		}
		pole[0][0] = (char)201;
		pole[pole_height - 1][pole_weight - 1] = (char)188;
		pole[0][pole_weight - 1] = (char)187;
		pole[pole_height - 1][0] = (char)200;
		int temp = pole_weight / 2;
	}//Заполнение
	void print_pole() { //Отрисовка поля
		cout << endl;
		for (int i = 0; i < pole_height; i++) {
			for (int j = 0; j < pole_weight; j++) {
				if (pole[i][j] != ' ' && j < pole_weight / 2)SetConsoleTextAttribute(HC, (WORD)((Red << 4) | White));
				if (pole[i][j] != ' ' && j > pole_weight / 2)SetConsoleTextAttribute(HC, (WORD)((Blue << 4) | White));
				if (pole[i][j] == ' ' && j < pole_weight / 2)SetConsoleTextAttribute(HC, (WORD)((Blue << 4) | White));
				if (pole[i][j] == ' ' && j > pole_weight / 2)SetConsoleTextAttribute(HC, (WORD)((Red << 4) | White));
				cout << pole[i][j];
			}
			SetConsoleTextAttribute(HC, (WORD)((Black << 4) | White));
			cout << endl;
		}

	}
	void print_score(bool check) { //Отрисовка счета
		COORD pos;
		int pos1 = pole_weight / 4, pos2 = (pole_weight / 4) * 3;
		pos.Y = 0;
		pos.X = pos1;
		SetConsoleCursorPosition(HC, pos);
		SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightMagenta));
		if (check)cout << p1.score;
		else cout << ' ';
		pos.X = pos2;
		SetConsoleCursorPosition(HC, pos);
		if (check)cout << p2.score;
		else cout << ' ';
		pos.X = (pole_weight / 2) - 4;
		SetConsoleCursorPosition(HC, pos);
		if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightMagenta));
		else SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
		cout << "Ping-Pong";
		SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightMagenta));
	}
	void print() { //Отрисовка всей игры
		print_score(true);
		print_pole();
		p1.print(true, true);
		p2.print(true, false);
		ball.pos.X = pole_weight / 2;
		ball.pos.Y = (down + 6) / 2;
		ball.print(true);
	}

	void goal_alert(bool check, bool p) { //Оповещение гола
		COORD pos;
		pos.Y = 0;
		pos.X = (pole_weight / 2) - 10;
		SetConsoleCursorPosition(HC, pos);
		if (!p) {
			if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightBlue));
			if (!check) SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
			cout << "Blue scored a goal!";
		}
		if (p) {
			if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightRed));
			if (!check) SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
			cout << "Red scored a goal!";
		}
	}

	void goal_pause() { //Пауза после гола
		COORD pos;
		pos.X = pole_weight / 2;
		pos.Y = pole_height / 2;
		SetConsoleCursorPosition(HC, pos);
		SetConsoleTextAttribute(HC, (WORD)((Blue << 4) | LightRed));
		cout << "3";
		Sleep(1000);
		pos.X--;
		SetConsoleCursorPosition(HC, pos);
		cout << " ";
		pos.X++;
		SetConsoleCursorPosition(HC, pos);
		cout << "2";
		Sleep(1000);
		pos.X--;
		SetConsoleCursorPosition(HC, pos);
		cout << " ";
		pos.X++;
		SetConsoleCursorPosition(HC, pos);
		cout << "1";
		Sleep(1000);
		pos.X--;
		SetConsoleCursorPosition(HC, pos);
		cout << " ";
	}

	void win_alert(bool check, bool p) {
		COORD pos;
		pos.Y = 0;
		pos.X = (pole_weight / 2) - 5;
		SetConsoleCursorPosition(HC, pos);
		if (p) {
			if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightBlue));
			if (!check) SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
			cout << "Blue win!";
		}
		if (!p) {
			if (check)SetConsoleTextAttribute(HC, (WORD)((Black << 4) | LightRed));
			if (!check) SetConsoleTextAttribute(HC, (WORD)((Black << 4) | Black));
			cout << "Red Win";
		}
	}

	bool goal_p1() {
		return (ball.pos.X == 1);
	}
	bool goal_p2() {
		return (ball.pos.X == pole_weight - 2);
	}
	bool RocketBordp1() {
		COORD temp = p1.pos;
		temp.Y -= 2;
		int chec = 0;
		if (ball.pos.X - 1 == 1)chec++;
		for (int i = 0; i < 4; i++) {
			if (ball.pos.Y == temp.Y)chec++;
			temp.Y += 1;
		}
		if (ball.pos.Y == temp.Y)chec++;
		if (chec == 2)return true;
		else return false;
	}
	bool RocketBordp2() {
		COORD temp = p2.pos;
		temp.Y -= 2;
		int chec = 0;
		if (ball.pos.X + 1 == temp.X)chec++;
		for (int i = 0; i < 4; i++) {
			if (ball.pos.Y == temp.Y)chec++;
			temp.Y += 1;
		}
		if (ball.pos.Y == temp.Y)chec++;
		if (chec == 2)return true;
		else return false;
	}
	void game(bool first) {
		if (first)if (!menu.eng(true))return;
		GamePlay();
		if (p1.score == win_score)win_alert(true, true);
		if (p2.score == win_score)win_alert(true, false);
		Sleep(3000);
		if (menu.eng(false))game(false);
	}
	void GamePlay() {
		char key;
		this->print();
		ball.start_random();
		for (;;) {
			ball.move();
			if (kbhit() != 0) {
				key = getch();
				if (ball.move_type == 1 || ball.move_type == 2 || ball.move_type == 6) { //Переключение управления - ball.pos.X<pole_weight / 2
					if (key == -106 || key == -26 || key == 87 || key == 119) { //Нажата Ц или ц или W или w
						if (p1.pos.Y - 1 > up) {
							p1.print(0, true);
							p1.pos.Y--;
							p1.print(1, true);
						}
					}
					if (key == -101 || key == -21 || key == 83 || key == 115) { //Нажата Ы или ы или S или s
						if (p1.pos.Y - 1 < down) {
							p1.print(0, true);
							p1.pos.Y++;
							p1.print(1, true);
						}
					}
				}
				if (ball.move_type == 3 || ball.move_type == 4 || ball.move_type == 5) { //Переключение управления - ball.pos.X > pole_weight / 2
					if (key == -32) {
						key = getch();
						if (key == 72) { //Нажата Вверх 72 111
							if (p2.pos.Y - 1 > up) {
								p2.print(0, false);
								p2.pos.Y--;
								p2.print(1, false);
							}
						}
						if (key == 80) { //Нажата Ы или ы или S или s 80 108
							if (p2.pos.Y - 1 < down) {
								p2.print(0, false);
								p2.pos.Y++;
								p2.print(1, false);
							}
						}
					}
				}
			}
			if (RocketBordp1()) {
				ball.racket_rekoshet();
				ball.move();
			}
			if (RocketBordp2()) {
				ball.racket_rekoshet();
				ball.move();
			}
			if (!ball.bord())ball.rekoshet();
			if (goal_p1()) {
				p2.score++;
				print_score(false);
				print_score(true);
				goal_alert(true, true);
				if (p2.score < 5)goal_pause();
				goal_alert(false, true);
				break;
			}
			if (goal_p2()) {
				p1.score++;
				print_score(false);
				print_score(true);
				goal_alert(true, false);
				if (p1.score < 5)goal_pause();
				goal_alert(false, false);
				break;
			}
		}
		if (p1.score < 5 && p2.score < 5)GamePlay();
	}
	~Pong() {
		for (int i = 0; i < pole_height; i++)delete[] pole[i];
		delete[] pole;
	}
};

int main() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Lucida Console"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 500, 220, 0, 0, true); //Перемещяет консоль в угол,MoveWindow(window_handle, x, y, width, height, redraw_window);
	system("mode con cols=73 lines=25"); //Делает консоль на весь экран
	system("title Ping-Pong by KhomenkoGames");
	srand(time(0));
	Pong Game;
	Game.game(true);
	system("CLS");
	system("pause");
	return 0;
}