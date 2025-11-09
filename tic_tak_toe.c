#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void start_game();
void single_player_mode(void);
void double_player_mode(void);

void print_table(char plases[]);
void read_move(char plases[], char player_name[], int turn);
void computer_move(char places[]);
int check_winner(char places[]);


int main()
{
    char c;
    printf("enter y to start the \"Tic Tac Toe\" Game : ");
    scanf("%c", &c);

    if (c == 'y')
        start_game();
    
    return 0;
}


void start_game()
{
// scaning inputs
    short mode;
    printf("\nSelect game mode : 1) 1 player Mode\n"
           "                   2) 2 player Mode\n: "
          );
    scanf("%hd", &mode);

    printf("Game in %hd player mode is being started . . . \n\n", mode);


//exicuting game accordingly    
    if(mode == 1)
    {
        single_player_mode();
    }
    else
    {
        double_player_mode();
    }


//asking for next game
    char a;
    printf("\nBut, whould you like to play again ? (enter 'y' to start the game once gain or 'n' for opposit) : ");
    scanf(" %c", &a);

    if(a == 'y')
    {
        start_game();
    }

    return;
}

void single_player_mode(void)
{
// scaning name of player
    char pl[30];
    printf("Enter your name : ");
    scanf(" %s", pl);

    printf("Please select the number of plase where you want to mark your move\n");

// loop for process of game
    char places[9] = "123456789";
    int winner = 0;
    for(int i = 0; i < 9; i++)
    {
        print_table(places);                    // To showcase the overview to choose right move
        
        if(i%2 == 0)                            // Alternates the turns between player and computer
        {
            read_move(places, pl, 0);
        }
        else
        {
            computer_move(places);
        }

        if ( i >= 4)                            // Startes checking winner from the five moves in totle
        {
            winner = check_winner(places);
        }

        if (winner == 1)                        // Declaring winner
        {
            if(i%2 == 0)
            {
                printf("\nSo you have become the winner of this game\n");
                break;
            }
            else
            {
                printf("\nSo computer has become the winner of this game\n");
                break;
            }
        }
    }

// in case of no one wins
    if (winner == 0)
    {
        printf("\nIt seems that this game has been tie");
    }
}

void double_player_mode(void)
{
// scaning names of players
    char pl[2][30]; 
    printf("Enter name of player 1 : ");
    scanf(" %s", pl[0]);
    printf("Enter name of player 2 : ");
    scanf(" %s", pl[1]);

    printf("Please select the number of plase where you want to mark your move\n");

// loop for process of game
    char places[9] = "123456789";
    int winner = 0;
    for(int i = 0; i < 9; i++)
    {
        print_table(places);                            // To showcase the overview to choose right move
        read_move(places, pl[i%2], i%2);                // Taking turns

        if ( i >= 4)                                    // Startes checking winner from the five moves in totle
        {
            winner = check_winner(places);
        }

        if (winner == 1)                                // Declaring winner
        {
            printf("\nSo %s has become the winner of this game\n", pl[i%2]);
            break;
        }
    }

// in case no one wins
    if (winner == 0)
    {
        printf("\nIt seems that this game has been tie");
    }

}


void print_table(char places[])
{
    printf
    (
        "\n       |       |       \n"
        "   %c   |   %c   |   %c   \n"
        "-----------------------\n"
        "       |       |       \n"
        "   %c   |   %c   |   %c   \n"
        "       |       |       \n"
        "-----------------------\n"
        "   %c   |   %c   |   %c   \n"
        "       |       |       \n",
        places[0], places[1], places[2],
        places[3], places[4], places[5],
        places[6], places[7], places[8]
    );
}

void read_move(char places[], char player_name[], int turn)
{
    char move;
    printf("%s's turn : ", player_name);
    scanf(" %c", &move);

// cases in which it is required to scan again
    if (move < '1' || move > '9')
    {
        printf("Invalid input !, you are suppose to provide answer in between 1 to 9\n");
        read_move(places, player_name, turn);
        return;
    }
    else if (move != places[move - '0' - 1])
    {
        printf("This place has alredy been taken! plese try another place\n");
        read_move(places, player_name, turn);
        return;
    }
    
// marking sign accorging to player
    if (turn)
    {
        places[move - '0' - 1] = 'X';
    }
    else
    {
        places[move - '0' - 1] = 'O';
    }

}

void computer_move(char places[])
{
// generating random valid move and printing it
    char move = (rand() % 9) + '1'; 
    while ((move < '1' || move > '9') || (places[move - '1'] != move))
    {
        move = (rand() % 9) + '1';
    }
    printf("Computer's turn : %c\n", move);


// marking move
    places[move - '0' - 1] = 'X';
}

int check_winner(char places[])
{
// all cases of winning
    if (
        (places[0] == places[1] && places[1] == places[2])
        ||
        (places[3] == places[4] && places[4] == places[5])
        ||
        (places[6] == places[7] && places[7] == places[8])
        ||
        (places[0] == places[3] && places[3] == places[6])
        ||
        (places[1] == places[4] && places[4] == places[7])
        ||
        (places[2] == places[5] && places[5] == places[8])
        ||
        (places[0] == places[4] && places[4] == places[8])
        ||
        (places[6] == places[4] && places[4] == places[2])
       )
    {
        return 1;
    }

    return 0;
}