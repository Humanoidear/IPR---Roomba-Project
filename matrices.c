#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SIZE 12

void printMatrix(int matrix[SIZE][SIZE], double previousPositions[100], int totalCleanDecison[50])
{
    for (int i = 0; i < pow(SIZE, 2) + 1; i++)
    {

        if (i % SIZE == 0 && i != 0)
        {
            for (int g = 0; g < 5; g++)
            {   
                char str[50];
                sprintf(str, "%.2lf", previousPositions[((i / SIZE) - 1) * 5 + (g)]);
                int a = atoi(strtok(str, "."));
                int b = atoi(strtok(NULL, "."));
                printf(" | \033[0;33m%02i\033[0;37m - x:%02i y:%02i/ %i", ((i / SIZE) - 1) * 5 + (g), a, b, totalCleanDecison[((i / SIZE) - 1) * 5 + (g)]);
            }
            printf("\n");
        }
        else if (i % SIZE == 0)
        {
            printf(" | \033[0;34mPrevious positions:\033[0;37m \n");
        }

        if (matrix[i / SIZE][i % SIZE] == -1)
        {
            printf("\033[0;33m🟧\033[0;37m");
        }
        else if (matrix[i / SIZE][i % SIZE] == 6)
        {
            printf("\033[0;34m🤖\033[0;37m");
        }
        else if (matrix[i / SIZE][i % SIZE] > 0)
        {
            switch (matrix[i / SIZE][i % SIZE])
            {
            case 1:
                printf("1️⃣ ");
                break;
            case 2:
                printf("2️⃣ ");
                break;
            case 3:
                printf("3️⃣ ");
                break;
            case 4:
                printf("4️⃣ ");
                break;
            }
        }
        else
        {
            printf("  ");
        }
    }
    printf("\n©2023 - The cum messiahs \n");
}

void moveEntity(int (*matrix)[SIZE][SIZE], int (*currentPos)[2], char direction, int *nextPos, int *cleanDecision)
{
    system("clear");

    switch (direction)
    {
    case 'S':
        if ((*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]] == -1)
        {
            printf("⚠️ You can't go there, there is a wall. \n");
        }
        else
        {
            (*matrix)[(*currentPos)[0]][(*currentPos)[1]] = *nextPos;
            if ((*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]] > 0)
            {
                *nextPos = (*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]];
                *cleanDecision = (*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]];
            }
            else
            {
                *nextPos = 0;
            }
            (*matrix)[(*currentPos)[0] + 1][(*currentPos)[1]] = 6;
            (*currentPos)[0] = (*currentPos)[0] + 1;
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
    case 'C':
        if (*nextPos > 0)
        {
            *nextPos = *nextPos - 1;
            *cleanDecision = *nextPos;
        }
    }
}

int main(int argc, char *argv[])
{
    int matrix[SIZE][SIZE];
    int currentPos[2] = {1, 1};
    int isClean = 0;
    int nextPos = 0;
    int prevSize = 0;
    double previousPositions[100];
    char tempString[50];
    int cleanDecision;
    int totalCleanDecison[100];
    srand(time(NULL));

    system("clear");

    for (int i = 0; i < pow(SIZE, 2); i++)
    {
        if (i / SIZE >= 1 && i / SIZE <= SIZE - 2 && i % SIZE >= 1 && i % SIZE <= SIZE - 2)
        {
            matrix[i / SIZE][i % SIZE] = rand() % 5;
            if (matrix[i / SIZE][i % SIZE] == 2 || matrix[i / SIZE][i % SIZE] == 4)
            {
                matrix[i / SIZE][i % SIZE] = 0;
            }
        }
        else
        {
            matrix[i / SIZE][i % SIZE] = -1;
        }
        matrix[currentPos[0]][currentPos[1]] = 6;
        matrix[3][3] = -1;
    }

    for (int i = 0; i < 100; i++)
    {
        previousPositions[i] = 0.0;
        totalCleanDecison[i] = 0;
    }

    do
    {
        char direction;

        printf("Matrix generated: \n");
        for (int i = 0; i < SIZE * 2; i++)
        {
            printf("=");
        }

        printMatrix(matrix, previousPositions, totalCleanDecison);

        cleanDecision = 0;

        printf("\nRoomba - Where do you want to go? (WASD - C to clean) | \033[33mTIP:\033[0m Inputs can be buffered \n");
        scanf(" %c", &direction); // Note the space before %c to consume any trailing newline
        moveEntity(&matrix, &currentPos, direction, &nextPos, &cleanDecision);

        // Update previousPositions after moving the entity
        sprintf(tempString, "%i.%i", currentPos[1], currentPos[0]);
        if (prevSize <= 100)
        {
            previousPositions[prevSize] = atof(tempString);
            totalCleanDecison[prevSize] = cleanDecision;
            prevSize++;
        }

        printf("\033[34mRoomba data:\033[0m x:%02d y:%02d - \033[34mCurrently on top of trash:\033[0m %c - \033[34mTrash-o-meter:\033[0m %i\n\n", currentPos[1], currentPos[0], nextPos > 0 ? 'Y' : 'N', cleanDecision);
    } while (isClean == 0);

    return 0;
}