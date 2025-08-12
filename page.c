#include<stdio.h>
int pagefound(int f[],int count,int a){
    for(int i=0;i<count;i++){
        if(f[i]==a){
            return 1;
        }
    }
    return 0;
}
int accesstotal(int arr[],int i,int a){
    int count =0;
    for(int j=i;j>=0;j--){
        if(arr[j]==a){
            count++;
        }
    }
    return count;
}
int accessrecent(int arr[],int i,int a){
    int count = 0;
    for(int j=i;j>=0;j--){
        count++;
        if(arr[j]==a){
            return count;
        }
    }
}
void fifo(int arr[], int n, int f[], int fno) {
    int fifoarr[fno][n];
    int front = 0, count = 0, p = 0, i, j;
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            fifoarr[i][j] = -1;
        }
    }

    for (i = 0; i < n; i++) {
        if (!pagefound(f, count, arr[i])) {
            p++;
            f[front] = arr[i];
            front = (front + 1) % fno;
            if (count != fno) {
                count++;
            }
        }
        // Store current frame state in fifoarr
        for (j = 0; j < count; j++) {
            fifoarr[j][i] = f[j];
        }
    }

    // Print the frame table
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            if (fifoarr[i][j] != -1) {
                printf("%d ", fifoarr[i][j]);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("Page Fault in FIFO = %d\n", p);
}
void lru(int arr[], int n, int f[], int fno) {
    int lruarr[fno][n];
    int front = 0, count = 0, p = 0, i, j;

    // Initialize lruarr to -1
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            lruarr[i][j] = -1;
        }
    }

    for (i = 0; i < n; i++) {
        if (!pagefound(f, count, arr[i])) {
            p++;
            int min = accesstotal(arr, i, f[0]);
            int minindex = 0;
            for (j = 1; j < count; j++) {
                if (accesstotal(arr, i, f[j]) < min) {
                    minindex = j;
                    min = accesstotal(arr, i, f[j]);
                }
            }
            f[minindex] = arr[i];
            if (count != fno) {
                count++;
            }
        }
        // Store current frame state in lruarr
        for (j = 0; j < count; j++) {
            lruarr[j][i] = f[j];
        }
    }

    // Print the frame table
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            if (lruarr[i][j] != -1) {
                printf("%d ", lruarr[i][j]);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("Page Fault in LRU = %d\n", p);
}
void lfu(int arr[], int n, int f[], int fno) {
    int lfuarr[fno][n];
    int count = 0, p = 0, i, j, k;

    // Initialize lfuarr to -1
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            lfuarr[i][j] = -1;
        }
    }

    for (i = 0; i < n; i++) {
        if (!pagefound(f, count, arr[i])) {
            p++;
            if (count < fno) {
                f[count++] = arr[i];
            } else {
                // Find LFU page
                int min_freq = n + 1, min_index = -1;
                int freq[fno], recent[fno];
                for (j = 0; j < fno; j++) {
                    freq[j] = accesstotal(arr, i - 1, f[j]);
                    recent[j] = accessrecent(arr, i - 1, f[j]);
                }
                min_freq = freq[0];
                min_index = 0;
                for (j = 1; j < fno; j++) {
                    if (freq[j] < min_freq) {
                        min_freq = freq[j];
                        min_index = j;
                    } else if (freq[j] == min_freq) {
                        if (recent[j] > recent[min_index]) {
                            min_index = j;
                        }
                    }
                }
                f[min_index] = arr[i];
            }
        }
        // Store current frame state in lfuarr
        for (j = 0; j < count; j++) {
            lfuarr[j][i] = f[j];
        }
    }

    // Print the frame table
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            if (lfuarr[i][j] != -1) {
                printf("%d ", lfuarr[i][j]);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("Page Fault in LFU = %d\n", p);
}
int main(){
    printf("Psge replacement algorithm:\n");
    int n,i,frameno;
    printf("Enter no of frames:");
    scanf("%d",&frameno);
    printf("Enter no of requests:");
    scanf("%d",&n);
    printf("Enter page string each separated by space\n");
    int arr[n],f[frameno];
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Page frames\n");
    fifo(arr,n,f,frameno);
    lru(arr,n,f,frameno);
    lfu(arr,n,f,frameno);
}