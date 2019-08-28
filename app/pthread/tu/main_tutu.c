#include <stdint.h>
#include <sched.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include<errno.h>
#include <stdio.h>

#define BUF_SIZE 1024

#define TUTU_DEFAULT	"com.antutu.ABenchMark"
//#define TUTU_DEFAULT	"com.antutu.tvbenchmark"
char * tutu_name;
void setPidChild(pid_t pid)
{
     struct sched_param param;
     DIR *dir;
     struct dirent *ptr;
     char dirpath[50];
     char childpath[50];
		static int rtpri = -1;
		 pid_t pid_t;
			
			if (rtpri == -1)
	    {
	    	rtpri = sched_get_priority_max(SCHED_RR)/2;
	  		printf("Init antutu rtpri=%d\n", rtpri);     
			}

    sprintf(dirpath, "/proc/%d/task", pid);
     dir = opendir(dirpath);
     if (NULL != dir)
     {
         while ((ptr = readdir(dir)) != NULL) {
             if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
                 continue;
             if (DT_DIR != ptr->d_type)
                 continue;
              sprintf(childpath, "%s/%s", dirpath, ptr->d_name);
        
        		param.sched_priority = rtpri;    		
        		pid_t = atoi(ptr->d_name);
       		 if (sched_getscheduler(pid_t) == SCHED_RR)
						continue;
					 printf("setPidChild  childpath:%s R %d\n", childpath, rtpri);
						if (sched_setscheduler(pid_t, SCHED_RR, &param) == -1) {
        			printf("sched_setscheduler() failed error=%d\n", errno);
       			}
         }
         closedir(dir);
     }
 }

void getPidByName(pid_t *pid, char *task_name)
 {
     DIR *dir;
     struct dirent *ptr;
     FILE *fp;
     char filepath[50];
     char cur_task_name[50];
     char buf[BUF_SIZE] = {0,0};

     dir = opendir("/proc");
     if (NULL != dir)
     {
         while ((ptr = readdir(dir)) != NULL) {
             if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
                 continue;
             if (DT_DIR != ptr->d_type)
                 continue;

             sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
             fp = fopen(filepath, "r");
             if (NULL != fp)
             {
                 if( fgets(buf, BUF_SIZE-1, fp)== NULL ){
                     fclose(fp);
                     continue;
                 }

                 //printf("<%s>.%s %s\n", ptr->d_name, task_name, buf);
                 if (!strncmp(task_name, buf,30)){
                  *pid = atoi(ptr->d_name);
                     printf("found!!! pid=%d, name:%s\n", *pid, buf);
                     fclose(fp);
                     return;
                 }
                 fclose(fp);
             }
         }
         closedir(dir);
     }
 }

int compareAntutuPid(pid_t pid) {
     FILE *fp;
     char filepath[50];
    char buf[BUF_SIZE] = {0,0};
    
    sprintf(filepath, "/proc/%d/cmdline", pid);
    fp = fopen(filepath, "r");
    if (NULL != fp) {
        if( fgets(buf, BUF_SIZE-1, fp)== NULL ){
         fclose(fp);
         return-1;
    }
    //printf("<%s>.\n", buf);
    if (!strncmp(tutu_name, buf, 30)){
        fclose(fp);
        //printf("<%s> pid:%d", buf, pid);
        return 0;
    }
    fclose(fp);
    }
    return -1;
}

int main(int argc,char *argv[])
{
      int pid = -1;
      int i;
  
	    tutu_name = argc > 1 ? argv[1] : TUTU_DEFAULT;
  		printf("<%s> %s\n", argv[0],tutu_name);
      while(1) {
      	usleep(100000);
        if (pid == -1 || compareAntutuPid(pid)==-1) {
           pid = -1;
            getPidByName(&pid, tutu_name);
        }
            
        if (pid==-1)
            continue;
    
        setPidChild(pid);


				

    }
}
