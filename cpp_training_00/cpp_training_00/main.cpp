//
//  main.cpp
//  cpp_training_00
//
//  Created by 荒木田英穂 on 2022/01/10.
//

#include <iostream>
#include <vector>

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



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    test_vector_00();
    return 0;
}
