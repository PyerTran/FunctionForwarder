/*
** Happiness/PyerTran Project, 2022
** FunctionForwarder [WSL : Ubuntu-20.04]
** File description:
** FunctionForwarder
*/

#ifndef FUNCTIONFORWARDER_HPP_
#define FUNCTIONFORWARDER_HPP_

#include <iostream>

#include <vector>
#include <utility>
#include <memory>
#include <vector>
#include <functional>

template<class...>struct types
{
    using type=types;
};

template<class Sig> struct args;
template<class R, class...Args>
struct args<R(Args...)>:types<Args...>{};
template<class Sig> using args_t=typename args<Sig>::type;

template <typename R, typename ... Types>
constexpr size_t getArgumentCount(R(*f)(Types ...))
{
   return sizeof...(Types);
}

template <typename R, typename ... Types>
class FunctionForwarder
{
    private:
        std::vector<std::string> awaited_args;
        std::vector<std::string> given_args;
        std::vector<std::string> needed_args;

    public:

        constexpr size_t getArgumentCount(R(*f)(Types ...))
        {
           return sizeof...(Types);
        }

        template <typename ... givenTypes>
        std::function<R()> forwarderSimple(R(*f)(Types ...), givenTypes ... args) {
            std::vector<std::string> listOfGiven = { typeid(givenTypes).name()... };
            std::vector<std::string> listOfAwaited = { typeid(Types).name()... };
            for (size_t i = 0; i < listOfAwaited.size(); i += 1) {
                if (i < listOfGiven.size())
                    std::cerr << "GIVEN typename " << i << " " << listOfGiven.at(i) << std::endl;
                else {
                    std::cerr << "GIVEN out of range"<< std::endl;
                }
                std::cerr << "AWAITED typename " << i << " " << listOfAwaited.at(i) << std::endl;
            }
            for (int i = 0; i < listOfAwaited.size(); i += 1) {
                if ((std::find(listOfGiven.begin(), listOfGiven.end(), listOfAwaited[i])==listOfGiven.end())) {
                    return std::function<R()>(nullptr);
                }
            }
            std::function<R()> res = [=] () {
                return f(args...);
            };
            return res;
        }

        template <typename T, typename ... givenTypes>
        std::function<T> forwarderJumbo(givenTypes ... args) {
            std::vector<std::string> given = { typeid(givenTypes).name()... };
            bool found = false;

            for (int i = 0; given.size(); i += 1) {
                found = false;
                for (int j = 0; this->awaited_args.size(); j += 1) { 
                    if (given[i].compare(this->awaited_args[j]) == 0) {
                        found = true
                        break;
                    }    
                }
                if (!found) {
                    this->needed_args.push_back(this->awaited_args[j]);
                }
            }
            // cant make another arg pack, paradox in the return value
            std::function<T> res = [=] () {

            };
        }

        FunctionForwarder(R(*f)(Types ...)) {
            this->awaited_args = { typeid(Types).name()... };
        }

        ~FunctionForwarder() {

        }
};

template <typename R, typename ... Types>
FunctionForwarder<R, Types ...> createForwarder(R(*f)(Types ...)) {
    FunctionForwarder<R, Types ...> ff (f);

    return ff;
}

#endif /* !FUNCTIONFORWARDER_HPP_ */
