//
//  main.cpp
//  cpp_training_02
//
//

#include <iostream>

#include <random>
#include <vector>
#include <chrono>
#include <execution>


const size_t DataSize = 5'000'000;
const int numLoop = 10;

void test_parallel_sort(void)
{
    std::random_device randd;

    // generate some random doubles:
    std::cout << "Test " << DataSize << std::endl;
    std::vector<double> Data(DataSize);
    for (auto& d : Data) {
        d = static_cast<double>(randd());
    }
    
    for (int i = 0; i < numLoop; i++) {
        std::vector<double> SortData(Data);
        const auto startTime = std::chrono::high_resolution_clock::now();
        std::sort(SortData.begin(), SortData.end());
        const auto endTime = std::chrono::high_resolution_clock::now();
        
        auto d = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count();
        
        std::cout << d << std::endl;
    }

#if 0
    for (int i = 0; i < numLoop; i++) {
        std::vector<double> SortData(Data);
        const auto startTime = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, SortData.begin(), SortData.end());
        const auto endTime = std::chrono::high_resolution_clock::now();
        
        auto d = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count();
        
        std::cout << d << std::endl;
    }
#endif

}

void print_vec_00(std::vector<int> v)
{
    for (int val : v) {
        std::cout << val << std::endl;
    }

}

void print_vec_01(std::vector<int>& v)
{
    for (int val : v) {
        std::cout << val << std::endl;
    }

}



void test_vector_00(void)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 99};
    
    for (int val : v) {
        std::cout << val << std::endl;
    }
    
    print_vec_00(v);
    print_vec_01(v);
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //test_parallel_sort();
    test_vector_00();
    
    
    return 0;
}
