#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameover;
const int height = 20;
const int width = 20;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void draw()
{
    system("CLS");
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                cout << "#";
            }
            else if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruity && j == fruitx)
            {
                cout << "F";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // snake tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout<<endl;
    cout << "Score:" << score << endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;

        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default :
            break;
        
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }
    // The snake can go thruogh the walls 
    if (x > width)
    {
        x = 0;
    }   
    else if (x < 0)
    {
        x = width - 1;
    }
    if (y > height)
    {
        y = 0;
    }
    else if (y < 0)
    {
        y = height - 1;
    }
    // snake cannot go through walls
    /*if (x >= width || x < 0 || y >= height || y < 0)
    {
        gameover = true;
    }*/
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameover = true;
        }
    }
        

    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;
    }
}

int main()
{
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep(100); // Adjust the sleep time to control the game speed
    }
    return 0;
}
