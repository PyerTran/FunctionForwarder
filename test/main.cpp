/*
** Happiness/PyerTran Project, 2022
** FunctionForwarder [WSL : Ubuntu-20.04]
** File description:
** main
*/

#include "FunctionForwarder.hpp"

int fun(float y, int x, std::string str) {
    return y;
}

int main()
{
    auto ff = createForwarder(fun);
    float x = 0;
    int y = 0;
    std::string l = "DD";

    auto finalF =  ff.forwarderSimple(fun, x, y, l);

    if (finalF != nullptr) {
        std::cout << "Forwarding successfull" << std::endl;
        finalF();
    }
    std::cout << ff.getArgumentCount(fun) << std::endl;
    return 0;
}