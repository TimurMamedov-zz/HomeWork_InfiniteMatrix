/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <memory>
#include "Column.h"

template<typename T, T defaultValue>
class Matrix
{
public:
//    class iterator
//    {
//    public:
//        iterator()
//        {

//        }

//        iterator(const iterator& it)
//        {

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
//            if()
//                pNode = pNode->next;
//            return *this;
//        }

//        iterator operator++(int) noexcept
//        {
//            auto tmp = *this;
//            return tmp;
//        }

//        iterator& operator--() noexcept
//        {
//            return *this;
//        }

//        iterator operator--(int) noexcept
//        {
//            auto tmp = *this;
//            return tmp;
//        }

        //            reference operator*() const noexcept
        //            {
        //                return pNode->data;
        //            }
        //            pointer operator->() const noexcept
        //            {
        //                return &pNode->data;
        //            }
//        std::map<row, column>::iterator map_it;
//        column::iterator col_it;
//    };

    Matrix() = default;

    T getDefaultValue(){ return defaultValue; }
    using row = size_type;
    using column = Column<T, defaultValue>;

    size_type size()
    {
        update();
        size_type size_ = 0;

        for(auto& elem : map)
        {
            size_ += elem.second.size();
        }

        return size_;
    }

    void update()
    {
        col_.update();
        savePreviousData();
        eraseData();
    }

    column& operator[](row index)
    {
        update();

        auto col = map.find(index);
        if(col == map.end())
        {
            index_ = index;
            return col_;
        }
        return map[index];
    }

private:
    std::unique_ptr<Matrix<T, defaultValue> > next;
    std::map<row, column> map;
    column col_;
    row index_;

    void savePreviousData()
    {
        if(col_.size())
        {
            if(col_.getLastElement() != defaultValue)
            {
                map.emplace(index_, col_);
                col_.eraseLastElement();
            }
        }
    }

    void eraseData()
    {
        if(map.find(index_) != map.end())
        {
            if(!map[index_].size())
            {
                map.erase(index_);
            }
        }
    }
};
