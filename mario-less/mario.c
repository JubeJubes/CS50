#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
      height   = get_int("Height: ");
    }
    while(height<1|| height>8);

    for (int i=0;i<height;i++){
        for (int j=0;j<height-1-i;j++){
            printf(" ");
        }
        for (int h=0; h<=i;h++){
            printf("#");
        }
        printf("\n");
    }
}