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
int main()
{

	printf(" \t\tPlease enter No of processes to schedule --- ");
	scanf("%d",&n);
	printf("\n\t\tPlease Enter Time Quantum --- ");
	scanf("%d",&TQ);
	for(int i=0;i<n;i++)
	{
             printf("\n\n\t\tEnter Process Id For %d Process --- ",(i+1));
	     scanf("%d",&(pro_det[i].process_id));
	     printf("\n\t\tEnter arrival time For %d Process ---",(i+1));
	     scanf("%d",&(pro_det[i].arrivaltime));
	     printf("\n\t\tEnter Execution time For %d Process ---",(i+1));
	     scanf("%d",&(pro_det[i].timeleft)); 
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
