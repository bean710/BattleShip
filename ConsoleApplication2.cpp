// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

bool printl(string);
string lower(string);
bool equalsIgnoreCase(string, string);
int random(int, int);

int board[10][10];
void initBoard();
void render();
void setupgame();
bool shoot(int, int);

int main()
{
	cout << random(2, 7);
	initBoard();

	std::string name;
	std::string command("");

	cout << "Why hello there! Welcome to battleship, what's your name?" << endl;
	cout << "Please enter your name: ";

	getline(cin, name);

	cout << "Welcome, " << name << ". Nice to meet you!" << endl;
	printl("This is a very simple battleship game.");
	printl("Here's a list of them:");
	cout << "LIST" << endl << "RENDER" << endl << "SETUPGAME" << endl << "SHOOT" << endl;

	while (true) {

		getline(cin, command);
		command = lower(command);

		 if (equalsIgnoreCase(command, "render")) {
			render();
		}
		else if (equalsIgnoreCase(command, "setupgame")) {
			setupgame();
		}
		else if (equalsIgnoreCase(command, "set")) {
			printl("Which column is the position you want to set in? (1-10): ");
			int col;
			cin >> col;
			printl("Which row is the position you want to set in? (1-10): ");
			int row;
			cin >> row;
			printl("What would you like the value to be? (0-3): ");
			int val;
			cin >> val;
			board[row-1][col-1] = val;
		}
		else if (equalsIgnoreCase(command, "shoot")) {
			printl("Which column is the position you want to shoot in? (1-10): ");
			int col;
			cin >> col;
			printl("Which row is the position you want toshoot in? (1-10): ");
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
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 0;
		}
	}
}

void setupgame() {
	/*for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int rolled = rand() % 6 + 1;
			if (rolled == 3) {
				board[j][i] = 2;
			}
		}
	}*/

	for (int j = 0; j < 5; j++) {
		switch (j) {
		case 0:
			break;
		}
	}
}

void render() {
	string defs = "%c[34m";
	char def[20];
	strcpy(def, defs.c_str());
	printf(def, 27);
	for (int i = 0; i <= 20; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < 10; j++) {
				cout << "+---";
			}
			printl("+");
		}
		else {
			for (int j = 0; j < 10; j++) {
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

bool shoot(int x, int y) {
	switch (board[y-1][x-1]) {
	case 0:
		board[y-1][x-1] = 1;
		return 0;
	case 2:
		board[y-1][x-1] = 3;
		return 1;
	default:
		return 0;
	}
}

int random(int min, int max) {
	return (rand() / 100)*max + min;
}