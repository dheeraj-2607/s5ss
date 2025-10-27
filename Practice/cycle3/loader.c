#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main(){
    FILE *fp;
    int straddr,i;
    char name[20],line[100],name1[20],*token;
    printf("Enter program name:");
    scanf("%s",name);
    fp = fopen("input.txt","r");
    if(fp == NULL){
        printf("File not found\n");
        exit(1);
    }
    fscanf(fp,"%s",line);
    token = strtok(line,"^");
    token = strtok(NULL,"^");
    strcpy(name1,token);
    printf("Name from object code: %s\n",name1);
    if(strcmp(name,name1)==0){
        while(fscanf(fp,"%s",line)!=EOF){
            if(line[0]=='T'){
                token = strtok(line,"^");
                token = strtok(NULL,"^");
                straddr = (int)strtol(token,NULL,16);
                token = strtok(NULL,"^");
                while((token = strtok(NULL,"^"))!=NULL){
                    int len = strlen(token);
                    for(i=0;i<len;i+=2){
                        printf("%06X\t%c%c\n",straddr,token[i],token[i+1]);
                        straddr++;
                    }
                }
            }
            else if(line[0]=='E'){
                break;
            }
        }
    }
    else{
        printf("Program name does not match\n");
    }
    fclose(fp);
}