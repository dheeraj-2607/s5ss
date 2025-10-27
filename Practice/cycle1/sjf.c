#include<stdio.h>
struct sjf
{
  int pid,atime,btime,wtime,tatime,stime,ctime; 
  int completed;  
}p[10];
int main(){
    int i,n,completed=0,cutime=0;
    float totwtime = 0,totatime=0;
    printf("Sjf\n");
    printf("No of processes:");
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        printf("\nArrival time and Burst time of P%d:",i+1);
        scanf("%d%d\n",&p[i].atime,&p[i].btime);
        p[i].pid = i+1;
        p[i].completed = 0;
    }
    while(completed !=n){
        int shortest = -1;
        int minbtime = 999;
        for(i=0;i<n;i++){
            if(p[i].atime <= cutime && !p[i].completed && p[i].btime < minbtime){
                minbtime = p[i].btime;
                shortest = i;
            }
        }
        if(shortest == -1){
            cutime++;
        }
        else{
            p[shortest].stime = cutime;
            p[shortest].ctime = p[shortest].stime + p[shortest].btime;
            if(p[shortest].wtime < 0){
                p[shortest].wtime = 0;
            }
            p[shortest].tatime = p[shortest].ctime - p[shortest].atime;
            p[shortest].wtime = p[shortest].tatime - p[shortest].btime;
            totwtime += p[shortest].wtime;
            totatime += p[shortest].tatime;
            cutime = p[shortest].ctime;
            p[shortest].completed = 1;
            completed++;
        }
    }
    printf("\n pid\t Atime\t Btime\t Wtime\t Tatime\t\n");
    for(i=0;i<n;i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].atime,p[i].btime,p[i].wtime,p[i].tatime);
    }
    printf("\nTotalWaitingtime : %2f\n Averagewaitingtime : %2f\n",totwtime,totwtime/n);
    printf("\nTotalTurnaroundtime : %2f\n Averageturnaroundtime : %2f\n",totatime,totatime/n);
    return 0;
}