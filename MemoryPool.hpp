#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <climits>
#include <cstddef>

template <typename T, size_t BlockSize = 4096>
class MemoryPool
{
    public:
    //使用 typedef 简化类型书写
        typedef T* pointer;
        // 定义 rebind<U>::other 接口
        template<typename U> struct rebind {
            typedef MemoryPool<U> other;
        };
        // 默认构造，初始化所有的糟指针
        // C++11 使用了noexpert 来显示的申明此函数不会抛出异常
        MemoryPool() noexcept {
            currentBlock_ = nullptr;
            currentSlot_ = nullptr;
            lastSlot_ = nullptr;
            freeSlots_ = nullptr;
        }
        //销毁一个现有的内存池
        ~MemoryPool() noexcept;

        // 同一个时间只能分配一个对象，n和hint会被忽视
        pointer allocate(size_t n = 1, const T* hint = 0);

        //销毁指针 p指向的内存区块
        void deallocate(pointer p, size_t n = 1);

        // 调用构造函数
        template<typename U, template... Args>
        void construct(U* p, Args&&... args);

        // 销毁内存池中的对象，即调用对象的析构函数
        template<typename U>
        void destroy(U *p){
            p->~U();
        }
    private:
     //用于存储内存池中的对象糟
     // 要么被实例化为一个存放对象的糟
     // 要么被实例化为一个指向存放对象糟的糟指针
     union Slot_ {
         T element;
         Slot_* next;
     };
     // 数据指针
     typedef char* data_pointer_;
     // 对象槽
    typedef Slot_ slot_type_;
    // 对象槽指针
    typedef Slot_* slot_pointer_;

    // 指向当前内存区块
    slot_pointer_ currentBlock_;
    // 指向当前内存区块的一个对象槽
    slot_pointer_ currentSlot_;
    // 指向当前内存区块的最后一个对象槽
    slot_pointer_ lastSlot_;
    // 指向当前内存区块中的空闲对象槽
    slot_pointer_ freeSlots_;

    // 检查定义的内存池大小是否过小
    static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};
#endif //MEMORY_POOL_HPP