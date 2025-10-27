#include<stdio.h>
struct fcfs
{
  int pid,atime,btime,wtime,tatime,stime,ctime;  /* data */
}p[10];
int main(){
    int i,n;
    float totwtime = 0,totatime=0;
    printf("Fcfs\n");
    printf("No of processes:");
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        printf("\nArrival time and Burst time of P%d:",i+1);
        scanf("%d%d\n",&p[i].atime,&p[i].btime);
        p[i].pid = i+1;
    }
    for(i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(p[j].atime > p[j+1].atime){
                struct fcfs temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    p[0].stime = p[0].atime;
    p[0].ctime = p[0].stime + p[0].btime;
    p[0].wtime = 0;
    p[0].tatime = p[0].btime;
    totwtime+=p[0].wtime;
    totatime+=p[0].tatime;
    for(i=1;i<n;i++){
        p[i].stime = (p[i-1].ctime > p[i].atime) ? p[i-1].ctime : p[i].atime;
        p[i].ctime = p[i].stime + p[i].btime;
        p[i].tatime = p[i].ctime - p[i].atime;
        p[i].wtime = p[i].tatime - p[i].btime;
        totwtime += p[i].wtime;
        totatime += p[i].tatime;
    }
    printf("\n pid\t Atime\t Btime\t Wtime\t Tatime\t\n");
    for(i=0;i<n;i++){
        for(int j = 0;j<n-1;j++){
            if(p[j].pid > p[j+1].pid){
                struct  fcfs temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
                
            }
        }
    }
    
    for(i=0;i<n;i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].atime,p[i].btime,p[i].wtime,p[i].tatime);
    }
    printf("\nTotalWaitingtime : %2f\n Averagewaitingtime : %2f\n",totwtime,totwtime/n);
    printf("\nTotalTurnaroundtime : %2f\n Averageturnaroundtime : %2f\n",totatime,totatime/n);
    return 0;
}
