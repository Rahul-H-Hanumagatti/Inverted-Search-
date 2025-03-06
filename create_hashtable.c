#include "inverted_search.h"
#include<stdlib.h>

void create_HT(Hash *arr, int size)
{
    for(int i=0;i<size;i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }
}