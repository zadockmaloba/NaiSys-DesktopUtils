#include "naisysindexedmap.h"

namespace NaiSys {
namespace Core {

template<typename T_ky, typename T_vl>
void IndexedMap<T_ky, T_vl>::push_back(const Pair &pair) throw()
{
    m_pairs.push_back(pair_ptr(pair));
}

template<typename T_ky, typename T_vl>
void IndexedMap<T_ky, T_vl>::push_front(const Pair &pair) throw()
{
    //TODO
    return;
}

template<typename T_ky, typename T_vl>
void IndexedMap<T_ky, T_vl>::pop_back() throw()
{
    m_pairs.pop_back();
}

template<typename T_ky, typename T_vl>
void IndexedMap<T_ky, T_vl>::pop_front() throw()
{
    //TODO
}

}
}
