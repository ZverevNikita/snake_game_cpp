#include <iostream> 
#include <conio.h> 
#include <windows.h> 
#include <locale.h> 

using namespace std;

bool game_over;
const int width = 21;
const int height = 21;
int x, y, food_x, food_y, score;
int snake_body_x[100], snake_body_y[100];
int snake_length;
int speed = 200;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection direction;

void EndGameMessage()
{
    cout << "Игра окончена! Ваш счёт: " << score << endl;
}

void Setup()
{
    game_over = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;
    food_x = rand() % width;
    food_y = rand() % height;
    score = 0;
    snake_length = 1;
    snake_body_x[0] = x;
    snake_body_y[0] = y;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "*";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "*";
            if (i == y && j == x)
                cout << "0";
            else if (i == food_y && j == food_x)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < snake_length; k++)
                {
                    if (snake_body_x[k] == j && snake_body_y[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "*";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "*";
    cout << endl;
    cout << "Текущий счёт: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'x':
            game_over = true;
            break;
        }
    }
}

void Logic()
{
    int x_change = snake_body_x[0];
    int y_change = snake_body_y[0];
    int x1, y1;
    snake_body_x[0] = x;
    snake_body_y[0] = y;
    for (int i = 1; i < snake_length; i++)
    {
        x1 = snake_body_x[i];
        y1 = snake_body_y[i];
        snake_body_x[i] = x_change;
        snake_body_y[i] = y_change;
        x_change = x1;
        y_change = y1;
    }
    switch (direction)
    {
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
    if (x >= width) game_over = true; else if (x < 0) game_over = true;
    if (y >= height) game_over = true; else if (y < 0) game_over = true;
    for (int i = 1; i < snake_length; i++)
        if (snake_body_x[i] == x && snake_body_y[i] == y)
            game_over = true;
    if (x == food_x && y == food_y)
    {
        score += 1;
        food_x = rand() % width;
        food_y = rand() % height;
        snake_length++;
        speed -= 10;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Setup();
    while (!game_over)
    {
        Draw();
        Input();
        Logic();
        Sleep(speed);
    }
    EndGameMessage();
}