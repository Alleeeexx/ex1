#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int findLines(FILE *file)
{
    assert(file);
    int lines = 0;
    rewind(file);
    char currentChar = fgetc(file);
    while (currentChar != EOF)
    {
        if (currentChar == '\n')
        {
            lines++;
        }
        currentChar = fgetc(file);
    }
    rewind(file);
    return lines;
}

int findStringLength(FILE *file)
{
    if (file == NULL)
    {
        return -1;
    }
    int length = 0;
    char c = fgetc(file);
    if (c == ' ' || c == '\n')
    {
        c = fgetc(file);
    }
    while (c != ' ' && c != '\n' && c != EOF)
    {
        length++;
        c = fgetc(file);
    }
    fseek(file, -(length + 1), SEEK_CUR);
    return length;
}

int main()
{
    FILE *file = fopen("D:/mtm/ex1/ExampleTest/hackers.txt", "r");

    printf("bruh\n");
    int number, size;
    fscanf(file, "%d", &number);
    printf("%d\n", number);
    printf("pos = %d", ftell(file));
    char c = fgetc(file);
    printf("xd-%c-xd\n", c);
    return 0;
}