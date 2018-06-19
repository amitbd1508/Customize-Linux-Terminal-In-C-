#include<stdlib.h>
#include<stdio.h>
#include<string.h>


#include<unistd.h>
#include<errno.h>


#define MAX 401
#define true 1
const int N=10;

void spiltCmdString(char* commend, char** x);
int executeTheCommend(char** var);



int main()
{
    char cmd[MAX+7];
    char* var[N+1];

    int cmdCount = 0;
    char* user = getenv("USER");   // "getenv" for Get username
    printf("\n\n  ============   Welcome %s   =============\n\n\n" ,user); //print user name
    while(true)
    {
        char* username = getenv("USER");   // "getenv" Get username
        if(strcmp(username,user)!=0)
            printf("\n\n  ============   Welcome %s   =============\n\n\n" ,username);
        printf("%s@line:%d> \a", username, ++cmdCount);
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) break;  //get input from user..
        if(cmd[strlen(cmd)-1] == '\n')    //remove newline and replace with null("\0");
            cmd[strlen(cmd)-1] = '\0';
        spiltCmdString(cmd, var);
        if(strcmp(var[0], "exit") == 0) break;
        if(strcmp(var[0], "hang") == 0)
        {
            while(true){ pid_t p=fork(); }
        }
        if(executeTheCommend(var) == 0) break;
    }

return 0;
}


void spiltCmdString(char* commend, char** x)
{   int i=0;
    for(i = 0; i < N; i++) {
        x[i] = strsep(&commend, " ");
        if(x[i] == NULL) break;
    }
}

int executeTheCommend(char** var)
{
    pid_t pid = fork();
    if (pid < 0) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }
    else if (pid == 0) {
        execvp(var[0], var); //execute cmd
        char* error = strerror(errno);   // Error occurred
        printf("shell: %s: %s\n", var[0], error);
        return 0;
    }
    else {
        int childStatus;
        waitpid(pid, &childStatus, 0);  //wait for child
        return 1;
    }
}
