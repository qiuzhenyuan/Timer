/**类型定义**/
typedef int timestamp;
typedef struct element{         //堆中的元素
    char key[20];
    timestamp expiration;
}element;

typedef struct Heap{
    int Capicity;              //堆的容量
    int Size;                  //堆中元素的数量
    element  *Elements;       //堆中存放时间戳元素的数组
}Heap;

/**函数声明**/
int isEmpty(Heap *heap);                //检查堆中元素是否为空
int isFull(Heap *heap);                 //检查堆是否已满
void insert(Heap *heap,char key[], timestamp x);   //往堆中插入元素
timestamp getMin(Heap *heap);          //返回堆中的最小元素
Heap *initHeap(int n);

const ZERO_POSITION = 'ZERO_KEY';             //第一个元素的key值
const timestamp MIN_TIMESTAMP = -1;        //时间戳不可能小于零，这个元素可以放在elements数组的第一个位置
const int MEMORY_LEAK = 101;               //内存不足的错误代号


