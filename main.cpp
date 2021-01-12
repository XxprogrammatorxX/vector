#include <iostream>
#include <string>
#include "vector.h"
/*
using Vector_b = Vector_base<int, std::allocator<int>>;


void print (const Vector_b& a){
    std::cerr << a.sz << "   " << a.space << "    "  << a.elem ;
    std::cerr << '\n';
}*/

int main(){    
    Vector<double> lol;
    for (int i = 0; i < 10; i++){
        lol.push_back(10 - i);
    } 
    Ha_ekpaH(lol);
    Vector<double> kek ={2};
    Ha_ekpaH(kek);
    kek.resize(5);
    Ha_ekpaH(kek);
    kek = lol;
    Ha_ekpaH(kek);
    Vector<double> xex = {5, 3.33, -6};
    Ha_ekpaH(xex);
    Vector<std::string> ooo = {"kek", "lol"};
    Ha_ekpaH(ooo);
    while (true)
    {
        Vector<std::string> v (10);
        for (int i = 0; i < 100; i++)
            v.push_back(std::string(100, 'f'));
        std::cout << v.at(v.size() - 1) << std::endl;
    }

    //std::cin >> ooo[1];
    /*Vector_b a (std::allocator<int> (), 5);
    print (a);
    Vector_b b = std::move(a);
    print (a);
    print (b);
    std::cerr << std::is_move_constructible<Vector_b>::value << '\n';*/
    int bb;
    std::cin >> bb;
    return 0;
}