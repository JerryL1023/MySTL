#include "../src/eVector.hpp"
#include<algorithm>
//测试迭代器

//TODO ： 找时间了解一下sort函数的写法和原理
int main(){
    eVector<int> ev1 = {1,3,4,5,1,2,-1};

    // std::cout << "iterator ev1.begin():" << ev1.begin() << std::endl;
    // std::cout << "iterator ev1.end():" << ev1.end() << std::endl;

    for(eVector<int>::iterator it = ev1.begin();it != ev1.end();it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //sort(ev1.begin(),ev1.end());
    
    //范围for循环原理：1.begin和end成员函数 2.重载*、前置++、!=
    for(auto& x : ev1){
        std::cout << x << " ";
        x = x * 10;
    }
    std::cout << std::endl;

    sort(ev1.begin(),ev1.end());
    for(auto& x : ev1){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << *max_element(ev1.begin(),ev1.end()) << std::endl;

    //指向第一个大于等于target的元素
    std::cout << *lower_bound(ev1.begin(),ev1.end(),3) << std::endl;
    return 0;
}