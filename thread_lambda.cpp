#include<iostream>
#include<thread>

using namespace std;


int main(){

    thread th([]()
    {
        cout << "Hello From Thread\n";     
    });

    cout << "Hello World!\n";
    th.join();
    return 0;

}
