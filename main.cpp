#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <vector>

#define HEIGHT 25
#define WIDTH 25

using namespace std;

int score;

class Snake{
    private:
        COORD position;
        int length;
        int velocity;
        char direction;
        vector<COORD> snakeBody;

    public:
        Snake(COORD position, int velocity);
        void change_direction(char direction);
        void move_snake();
        COORD get_position();
        bool isEaten(COORD food_position);
        void increaseLength();
        bool isCollisionTrue();
        vector<COORD> get_snakeBody();
};

class Food{
    private:
        COORD position;
    public:
        Food();
        void generateFood();
        COORD get_position();
};

Snake::Snake(COORD position, int velocity){
    this-> position = position;
    this->velocity= velocity;
    length= 1;
    direction= 'n';

    snakeBody.push_back(position);
};

void Snake::change_direction(char newDirection){this->direction=newDirection;}

COORD Snake::get_position(){return position;}

vector <COORD> Snake:: get_snakeBody(){return snakeBody;}

void Snake::move_snake(){
    switch(direction)
    {
        case 'u': position.Y -= velocity; break;
        case 'd': position.Y += velocity; break;
        case 'l': position.X -= velocity; break;
        case 'r': position.X += velocity; break;
    }

    snakeBody.push_back(position);
    if (snakeBody.size()> length){
            snakeBody.erase(snakeBody.begin());
    }
}


void Snake::increaseLength(){
length++;
}

bool Snake:: isCollisionTrue(){
    if(position.X<1 || position.X> WIDTH-2 || position.Y <1 || position.Y> HEIGHT-2)return true;

    for (int i=0; i<length-2; i++){
        if (position.X== snakeBody[i].X && position.Y== snakeBody[i].Y) return true;
    }
    return false;
}

bool Snake::isEaten(COORD food_position){
    if (food_position.X==position.X && food_position.Y==position.Y) return true;
    return false;
}

Food::Food(){
    generateFood();
}

void Food::generateFood(){
    position.X= rand()% (WIDTH-3)+1;
    position.Y= rand()% (HEIGHT-3)+1;
}

COORD Food::get_position(){
return position;
}

Snake snake({WIDTH/2,HEIGHT/2},1);
Food food;

/*The following function was  obtained from a thread on stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c*/

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
/* This signals the end of the snippet of code that was borrowed.*/

void createBoard(){
    COORD snake_position= snake.get_position();
    COORD food_position= food.get_position();
    vector<COORD> fullSnakeBody= snake.get_snakeBody();

    cout<< "                Press any arrow key to begin:\n\n";
    for (int i =0; i < HEIGHT; i++){
        cout << "\t\tx ";
        for (int j= 0; j < WIDTH-2; j++){
            if (i== 0 || i== HEIGHT-1){
                cout<< "x ";
            }
            else if (i==snake_position.Y && j+1== snake_position.X) {
                cout<< "@ ";
            }
            else if (i==food_position.Y && j+1==food_position.X){
                cout << "* ";
            }
            else{
                bool isSnakeBody= false;
                for (int k=0; k <fullSnakeBody.size()-1; k++){
                    if (i== fullSnakeBody[k].Y && j+1==fullSnakeBody[k].X)
                    {
                        cout<< "O ";
                        isSnakeBody= true;
                        break;
                    }

                }
                if(!isSnakeBody){cout << "  ";}
            }
        }
    cout << "x\n";
    }
    cout<< "SCORE= "<< score << "\n\n";


}


int main(){
    score=0;
    hidecursor();
    srand(time(NULL));
    bool(gameOver)=false;


    while(!gameOver){
        createBoard();
        if(kbhit()){
            switch(getch())
            {
                case 72: snake.change_direction('u'); break;
                case 80: snake.change_direction('d');break;
                case 75: snake.change_direction('l');break;
                case 77: snake.change_direction('r');break;
            }
        }

        if (snake.isEaten(food.get_position())){
            food.generateFood();
            snake.increaseLength();
            score += 10;
        }

        if (snake.isCollisionTrue()) gameOver=true;

        snake.move_snake();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
    }
}
