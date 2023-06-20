# Matrix Multiplication in C

Program for matrix multiplication.
Not for beginners.

# Getting Started

## Prerequisite

* This program contains implementation of dynamic memory allocations and pointer arithmetic.


## Explanation

### Main Function

```C
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
```

This is the code of main function and to be honest the flow of program here is little confusing.

First I am using a for loop to print the input message on screen and before incrementing the loop, taking input from the user, using custom `inputValidation()` function.

I have already explained the workflow of inputValidation function in detail [here](https://github.com/l-kaushik/input-validation-in-C) but I'll explain, few changes that I've added into the function later in this repository.

Below the for loop there is an if condition, that checks if both matrices are suitable for matrix multiplication or not.

Basically for matrix multiplication the number of columns in the first matrix must be equal to the number of rows in the second matrix, later they are the rows and the columns of resultant matrix.

At the end of the main function before return, I am calling a function `matrixMulti()` with size argument in it.

### Input Validation Function

```C
double inputValidation(int type)
{
    char input[30];
    double result;

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0'; // removing the trailing spaces
            char *endptr;

            if (type == 1) // some checks for size of matrix
            {
                if (strstr(input, "-")) // negative value checking
                {
                    printf("size of matrix can't be negative\n");
                }
                else if (strstr(input, ".")) // float value checking
                {
                    printf("size of matrix should be an integer\n");
                }
                else
                {
                    calc:
                    result = strtod(input, &endptr);
                    if (*endptr != '\0')
                    {
                        printf("Invalid input. Please try again.\n");
                    }
                    else
                    {
                        return result;
                    }
                }
            }
            else
            {
                goto calc; //jumping to calc
            }
        }
        else
        {
            return -1;
        }
    }
}
```

This is the input validation function, which will check for any invalid input throughout the program, whether it is the input related to the size of matrices or the elements of matrices.

The function takes one argument named `type`:
* This type argument can contain 1 and any other value.
* If type is set to one that means the input is related to the size of matrix and size of matrix can't be a negative number, a decimal number and an alphabet.

And that's what we checking here:

```C
while (1)
{
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        input[strcspn(input, "\n")] = '\0'; // removing the trailing spaces
        char *endptr;
```

Entering into an infinite loop that runs until condition is true, then the code from `if` to `char *endptr;` is reponsible for taking input, explained in detail [here](https://github.com/l-kaushik/input-validation-in-C).

```C
if (type == 1) // some checks for size of matrix
{
    if (strstr(input, "-")) // negative value checking
    {
        printf("size of matrix can't be negative\n");
    }
    else if (strstr(input, ".")) // float value checking
    {
        printf("size of matrix should be an integer\n");
    }
    else
    {
        calc:
        result = strtod(input, &endptr);
        if (*endptr != '\0')
        {
            printf("Invalid input. Please try again.\n");
        }
        else
        {
            return result;
        }
    }
}
else
{
    goto calc; //jumping to calc
}
```
This conditional block is just after the `char *endptr;` and in the condition we checking if type is 1 or not:
* If it's 1 then we checking for any negative values.
* 2nd we checking for decimal values if no negative values are there.
* At last, checking if there is a presence of any alphabets or not.
* After verifying these conditions returning the value.

In the else block there is line: `got calc;` which will jump the program directly to alphabets checking only when, when the type is not equals to 1, because elements can be a decimal and a negative number.

**NOTE:-** In the main function, where we taking the input from user using `size[i] = (int)inputValidation(1);` the value returned by the `inputValidation()` is getting typecasted into the int because our function is returning a type `double` value.

### Matrix Multi Function

This is the key function of the whole program, responsible for allocating memory, storing the matrices and also calculating the multiplication.

This function takes size of matrices as an argument and later use it for memory allocations.

Basically there are 3 parts of this function itself:

#### 1. Memory Allocation

```C
float **mat1;
float **mat2;
float **resultMat; // these are matrices
    
float sum = 0;

int j, i, k, count = 1;  // loop variables except count


// Allocating memory for the matrix 1
mat1 = (float **)malloc(size[0] * sizeof(float *)); // array of pointers

for(int i = 0; i < size[0]; i++)
{
    mat1[i] = (float *)malloc(size[1] * sizeof(float)); // array of float for each pointers
}

// Allocating memory for the matrix 2
mat2 = (float **)malloc(size[2] * sizeof(float *)); 

for(int i = 0; i < size[2]; i++)
{
    mat2[i] = (float *)malloc(size[3] * sizeof(float)); 
}

// Allocating memory for the resultant matrix
resultMat = (float **)malloc(size[0] * sizeof(float *));

for(int i = 0; i < size[0]; i++)
{
    resultMat[i] = (float *)malloc(size[3] * sizeof(float)); 
}
```

The above part of the function `matrixMulti()` allocates the memory.

```C
float **mat1;
float **mat2;
float **resultMat;
```

These are the variable declaration or more specifically a declaration of 2d dynamic array.

Let me explain it:
* `float *;` indicates a pointer to a float, or a pointer that points either to a single float value or to the first index/element of a dynamically allocated array of floats.

* `float **;` indicates a pointer to a pointer to a float, or a pointer that points to the first index/element of an array whose each element is also a pointer to a dynamically allocated array of floats.

    For example:- 
    
    a1[] = {1, 2, 3}, 
    
    a2[] = {3, 4, 5}, 
    
    a3[] = {5, 6, 7},
    
    here a1, a2 and a3 are 3 arrays, I have write the integer values just to make it look clear.

    a[] = [&a1, &a2, &a3]

    here a is another array that contains, the address of the other 3 arrays, an in short I can say that, a is an array that points to the another arrays of type int.

    We getting same functionality with `float **mat1;` but dynamically using [malloc()](https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/) function.

 **Above two points are can be hard to grasp and in that case, I would suggest you to google about them, if you didn't get them.**