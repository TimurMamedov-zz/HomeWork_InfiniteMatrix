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

    }

    column& operator[](row index)
    {
        savePreviousValue();

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

    void savePreviousValue()
    {
        col_.eraseData();
        col_.savePreviousData();
        for(auto it = col_.begin(); it != col_.end(); ++it)
        {
            if(it->second != defaultValue)
            {
                map.emplace(index_, col_);
                col_[it->first] = defaultValue;
                col_.eraseData();
                break;
            }
        }
    }
};
