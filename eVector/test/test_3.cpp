#include "../src/eVector.hpp"

//局部变量使用引用是为了减少拷贝消耗
//const + 引用 = 常量引用
// 常量引用可以绑定右值 ：临时的变量也可以绑定在引用上
// 但是常量对象 在调用成员函数的时候 成员函数必须不能具备写权限
// 后置const可以限制写权限
void process(const eVector<int> &ev){
    //std::cout << "ev.size():" << ev.size() << std::endl;
}

int main(){
    process({1,2,3});

    eVector<int> ev1 = {1,2,3};
    process(ev1);

    return 0;
}