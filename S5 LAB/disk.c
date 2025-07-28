#include<stdio.h>
int seek(int a,int b){
    if(a>b){
        return a-b;
    } else {
        return b-a;
    }
}
void copy(int arr[],int temp[],int n){
    for(int i=0;i<n;i++){
        temp[i] = arr[i];
    }
}
void sort(int arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
int reqindex(int arr[],int n,int p){
    for(int i=0;i<n;i++){
        if(arr[i]>=p){
            return 1;
        }
    }
}
void fcfs(int arr[],int n,int p,int max){
    printf("FCFS Disk Scheduling\n");
    int seekt = 0;
    printf("%d=> ", p);
    for(int i=0;i<n;i++){
        seekt += seek(p, arr[i]);
        if(i!= n-1){
            printf("%d=> ", arr[i]);
        } else {
            printf("%d\n", arr[i]);
        }
        p = arr[i];
    }
        printf("Total Head movement in FCFS = %d\n", seekt);
}
void scan(int arr[], int n, int p, int max) {
    printf("SCAN Disk Scheduling\n");
    int seekt = 0;
    int temp[n],i;
    copy(arr, temp, n);
    sort(temp, n);
    
    int index = reqindex(temp, n, p);
    seekt+=seek(p,max);
    printf("%d=> ", p);
    for (int i = index; i < n; i++) {
        printf("%d=> ", temp[i]);
        p = temp[i];
    }
    p=max;
    for(i=index-1;i>=0;i--){
        if(i!=0){
            printf("%d=> ", temp[i]);
        } else {
            printf("%d\n", temp[i]);
        }
        p=temp[i];
    }
    seekt += seek(0, temp[i]);
    printf("\nTotal Head movement in SCAN = %d\n", seekt);
}
void cscan(int arr[], int n, int p, int max) {
    printf("C-SCAN Disk Scheduling\n");
    int seekt = 0;
    int temp[n], i;
    copy(arr, temp, n);
    sort(temp, n);
    
    int index = reqindex(temp, n, p);
    seekt += seek(p, max);
    printf("%d=> ", p);
    for (i = index; i < n; i++) {
        printf("%d=> ", temp[i]);
        p = temp[i];
    }
    printf("%d/n", max);
    p = 0;
    
    for (i = 0; i < index; i++) {
        if (i != index-1) {
            printf("%d=> ", temp[i]);
        } else {
            printf("%d\n", temp[i]);
        }
        p = temp[i];
    }
    seekt += seek(max,0);
    if(index>0){
        seekt+=seek(0,temp[index-1]);
    }
    printf("\nTotal Head movement in C-SCAN = %d\n", seekt);
}
void main(){
    printf("Disk Scheduling Algorithms\n");
    int n,pos,i,min,max,p;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("enter disk track limit:");
    scanf("%d", &max);
    printf("Enter the request\n");
    int arr[n];
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Enetr current position of disk head:");
    scanf("%d",&p);
    fcfs(arr,n,p,max);
    scan(arr,n,p,max);
    cscan(arr,n,p,max);
}