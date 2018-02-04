/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <memory>
#include <tuple>
#include "Last.h"

template<typename T, T defaultValue>
class Matrix : public Last<T, defaultValue>
{
public:
    using row = index_type;
    using column = Intermediary<T, defaultValue>;
//    using return_type = std::tuple<size_type, size_type, T>;
//    class iterator
//    {
//    public:
//        using map_iterator = typename std::map<row, column>::iterator;
//        iterator(map_iterator it)
//        {
//            map_it = it;
//            col_it = map_it->second.begin();
//        }

//        iterator(const iterator& it)
//        {
//            map_it = it.map_it;
//        }

//        ~iterator() = default;

//        bool operator==(const iterator& it) const
//        {
//            return map_it == it.map_it;
//        }
//        bool operator!=(const iterator& it) const
//        {
//            return map_it != it.map_it;
//        }

//        iterator& operator++() noexcept
//        {
//            if(col_it != map_it->second.end())
//                col_it++;

//            if(col_it == map_it->second.end())
//            {
//                map_it++;
//                col_it = map_it->second.begin();
//            }
//            return *this;
//        }

//        iterator operator++(int) noexcept
//        {
//            auto tmp = *this;
//            if(col_it != map_it->second.end())
//                col_it++;

//            if(col_it == map_it->second.end())
//            {
//                map_it++;
//                col_it = map_it->second.begin();
//            }
//            return tmp;
//        }

//        iterator& operator--() noexcept
//        {
//            if(col_it != map_it->second.rbegin())
//                col_it--;

//            if(col_it == map_it->second.rbegin())
//            {
//                map_it--;
//                col_it = map_it->second.rend();
//            }
//            return *this;
//        }

//        iterator operator--(int) noexcept
//        {
//            auto tmp = *this;
//            if(col_it != map_it->second.rbegin())
//                col_it--;

//            if(col_it == map_it->second.rbegin())
//            {
//                map_it--;
//                col_it = map_it->second.rend();
//            }
//            return tmp;
//        }

//        return_type operator*() const noexcept
//        {
//            return return_type(map_it->first, col_it->first, col_it->second);
//        }
//        pointer operator->() const noexcept
//        {
//            return &pNode->data;
//        }

//        map_iterator map_it;
//        typename column::column_iterator col_it;
//    };

//    iterator begin()
//    {
//        return iterator(map.begin());
//    }

//    iterator end()
//    {
//        return iterator(map.end());
//    }

    Matrix() = default;

    T getDefaultValue(){ return defaultValue; }

    index_type size()
    {
//        update();
//        size_type size_ = 0;

//        for(auto& elem : map)
//        {
//            size_ += elem.second.size();
//        }
//        if(next)
//            size_ += next->size();

//        return size_;
    }

    void update()
    {
//        col_.update();
//        savePreviousData();
//        eraseData();
    }
};
