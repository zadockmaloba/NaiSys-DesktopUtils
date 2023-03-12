#ifndef NAISYS_INDEXED_MAP_H
#define NAISYS_INDEXED_MAP_H

#include <vector>
#include <tuple>
#include <memory.h>

namespace NaiSys {
namespace Core {

template <typename T_ky, typename T_vl>
class IndexedMap
{
private:
    class Pair
    {
    public:
        Pair(const T_ky &key, const T_vl &value)
            : m_key{ key }, m_value{ value }
        {

        }
        ~Pair(){}
        T_ky key() const {
            return m_key;
        }
        void setKey(const T_ky &newKey) {
            m_key = newKey;
        }
        T_vl value() const {
            return m_value;
        }
        void setValue(const T_vl &newValue) {
            m_value = newValue;
        }

    private:
        T_ky m_key;
        T_vl m_value;
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
    void push_back(const Pair &pair) throw();
    void push_front(const Pair &pair) throw();
    void pop_back() throw();
    void pop_front() throw();

    pair_array pairs() const {
        return m_pairs;
    }
    void setPairs(const pair_array &newPairs) {
        m_pairs = newPairs;
    }
    size_t size() const {
        return m_pairs.size();
    }
    const T_vl at(const T_ky &_key) const {
        for(auto &v : m_pairs) {
            if(_key == v->key()) return v->value();
        }
        return nullptr;
    }
    auto begin() { return m_pairs.begin(); }
    auto end() { return m_pairs.end(); }

public://operators
    Pair &operator[](T_ky _key) const throw() {
        for(auto &v : m_pairs) {
            if(_key == v->key()) return v;
        }
        return nullptr;
    }

private:
    pair_array m_pairs;
};

}
}

#endif //naisysindexedmap.h
