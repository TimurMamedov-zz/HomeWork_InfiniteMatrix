/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <map>

template<typename T, T defaultValue>
class Column
{
public:
    const T& getLastElement()
    {
        if(map.find(index_) != map.end())
            return map[index_];
        return defaultValue_;
    }

    void eraseLastElement()
    {
        if(map.find(index_) != map.end())
            map.erase(index_);
    }

    void update()
    {
        eraseData();
        savePreviousData();
    }

    T& operator[](const std::uintmax_t& index)
    {
        update();

        index_ = index;
        auto it = map.find(index);
        if(it == map.end())
        {
            return defaultValue_;
        }
        return map[index];
    }

    std::uintmax_t size()
    {
        eraseData();
        savePreviousData();

        return map.size();
    }

private:
    std::map<std::uintmax_t, T> map;
    T defaultValue_ = defaultValue;
    std::uintmax_t index_ = 0;

    void savePreviousData()
    {
        if(defaultValue_ != defaultValue)
        {
            map.emplace(index_, defaultValue_);
            defaultValue_ = defaultValue;
        }
    }

    void eraseData()
    {
        if((!map.empty()) && (map.find(index_) != map.end()))
        {
            if(map[index_] == defaultValue)
            {
                map.erase(index_);
            }
        }
    }
};
