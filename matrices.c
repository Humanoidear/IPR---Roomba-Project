#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SIZE 12

void printMatrix(int matrix[SIZE][SIZE], double previousPositions[100], int totalCleanDecison[50])
{
    for (int i = 0; i < pow(SIZE, 2) + 1; i++) // repeat until all of the matrix is printed
    {

        if (i % SIZE == 0 && i != 0)
        {
            for (int g = 0; g < 5; g++) // draw the previous positions
            {   
                char str[50];
                sprintf(str, "%.2lf", previousPositions[((i / SIZE) - 1) * 5 + (g)]);
                int a = atoi(strtok(str, "."));
                int b = atoi(strtok(NULL, "."));
                printf(" | \033[0;33m%02i\033[0;37m - x:%02i y:%02i/ %i", ((i / SIZE) - 1) * 5 + (g), a, b, totalCleanDecison[((i / SIZE) - 1) * 5 + (g)]);
            }
            printf("\n");
        }
        else if (i % SIZE == 0) // if it's the first line of the matrix, show title
        {
            printf(" | \033[0;34mPrevious positions:\033[0;37m \n");
        }

        if (matrix[i / SIZE][i % SIZE] == -1) // if the current position is a wall, print a wall
        {
            printf("\033[0;33m🟧\033[0;37m");
        }
        else if (matrix[i / SIZE][i % SIZE] == 6) // if the current position is the roomba, print the roomba
        {
            printf("\033[0;34m🤖\033[0;37m");
        }
        else if (matrix[i / SIZE][i % SIZE] > 0) // if the current position is trash, print the trash
        {
            switch (matrix[i / SIZE][i % SIZE])
            {
            case 1: // 1 trash
                printf("1️⃣ ");
                break;
            case 2: // 2 trash
                printf("2️⃣ ");
                break;
            case 3: // 3 trash
                printf("3️⃣ ");
                break;
            case 4: // 4 trash
                printf("4️⃣ ");
                break;
            }
        }
        else
        {
            printf("  ");
        }
    }
    printf("\n©2023 - The cum messiahs \n"); // print credits
}

void moveEntity(int (*matrix)[SIZE][SIZE], int (*currentPos)[2], char direction, int *nextPos, int *cleanDecision)
{
    system("clear");

    switch (direction)
    {
    case 'S': // moving downwards
        if ((*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]] == -1) // check if the next position is a wall
        {
            printf("⚠️ You can't go there, there is a wall. \n"); // if it is, print a warning
        }
        else // begin moving the roomba
        {
            (*matrix)[(*currentPos)[0]][(*currentPos)[1]] = *nextPos;
            if ((*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]] > 0) // there is trash on the next position
            {
                *nextPos = (*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]]; // store it in the temporary nextPos variable
                *cleanDecision = (*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]]; // store it in the cleanDecision variable
            }
            else
            {
                *nextPos = 0; // there is no trash, set nextPos to 0 to prevent previous data from corrupting the current
            }
            (*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]] = 6; // set the roomba to the next position
            (*currentPos)[0] = (*currentPos)[0] + 1; // update the coordinates of the roomba
        }
        break;
    case 'W':
        if ((*matrix)[(*currentPos)[0] - 1][(*currentPos)[1]] == -1)
        {
            printf("⚠️ You can't go there, there is a wall. \n");
        }
        else
        {
            (*matrix)[(*currentPos)[0]][(*currentPos)[1]] = *nextPos;
            if ((*matrix)[(*currentPos)[0] - 1][(*currentPos)[1]] > 0)
            {
                *nextPos = (*matrix)[(*currentPos)[0] - 1][(*currentPos)[1]];
                *cleanDecision = (*matrix)[(*currentPos)[0] - 1][(*currentPos)[1]];
            }
            else
            {
                *nextPos = 0;
            }
            (*matrix)[(*currentPos)[0] - 1][(*currentPos)[1]] = 6;
            (*currentPos)[0] = (*currentPos)[0] - 1;
        }
        break;
    case 'D':
        if ((*matrix)[(*currentPos)[0]][(*currentPos)[1] + 1] == -1)
        {
            printf("⚠️ You can't go there, there is a wall. \n");
        }
        else
        {
            (*matrix)[(*currentPos)[0]][(*currentPos)[1]] = *nextPos;
            if ((*matrix)[(*currentPos)[0]][(*currentPos)[1] + 1] > 0)
            {
                *nextPos = (*matrix)[(*currentPos)[0]][(*currentPos)[1] + 1];
                *cleanDecision = (*matrix)[(*currentPos)[0]][(*currentPos)[1] + 1];
            }
            else
            {
                *nextPos = 0;
            }
            (*matrix)[(*currentPos)[0]][(*currentPos)[1] + 1] = 6;
            (*currentPos)[1] = (*currentPos)[1] + 1;
        }
        break;
    case 'A':
        if ((*matrix)[(*currentPos)[0]][(*currentPos)[1] - 1] == -1)
        {
            printf("⚠️ You can't go there, there is a wall. \n");
        }
        else
        {
            (*matrix)[(*currentPos)[0]][(*currentPos)[1]] = *nextPos;
            if ((*matrix)[(*currentPos)[0]][(*currentPos)[1] - 1] > 0)
            {
                *nextPos = (*matrix)[(*currentPos)[0]][(*currentPos)[1] - 1];
                *cleanDecision = (*matrix)[(*currentPos)[0]][(*currentPos)[1] - 1];
            }
            else
            {
                *nextPos = 0;
            }
            (*matrix)[(*currentPos)[0]][(*currentPos)[1] - 1] = 6;
            (*currentPos)[1] = (*currentPos)[1] - 1;
        }
        break;
    case 'C': // clean the tile
        if (*nextPos > 0) // check if there's something to clean
        {
            *nextPos = *nextPos - 1; // there is, substract 1
            *cleanDecision = *nextPos; // update the cleanDecision variable with the current data
        }
    }
}


