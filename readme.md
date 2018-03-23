## 简介

用最小堆实现的定时器，模拟Redis定时删除过期键的功能。

- 用堆来保存海量键值，插入和删除最小元素的时间复杂度均为O(logn);
- 实现堆的动态扩容和缩小，元素数量大于堆容量1/2则扩容，小于1/6则缩小；
- 每隔5秒进行一次过期键检查；
- 创建了两个线程，一个用于过期检查，一个用于与前台交互（输入命令）；



## 编译&运行

```
make 
./HeapTimer.o
```



## 使用方法

```
//指定tom 的过期时间为1571993945
set tom 1571993945    
```

