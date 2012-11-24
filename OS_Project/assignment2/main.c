#include <stdlib.h>
#include <stdio.h>

int main()
{
    /*
    printf("getchar test:\n");
    char c = getchar();
    printf("char was %c\n", c);
    */
    printf("scanf test:\n");
    char c;
    __isoc99_scanf("%c", &c);
    printf("c is %c\n", c);
    return 0;
}
