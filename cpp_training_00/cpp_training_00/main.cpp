//
//  main.cpp
//  cpp_training_00
//
//

#include <iostream>
#include <vector>
#include <queue>
#include <future>

void test_vector_00(void)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    decltype(v)::iterator it = std::find(v.begin(), v.end(), 3);
    if (it != v.end()) {
        std::cout << *it << std::endl;
    
    } else {
        std::cout << "no" << std::endl;

    }
}

void test_queue_00(void)
{
    std::queue<int> q;
    q.push(10);
    q.push(13);
    q.push(16);
    
    while (!q.empty()) {
        std::cout << q.front() << std::endl;
        q.pop();
    }
}

void test_queue_01(void)
{
    std::queue<std::shared_ptr<int>> q;
    q.push(std::make_shared<int>(10));
    q.push(std::make_shared<int>(13));
    q.push(std::make_shared<int>(16));
    
    while (!q.empty()) {
        std::shared_ptr<int> ref = q.front();
        std::cout << *ref << std::endl;
        q.pop();
    }
}

int parallel_add(int a, int b)
{
    return a+b;
}

void test_feature_00(void)
{
    std::future<int> f1 = std::async(std::launch::deferred | std::launch::async, parallel_add, 5, 6 );
    int a = parallel_add(3, 6);
    
    std::cout << a + f1.get() << std::endl;
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //test_vector_00();
    //test_queue_00();
    //test_queue_01();
    test_feature_00();
    
    return 0;
}
