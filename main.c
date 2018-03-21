#include "minHeap.c"
#include "UnitTest.c"
#include <time.h>
#include <pthread.h>

pthread_t CmdThread;        //命令交互线程
pthread_t timmerThread;     //定时删除过期键的线程
pthread_mutex_t mut;        //互斥锁


int ia = 6;
void *run_timer(){
    while(ia--){
    printf("run");
    printf("after");
    sleep(1);
    }
    pthread_exit(NULL);
}    


/**
 *根据用户输入的指令，进行处理
 *目前只支持"set" 指令
 */
int excuteCommand(Heap *heap, char action[], char key[], int value){
    if(strcmp(action, "set") == 0){
        insert(heap, key, value);        

    }else{
        printf("wrong command!");
    }
}

/*
 *解析从控制台输入的命令，
 并判断命令的有效性
 */
void parseCommand(Heap *heap){
    char action[50];
    char key[50]; 
    int value;

    do{
        char action[50];
        char key[50]; 
        int value;

        printf("HeapTimer-> ");
        scanf("%s %s %d",&action, &key, &value);
        excuteCommand(heap,action, key, value);
        printf("\n");
    }while(1);
}

void main(){
    memset(&timmerThread, 0, sizeof(timmerThread));
    if(pthread_create(&timmerThread, NULL, run_timer, NULL) != 0){
        printf("创建线程失败");
    }
    pthread_join(timmerThread, NULL);
    //int seconds;
    //seconds = time((time_t*)NULL);
    //printf("您好，当前时间戳为：%d\n", seconds);
    //Heap *heap = initHeap(50);
    //parseCommand(heap); 
    //TestInitHeap();
}



