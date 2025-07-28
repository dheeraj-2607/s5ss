#include<stdio.h>
struct process{
    int pid,atime,btime,wtime,tatime,ctime,priority;
};
int main(){
    int n,time=0,count=0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for(int i=0;i<n;i++){
    printf("Enter the arrival time, burst time and priority of each proces%d: ",i);
    scanf("%d%d%d",&p[i].atime,&p[i].btime,&p[i].priority);
        p[i].pid=i+1;
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(p[i].atime>p[j].atime){
                struct process temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    time=p[0].atime;
    for(int i=0;i<n;i++){
        count=0;
        for(int j=0;j<n;j++){
            if(p[j].atime<=time){
                count++;
             }
            else{
                 break;
            }
        }
        if(count>1){
        for(int k=i;k<count;k++){
            for(int l=k;l<count;l++){
                if(p[k].priority>p[l].priority){
                    struct process temp=p[k];
                    p[k]=p[l];
                    p[l]=temp;
                }
            }
        }
    }
    p[i].wtime=time-p[i].atime;
    p[i].tatime=p[i].wtime+p[i].btime;
    time=time+p[i].btime;
    p[i].ctime=time;
    }

    float avg_wtime = 0;
    float avg_tatime = 0;
    for(int i=0;i<n;i++){
        avg_wtime += p[i].wtime;
        avg_tatime += p[i].tatime;
    }
    avg_wtime /= n;
    avg_tatime /= n;
    printf("\n\nProcess\tArrival time\tBurst time\tPriority\tWaiting time\tTurnaround time\tCompletion time\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].atime, p[i].btime,p[i].priority, p[i].wtime, p[i].tatime, p[i].ctime);
    }
    printf("\nAverage waiting time: %f", avg_wtime);
    printf("\nAverage turnaround time: %f\n", avg_tatime);
    return 0;
}


