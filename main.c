#include "minHeap.c"
#include <math.h>
#include <time.h>
#include <pthread.h>


pthread_t thread[2];
pthread_mutex_t mut;	//互斥锁
Heap *heap;


//执行命令所代表的操作,目前仅支持set 操作 
void  excuteCommand(Heap *heap, char action[], char key[], int value){
    if(strcmp(action, "set") == 0){
        insert(heap, key, value);        

    }else{
        printf("wrong command!\n");
    }
}

//解析用户输入的命令
void *commandParser()
{
    while(1){
        char action[50];
        char key[50]; 
        int value;

        printf("HeapTimer-> ");
        scanf("%s %s %d",&action, &key, &value);
        pthread_mutex_lock(&mut);   //对堆进行插入操作前，需要加锁
        excuteCommand(heap,action, key, value);
        pthread_mutex_unlock(&mut);
    }
    pthread_exit(NULL);
}

//定时删除过期键
void *timmer(){
    while(1)
    {   int sleepTime = 5;
        int currentMin = getMin(heap);
        int currentTime = time((time_t)NULL);
        //此处只删除最早过期的键，是为了避免当大量键在很短的一个时间段内过期时，删除键的线程持有
        //锁的时间太长，这样会一直阻塞添加键的线程
        //毕竟删除键并不是优先级最高的任务
        if(currentMin != MIN_TIMESTAMP && currentMin < currentTime){
            pthread_mutex_lock(&mut);       //获得互斥锁
            deleteMin(heap); 
            pthread_mutex_unlock(&mut);     //释放锁
        }
        
        sleep(sleepTime);
    }
    pthread_exit(NULL);
}

//创建线程
void thread_create(void)
{
    int temp;
    memset(&thread, 0, sizeof(thread));          
    /*创建线程*/
    if((temp = pthread_create(&thread[0], NULL, timmer, NULL)) != 0)       
        printf("计时器线程创建失败!\n");
    if((temp = pthread_create(&thread[1], NULL, commandParser, NULL)) != 0)  
        printf("命令解析线程创建失败");
}

//线程同步
void thread_wait(void)
{
    /*等待线程结束*/
    if(thread[0] !=0) {                  
        pthread_join(thread[0],NULL);
        printf("计时器线程已经结束\n");
    }
     if(thread[1] !=0) {               
        pthread_join(thread[1],NULL);
        printf("命令行线程已经结束\n");
    }

}

//展示信息
void showInfo(){
    int seconds = time((time_t)NULL);
    printf("命令格式：set [key] [timestamp], 设置过期时间\n");
    printf("如set tom %d\n\n", seconds+100);
    printf("Tips:当前时间戳为：%d\n", seconds);

}

int main()
{
    showInfo();

    pthread_mutex_init(&mut,NULL);		//初始化互斥锁
    heap = initHeap(INIT_HEAP_SIZE);    //初始化堆
    thread_create();
    thread_wait();
    return 0;

}

