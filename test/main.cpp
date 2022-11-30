/*
** Happiness/PyerTran Project, 2022
** FunctionForwarder [WSL : Ubuntu-20.04]
** File description:
** main
*/

#include "FunctionForwarder.hpp"

int fun(float y, int x, std::string str) {
    return 4;
}

int main()
{
    auto ff = createForwarder(fun);
    int y = 0;
    std::string l = "DD";

    auto finalF =  ff.forwarderSimple(fun, y, y, l);

    if (finalF != nullptr) {
        std::cout << "Forwarding successfull" << std::endl;
        finalF();
    }
    std::cout << ff.getArgumentCount(fun) << std::endl;
    return 0;
}