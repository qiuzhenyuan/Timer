#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "minHeap.h"
#include <string.h>

//检查堆是否为空
int isEmpty(Heap *heap){
    return heap->Size == 0 ? 1 : -1;
}

//检查堆是否已满
int isFull(Heap *heap){
    int i = heap->Size == heap->Capicity ? 1 : -1;
    return i;
}

//往堆中插入元素
void insert(Heap *heap, char key[],timestamp x ){
    if(heap == NULL){
        printf("空指针");
        return;
    }
    if(isFull(heap)== 1){
        printf("堆已满,不能放入新的键值");
        return;
    }
    int i = ++heap->Size;
    int parent = i/2;
    while((i != 1) && x < heap->Elements[parent].expiration){   
        strcpy(heap->Elements[i].key,  heap->Elements[parent].key);         //父节点下移
        heap->Elements[i].expiration =  heap->Elements[parent].expiration;  //父节点下移
        i = parent;         //父节点位置座位子节点
        parent /= 2;        //求父结点
    }
    //找到合适的位置，把元素放进去
    strcpy(heap->Elements[i].key, key);
    heap->Elements[i].expiration = x;  
    printf("插入了%s,过期时间为%d, 位置为%d,堆容量为%d,堆中有元素%d个\n",key, x, i,
            heap->Capicity, heap->Size);
   //满足条件则扩大堆容量 
    if(heap->Capicity < heap->Size*2)
        expandHeap(heap);
}

//初始化一个容量为n的堆
Heap * initHeap(int n){
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->Size = 0;
    heap->Capicity = n;
    heap->Elements = malloc(sizeof(element)*(n+1));
    if(heap->Elements == NULL){
        exit(MEMORY_LEAK);
    }
    heap->Elements[0].expiration = MIN_TIMESTAMP;   //Elements数组中，第一个元素的过期时间是MINTIMESTAMP
    return heap;
}


//删除最小的元素,返回该元素值
int  deleteMin(Heap *heap ){
    if(heap == NULL){
        printf("空指针");
        return MIN_TIMESTAMP;
    }
    if(isEmpty(heap) == 1){
        printf("堆已经为空");
        return MIN_TIMESTAMP;
    }
    int i,child;
    element minElement = heap->Elements[1];
    element lastElement = heap->Elements[heap->Size--];
    for (i=1; i*2 <= heap->Size; i=child){
        child = i*2;
        //找出更小的一个孩子
        if(child < heap->Size && 
                heap->Elements[child].expiration > heap->Elements[child+1].expiration)
            child++;
        if(lastElement.expiration <= heap->Elements[child].expiration)
            break;
        heap->Elements[i].expiration = heap->Elements[child].expiration;  //小的孩子往上走
        strcpy(heap->Elements[i].key, heap->Elements[child].key);
    }
    strcpy(heap->Elements[i].key,lastElement.key); 
    heap->Elements[i].expiration = lastElement.expiration;
    //检查元素数量，小于容量的1/6，则缩小堆的容量
    if(heap->Capicity > heap->Size * 6 && heap->Capicity > INIT_HEAP_SIZE)
        shrinkHeap(heap);
    return minElement.expiration;
}

//获取最快过期的元素,堆为空时，返回Elements[0]
timestamp getMin(Heap *heap){
    if(isEmpty(heap) == 1){
        return MIN_TIMESTAMP;
    }
    return heap->Elements[1].expiration;
}

//扩大堆
void expandHeap(Heap *heap){
    heap->Capicity = 2 * heap->Capicity;
    element *newEle = malloc(sizeof(element) * heap->Capicity);
    int i;
    for(i = 0; i < heap->Size; i++){
        newEle[i] = heap->Elements[i];
    }
    element *oldEle = heap->Elements;
    heap->Elements = newEle;
    free(oldEle);
    printf("堆容量调整,扩大为：%d\nHeapTimer->", heap->Capicity);
}

//缩小堆
void shrinkHeap(Heap *heap){
    heap->Capicity =  heap->Capicity / 2;
    element *newEle = malloc(sizeof(element) * heap->Capicity);
    int i;
    for(i = 0; i < heap->Size; i++){
        newEle[i] = heap->Elements[i];
    }
    element *oldEle = heap->Elements;
    heap->Elements = newEle;
    free(oldEle);
    printf("堆容量调整,缩小为：%d\nHeapTimer->", heap->Capicity);


}
