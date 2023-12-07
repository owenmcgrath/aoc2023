#include <string>
#include <iostream>
#include "one/one.h"
#include "two/two.h"
#include "three/three.h"
#include "four/four.h"
#include "five/five.h"
#include "six/six.h"
#include "seven/seven.h"

#include <functional>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cout << "You forgot to enter a day!" << std::endl;
        return -1;
    }
    int day = atoi(argv[1]);

    vector<function<void()>> funcs = {one::solve, two::solve, three::solve, four::solve, five::solve, six::solve, seven::solve};

    if (day - 1 < funcs.size())
    {
        std::cout << "Solving Day " << day << " solver" << std::endl;
        funcs[day - 1]();
    }
    else
    {
        std::cout << " Not solved yet! " << std::endl;
    }
}