// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

bool printl(string);
string lower(string);
bool equalsIgnoreCase(string, string);
int random(int, int);

bool rmode = false;
bool gameSet = false;

int **board;
void setupBlankBoard();
void initBoard();
bool boardSet = false;

const int MAX_WIDTH = 58, MAX_HEIGHT = 30;
const int SHIP_NUM = 1;
int width, height;

void render();
void setupgame();
bool shoot(int, int);

void buildShip(int);

int main()
{
	srand(time(NULL));
	std::string command("");

	printl("This is a very simple battleship game.");
	printl("Here's a list of commands:");
	cout << "LIST" << endl << "SETUPBOARD" << endl << "RENDER" << endl << "SETUPGAME" << endl << "SHOOT" << endl << "RMODE" << endl;

	while (true) {

		getline(cin, command);
		command = lower(command);

		if (equalsIgnoreCase(command, "render")) {
			render();
		}
		else if (equalsIgnoreCase(command, "setupgame")) {
			setupgame();
		}
		else if (equalsIgnoreCase(command, "setupboard")) {
			setupBlankBoard();
		}
		else if (equalsIgnoreCase(command, "rmode")) {
			if (rmode) {
				printl("RMODE has been turned off.");
				rmode = false;
			}
			else {
				printl("RMODE has been turned on.");
				rmode = true;
			}
		}
		else if (equalsIgnoreCase(command, "set")) {
			printl("Which column is the position you want to set in? (1-" + to_string(width) + "): ");
			int col;
			cin >> col;
			printl("Which row is the position you want to set in? (1-" + to_string(height) + "): ");
			int row;
			cin >> row;
			printl("What would you like the value to be? (0-3): ");
			int val;
			cin >> val;
			board[row-1][col-1] = val;
		}
		else if (equalsIgnoreCase(command, "shoot")) {
			printl("Which column is the position you want to shoot in? (1-" + to_string(width) + "): ");
			int col;
			cin >> col;
			printl("Which row is the position you want to shoot in? (1-" + to_string(height) + "): ");
			int row;
			cin >> row;
			if (shoot(col, row)) {
				printl("You hit a ship!");
			}
			else {
				printl("Miss!");
			}
		}
		else if (command == "") {
		} else {
			printl("Here's a list of commands:");
			cout << "LIST" << endl << "RENDER" << endl << "SETUPGAME" << endl << "SHOOT" << endl;
		}
	}

    return 0;
}

bool printl(string s) {
	cout << s << endl;
	return true;
}

string lower(string s) {

	int size = s.size();
	string out;
	out.resize(size);
	int i = 0;
	while (s[i]) {
		out[i] = std::tolower(s[i]);
		i++;
	}
	return out;
}

bool equalsIgnoreCase(string s1, string s2) {
	string newS1, newS2;
	newS1 = lower(s1);
	newS2 = lower(s2);

	if (newS1 == newS2) {
		return true;
	} 
	return false;
}

void initBoard() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j] = 0;
		}
	}
}

void setupgame() {

	if (boardSet) {
		for (int j = 0; j < SHIP_NUM; j++) {

			switch (j) {
			case 0:
				buildShip(5);
				break;
			case 1:
				buildShip(4);
				break;
			case 2:
				buildShip(4);
				break;
			case 3:
				buildShip(3);
				break;
			case 4:
				buildShip(2);
				break;
			default:
				buildShip(random(2, 5));
			}
		}
		gameSet = true;
	}
	else {
		printl("You haven't initialized the board yet! Use: SETUPBOARD");
	}

	if (rmode)
		render();
}

