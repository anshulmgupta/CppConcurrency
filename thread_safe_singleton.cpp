#include <iostream>
#include <mutex>
using namespace std;

class Singleton{
    static Singleton *instance;
    static mutex m_;
    Singleton(){}
public:
    static Singleton* get_instance(){
        if(instance == nullptr){
            m_.lock();
            if(instance == nullptr){
                instance = new Singleton();
            }
            m_.unlock();
        }
        return instance;
    }
    void print(){
        cout << "Yayyy!!!" << endl;
    }
};

Singleton * Singleton::instance = nullptr;
mutex Singleton::m_;

int main(){
    Singleton *obj = Singleton::get_instance();
    obj->print();
}
