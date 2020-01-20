//在一个高可用的软件中，如果我们仅仅单纯的向操作系统去申请内存，当出现内存不足时就退出软件，是明显不合理的。
// 应该考虑在内存不足的时候，考虑如何管理并且优化自己已经使用的内存，这样才能使得软件更加可用。
// 实现一个内存池，并且使用一个栈结构来测试我们的内存池提供的分配性能。
'''
每一次进行内存分配，就会消耗一次分配内存的时间，设这个时间为 T，那么进行 n 次分配总共消耗的时间就是 nT；
如果我们一开始就确定好我们可能需要多少内存，那么在最初的时候就分配好这样的一块内存区域，当我们需要内存的时候，
直接从这块已经分配好的内存中使用即可，那么总共需要的分配时间仅仅只有 T。当 n 越大时，节约的时间就越多。
'''
#include <iostream>
#include <cassert>
#include <ctime> // clock()
#include <vector>
#include "MemoryPool.hpp"  //MemoryPool<T>
#include "StackAlloc.hpp" //StackAlloc<T, Alloc>
using namespace std;
//插入元素个数 
#define ELEMS 10000000
//重复次数
#define REPS 100

int main()
{
    clock_t start;

    //使用STL 默认分配器
    StackAlloc<int,allocator<int>> stackDefault;
    start = clock();
    for(int j = 0;j<REPS; j++)
    {
        assert(stackDefault.empty());
        for(int i = 0;i<ELEMS;i++)
            stackDefault.push(i);
        for(int i =0;i<ELEMS;i++)
            stackDefault.pop();
    }
    cout<<"Default Allocator Time: ";
    cout<<(((double)clock() - start)/CLOCKS_PER_SEC)<<endl;

    //使用内存池
    StackAlloc<int, MemoryPool<int>> stackPool;
    start = clock();
    
}