#include<stdio.h>
int qu[20],f=-1,r=-1;
struct rr{
    int pid,atime,btime,ctime,tatime,wtime,stime,left;
}p[20];
struct done{
    int pid,stime,ctime;
}d[20];

void enq(int j){
    if(f==-1){
        f=0;
    }
    qu[r]=j;
}
int dq(){
    int it = qu[f];
    if(f==r){
        f=-1;
        r=-1;
    }
    else{
        f++;
    }
    return it;
}
void main(){
    int i,n,j,k,num = 0,ls=0,t,curr=0,totime=0;
    float avgwt=0,avgtat=0;
    int totwtime=0,totatime=0;
    printf("Round Robin\n");
    printf("No of processes:");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("\nArrival time and Burst time of P%d:",i+1);
        scanf("%d%d",&p[i].atime,&p[i].btime);
        p[i].pid = i+1;
        p[i].left = p[i].btime;
        p[i].stime = 0;
    }
    printf("Enter time quantum:");
    scanf("%d",&t);
    for(i=0;ls<n;){
        for(j=0;j<n;j++){
            if(p[j].stime==0 && p[j].atime <= curr){
                enq(j);
                p[j].stime = 1;
            }
        }
        if(f!=-1){
            k = dq();
            d[num].stime = curr;
            if(p[k].left <= t){
                d[num].ctime = curr + p[k].left;
                curr += p[k].ctime;
                curr = d[num].ctime;
                p[k].tatime = p[k].ctime - p[k].atime;
                p[k].wtime = p[k].tatime - p[k].btime;
                p[k].stime = 2;
                ls++;
                num++;
            }
            else{
                d[num].ctime = curr + t;
                curr = d[num].ctime;
                p[k].left -= t;
                num++;
                for(j=0;j<n;j++){
                    if(p[j].stime==0 && p[j].atime <= curr){
                        enq(j);
                        p[j].stime = 1;
                    }
                }
                enq(k);
            }
        }
        else{
            curr++;
        }
        totime=curr;
        printf("\n pid\t Atime\t Btime\t Wtime\t Tatime\t\n");
    for(i=0;i<n;i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].atime,p[i].btime,p[i].wtime,p[i].tatime);
    }
    totwtime += p[i].wtime;
    totatime += p[i].tatime;
    }
    printf("\nTotalWaitingtime : %2d\n Averagewaitingtime : %2d\n",totwtime,totwtime/n);
    printf("\nTotalTurnaroundtime : %2d\n Averageturnaroundtime : %2d\n",totatime,totatime/n);
    

}