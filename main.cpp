/* Playable terminal maze generator */

#include <iostream>
#include <ctime>
#include <algorithm>
#include <stack>
#define delete "\x1B[2J\x1B[H" // clear console
#define color "\033[107;107m" // white color and background
#define stop "\033[107;0m" // white color no background
using namespace std;


void draw(char maze[][30]) {
    cout << delete << endl << endl << color;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            if (maze[i][j] == 'w') {
                cout << color << maze[i][j] << maze[i][j]<< stop;
                // double output
            }
            else if (maze[i][j] == 'x') {
                cout << ":)";
            }
            else {
                cout << maze[i][j] << maze[i][j];
                // double output
            }
        }
        cout << endl;
    }
    cout << endl;
}

void add_room(int y_cord, int x_cord, int height, int width, char maze[][30]) {
    for (int i = y_cord; i < (y_cord + height); i++) {
        for (int j = x_cord; j < (x_cord + width); j++) {
            maze[i][j] = ' ';
        }
    }
}

void add_entrance(int y_cord, int x_cord, int height, int width, char maze[][30]) {
    bool done = false;
    int checkY, checkX, choice;
    while (!done) {
        checkY = rand() % height;
        checkX = rand() % width;
        choice = rand() % 4;
        checkY += y_cord;
        checkX += x_cord;
        if (maze[checkY][x_cord - 2] == ' ' && choice == 0) {
            maze[checkY][x_cord - 1] = ' ';
            done = true;
        }
        if (maze[checkY][x_cord + width + 1] == ' ' && done == false && (x_cord + width + 1 < 29) && choice == 1) {
            maze[checkY][x_cord + width] = ' ';
            done = true;
        }
        if (maze[y_cord - 2][checkX] == ' ' && done == false && choice == 2) {
            maze[y_cord - 1][checkX] = ' ';
            done = true;
        }
        if (maze[y_cord + height + 1][checkX] == ' ' && done == false  && (y_cord + height + 1 < 29) && choice == 3) {
            maze[y_cord + height][checkX] = ' ';
            done = true;
        }
    }
}

