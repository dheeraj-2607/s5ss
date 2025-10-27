#include<stdio.h>
struct priority
{
  int pid,atime,btime,wtime,tatime,stime,ctime,priority; 
}p[10];
int main(){
    int i,n,time = 0, count = 0;
    float totwtime = 0,totatime=0;
    printf("Priority\n");
    printf("No of processes:");
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        printf("\nArrival time,Burst time and Priority of P%d:",i+1);
        scanf("%d%d%d\n",&p[i].atime,&p[i].btime,&p[i].priority);
        p[i].pid = i+1;
    }
    for(i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(p[i].atime > p[j].atime){
                struct priority temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    time = p[0].atime;
    for(i=0;i<n;i++){
        count = 0 ;
        for(int j=0;j<n;j++){
            if(p[j].atime <= time){
                count++;
            }
            else{
                break;
            }
        }
        if(count > 1){
            for(int k=i;i<count;k++){
                for(int l = k;l<count ;l++){
                    if(p[k].priority > p[l].priority){
                        struct priority temp = p[k];
                        p[k] = p[l];
                        p[l] = temp;
                    }
                }
            }
        }
        p[i].wtime = time - p[i].atime;
        p[i].tatime = p[i].wtime + p[i].btime;
        time += p[i].btime;
        p[i].ctime = time;
    }

    for(i=0;i<n;i++){
        totwtime += p[i].wtime;
        totatime += p[i].tatime;
    }
    printf("\n pid\t Atime\t Btime\t Wtime\t Tatime\t Cotime\n");
    for(i=0;i<n;i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].atime,p[i].btime,p[i].wtime,p[i].tatime,p[i].ctime);
    }
    printf("\nTotalWaitingtime : %2f\n Averagewaitingtime : %2f\n",totwtime,totwtime/n);
    printf("\nTotalTurnaroundtime : %2f\n Averageturnaroundtime : %2f\n",totatime,totatime/n);
}