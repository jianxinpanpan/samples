#define _GNU_SOURCE   
  
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <sched.h>    
#include <pthread.h>  
#include <unistd.h>   
#include <errno.h>  
#include <string.h>  
  
typedef void* (*threadfunc)(void *data);  
int thread_stop = 0;  
  
void *pt_fn(void * data)  
{  
    while(1)  
    {  
	sleep(1);
        printf("pt_fn.\n");  
    }  
    return ((void *)0) ;
}  
  
int pcreate_rr_thread(pthread_t *tid, int priority, threadfunc func, void *data)  
{  
    pthread_attr_t  attr;  
    struct sched_param  params;  
    int ret = 0;  
    pthread_attr_init(&attr);  
    //不继承父线程的调度策略  
    if((ret = pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED)))  
    {  
        printf("pthread_attr_setinheritsched failed.\n");  
    }  
    //设置子线程为RR调度策略           
    if((ret = pthread_attr_setschedpolicy(&attr,SCHED_RR)))  
    {  
        printf("pthread_attr_setschedpolicy failed.\n");  
    }  
    //设置优先级  
    params.sched_priority = priority;  
    if((ret = pthread_attr_setschedparam(&attr, &params)))  
    {  
        printf("pthread_attr_setschedparam failed.\n");  
    }  
    //创建线程  
    if((ret = pthread_create(tid, &attr, func, (void *)data)))  
    {  
        printf("pthread_create failed with error.\n");  
    }  
      
    return ret;  
      
}  
  
int main(void)  
{  
    int ret; 
    char exit;  
    pthread_t thread;  
    int max_prio;  
  
    max_prio = sched_get_priority_max(SCHED_RR);  
    if((ret = pcreate_rr_thread(&thread, max_prio, pt_fn, NULL)))  
    {  
        printf("pcreate_rr_thread thread failed.\n");  
        goto err_pthread_tx;  
    }  
    while(exit != 'q')  
    {  
        scanf("%c", &exit);  
    }  
    thread_stop = 1;     
    pthread_join(thread, NULL);  
    printf("exit successed.\n");  
    return ret;  
err_pthread_tx:  
    return ret;      
}  
