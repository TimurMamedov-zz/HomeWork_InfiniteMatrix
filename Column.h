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
    class iterator
        {
        public:
            iterator() = default;

            iterator(const typename std::map<std::uintmax_t, T>::iterator& it)
            {
                map_it = it;
            }

            iterator(const iterator& it) = default;
            ~iterator() = default;

            bool operator==(const iterator& it) const
            {
                return map_it == it.map_it;
            }
            bool operator!=(const iterator& it) const
            {
                return map_it != it.map_it;
            }

            iterator& operator++() noexcept
            {
                map_it++;
                return *this;
            }

            iterator operator++(int) noexcept
            {
                auto tmp = *this;
                map_it++;
                return tmp;
            }

            iterator& operator--() noexcept
            {
                map_it--;
                return *this;
            }

            iterator operator--(int) noexcept
            {
                auto tmp = *this;
                map_it--;
                return tmp;
            }
            typename std::map<std::uintmax_t, T>::iterator map_it;
        };

    const T& getLastElement()
    {
        if(map.find(index_) != map.end())
            return map[index_];
        return defaultValue_;
    }

    iterator begin()
    {
        return iterator(map.begin());
    }

    iterator end()
    {
        return iterator(map.end());
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
