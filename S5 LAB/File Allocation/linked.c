#include <stdio.h>
#include <stdlib.h> 
int nof, i, j, noBlk[10], key;
struct table{
    int blkNo;
    struct table *link;
};
struct table *file[10], *head, *tail, *new, *temp;
int main(){
    printf("\nEnter the Number of Files : ");
    scanf("%d", &nof);
    for (i = 1; i <= nof; i++){
        printf("\nEnter No of Blocks of File %d : ", i);
        scanf("%d", &noBlk[i]);
        printf("Enter the Blocks of File : ");
        tail = head = NULL;
        for (j = 0; j < noBlk[i]; j++){
            new = malloc(sizeof(struct table)); 
            scanf("%d", &new->blkNo);
            new->link = NULL;
            if (head == NULL){
                head = new;
                tail = new;
            }
            else{
                tail->link = new;
                tail = new;
            }
        }
        file[i] = head; 
    }
    printf("\nEnter the File Number to Search : ");
    scanf("%d", &key);
    if (key > nof || key < 1) 
        printf("\tFile Not Found !!!\n");
    else {
        printf("\nFile Name\t\tNo of Blocks\t\tStart Block\t\tOccupied Blocks\n");
        printf("\n%7d    %10d    %10d \t\t", key, noBlk[key], file[key]->blkNo);
        temp = file[key];
        while (temp != NULL){
            printf(" %d -> ", temp->blkNo);
            temp = temp->link;
        }
    }
    for (i = 1; i <= nof; i++){
        struct table *current = file[i];
        while (current != NULL){
            struct table *next = current->link;
            free(current);
            current = next;
        }
    }

    return 0;
}


/*

       --------------------------------------Output -1----------------------------------

        Enter the Number of Files : 3

        Enter No of Blocks of File 1 : 2
        Enter the Blocks of File : 10 14

        Enter No of Blocks of File 2 : 4
        Enter the Blocks of File : 66 55 44 33

        Enter No of Blocks of File 3 : 2
        Enter the Blocks of File : 68 90

        Enter the File Number to Search : 2

         File Name    No of Blocks    Start Block         Occupied Blocks
              2             4            66              66 ->  55 ->  44 ->  33 ->
        

        ---------------------------------------Output-2---------------------------------

        Enter the Number of Files : 3

        Enter No of Blocks of File 1 : 2
        Enter the Blocks of File : 10 14

        Enter No of Blocks of File 2 : 4
        Enter the Blocks of File : 66 55 44 33

        Enter No of Blocks of File 3 : 2
        Enter the Blocks of File : 68 90

        Enter the File Number to Search : 4
                File Not Found !!!

*/