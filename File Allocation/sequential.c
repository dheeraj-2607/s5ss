#include<stdio.h>
int nof, i, strBlk[10], noBlk[10], key;
int main(){
    printf("\nEnter the Number of Files  :  ");
    scanf("%d", &nof);
    for (i = 1; i <= nof; i++){
        printf("Enter Starting Block & No of Blocks of File %d  : ", i);
        scanf("%d %d", &strBlk[i], &noBlk[i]);    
    }
    printf("\nEnter the File Number to Search  : ");
    scanf("%d", &key);
    if(key > nof)
        printf("\tFile Not Found !!!\n");
    else{
        printf("\nFile Name\t\tStart Block\t\tOccupied Blocks\n");
        printf("\n  %7d   %10d               ", key, strBlk[key]);
        for (i = 0; i < noBlk[key]; i++)
            printf(" %d ", strBlk[key] + i);
    }
    return 0;
}



/*

       -----------------------Output -1--------------------

        Enter the Number of Files  :  3
        Enter Starting Block & No of Blocks of File 1  : 85 10
        Enter Starting Block & No of Blocks of File 2  : 102 4
        Enter Starting Block & No of Blocks of File 3  : 60 6

        Enter the File Number to Search  : 2

           File Name   Start Block        Occupied Blocks
                2          102                102  103  104  105
        

        --------------------Output-2-----------------------

        Enter the Number of Files  :  3
        Enter Starting Block & No of Blocks of File 1  : 85 10
        Enter Starting Block & No of Blocks of File 2  : 102 4
        Enter Starting Block & No of Blocks of File 3  : 60 6

        Enter the File Number to Search  : 5
                File Not Found !!!  


*/