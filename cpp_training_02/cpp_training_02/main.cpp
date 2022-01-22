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
#include <list>

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
            
            std::cout << "s = " << s << std::endl;
            std::cout << "i = " << i << std::endl;

        }
    } else {
        std::cerr << "I cannot open " << std::endl;
    }
    
}

template<typename T>
std::list<T> qs_seq(std::list<T> input)
{
    //recursive condition
    if ( input.size() < 2 )
    {
        return input;
    }

    //move frist element in the list to result list and take it as pivot value
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    //partition the input array so that t< pivot in lower part and t> pivot in upper part of input list
    auto divide_point = std::partition(input.begin(), input.end(),
        [&](T const& t)
        {
            return t < pivot;
        });

    //move lower part of the list to separate list so that we can make recursive call
    std::list<T> lower_list;
    lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

    //call the sequenctial_quick_sort recursively
    auto new_lower(qs_seq(std::move(lower_list)));
    auto new_upper(qs_seq(std::move(input)));

    //transfer all elements in to result list
    result.splice(result.begin(), new_lower);
    result.splice(result.end(), new_upper);

    return result;
}

void test_qs_00(void)
{
    std::list<int> l = {19, 71, 8, 13, 5};
    std::list<int> q = qs_seq(l);
    for (int v : q) {
        std::cout << v << "," << std::endl;
 
    }
    
    {
        
        std::list<int> xs = {4, 5, 6};
        std::list<int> ys = {1, 2, 3};
        xs.splice(xs.begin(), std::move(ys));
        for (int v : xs) {
            std::cout << v << ",";
        }
        std::cout << std::endl;
    }
    {
       std::list<int> xs = {4, 5, 6};
       std::list<int> ys = {1, 2, 3};

       xs.splice(xs.begin(), std::move(ys), ys.begin(), std::next(ys.begin(), 2));
        for (int v : xs) {
            std::cout << v << ",";
        }
        std::cout << std::endl;

     }
    {
       
        std::list<int> xs = {1, 2, 3};
        std::list<int> ys = {4, 5, 6};
        xs.splice(xs.end(), std::move(ys), ys.begin(), std::next(ys.begin(), 1));
        for (int v : xs) {
             std::cout << v << ",";
         }
         std::cout << std::endl;

      }

    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //test_parallel_sort();
    //test_vector_00();
    //test_shared_ptr();
    //test_fstream_00();
    test_qs_00();
    
    return 0;
}
