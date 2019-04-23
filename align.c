#include <stdio.h>
#pragma pack(4)

struct A{
    char x;
    int y;

};

int main()
{
    printf("size = %ld\n", sizeof(struct A));    
    return 0;
}

