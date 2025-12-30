#include "../src/eVector.hpp"

int main(){
    eVector<int> ev1 = {1,2,3,4};
    eVector<int> ev = ev1;//拷贝构造
    eVector<int> ev2 = {2,3,4,5};//operator

    ev1 = ev2;//触发opeator =的时候 传参触发拷贝构造
    
    return 0;
}