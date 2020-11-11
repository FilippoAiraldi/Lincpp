#pragma once

namespace Lincpp
{
    template <typename Expr>
    struct SelectClause : public Expression<SelectClause<Expr>>
    {
    };
} // namespace Lincpp
