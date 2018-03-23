//#include "minHeap.c"

void TestPrintHeap(Heap *heap);
int TestGetMin(Heap *heap);
void TestInsertHeap(Heap *heap);
void TestDeleteMin(Heap *heap);

const int  TEST_COUNT =  10;


void TestInitHeap(){
    Heap *heap = initHeap(TEST_COUNT);
    printf("初始化完成，堆大小为%d", heap->Size);
    printf("堆容量为：%d", heap->Capicity);
    TestInsertHeap(heap);
    TestPrintHeap(heap);
    TestGetMin(heap);
    TestDeleteMin(heap);
}

void TestInsertHeap(Heap *heap){
    int space = heap->Capicity - heap->Size;
    while(space > 0){
        char test[]="test";
        insert(heap, test, space);
        space = heap->Capicity - heap->Size;
    }
}

void TestDeleteMin(Heap *heap){
    int i=TEST_COUNT;
    while(i > 0){
        int item = deleteMin(heap);
        printf("删除了%d\n", item);
        --i;
    }
    TestPrintHeap(heap);  
}

int TestGetMin(Heap *heap){
    timestamp tsp = getMin(heap);
    printf("%d", tsp);
    return tsp;
}

//打印堆中的元素
void TestPrintHeap(Heap *heap){
    int i = 1;
    printf("堆的元素为：");
    while(i <= heap->Size){
        printf("{%s: %d } ", heap->Elements[i].key,heap->Elements[i].expiration);
        ++i;
    }
    printf("\n");
}
