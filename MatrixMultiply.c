#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double inputValidation(int);
void matrixMulti(int *);

int main()
{
    int size[4], n, i = 0;

    for (i = 0; i < 4;)
    {
        if (i == 0)
        {
            printf("Enter size of 1st matrix:- ");
        }
        else if (i == 2)
        {
            printf("Enter size of 2nd matrix:- ");
        }
        size[i] = (int)inputValidation(1);
        i++;
    }

    if (size[1] != size[2])
    {
        printf("Multiply of these matrices is not possible\n");
        exit(0);
    }

    matrixMulti(size); // this function will store two matrices and also print the resultant matrix

    return 0;
}

void matrixMulti(int *size)
{
    // below declaration will throw error in turbo C
    float mat1[size[0]][size[1]], mat2[size[2]][size[3]], resultMat[size[0]][size[3]], sum = 0; // these are the matrices
    int j, i, k, count = 1;                                                                     // j, i and k are loop variables

    // below nested loops are used to store the elements of both the matrices
    for (k = 0; k <= 2;)
    {
        printf("\nEnter elements of %d matrix:- \n\n", count);
        for (j = 0; j < size[k]; j++)
        {
            for (i = 0; i < size[k + 1]; i++)
            {
                printf("Enter %d %d element:- ", j, i);
                if (k == 0)
                {
                    mat1[j][i] = inputValidation(0);
                }
                else
                {
                    mat2[j][i] = inputValidation(0);
                }
            }
        }
        count++;
        k += 2;
    }

    count = 1;
    printf("\nprinting elements\n\n");

    // below nested loops are used to print the elements of both the matrices
    for (k = 0; k <= 2;)
    {
        printf("printing elements of %d matrix:- \n", count);
        for (j = 0; j < size[0]; j++)
        {
            for (i = 0; i < size[k + 1]; i++)
            {
                if (k == 0)
                {
                    printf("%.2f\t", mat1[j][i]);
                }
                else
                {
                    printf("%.2f\t", mat2[j][i]);
                }
            }
            printf("\n");
        }
        printf("\n");
        count++;
        k += 2;
    }

    printf("Resultant Matrix\n");
    // calculation and printing of resultant matrix
    for (j = 0; j < size[0]; j++)
    {
        for (i = 0; i < size[3]; i++)
        {
            for (k = 0; k < size[1]; k++)
            {
                sum += mat1[j][k] * mat2[k][i];
            }
            resultMat[j][i] = sum;
            sum = 0;
            printf("%.2f\t", resultMat[j][i]);
        }
        printf("\n");
    }
}

// validating the user input, whether its size of matrix or an element
double inputValidation(int type)
{
    char input[30];
    double result_double;
    long long result_long;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; // removing the trailing spaces
            char *endptr;

            if (type == 0)
            {
                result_double = strtod(input, &endptr);
            }
            else
            {
                if(input[0] == "-")
                {
                    printf("size of matrix can't be negative\n");
                    fflush(stdin);
                }
                else
                {
                    result_long = strtoll(input, &endptr, 10);
                }
            }

            if (*endptr != '\0')
            {
                printf("Invalid input. Please try again.\n");
            }
            else
            {
                if(type == 0)
                    return result_double;
                else
                {
                    return result_long;
                }
            }
        }
        else
        {
            return -1;
        }
    }