int main()
{
    char maze[30][30];
    fill(*maze, *maze + 30 * 30, 'w');
    bool done = false;
    bool up = false, down = false, left = false, right = false;
    stack<int> stack;
    int choice, count = 0, count2 = 0, count3 = 0;
    
    srand(time(0));
    
    int mole_row = (rand() % 11) + 9;
    int mole_col = (rand() % 11) + 9;
    
    
    // add_rooms that have no entrances, call add_entrance after maze is generated
    add_room(1, 25, 4, 4, maze);
    //add_room(20, 1, 9, 9, maze);
    
    maze[mole_row][mole_col] = 'X';
    
    do {
        do {
            up = false;
            down = false;
            left = false;
            right = false;
            done = false;
            count3 = 0;
            
            // up
            /* check for this this:
            w w w
            w w w
              X       */
            if ((maze[mole_row - 1][mole_col] == 'w')
                && (maze[mole_row - 2][mole_col] == 'w') 
                && (maze[mole_row - 2][mole_col - 1] == 'w') 
                && (maze[mole_row - 2][mole_col + 1] == 'w') 
                && (maze[mole_row - 1][mole_col + 1] == 'w') 
                && (maze[mole_row - 1][mole_col - 1] == 'w')
                && (mole_row > 1)) 
                {
                    up = true;
                    count3++;
            }
            
            // down
            /* check for this this:
              X
            w w w 
            w w w     */
            if ((maze[mole_row + 1][mole_col] == 'w')
                && (maze[mole_row + 2][mole_col] == 'w') 
                && (maze[mole_row + 2][mole_col - 1] == 'w') 
                && (maze[mole_row + 2][mole_col + 1] == 'w') 
                && (maze[mole_row + 1][mole_col + 1] == 'w') 
                && (maze[mole_row + 1][mole_col - 1] == 'w')
                && (mole_row < 28))
                {
                    down = true;
                    count3++;
            }
            
            // left
            /* check for this this:
            w w 
            w w X
            w w       */
            if ((maze[mole_row][mole_col - 1] == 'w')
                && (maze[mole_row][mole_col - 2] == 'w')
                && (maze[mole_row - 1][mole_col - 2] == 'w')
                && (maze[mole_row + 1][mole_col - 2] == 'w')
                && (maze[mole_row - 1][mole_col - 1] == 'w')
                && (maze[mole_row + 1][mole_col - 1] == 'w')
                && (mole_col > 1)) 
                {
                    left = true;
                    count3++;
            }
            
            // right
            /* check for this this:
              w w 
            X w w 
              w w     */
            if ((maze[mole_row][mole_col + 1] == 'w')
                && (maze[mole_row][mole_col + 2] == 'w')
                && (maze[mole_row - 1][mole_col + 2] == 'w')
                && (maze[mole_row + 1][mole_col + 2] == 'w')
                && (maze[mole_row - 1][mole_col + 1] == 'w')
                && (maze[mole_row + 1][mole_col + 1] == 'w')
                && (mole_col < 28)) 
                {
                    right = true;
                    count3++;
            }
            
            if (count3 >= 2) {
                stack.push(mole_row);
                stack.push(mole_col);
            }
            
            do {
                choice = rand() % 10;
                done = false;
                
                switch (choice) {
                    case 0:
                        if (up) {    
                            maze[mole_row][mole_col] = ' ';
                            mole_row--;
                            done = true;
                        }
                        break;
                    case 1:
                        if (down) {
                            maze[mole_row][mole_col] = ' ';
                            mole_row++;
                            done = true;
                        }
                        break;
                    case 2:
                    case 4:
                    case 5:
                    case 6:
                        if (left) {
                            maze[mole_row][mole_col] = ' ';
                            mole_col--;
                            done = true;
                        }
                        break;
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                        if (right) {    
                            maze[mole_row][mole_col] = ' ';
                            mole_col++;
                            done = true;
                        }
                        break;
                }
                
                if (!up && !down && !left && !right) {
                    done = true;
                }
                
                count2++;
                
            } while (!done);
            
            maze[mole_row][mole_col] = ' ';
            
            count++;
            
        } while (up || down || left || right);
        
        mole_col = stack.top();
        stack.pop();
        mole_row = stack.top();
        stack.pop();
        
    } while (stack.size() != 0);
    
    
    // add_rooms that overlay maze and add_entrances here
    //add_entrance(20, 1, 9, 9, maze);
    add_entrance(1, 25, 4, 4, maze);
    
    int j = 1;
    while (maze[1][j] != ' ') {
        j++;
    }
    maze[0][j] = 'x';
    
    int i = 28;
    while (maze[28][i] != ' ') {
        i--;
    }
    maze[29][i] = ' ';
    
    draw(maze);
    
    char move;
    int y_cord = 0, x_cord = j;
    
    while (y_cord != 29) {
        done = false;
        cin >> move;
        
        if (move == 'W' && y_cord >= 0) {
            if (maze[y_cord - 1][x_cord] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                y_cord--;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 'w' && y_cord >= 0) {
            while (maze[y_cord - 1][x_cord] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                y_cord--;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 'S' && y_cord <= 29) {
            if (maze[y_cord + 1][x_cord] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                y_cord++;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 's' && y_cord <= 29) {
            while (maze[y_cord + 1][x_cord] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                y_cord++;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 'A' && x_cord >= 0) {
            if (maze[y_cord][x_cord - 1] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                x_cord--;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 'a' && x_cord >= 0) {
            while (maze[y_cord][x_cord - 1] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                x_cord--;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 'D' && x_cord <= 29) {
            if (maze[y_cord][x_cord + 1] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                x_cord++;
                maze[y_cord][x_cord] = 'x';
            }
        }
        if (move == 'd' && x_cord <= 29) {
            while (maze[y_cord][x_cord + 1] == ' ') {
                done = true;
                maze[y_cord][x_cord] = ' ';
                x_cord++;
                maze[y_cord][x_cord] = 'x';
            }
        }
        
        draw(maze);
    }
    
    cout << "You Win!";
    
    return 0;
}










