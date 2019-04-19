#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>

#define WAITING 2
#define RUNNING 3
#define EXIT 4
#define NEW 0
#define READY 1


int time_in_system=0,time_in_exec=0,EXITED=0,TQ,CS=1,n;
struct rajat 
{
	int process_id;
	int state;
	int timeleft;
	int arrivaltime;
	int watingtime,turnaroundtime,complitiontime,excution;
	struct rajat *previous;
	struct rajat *next;
} *pro_det;
struct Queue
{
	struct rajat *front ,*rear;
}*rqueue;

void enqueue(struct rajat *proc)
{
	  if(rqueue->front==NULL)
      { 
         proc->previous=NULL;

         proc->next=NULL;
         rqueue->front=proc;           
         rqueue->rear=proc;
         return;
      }
     proc->previous=rqueue->rear;
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
		  EXITED=1; 
		  
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
	     printf("\n\t\tEnter arrival time For %d Process ---",(i+1));
	     scanf("%d",&(pro_det[i].arrivaltime));
	     printf("\n\t\tEnter Execution time For %d Process ---",(i+1));
	     scanf("%d",&(pro_det[i].timeleft)); 
	     
            pro_det[i].excution=pro_det[i].timeleft;
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
        if(EXITED==1)
        {

                    break;      
        }
        
        if(rqueue->front!=NULL && CS==1)
	{
             time_in_exec=1;
	     pr=deQueue();
             pr->state=RUNNING;
             pr->timeleft--;
	     time_in_system++;
             if(time_in_exec==pr->excution)
             {
                  CS=1;
                  pr->state=EXIT;
                  pr->complitiontime=time_in_system;
                  pr->turnaroundtime=time_in_system-pr->arrivaltime;
                  pr->watingtime=pr->turnaroundtime-pr->excution;
             }
             else
            {
               CS=0;
              }
	}
        else if(CS==0&&pr!=NULL && pr->state==RUNNING )
	{
             if(pr->timeleft==0)
             {
                  CS=1;
                  pr->state=EXIT;
                  pr->complitiontime=time_in_system;
                  pr->turnaroundtime=time_in_system-(pr->arrivaltime);
                  pr->watingtime=(pr->turnaroundtime)-(pr->excution);
                  continue;
             }      
             time_in_exec++;
             pr->timeleft--;
            time_in_system++;

             if(pr->timeleft==0)
             {
                  CS=1;
                  pr->state=EXIT;
                  pr->complitiontime=time_in_system;
                  pr->turnaroundtime=time_in_system-(pr->arrivaltime);
                  pr->watingtime=(pr->turnaroundtime)-(pr->excution);
             }            
             else if(time_in_exec==TQ)
             {
                pr->state=READY;
                enqueue(pr);
                CS=1;
              }
            else
          { 
              CS=0;
	  }

          
             
          
	}
else
{
time_in_system++;
}
}
int sumwt=0,sumtat=0;
for(int i=0;i<n;i++)
	{
           printf("\n\nprocess process_id=%d\t:::complitiontime=%d\t:::turnaroundtime=%d\t:::watingtime=%d",pro_det[i].process_id,pro_det[i].complitiontime,pro_det[i].turnaroundtime,pro_det[i].watingtime);
           sumwt+=pro_det[i].watingtime;
           sumtat+=pro_det[i].turnaroundtime;
           
	}
printf("\n\n Avergae turnaroundtime=%f \t::: Average watingtime=%f\n\n",(sumtat/(n*1.0)),(sumwt/(n*1.0)));
}
