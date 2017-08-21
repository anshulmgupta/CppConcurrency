#include<iostream>
#include<thread>

using namespace std;


void thread_function(){
 
    cout << "Hello From Thread\n" << endl;

}

int main(){

    thread th(&thread_function);
    cout << "Hello World!\n" << endl;
    th.join();
    return 0;

}
