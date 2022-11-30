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

//template <typename Fun, typename ... Types>
//std::function<decltype(Fun)(Types)>

//template <typename Fun, typename ... Types>
//std::function<decltype(Fun())> FunctionForwarder(Fun f,Types ... arg)
//{
//    int given_n_arg = sizeof...(Types);
//    size_t awaits_n_arg = getArgumentCount(f);
//    std::cerr << "functions was given: " << given_n_arg << " and awaited: "<< awaits_n_arg << std::endl;
//}

//template <typename R, typename ... Types>
//class FunctionForwarder
//{
//    private:
//        constexpr size_t getArgumentCount(R(*f)(Types ...))
//        {
//           return sizeof...(Types);
//        }
//
//        int number_args;
//    public:
//        FunctionForwarder(R(*f)(Types ...)) {
//            this->number_args = getArgumentCount(f);
//        }
//        ~FunctionForwarder() {
//        }
//
//        template <typename ... givenTypes>
//        std::function<R()> forwarder(R(*f)(Types ...), givenTypes ... args) {
//            std::vector<std::string> listOfGiven = { typeid(givenTypes).name()... };
//            std::vector<std::string> listOfAwaited = { typeid(Types).name()... };
//            for (size_t i = 0; i < listOfGiven.size(); i += 1) {
//                std::cerr << "typename " << i << " " << listOfGiven.at(i) << std::endl;
//            }
//        }
//};
//

template <typename R, typename ... Types>
class FunctionForwarder
{
    private:
        using returnType = void;
        using argTypes = void;

        std::function<returnType(argTypes)> func = 0;
        
        //constexpr size_t getArgumentCount(R(*f)(Types ...))
        //{
        //   return sizeof...(Types);
        //}
//
        //template <typename ... givenTypes>
        //std::function<R()> forwarder(R(*f)(Types ...), givenTypes ... args) {
        //    std::vector<std::string> listOfGiven = { typeid(givenTypes).name()... };
        //    std::vector<std::string> listOfAwaited = { typeid(Types).name()... };
        //    for (size_t i = 0; i < listOfGiven.size(); i += 1) {
        //        std::cerr << "typename " << i << " " << listOfGiven.at(i) << std::endl;
        //    }
        //}
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
                if (i < listOfAwaited.size())
                    std::cerr << "GIVEN typename " << i << " " << listOfGiven.at(i) << std::endl;
                else {
                    std::cerr << "GIVEN out of range"<< std::endl;
                }
                std::cerr << "AWAITED typename " << i << " " << listOfGiven.at(i) << std::endl;
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

        FunctionForwarder(R(*f)(Types ...)) {
            //this->returnType = R;
            //this->argTypes = Types;
            //this->func = f;
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