void render() {
	if (boardSet) {
		string defs = "%c[34m";
		char def[20];
		strcpy(def, defs.c_str());
		printf(def, 27);
		for (int i = 0; i <= height*2; i++) {
			if (i % 2 == 0) {
				for (int j = 0; j < width; j++) {
					cout << "+---";
				}
				printl("+");
			}
			else {
				for (int j = 0; j < width; j++) {
					string val = to_string(board[i / 2][j]);
					cout << "| ";
					string foo;
					char bar[1024];
					switch (board[i / 2][j]) {
					case 1:
						foo = "%c[37m" + to_string(board[i / 2][j]) + " ";
						strcpy(bar, foo.c_str());
						printf(bar, 27);
						printf(def, 27);
						break;
					case 2:
						foo = "%c[32m" + to_string(board[i / 2][j]) + " ";
						strcpy(bar, foo.c_str());
						printf(bar, 27);
						printf(def, 27);
						break;
					case 3:
						foo = "%c[31m" + to_string(board[i / 2][j]) + " ";
						strcpy(bar, foo.c_str());
						printf(bar, 27);
						printf(def, 27);
						break;
					default:
						cout << to_string(board[i / 2][j]) + " ";
						printf(def, 27);
						break;
					}
				}
				cout << "|\n";
			}
		}
		printf("%c[0m", 27);
	}
	else {
		printl("You haven't initialized the board yet! Use: SETUPBOARD");
	}

}

bool shoot(int x, int y) {
	bool hit = false;
	switch (board[y-1][x-1]) {
	case 0:
		board[y-1][x-1] = 1;
		hit = false;
		break;
	case 2:
		board[y-1][x-1] = 3;
		hit = true;
		break;
	default:
		hit = false;
		break;
	}

	bool shipStillAlive = false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == 2) {
				shipStillAlive = true;
			}
		}
	}

	if (gameSet) {
		if (!shipStillAlive) {
			printl("YOU WIN!!!");
			// TODO End game.
		}
	}

	if (rmode)
		render();

	if (hit) {
		return true;
	}
	else {
		return false;
	}

}

int random(int min, int max) {
	return rand() % max + min;
}

void setupBlankBoard()
{
	if (!boardSet) {
		bool isOkay = false;

		while (!isOkay) {
			cout << "How many columns would you like the board to have?";
			cin >> width;
			if (width > MAX_WIDTH) {
				printl("That's too big! Max is " + to_string(MAX_WIDTH) + "!");
			}
			else {
				isOkay = true;
			}
		}

		isOkay = false;

		while (!isOkay) {
			cout << "How many rows would you like the board to have?";
			cin >> height;
			if (height > MAX_HEIGHT) {
				printl("That's too big! Max is " + to_string(MAX_HEIGHT) + "!");
			}
			else {
				isOkay = true;
			}
		}

		board = new int*[height];

		for (int i = 0; i < height; i++) {
			board[i] = new int[width];
		}
		boardSet = true;
		initBoard();
	}
}

void buildShip(int size) {
	bool reset = false;
	bool loop = true;

	int xpos = random(1, width);
	int ypos = random(1, height);
	int dir = random(1, 4);

	while (loop) {
		if (reset) {
			xpos = random(1, width);
			ypos = random(1, height);
			dir = random(1, 4);
			reset = false;
		}
		switch (dir) {
		case 1:
			if (ypos + size > height) {
				dir = 2;
			}
			else {
				for (int c = 0; c < size; c++) {
					board[ypos + c - 1][xpos - 1] = 2;
				}
				loop = false;
				break;
			}
		case 2:
			if (xpos + size > width) {
				dir = 3;
			}
			else {
				for (int c = 0; c < size; c++) {
					board[ypos - 1][xpos + c - 1] = 2;
				}
				loop = false;
				break;
			}
		case 3:
			if (ypos - size < 0) {
				dir = 4;
			}
			else {
				for (int c = 0; c < size; c++) {
					board[ypos - c - 1][xpos - 1] = 2;
				}
				loop = false;
				break;
			}
		case 4:
			if (xpos - size < 0) {
				reset = true;
			}
			else {
				for (int c = 0; c < size; c++) {
					board[ypos - 1][xpos - c - 1] = 2;
				}
				loop = false;
				break;
			}
		}
	}

	printl("lit " + to_string(size) + " " + to_string(xpos) + " " + to_string(ypos) + " " + to_string(dir));
}