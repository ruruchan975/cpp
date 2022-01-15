//
//  main.cpp
//  cpp_training_01
//
//

#include <iostream>
#include <functional>
#include <thread>
#include <future>
#include <numeric>
#include <stdexcept>



int add(int x, int y)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
    int result = x + y;
    return result;
}

void test_task_package_00(void)
{
    std::packaged_task<int(int, int)> my_add(add);
    std::future<int> fut = my_add.get_future();
    my_add(10, 13);
    std::cout << "main thread id = " << std::this_thread::get_id() <<
    " result = " << fut.get() << std::endl;
    
}

void test_task_package_01(void)
{
    std::packaged_task<int(int, int)> my_add(add);
    std::future<int> fut = my_add.get_future();
    
    std::thread threadx(std::move(my_add), 5, 6);
    threadx.detach();
    std::cout << "detached" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "main thread id = " << std::this_thread::get_id() <<
    " result = " << fut.get() << std::endl;

}

void print_int(std::future<int>& fut)
{
    std::cout << "wait for comming data." << std::endl;
    std::cout << "v = " << fut.get() << std::endl;
}

void test_promise_00(void)
{
    std::promise<int> promise;
    std::future<int> fut = promise.get_future();
    
    std::thread print_thread(print_int, std::ref(fut));
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "set value !!" << std::endl;
    promise.set_value(10);
    
    print_thread.join();
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    test_task_package_01();
    //test_promise_00();
    return 0;
}
