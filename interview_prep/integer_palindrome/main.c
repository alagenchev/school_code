#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
bool isPali(int);
int main()
{
    int x = 12521;
    bool pal = isPali(x);
    printf("pali is %d\n", pal);
    return 0;
}

int getSmallest(int x)
{
    return x % 10;
}
int getBiggest(x)
{

    while(x/10 != 0)
    {
        x = x / 10;
    }
    return x;
}

int getBiggestPower(x)
{
    int count = 0;
    while(x/10 != 0)
    {
        count++;
        x = x / 10;
    }
    return count;
}

bool isPali(int x)
{
    if (x /10 < 10)
    {
        return true;
    }
    if(getSmallest(x) != getBiggest(x))
    {
        return false;
    }

    int biggest = pow(10,getBiggestPower(x))*getBiggest(x);
    int rest = (x - biggest) / 10;
    return isPali(rest);
}


