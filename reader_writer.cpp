#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>

using namespace std;
using std::string;
using std::cout;
using std::endl;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::chrono::milliseconds;
using std::thread;
using std::this_thread::sleep_for;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::condition_variable;

int data = 0;
int reader_count = 0;
mutex read_lock;
mutex write_lock;
condition_variable read_cond;

void Reader(string name){
    int i = 0;
    while(i < 10){
        read_lock.lock();
        reader_count++;
        if(reader_count == 1){
            write_lock.lock();
        }
        read_lock.unlock();
        cout << "Reader " << name << " read data = " << data << endl;
        read_lock.lock();
        reader_count--;
        if(reader_count == 0){
            write_lock.unlock();
        }
        read_lock.unlock();
        i++;
    }
}

void Writer(string name){
    int i=0;
    while(i<10){
        write_lock.lock();
        data++;
        cout << "Writer " << name << " incremented data to = " << data << endl;
        write_lock.unlock();
        i++;
    }
}

void ReaderCV(string name){
    int i = 0;
    while(i < 10){
        read_lock.lock();
        reader_count++;
        read_lock.unlock();
        cout << "Reader " << name << " read data = " << data << endl;
        read_lock.lock();
        reader_count--;
        read_cond.notify_one();
        read_lock.unlock();
        i++;
    }
}

void WriterCV(string name){
    int i=0;
    while(i<10){
        write_lock.lock();
        bool done = false;
        while(!done){
            unique_lock<mutex> lock(read_lock);
            if(reader_count == 0){
                data++;
                cout << "Writer " << name << " incremented data to = " << data << endl;
                done = true;
            }
            else{
                while(reader_count != 0){
                    read_cond.wait(lock);
                }
            }
        }
        write_lock.unlock();
        i++;
    }
}

int writer_count = 0;
mutex writer_lock;
condition_variable write_cond;

void WrtPrefReaderCV(string name){
    int i = 0;
    while(i < 10){
        read_lock.lock();
        bool done = false;
        while(!done){
            unique_lock<mutex> lock(write_lock);
            if(writer_count == 0){
                cout << "Reader " << name << " read data = " << data << endl;
                done = true;
            }
            else{
                while(writer_count != 0){
                    write_cond.wait(lock);
                }
            }
        }
        read_lock.unlock();
        i++;
    }
}

void WrtPrefWriterCV(string name){
    int i=0;
    while(i<10){
        write_lock.lock();
        writer_count++;
        write_lock.unlock();
        writer_lock.lock();
        data++;
        cout << "Writer " << name << " incremented data to = " << data << endl;
        writer_lock.unlock();
        write_lock.lock();
        writer_count--;
        write_cond.notify_one();
        write_lock.unlock();
        i++;
    }
}

int main(int argc, char* argv[]) {
    thread r0(WrtPrefReaderCV, "r0");
    thread r1(WrtPrefReaderCV, "r1");
    thread w0(WrtPrefWriterCV, "w0");
    thread w1(WrtPrefWriterCV, "w1");
    sleep_for(milliseconds(10000));
    r0.join();
    r1.join();
    w0.join();
    w1.join();
    return 0;
}
