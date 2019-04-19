#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4
    int process_id,n,TQ;
	int arrivaltime;
	int waitingtime,turnaroundtime,complilationtime,exect; 
struct rajat 
{
	int process_id;
	int state;
	int timeleft;
	int arrivaltime;
} *pro_det;

struct Queue
{
	struct rajat *front ,*rear;
}*rqueue;
void enqueue(struct rajat *proc)
{
	  if(rqueue->front==NULL)
      { 
         proc->prev=NULL;
         proc->next=NULL;
         rqueue->front=proc;           
         rqueue->rear=proc;
         return;
      }
     proc->prev=rqueue->rear;
     rqueue->rear->next=proc;
     rqueue->rear=proc;
}
struct rajat *  deQueue()
{
     if(rqueue->front==NULL)
     {
	     return NULL;
     }
     struct rajat * temp=rqueue->front;
     rqueue->front=rqueue->front->next;
     temp->next=NULL;
     if(rqueue->front==NULL)
     {
	     rqueue->rear=NULL;
     }
     return temp;
}
void checkfornewlyarrived()
{
int count=0;
           for(int i=0;i<n;i++)
	   {
		   if(pro_det[i].state == NEW && time_in_system>=pro_det[i].arrivaltime)
		   {      
			   enqueue(&pro_det[i]);
			   pro_det[i].state=READY;			   
                    }
                  if(pro_det[i].state==EXIT)
                  {
                    count++;
			}
	   }
	   if(count==n)
	   {
		  EVERYTHINGEXITED=1; 		  
	   }
}


int main()
{
rqueue =(struct Queue*) malloc(sizeof(struct Queue));
	printf(" \t\tPlease enter No of processes to schedule --- ");
	scanf("%d",&n);
	printf("\n\t\tPlease Enter Time Quantum --- ");
	scanf("%d",&TQ);
	pro_det=(struct rajat *)malloc(sizeof(struct rajat)*n);
	for(int i=0;i<n;i++)
	{
             printf("\n\n\t\tEnter Process Id For %d Process --- ",(i+1));
	     scanf("%d",&(pro_det[i].process_id));
            pro_det[i].exect=pro_det[i].timeleft;
	    pro_det[i].state=NEW;
	}
 struct rajat key; 
    int i,j;
    for (i = 1; i < n; i++) { 
        key = pro_det[i]; 
        j = i - 1; 
        while (j >= 0 && pro_det[j].arrivaltime > key.arrivaltime) { 
            pro_det[j + 1] = pro_det[j]; 
            j = j - 1; 
        } 
        pro_det[j + 1] = key; 
    } 
struct rajat *pr;
while(1)
{
        checkfornewlyarrived();
        if(EVERYTHINGEXITED==1)
        {
                    break;      
        }
        if(rqueue->front!=NULL && ContextSwitch==1)
	{
             time_in_exection=1;
	     pr=deQueue();
             pr->state=RUNNING;
             pr->timeleft--;
	     time_in_system++;
             if(time_in_exection==pr->exect)
             {
                  ContextSwitch=1;
                  pr->state=EXIT;
                  pr->complilationtime=time_in_system;
                  pr->turnaroundtime=time_in_system-pr->arrivaltime;
                  pr->waitingtime=pr->turnaroundtime-pr->exect;
             }
             else
            {
               ContextSwitch=0;
              }

int sumwaitingtime=0,sumturnaroundtime=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess process_id=%d\t:::complilationtime=%d\t:::turnaroundtime=%d\t:::waitingtime=%d",pro_det[i].process_id,pro_det[i].complilationtime,pro_det[i].arrivaltime,pro_det[i].waitingtime);
           sumwaitingtime+=pro_det[i].waitingtime;
           sumturnaroundtime+=pro_det[i].turnaroundtime;         
	}
printf("\n\n Avergae turnaroundtime=%f \t::: Average waitingtime=%f\n\n",(sumturnaroundtime/(n*1.0)),(sumwaitingtime/(n*1.0)));
}
