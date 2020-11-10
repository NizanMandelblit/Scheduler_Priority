

#include "string.h"
#include "stdio.h"
#define NUM_PROCESSES 2
/**
 * process control block to hold all relevant information about a process
 */
struct pcb {
    int pid;         /* ID of the proces */
    int priority;    /* process priority */
    int is_attached; /* 1 if attached to processlist, else 0 */
    int *function;   /* pointer to the process function */
    char name[10];   /* Name of the process */
} typedef pcb;
pcb processlist[NUM_PROCESSES];
int process0();
int process1();
int numAttachedProc = 0; /* Number of procsess attached */
/**
 * @brief  the function attach a proccses to the proceses list
 * @note
 * @param  *name: name of the procses
 * @param  priority: priority number of the procses
 * @param  *function: pointer to procses function
 * @retval 0 if all went well, -1 for errors.
 */
int process_attach(char *name, int prio, void *function)
{
    int i = 0;
    printf("beginning process_attach\n");
    while (i < NUM_PROCESSES)
    {
        //looking for a vacant spot in the proccses list to attach the procsess to
        if (processlist[i].is_attached != 1)
        {
            printf("\nattached process %d",i);
            processlist[i].pid = i;
            strcpy(processlist[i].name, name);
            processlist[i].priority = prio;
            processlist[i].function = function;
            processlist[i].is_attached = 1;
            break;
        }
        printf("\n");
        i++;
    }
    numAttachedProc++;
    return 0;
}

/**
 * @brief  the function is detaching a process from the processes list.
 *         please be aware the process object is not being removed from the list,
 *         rather the function simply changes its 'is_attached' attribute to false.
 * @note
 * @param  pid: the procsess id number
 * @retval 0 if all went well.
 */
int process_detach(int pid)
{
    processlist[pid].is_attached = 0;
    numAttachedProc--;
    return 0;
}

int process0()
{

    printf("\ntest procsses 0\n");
    process_detach(0);
    return 0;
}

int process1()
{
    printf("\ntest procsess 1\n");
    process_detach(1);
    return 0;
}

/**
 * @brief  a function to simulate a simple non-preemptive Priority scheduler.
 * @note
 * @retval
 */
int scheduler()
{
    int i = 0;
    void (*p)(void);
    if (numAttachedProc > 1)
    {
        int maxPriority = processlist[0].priority;
        i++;
        while (i < NUM_PROCESSES)
        {
            if (processlist[i].is_attached)
            {
                if (maxPriority < processlist[i].priority)
                {
                    maxPriority = processlist[i].priority;
                }
            }
            i++;
        }
        i = 0;
        while (i < NUM_PROCESSES)
        {
            if (processlist[i].is_attached == 1 && maxPriority == processlist[i].priority)
            {
                p = (void *)processlist[i].function;
            }
            i++;
        }
        (*p)();
    }
    else
    {
        i=0;
        while (i < NUM_PROCESSES)
        {
            if (processlist[i].is_attached)
            {
                break;
            }
            i++;
        }
        p = (void *)processlist[i].function;
        (*p)();
    }
    return 0;
}
int main() {

    //testing the scheduler
    process_attach("process0", 10, process0);
    process_attach("process1", 9, process1);
    scheduler();
    scheduler();
    getchar( );

}