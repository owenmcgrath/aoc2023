#include <string>
#include <iostream>
#include "one/one.h"
#include "two/two.h"
#include <functional>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

    if(argc < 2)
    {
        std::cout << "You forgot to enter a day!" << std::endl;
        return -1;
    } 
    int day = atoi(argv[1]);

    vector<function<void()>> funcs = {one::solve, two::solve};

    if(day - 1 < funcs.size())
    {
        std::cout << "Solving Day " << day << " solver" << std::endl;
        funcs[day - 1]();
    }
    else 
    {
        std::cout << " Not solved yet! " << std::endl;
    }


}