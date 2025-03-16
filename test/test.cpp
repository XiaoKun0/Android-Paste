// 例子
#include <iostream>

#include "../src/Paste.hpp"

int main() {
    std::cout << "阻塞获取" << std::endl;
    std::cout << ET::Paste() << std::endl;

    std::cout << "非阻塞获取" << std::endl;
    std::string StrA;
    bool A = true;
    for (int i = 1;; i++) {
        ET::NB::Paste(&A, &StrA);  // 严格按照此方法调用

        std::cout << "正常循环中，计数 " << i << "\r" << std::flush;
        
        if (!StrA.empty()) {
            std::cout << "\n" << StrA << std::endl;
            break;
        }
    }

    return 0;
}
