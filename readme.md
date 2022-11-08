# FunctionForwarder

the principle of the Function Forwarder is to treat Functions the same as in haskell.

Example: let's admit a function as follow; int -> float -> std::string -> std::string in your current scope you can only give it a std::string and a int.
The function forwarder will return you a std::function as follows: float -> std::string.

In simpler terms you give it a function with an incomplete set of arguments and it will return you an std::function who ask only for the missing arguments. 