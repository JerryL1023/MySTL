#include "../src/eVector.hpp"

//验证基础功能
int main(){
    eVector<int> ev1(10,2020);
    for(int i=0;i<10;i++){
        //验证构造函数
        ev1[i] = i;
        cout << ev1[i] << ' ';
    }
    cout << endl;
    
    eVector<int> ev2(ev1);
    for(int i=0;i < ev2.size();i++){
        cout << ev2[i] << ' ';
    }
    cout << endl;
    
    eVector<int> ev3({2,0,2,0,1,2,2,2});
    for(int i=0;i < ev3.size();i++){
        cout << ev3[i] << ' ';
    }
    cout << endl;

    eVector<int> ev4;
    cout << ev4.at(0) << endl;
    return 0;
}