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
    Matrix() = default;

    T getDefaultValue(){ return defaultValue; }
    using row = std::uintmax_t;
    using column = Column<T, defaultValue>;

    std::uintmax_t size()
    {
        update();
        std::uintmax_t size_ = 0;

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
