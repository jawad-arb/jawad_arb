#include<stdio.h>
#include<stdlib.h>


int main(){
FILE* fp;
fp=fopen("test.txt","r");
int id ;
fseek(fp,-76,SEEK_END);
char nom[20],prenom[20];


fscanf(fp,"%d",&id);
printf("id:%d",id);









fclose(fp);
    return 0;
}