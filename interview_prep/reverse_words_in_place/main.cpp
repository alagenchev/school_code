
#include<string>
#include<cstring>
#include<iostream>

using namespace std;
void reverseWord(int startIndex, char **toReverse, int size);

int main(int argc, char ** argv)
{
    int size = 18;
    char *toReverse = new char(size);
    strcpy(toReverse,"to  reverse me too");

    cout<<"will be reversing: "<<toReverse<<endl;


    int startIndex = 0;

    int endIndex = size - 1;

    while(startIndex < endIndex)
    {
        char temp = toReverse[startIndex];
        toReverse[startIndex] = toReverse[endIndex];
        toReverse[endIndex] = temp;


        startIndex++;
        endIndex--;

    }


    reverseWord(0, &toReverse, size);

    cout<<"reversed: "<< toReverse<<endl;


    delete(toReverse);
}

void reverseWord(int startIndex, char **toReverse, int size)
{
    if(size - startIndex < 2)
    {
        return;
    }

    while((*toReverse)[startIndex] == ' ')
    {
        startIndex++;
    }

    int endIndex = size - 1;
    for(int i = startIndex; i< size ; i++)
    {
        if((*toReverse)[i] == ' ')
        {
            endIndex = i - 1;
            break;
        }
    }

    int i = startIndex; 
    int j = endIndex;
    while(i < j)
    {
        char temp = (*toReverse)[i];
        (*toReverse)[i] = (*toReverse)[j];
        (*toReverse)[j] = temp; 
        i++;
        j--;
    }

    reverseWord(endIndex + 1, toReverse, size);
}

