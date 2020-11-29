#pragma once

#include <iostream>

namespace Lincpp
{
    template <typename TIterator>
    struct Orderable
    {
    public:
        typedef typename std::iterator_traits<TIterator>::value_type TElement;

        template <typename TComparer>
        explicit Orderable(TIterator begin, TIterator end, TComparer comparer) : _begin(begin), _end(end)
        {
            CHECK_COMPARER(TComparer, TElement);
            this->_comparers.push_back(comparer);
        }

        template <typename TComparer>
        Orderable<TIterator> &ThenBy(TComparer comparer)
        {
            CHECK_COMPARER(TComparer, TElement);
            this->_comparers.push_back(comparer);
            return *this;
        }

        // template <typename TComparer>
        // Orderable<TIterator> &ThenByDescending(TComparer comparer)
        // {
        //     CHECK_COMPARER(TComparer, _TElement);
        //     this->_comparers.push_back(std::not_fn(comparer));
        //     return *this;
        // }

        std::forward_list<TElement> ToForwardList()
        {
            std::forward_list<TElement> fl(this->_begin, this->_end);
            auto fcns = _comparers;
            fl.sort([&fcns](TElement &a, TElement &b) {
                for (auto it = fcns.begin(); it != fcns.end(); ++it)
                {
                    if ((*it)(a, b))
                        return true;
                    if ((*it)(b, a))
                        return false;
                }
                return false;
            });
            return fl;
        }

        std::list<TElement> ToList()
        {
            std::list<TElement> l(this->_begin, this->_end);
            auto fcns = _comparers;
            l.sort([&fcns](TElement &a, TElement &b) {
                for (auto it = fcns.begin(); it != fcns.end(); ++it)
                {
                    if ((*it)(a, b))
                        return true;
                    if ((*it)(b, a))
                        return false;
                }
                return false;
            });
            return l;
        }

        std::vector<TElement> ToVector()
        {
            std::vector<TElement> v(this->_begin, this->_end);
            auto fcns = _comparers;
            std::sort(v.begin(), v.end(), [&fcns](TElement &a, TElement &b) {
                for (auto it = fcns.begin(); it != fcns.end(); ++it)
                {
                    if ((*it)(a, b))
                        return true;
                    if ((*it)(b, a))
                        return false;
                }
                return false;
            });
            return v;
        }

    private:
        const TIterator _begin;
        const TIterator _end;
        std::list<std::function<bool(const TElement &, const TElement &)>> _comparers;
    };
} // namespace Lincpp
