#include <tuple>
#include <iostream>

template <typename ...Params>
void function(int n, Params const& ... params) {
    constexpr int size = sizeof...(Params);
    auto tuple = std::forward_as_tuple(params...);

    if (n > size - 1) {
        throw std::out_of_range("your n is too large");
    }

    [&]<std::size_t ...I>(std::index_sequence<I...>){ //we do this to get access to the I (c++20)
        (..., // this is a fold-expression (c++17)
            [&](){ // we can only expand simple stuff so we need to wrap
                   // the complex stuff in antoher lamba.
                if(n == I) { // this is the actual switch
                    std::cout << std::get<I>(tuple) << std::endl;
                }
            }()
        );
    }(std::make_index_sequence<size>{});
}


int main(){
    function(2, "cat", "dog", 42, "wolf");
    function(1, "cat", "dog", 42, "wolf");
    function(55, "cat", "dog", 42, "wolf");
}
