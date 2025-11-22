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

    eVector(size_t size,T init = T()) : data_(new T[size]),size_(size),capacity_(0){
        std::cout << "eVector(size_t size,T init = T())" << std::endl;
        for(size_t i = 0;i < size;i++){
            data_[i] = init;
        }
    }

    eVector(const eVector<T> &other) : data_(new T[other.size()]),size_(other.size()),capacity_(0){
        std::cout << "eVector(eVector<T> &other)" << std::endl;
        for(size_t i=0;i<other.size();i++){
            data_[i] = other[i];
        }
    }

    eVector(const initializer_list<T> &init) : data_(new T[init.size()]),size_(0),capacity_(0){
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
    T& at(size_t index) const{
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
    void resize(size_t newSize,T init = T()){
        while(capacity_ <= newSize){
            //进行扩容
            reserve(capacity_ * 2);
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
};


