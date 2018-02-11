/*!
\file
\brief функции для вывода std::tuple в стандартный поток вывода
*/
#include <tuple>

template<typename Type, unsigned N, unsigned Last>
struct tuple_printer
{
    static void print(std::ostream& out, const Type& value)
    {
        out << std::get<N>(value);
        tuple_printer<Type, N + 1, Last>::print(out, value);
    }
};

template<typename Type, unsigned N>
struct tuple_printer<Type, N, N>
{
    static void print(std::ostream& out, const Type& value)
    {
        out << std::get<N>(value);
    }

};

template<typename... Types>
std::ostream& operator<<(std::ostream& out, const std::tuple<Types...>& value)
{
    tuple_printer<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(out, value);
    return out;
}
