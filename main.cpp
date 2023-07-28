#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 25

using namespace std;

enum terrain
{
    STONE,
    DIRT,
    TREE
};

terrain terrain_list[SIZE][SIZE];

class Player
{
public:
    int map_y = 0;
    int map_x = 0;
    int y = 0;
    int x = 0;
    void interact(string input);
};

void generator()
{
    int type_int = 0;
    srand (time(NULL));
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            type_int = rand() % 3+0;
            terrain_list[i][j] = (terrain)type_int;
        }
    }
}

void save(bool with_player, Player* player)
{
    if (with_player)
    {
        FILE *file;
        char player_path[11];
        sprintf(player_path, "player.txt");
        file = fopen(player_path, "w");
        char to_write[9];
        sprintf(to_write, "%d\n%d\n%d\n%d\n", player->map_y, player->map_x, player->y, player->x);
        fwrite(to_write, sizeof(to_write), 1, file);
        fclose(file);
    }
    char filename[10];
    sprintf(filename, "%4d-%4d", player->map_x, player->map_y);
    FILE *chunk = fopen(filename, "w");
    fwrite(terrain_list, sizeof(terrain_list), 1, chunk);
    fclose(chunk);
}
void load(bool with_player, Player* player)
{
    if (with_player)
    {
        FILE *file;
        char player_path[11];
        sprintf(player_path, "player.txt");
        if ((file = fopen(player_path, "r")))
        {
            fscanf(file, "%d%d%d%d", &player->map_y, &player->map_x, &player->y, &player->x);
        }
        else 
        {
            file = fopen(player_path, "w");
        }
        fclose(file);
    }
    char filename[10];
    sprintf(filename, "%4d-%4d", player->map_x, player->map_y);
    FILE* chunk;
    if ((chunk = fopen(filename, "r")))
    {
        chunk = fopen(filename, "r");
        fread(terrain_list, sizeof(terrain_list), 1, chunk);
        fclose(chunk);
    }
    else
    {
        generator();
    }
}
void Player::interact(string input)
{
    if (input == "w")
    {
        if (y < SIZE) y++;
        else {y=0; save(false, this); map_y++; load(false,this);}
    }
    if (input == "s")
    {
        if (y < 0) y--;
        else {y=SIZE; save(false, this); ;map_y--;load(false,this);}
    }
    if (input == "d")
    {
        if (x < SIZE) x++;
        else {x=0; save(false, this); map_x++;load(false,this);}
    }
    if (input == "a")
    {
        if (x > 0) x--;
        else {x=SIZE; save(false, this); map_x--;load(false,this);}
    }
    if (input == "save")
    {
        save(true, this);
    }    
    if (input == "load")
    {
        load(true, this);
    }
    // SHOULD BE MOVED INTO DIFFRENT FUNCTION
    for (int i=0; i<100; i++)
    {
        cout << endl;
    }
    // SHOULD USE ENUM (or something)
    if (input == "e")
    {
        string name_of_terrain;
        switch (terrain_list[x][y])
        {
            case STONE:
                name_of_terrain = "stone";
                break;
            case DIRT:
                name_of_terrain = "dirt";
                break;
            case TREE:
                name_of_terrain = "tree";
                break;
        }
        cout << name_of_terrain << endl;
    }   
    cout << "x: " << x << " y: " << y << " map_x: " << map_x << " map_y: " << map_y << endl;
}

int main()
{
    Player player;
    load(true, &player);
    string input;
    cout << "DON'T USE ctrl-d IT WILL BREAK EVERYTHING\n";
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