// main function
int main(int argc, char *argv[])
{
    //generate initial variables
    int matrix[SIZE][SIZE];
    int currentPos[2] = {1, 1}; //current position of the roomba
    int isClean = 0; // check whether the roomba has cleaned all the trash
    int nextPos = 0; // store amount of trash on current square occupied by roomba
    int prevSize = 0;
    double previousPositions[100]; // array to store 100 previous positions of the roomba
    char tempString[50]; // temporary string to store previous positions
    int cleanDecision;
    int totalCleanDecison[100]; // array to store 100 clean decisions
    srand(time(NULL)); // initialize random seed

    system("clear"); // clear the terminal

    for (int i = 0; i < pow(SIZE, 2); i++) // generate the matrix randomly
    {
        if (i / SIZE >= 1 && i / SIZE <= SIZE - 2 && i % SIZE >= 1 && i % SIZE <= SIZE - 2)
        {
            matrix[i / SIZE][i % SIZE] = rand() % 5;
            if (matrix[i / SIZE][i % SIZE] == 2 || matrix[i / SIZE][i % SIZE] == 4) // if rrandom number is 2 or 4, set it to 0 (no trash)
            {
                matrix[i / SIZE][i % SIZE] = 0;
            }
        }
        else
        {
            matrix[i / SIZE][i % SIZE] = -1; // else, set a wall
        }
        matrix[currentPos[0]][currentPos[1]] = 6; //place the player on the matrix
        matrix[3][3] = -1; // place a wall on (3,3)
    }

    for (int i = 0; i < 100; i++) // clear garbage data on the array
    {
        previousPositions[i] = 0.0;
        totalCleanDecison[i] = 0;
    }

    do // repeat until the roomba has cleaned all the trash (not yet implemented)
    {
        char direction;

        printf("Matrix generated: \n");
        for (int i = 0; i < SIZE * 2; i++) // draw divider
        {
            printf("=");
        }

        printMatrix(matrix, previousPositions, totalCleanDecison); // print the matrix

        cleanDecision = 0;

        printf("\nRoomba - Where do you want to go? (WASD - C to clean) | \033[33mTIP:\033[0m Inputs can be buffered \n");
        scanf(" %c", &direction); // check for the position or clean command
        moveEntity(&matrix, &currentPos, direction, &nextPos, &cleanDecision); // move the roomba and update the matrix

        // Hacky code to store the positions on 1 array position
        sprintf(tempString, "%i.%i", currentPos[1], currentPos[0]); // copy both positions to a string
        if (prevSize <= 100) // prevent array overflow
        {
            previousPositions[prevSize] = atof(tempString); // convert string to double and store it on the array
            totalCleanDecison[prevSize] = cleanDecision;
            prevSize++;
        }

        printf("\033[34mRoomba data:\033[0m x:%02d y:%02d - \033[34mCurrently on top of trash:\033[0m %c - \033[34mTrash-o-meter:\033[0m %i\n\n", currentPos[1], currentPos[0], nextPos > 0 ? 'Y' : 'N', cleanDecision); // show data about the roomba
    } while (isClean == 0);

    return 0;
}