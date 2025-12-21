#include <iostream>
#include <string>
#include <sstream>


using namespace std;

template<typename T>
class eVector{
private:
    T* data_;//存放数据
    size_t size_;//存在的数据个数
    size_t capacity_;//内存容量
    
    void checkRange(size_t index){
        if(index >= size_){
            stringstream ss;
            ss << "out of range , index: " << index << ", size = " << size_;
            throw out_of_range(ss.str());
        }
    }
public:
    eVector() : data_(nullptr),size_(0),capacity_(0){}

    eVector(size_t size,T init = T()) : data_(new T[size]),size_(size),capacity_(size_){
        std::cout << "eVector(size_t size,T init = T())" << std::endl;
        for(size_t i = 0;i < size;i++){
            data_[i] = init;
        }
    }

    eVector(const eVector<T> &other) : data_(new T[other.size()]),size_(other.size()),capacity_(other.capacity_){
        std::cout << "eVector(eVector<T> &other)" << std::endl;
        for(size_t i=0;i<other.size();i++){
            data_[i] = other[i];
        }
    }

    eVector(const initializer_list<T> &init) : data_(new T[init.size()]),size_(0),capacity_(init.size()){
        std::cout << "eVector(initializer_list<T> init)" << std::endl;
        for(T elem : init){
            data_[size_++] = elem;
        }
    }

    ~eVector(){
        delete[] data_;
    }

    // 工具函数
    // 后置const表示 函数内部不会修改对象非静态成员变量
    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void clear(){
        size_ = 0;
    }

    /* A.访问方式 */

    //可修改版本
    T& operator[](size_t index){
        return data_[index];
    }

    //只读版本 
    //前置const是因为返回的是引用 后置const表示不修改对象
    //notice: 由于指针的特殊性，data_为一个地址，地址不可变，但地址中存储的数据可变
    const T& operator[](size_t index) const{
        return data_[index];
    }

    //size标记的才是可以访问的元素，此外即使分配了内存也不属于可以安全访问的元素
    T& at(size_t index){
        checkRange(index);
        return data_[index];
    }

    const T& at(size_t index) const{
        checkRange(index);
        return data_[index];
    }
    /* B.动态扩容 */
    //reserve : 填充capacity_字段 形成数据迁移
    void reserve(size_t newCapacity){
        //如果现有容量大于预留容量 直接返回
        if(newCapacity <= capacity_){
            return;
        }

        //预留容量大于现有容量
        T* newdata_ = new T[newCapacity];
        for(size_t i=0;i<size_;i++){
            newdata_[i] = data_[i];
        }
        delete[] data_;//释放旧内存
        data_ = newdata_;

        capacity_ = newCapacity;
    }

    //resize:填充size_字段，将数据填入
    //覆盖原有数据版本
    void resize(size_t newSize,T init = T()){
        while(capacity_ < newSize){
            //进行扩容
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCapacity);
        }

        //在有足够空间的前提下
        for(size_t i=0;i<newSize;i++){
            data_[i] = init;
        }
        size_ = newSize;
    }

    void push_back(T elem){
        //相等时就扩容
        if(capacity_ == size_){
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCapacity);
            //reserve(capacity_ * 2);
            //0*2 = 0 无效扩容
        }
        data_[size_++] = elem;
    }

    //应该返回副本，所以不能用引用
    T pop(){
        if(size_ == 0){
            throw std::out_of_range("eVector is empty! Can not pop()");
        }        
        
        //当size_为1时，0才是可访问下标
        return data_[--size_];
    }

    /* C.迭代器 */
    class iterator{
    private:
        T *ptr_;
        
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() : ptr_(nullptr){}

        iterator(T* ptr) : ptr_(ptr){}

        //!=
        bool operator!=(const iterator& other) const{
            return ptr_ != other.ptr_;
        }

        bool operator==(const iterator& other) const{
            return ptr_ == other.ptr_;
        }

        //仅仅适配eVector迭代器的比较运算符
        //sort函数中，使用小于运算符来判断迭代器的前后关系
        bool operator<(const iterator& other) const{
            return ptr_ < other.ptr_;//并不代表值的大小比较，类似于下标比较
        }

        //引用确保 可以通过迭代器修改具体的值
        T& operator*(){
            return *ptr_;
        }

        T* operator->(){
            return ptr_;
        }

        //前置的++ 返回的是自身,可以避免一次临时对象的生成
        iterator& operator++(){
            ptr_++;
            return *this;
        }

        //后置++ 在括号中加上int
        //返回的是 递增前的副本
        iterator operator++(int){
            iterator tmp = *this;
            ptr_++;
            return tmp;
        }

        iterator operator--(){
            ptr_--;
            return *this;
        }

        iterator operator--(int){
            iterator tmp = *this;
            ptr_--;
            return tmp;
        }

        iterator operator-(size_t n){
            return iterator(ptr_ - n);
        }

        iterator operator+(size_t n){
            return iterator(ptr_ + n);
        }
        
        //+= 实现自递增 避免返回拷贝
        iterator operator+=(difference_type n){
            ptr_ += n;
            return *this;
        }

        size_t operator-(const iterator& other) const{
            return ptr_ - other.ptr_;
        }
    };

    //begin和end必须是值传递
    iterator begin() const{
        return iterator(data_);
    }

    iterator end() const{
        return iterator(data_ + size_);
    }

    /* D.插入和删除 */
    iterator insert(iterator pos,const T& value){
        size_t index = pos - begin();

        if(size_ == capacity_){
            size_t newCapcity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCapcity);
        }

        for(size_t i = size_;i > index;i--){
            data[i]  = data[i-1];
        }

        data[index] = value;
        size_++;

        return iterator(begin() + index);
    }

    iterator erase(iterator pos){
        if(pos == end())
            return end();

        size_t index = pos - begin();
    }

};


