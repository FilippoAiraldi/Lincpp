#pragma once

namespace Lincpp
{
    namespace internal
    {
        template <typename Derived>
        struct Query
        {
        private:
            typedef typename traits<Derived>::Source TSource;
            typedef typename traits<Derived>::Element TElement;

        protected:
            Derived &derived() { return *static_cast<Derived *>(this); }
            const Derived &derived() const { return *static_cast<const Derived *>(this); }

        public:
            const TElement &ElementAt(typename TSource::size_type i) { return this->derived().ElementAt(i); }
        };
    } // namespace internal
} // namespace Lincpp
