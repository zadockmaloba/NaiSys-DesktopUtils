#ifndef NAISYS_INDEXED_MAP_H
#define NAISYS_INDEXED_MAP_H

#include <vector>
#include <tuple>
#include <memory>

namespace NaiSys {
namespace Core {

template <typename T_ky, typename T_vl>
class IndexedMap
{
private:
    class Pair
    {
    public:
        Pair(T_ky const &key, T_vl const &value)
            : m_first{ key }, m_second{ value }
        {

        }
        ~Pair(){}
        T_ky first() const {
            return m_first;
        }
        void setFirst(const T_ky &newKey) {
            m_first = newKey;
        }
        T_vl second() const {
            return m_second;
        }
        void setSecond(const T_vl &newValue) {
            m_second = newValue;
        }

    private:
        T_ky m_first;
        T_vl m_second;
    };

public://typedefs
    using pair_ptr = std::shared_ptr<Pair>;
    using pair_array = std::vector<pair_ptr>;

public:
    IndexedMap(const pair_array &p = {})
        : m_pairs{ p }
    {

    }
    ~IndexedMap() {}

public:
    void push_back(T_ky const &_key, T_vl const &_value)
    {
        auto temp = std::make_shared<Pair>(Pair(_key, _value));
        m_pairs.push_back(temp);
        m_size+=1;
    }
    void push_front(const Pair &pair) throw()
    {
        //TODO
        return;
    }
    void pop_back() throw()
    {
        m_pairs.pop_back();
        m_size-=1;
    }
    void pop_front() throw()
    {
        //TODO
    }

    pair_array pairs() const {
        return m_pairs;
    }
    void setPairs(const pair_array &newPairs) {
        m_pairs = newPairs;
    }
    size_t size() const {
        return m_size;
    }
    const T_vl at(const T_ky &_key) const {
        if(m_pairs.begin() != m_pairs.end()) {
            for(auto &v : m_pairs) {
                if(_key == v->first()) return v->second();
            }
        }
        return T_vl{};
    }
    auto begin() { return m_pairs.begin(); }
    auto end() { return m_pairs.end(); }

public://operators
    Pair &operator[](T_ky _key) const throw() {
        for(auto &v : m_pairs) {
            if(_key == v->first()) return v;
        }
        return nullptr;
    }

private:
    pair_array m_pairs;
    size_t m_size = 0;
};

}
}

#endif //naisysindexedmap.h
