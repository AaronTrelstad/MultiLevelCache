#include <iostream>
#include "Cache.h" 

int main() {
    Cache<int, int> cache(3, 4);

    cache.put(1, 10);  
    cache.put(2, 20); 
    cache.put(3, 30);  
    cache.put(4, 40);  
    cache.put(5, 50);  
    cache.put(6, 60); 
    cache.put(7, 70); 

    std::cout << "Get key 3: " << cache.get(3) << std::endl; 
    std::cout << "Get key 4: " << cache.get(4) << std::endl; 

    return 0;
}

