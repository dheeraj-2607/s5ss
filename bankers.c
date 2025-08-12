#include<stdio.h>
int cserv(int avail[],int need[],int n){
    for(int i=0;i<n;i++){
        if(need[i]>avail[i]){
            return 0;
        }
    }
    return 1;
}
int main(){
    printf("Bankers algorithm\n");
    printf("No of processes: ");
    int n, r, i, j;
    scanf("%d", &n);
    printf("No of resources: ");
    scanf("%d", &r);
    int avail[r];
    printf("Enter available resources:\n");
    for(i = 0; i < r; i++){
        scanf("%d", &avail[i]);
    }
    int alloc[n][r];
    int max[n][r];
    int need[n][r];
    printf("Allocation matrix:\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < r; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter max matrix:\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < r; j++){
            scanf("%d", &max[i][j]);
        }
    }
    printf("Need Matrix:\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < r; j++){
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%2d ", need[i][j]);
        }
        printf("\n");
    }
    int count = 0;
    int flag[n];
    for(i = 0; i < n; i++){
        flag[i] = 0;
    }
    int temp[n];
    while(count < n){
        int found = 0;
        for(i = 0; i < n; i++){
            if(flag[i] == 0){
                int can_allocate = 1;
                for(j = 0; j < r; j++){
                    if(need[i][j] > avail[j]){
                        can_allocate = 0;
                        break;
                    }
                }
                if(can_allocate){
                    for(j = 0; j < r; j++){
                        avail[j] += alloc[i][j];
                    }
                    temp[count] = i;
                    count++;
                    flag[i] = 1;
                    found = 1;
                    printf("P%d has completed execution\n", i);
                    printf("\nNeed Matrix\n");
                    for(int x = 0; x < n; x++){
                        for(int y = 0; y < r; y++){
                            printf("%2d ", need[x][y]);
                        }
                        printf("\n");
                    }
                }
            }
        }
        if(!found){
            printf("System is not in a safe state.\n");
            break;
        }
    }
    if(count == n){
        printf("Safe sequence:\n");
        for(i = 0; i < n; i++){
            printf("P%d", temp[i]);
            if(i != n-1) printf(" -> ");
        }
        printf("\n");
    }
    return 0;
}