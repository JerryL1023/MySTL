#include <iostream>
#include <string>

using namespace std;

template<typename T>
class eVetor{
private:
    T* _data;
    size_t _size;

public:
    eVetor(size_t size,T init = T()){
        _data = new T[size];
        for(int i = 0;i < size;i++){
            _data[i] = init;
        }
        _size = size;
    }


    ~eVetor(){

    }

    T& operator[](int index){
        return _data[index];
    }
};

int main(){
    eVetor<int> ev1(10);

    for(int i=0;i<10;i++){
        cout << ev1[i] << endl;
    }
    
    return 0;
}