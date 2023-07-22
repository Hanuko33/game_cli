#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int terrain_list[25][5];

class Player
{
public:
    int y = 0;
    int x = 0;
    void interact(string input);
}; 

// W.I.P ADD SAFETY!
void Player::interact(string input)
{
    if (input == "w")
    {
        y++;
    }

    // change this to use "if" statement
    /*
    switch (input)
    {
        case "s":
            y+=25;
            break;
        case "a":
            x-=25;
            break;
        case "d":
            x+=25;
            break;
        case "w":
            y-=25; 
            break;
        break;
    }
    */
    // SHOULD BE MOVED INTO DIFFRENT FUNCTION
    for (int i=0; i<100; i++)
    {
        cout << endl;
    }
    if (input == "e")
    {
        string name_of_terrain;
        switch (terrain_list[x][y])
        {
            case 0:
                name_of_terrain = "stone";
                break;
            case 1:
                name_of_terrain = "dirt";
                break;
            case 2:
                name_of_terrain = "tree";
                break;
        }
        cout << terrain_list[x][y] << name_of_terrain << endl;
    }   
    cout << "x: " << x << " y: " << y << endl;
}

void generator()
{
    int type_int = 0;
    srand (time(NULL));
    for (int i=0; i<25; i++)
    {
        for (int j=0; j<5; j++)
        {
            type_int = rand() % 3+0;
            terrain_list[i][j] = type_int;
        }
    }
}
int main()
{
    Player player;
    player.x = 0;
    player.y = 0;
    generator();
    string input;
    for (;;)
    {   
        cout << "Player cli > ";
        cin >> input;
        if (input == "exit")
        {
            return 0;
        }
        player.interact(input);      
    }
}
