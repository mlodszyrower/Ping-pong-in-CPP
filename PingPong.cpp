#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

enum Direction { STOP, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT };

class Ball 
{
private: 
	int x, y;
	int originalX, originalY;
	Direction direction;
public:
	Ball(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posY; 
		y = posY;
		direction = STOP;
	}
	void Reset() {
		x = originalX;
		y = originalY;
		direction = STOP;
	}
	void ChangeDirection(Direction dir) {
		direction = dir;
	}
	void RandomDirection() {
		direction = (Direction)((rand() % 6) + 1);
	}
	inline int GetX() {
		return x;
	}

	inline int GetY() {
		return y;
	}
	inline Direction GetDirection() {
		return direction;
	}
	void Move() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}
	friend ostream& operator<<(ostream& o, Ball b) {
		o << "Ball [" << b.x << "," << b.y << "][" << b.direction << "]";
		return o;
	}

};

class Paddle {
private:
	int x, y;
	int originalX, originalY;
public:
	Paddle() {
		x = y = 0;
	}
	Paddle(int posX, int posY) : Paddle() {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() {
		x = originalX; 
		y = originalY;
	}
	inline int GetX() {
		return x;
	}
	inline int GetY() {
		return y;
	}
	inline void MoveUp() {
		y--;
	}
	inline void MoveDown() {
		y++;
	}
	friend ostream& operator<<(ostream& o, Paddle b) {
		o << "Paddle [" << b.x << "," << b.y << "]";
		return o;
	}
};

class GameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	Ball* ball;
	Paddle* player1;
	Paddle* player2;
public:
	GameManager(int w, int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new Ball(w / 2, h / 2);
		player1 = new Paddle(1, h / 2 - 3);
		player2 = new Paddle(w - 2, h / 2 - 3);
	}
	~GameManager() {
		delete ball, player1, player2;
	}
	void ScoreUp(Paddle * player) {
		if (player == player1)
			score1++;
		else
			score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw() {
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->GetX();
				int bally = ball->GetY();
				int player1x = player1->GetX();
				int player1y = player1->GetY();
				int player2x = player2->GetX();
				int player2y = player2->GetY();

				if (j == 0)
					cout << "#";

				if (ballx == j && bally == i)
					cout << "0";
				else if (player1x == j && player1y == i)
					cout << "#";
				else if (player2x == j && player2y == i)
					cout << "#";

				else if (player1x == j && player1y + 1 == i)
					cout << "#";
				else if (player1x == j && player1y + 2 == i)
					cout << "#";
				else if (player1x == j && player1y + 3 == i)
					cout << "#";

				else if (player2x == j && player2y + 1 == i)
					cout << "#";
				else if (player2x == j && player2y + 2 == i)
					cout << "#";
				else if (player2x == j && player2y + 3 == i)
					cout << "#";
				

				else
					cout << " ";

				if (j == width - 1)
					cout << "#";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
	}
	void Input() {
		ball->Move();

		int ballx = ball->GetX();
		int bally = ball->GetY();
		int player1x = player1->GetX();
		int player1y = player1->GetY();
		int player2x = player2->GetX();
		int player2y = player2->GetY();

		if (_kbhit()) {
			char current = _getch();
			if (current == up1)
				if (player1y > 0) 
					player1->MoveUp();
			if (current == up2)
				if (player2y > 0)
					player2->MoveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->MoveDown();
			if (current == down2)
				if (player2y + 4 < height)
					player2->MoveDown();

			if (ball->GetDirection() == STOP) 
				ball->RandomDirection();

			if (current == 'q') 
				quit = true;
		}
	}
	void Logic() {
		int ballx = ball->GetX();
		int bally = ball->GetY();
		int player1x = player1->GetX();
		int player1y = player1->GetY();
		int player2x = player2->GetX();
		int player2y = player2->GetY();

		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->ChangeDirection((Direction)((rand() % 3) + 4));
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->ChangeDirection((Direction)((rand() % 3) + 1));

		if (bally == height - 1)
			ball->ChangeDirection(ball->GetDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		if (bally == 0)
			ball->ChangeDirection(ball->GetDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		if (ballx == width - 1)
			ScoreUp(player1);
		if (ballx == 0)
			ScoreUp(player2);
	}
	void Run() {
		while (!quit) {
			Draw();
			Input();
			Logic();
		}
	}
};

int main()
{
	GameManager gm(40, 20);
	gm.Run();
}
