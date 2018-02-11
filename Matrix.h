/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <memory>
#include <utility>
#include <map>
#include <tuple>

template<std::size_t, class T>
using T_ = T;

struct Indexes
{
    template<typename T, std::size_t dimension>
    static auto gen()
    {
        return Indexes::gen<T>(std::make_index_sequence<dimension>{});
    }

    template<typename T, std::size_t... Is>
    static auto gen(std::index_sequence<Is...>)
    {
        return std::tuple<T_<Is, T>...>{};
    }
};

template<typename T, T defaultValue, std::size_t dimension>
class Matrix;

template<std::size_t temp_dim, typename T, T defaultValue, std::size_t dimension>
struct Intermediary;

template<typename T, T defaultValue, std::size_t dimension>
struct Intermediary<dimension, T, defaultValue, dimension>
{
    using index_type = decltype(Indexes::gen<std::size_t, dimension>());
    Intermediary(Matrix<T, defaultValue, dimension>& matr, index_type curr_index):matr_(matr), current_index(curr_index){}

    Intermediary& operator=(const T& value)
    {
        auto pair = matr_.find(current_index);
        if (value != defaultValue)
        {
            if (pair == matr_.end())
                matr_.emplace(current_index, value);
            else
                pair->second = value;
        }
        else if (pair != matr_.end())
            matr_.erase(pair);
        return *this;
    }

    bool operator ==(const T& value)
    {
        auto pair = matr_.find(current_index);
        if(value != defaultValue)
        {
            if(pair != matr_.end())
            {
                return pair->second == value;
            }
            else
                return false;
        }
        else if(pair != matr_.end())
        {
            return false;
        }
        else
            return true;
    }

    operator T() const
    {
        auto pair = matr_.find(current_index);
        if (pair == matr_.end())
            return defaultValue;
        else
            return pair->second;
    }

private:
    Matrix<T, defaultValue, dimension>& matr_;
    index_type current_index;
};

template<std::size_t temp_dim, typename T, T defaultValue, std::size_t dimension>
struct Intermediary
{
    using index_type = decltype(Indexes::gen<std::size_t, temp_dim>());
    Intermediary(Matrix<T, defaultValue, dimension>& matr, index_type curr_index):matr_(matr), current_index(curr_index){}

    Intermediary<temp_dim + 1, T, defaultValue, dimension> operator [](std::size_t index)
    {
//        if(temp_dim + 1 != dimension)
        return Intermediary<temp_dim + 1, T, defaultValue, dimension>(matr_, std::tuple_cat(current_index, std::make_tuple(index)));
//        else
//            return Intermediary<dimension, T, defaultValue, dimension>(matr_, std::tuple_cat(current_index, std::make_tuple(index)));
    }

private:
    Matrix<T, defaultValue, dimension>& matr_;
    index_type current_index;
};

template<typename T, T defaultValue, std::size_t dimension = 2>
class Matrix final : public std::map<decltype(Indexes::gen<std::size_t, dimension>()), T>
{
public:
    using index = decltype(Indexes::gen<std::size_t, dimension>());
    Intermediary<1, T, defaultValue, dimension> operator [](std::size_t index)
    {
        return Intermediary<1, T, defaultValue, dimension>(*this, std::make_tuple(index));
    }

    Intermediary<dimension, T, defaultValue, dimension> operator [](index ind)
    {
        return Intermediary<dimension, T, defaultValue, dimension>(*this, ind);
    }
    class iterator
        {
        public:
            using inner_iterator = typename std::map<decltype(Indexes::gen<std::size_t, dimension>()), T>::iterator;
            iterator(inner_iterator it)
            {
                iterator_ = it;
            }

            ~iterator() = default;

            bool operator==(const iterator& it) const
            {
                return iterator_ == it.iterator_;
            }

            bool operator==(const inner_iterator &inner_iterator_) const
            {
                return iterator_ == inner_iterator_;
            }

            friend bool operator==(const inner_iterator &inner_iterator_, const iterator& it)
            {
                return inner_iterator_ == it.iterator_;
            }
            bool operator!=(const iterator& it) const
            {
                return iterator_ != it.iterator_;
            }

            bool operator!=(const inner_iterator &inner_iterator_) const
            {
                return iterator_ != inner_iterator_;
            }

            friend bool operator!=(const inner_iterator &inner_iterator_, const iterator& it)
            {
                return inner_iterator_ != it.iterator_;
            }

            iterator& operator++() noexcept
            {
                iterator_++;
                return *this;
            }

            iterator operator++(int) noexcept
            {
                auto tmp = *this;
                iterator_++;
                return tmp;
            }

            iterator& operator--() noexcept
            {
                iterator_--;
                return *this;
            }

            iterator operator--(int) noexcept
            {
                auto tmp = *this;
                iterator_--;
                return tmp;
            }

            auto operator*() const noexcept
            {
                return std::tuple_cat(iterator_->first, std::make_tuple(iterator_->second));
            }

            inner_iterator iterator_;
        };

        iterator begin()
        {
            return iterator(std::map<decltype(Indexes::gen<std::size_t, dimension>()), T>::begin());
        }

        iterator end()
        {
            return iterator(std::map<decltype(Indexes::gen<std::size_t, dimension>()), T>::end());
        }
};
