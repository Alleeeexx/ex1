#include <assert.h>
#include <string.h>
#include <stdio.h>

int main()
{
    FILE *file = fopen("D:/mtm/ex1/ExampleTest/students.txt", "r");
    printf("xd = %d\n", ftell(file));
    printf("xd = %d\n", ftell(file));
    printf("xd = %d xd = %c\n", ftell(file), fgetc(file));
}