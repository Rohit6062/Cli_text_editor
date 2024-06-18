#include<stdio.h>
#include<stdlib.h>


int main()
{
    int l;
    scanf("%lc", &l);
    printf("l = %d\n", l-48);
    return 0;
}










/*
int main(){
    FILE* f = fopen("test1.txt","r");
    fseek(f,1015,SEEK_CUR);
    printf("%d\n",fgetc(f));
    printf("ftell(f) = %ld\n", ftell(f));
    return 0;
}*/
