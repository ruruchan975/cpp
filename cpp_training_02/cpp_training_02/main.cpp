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
#include <memory>
#include <fstream>

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


void test_shared_ptr_sub00(std::vector<std::shared_ptr<int>> v)
{
    std::cout << "test_shared_ptr_sub00" << std::endl;
    for (std::shared_ptr<int> x : v) {
        std::cout << *x << std::endl;
    }
}


void test_shared_ptr(void)
{
    std::shared_ptr<int> ps = std::make_shared<int>(20);
    std::unique_ptr<int> pu = std::make_unique<int>(100);
    std::unique_ptr<int> pui;
    std::shared_ptr<int> psi;
    
    //pui = pu;
    psi = ps;
    
    std::cout << *ps << std::endl;
    std::cout << *psi << std::endl;
    std::cout << *pu << std::endl;
    
    std::vector<std::shared_ptr<int>> v;
    std::shared_ptr<int> ps0 = std::make_shared<int>(99);
    v.push_back(ps);
    v.push_back(ps0);
    v.push_back(psi);
    v.push_back(ps0);
    *psi = 30;
    
    test_shared_ptr_sub00(v);
    
    
}


void test_fstream_00(void)
{

    std::ofstream ofs("sample.txt");
    ofs << "Sample" << 19 << std::endl;
    ofs.close();
    
    
    std::ifstream ifs("sample.txt");
    if (ifs) {
        if (ifs) {
            std::string s;
            int i;
            ifs >> s >> i;
            
            std::cout << s << std::endl;
            std::cout << i << std::endl;
            
        }
        std::cout << "s = " << s << std::endl;
        std::cout << "i = " << i << std::endl;
    } else {
        std::cerr << "I cannot open " << std::endl;
    }
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //test_parallel_sort();
    //test_vector_00();
    //test_shared_ptr();
    test_fstream_00();
    
    
    return 0;
}
