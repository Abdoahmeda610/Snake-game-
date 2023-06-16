
#include <conio.h>
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#else
#define ClearScreen() std::cout << "\033[2J\033[1;1H"
#endif
// colors 👇👇
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"


using namespace std;
bool gameover;
const int width = 20;
const int height = 17;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //snake coordinates
int nTail;
enum eDirecton {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls
eDirecton dir;
void Setup() {
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; //display fruit in a random place
    fruitY = rand() % height;
    score = 0;
}
void Draw() {
    system("cls");
    for(int i = 0; i < width+2; i++)
        cout<<BLUE << "#"<<RESET;
    cout << endl ;
    for (int i = 0; i < height ; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout<<BLUE <<"#"<<RESET; //walls
            if (i == y && j == x)
                cout<<YELLOW<< "*"<<RESET; // snake tale
            else if (i == fruitY && j == fruitX )
                cout<<MAGENTA << "%"<<RESET; // change it to change the fruit
            else {
                bool print = false;
                for (int k = 0; k< nTail ; k++) {
                    if (tailX [k] == j && tailY [k] == i) {
                        cout<<GREEN<< "*"<<RESET;
                        print = true;
                    }
                }
                if (!print) cout <<" ";
            }
            if (j == width -1)
                cout<<BLUE << "#"<<RESET;
        }
        cout << endl;
    }
    for (int i = 0; i< width+2; i++)
        cout<<BLUE << "#"<<RESET;
    cout << endl;
    cout<<GREEN << "Score:" << score << endl ;
}
void Input ()
{
    if (_kbhit ()) {
        switch (_getch ()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN ;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}
void algorithm()
{
    int prevX = tailX [0];
    int prevY = tailY [0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail ; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y ;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x =0;
    else if (x <0) x = width -1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;
    for (int i =0; i< nTail ; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
    if (x == fruitX && y == fruitY) {
        score +=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail ++;
    }
}
int main()
{
    Setup();
    while (!gameover) {
        Draw ();
        Input ();
        algorithm ();
  ClearScreen();  
   std::this_thread::sleep_for(std::chrono::milliseconds(120));
  
    }
    return 0;
}



