
// https://stackoverflow.com/questions/42032755/perfect-forwarding-of-functions-to-build-a-function-list-class

template <typename T>
void f(T&&)
{
    std::tuple<T>{}; // (0)
    std::tuple<T&&>{}; // (1)
}

//  T is deduced as T for rvalues.
//  T is deduced as T& for lvalues.
