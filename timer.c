

//获取当前时间
int getCurrentTime(){
    //测试用，后面再补上获取当前时间戳的代码
    return 1;
}



void Expire(Heap *heap){
    int latlyKey = getMin(heap);
    //在堆中，不断取出最小元素，若已过期，则删除，并调整堆
    //当然，redis采用的也是主动删除加懒惰删除的策略
    //所以可以对当前时间戳的个位数,加1，对9取模然后做判断，就可以控制为10秒检查一次了
    while (1){
         if(latlyKey != MIN_TIMESTAMP && latlyKey < getCurrentTime()){
            deleteMin(heap);
        }else{
             //休眠 getCurrentTime() - latlykey的时间（或者取这个值和某一固定值的max值）
            //不过本身获取最快过期元素的复杂度就是常数阶，这个优化可能不会带来多大作用
            //
            //代码略 ……
        }
    }   
}


