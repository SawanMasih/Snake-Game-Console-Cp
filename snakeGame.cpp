
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <string>
#include <conio.h>

using namespace std;

bool gameover;

const int wi = 60;
const int hi = 30;

char s[30][60];
int fX, fY;
int score;
int x, y;
int nTail;
int a[100];
int b[100];
string name;
enum eDirection { S = 0, L, R, U, D };
eDirection dir;

int attempts = 0;

void Setup()
{
    gameover = false;
    dir = S;
    fX = rand() % wi;
    fY = rand() % hi;
    x = 20;
    y = 20;
    score = 0;
    nTail = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < hi; i++) {
        for (int j = 0; j < wi; j++) {
            if (i == 0 || i == hi - 1 || j == 0 || j == wi - 1) {
                s[i][j] = '#';
            }
            else if (i == y && j == x) {
                s[i][j] = 'o';
            }
            else if (i == fY && j == fX) {
                s[i][j] = '.';
            }
            else {
                bool print = false;

                for (int k = 0; k < nTail; k++) {
                    if (a[k] == j && b[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }

                if (!print) {
                    s[i][j] = ' ';
                }
            }
        }
    }
    for (int i = 0; i < hi; i++) {
        for (int j = 0; j < wi; j++) {
            cout << s[i][j];
        }
        cout << endl;
    }
    cout << "Score " << score << endl;
}

void Input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = L;
            break;
        case 'd':
            dir = R;
            break;
        case 'w':
            dir = U;
            break;
        case 'z':
            dir = D;
            break;
        default:
            break;
        }
    }
}

void logic()
{
    int pX = a[0];
    int pY = b[0];
    int p2X, p2Y;
    a[0] = x;
    b[0] = y;

    for (int i = 1; i < nTail; i++) {
        p2X = a[i];
        p2Y = b[i];
        a[i] = pX;
        b[i] = pY;
        pX = p2X;
        pY = p2Y;
    }

    switch (dir) {
    case L:
        x--;
        break;
    case R:
        x++;
        break;
    case U:
        y--;
        break;
    case D:
        y++;
        break;
    default:
        break;
    }

    if (x >= wi || x < 0 || y >= hi || y < 0) {
        gameover = true;
        cout << "Game over" << endl;
    }

    for (int i = 0; i < nTail; i++) {
        if (a[i] == x && b[i] == y) {
            gameover = true;
            cout << "Game over" << endl;
        }
    }

    if (x == fX && y == fY) {
        srand(time(0));
        score = score + 1;
        fX = rand() % wi;
        fY = rand() % hi;
        nTail++;
    }
}

int main()
{
    cout << "----------WELLCOME TO SNAKE GAME----------";
    cout << "   ";
    cout << "Enter your name: ";
    getline(cin, name);

    while (attempts < 3) {
        Setup();

        while (!gameover) {
            Draw();
            Input();
            logic();
            Sleep(10);
        }

        cout << "Attempt " << attempts + 1 << ": " << name << "'s Score - " << score << endl;
        attempts++;

        if (attempts < 3) {
            char response;
            cout << "Do you want to play again? (y/n): ";
            cin >> response;

            if (response != 'y' && response != 'Y') {
                break;
            }
        }
    }

    cout << "Thank you for playing!" << endl;
    system("pause");
    return 0;
}
