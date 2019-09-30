/*******
 * lua 表
 */

#include "structs.h"
#include <math.h>

/**
 * double frexp (double x, int *exponent)
 * 把浮点数x分解成尾数和指数，返回值为尾数，指数存在exponent中。x = mantissa * 2 ^ exponent
 */

#define dummynode (&dummynode_)

static const Node dummynode_ = {
    {NILCONSTANT},
    {{NILCONSTANT, 0}}
};

#define hashpow2(t, n) (gnode(t, lmod((n), sizenode(t))))
#define hashint(t, i)       hashpow2(t, i)
#define hashstr(t,str)      hashpow2(t, (str)->hash)
#define hashboolean(t,p)    hashpow2(t, p)
#define hashmod(t, n) (gnode(t, ((n) % ((sizenode(t)-1)|1))))

static int l_hashfloat (number n)
{
    int i;
    integer ni;
    n = frexp(n, &i) * cast(number, INT_MIN);
    if (!lua_numbertointeger(n, &ni)) {
        return 0;
    }
    else {
        unsigned int u = cast(unsigned int, i) + cast(unsigned int, ni);
        return cast_int(u <= cast(unsigned int, INT_MAX) ? u : ~u);
    }
}

static Node *mainposition (const Table *t, const TValue *key)
{
    switch (ttype(key)) {
        case LUA_TNUMINT:
            return hashint(t, ivalue(key));
        case LUA_TNUMFLT:
            return hashmod(t, l_hashfloat(fltvalue(key)));
        case TSHRSTR:
            return hashstr(t, tsvalue(key));
        case TLNGSTR:
            return hashpow2(t, l_hashlongstr(tsvalue(key)));
        case LUA_TBOOLEAN:
            return hashboolean(t, bvalue(key));
        default:
            return NULL;
    }
}

// Lua 的数组部分是从1开始的
static unsigned int arrayindex (const TValue *key)
{
    if (ttisinteger(key)) {
        integer k = ivalue(key);
        if (0 < k && (unsigned long long)k <= MAXASIZE)
            return cast(unsigned int, k);
    }
    return 0;
}



#define TEST_6

#ifdef TEST_6

int main(int argc, const char *argv[])
{
#ifdef TEST_FREXP
    double x = 1024, fraction;
    int e;
    fraction = frexp(x, &e);
    printf("x = %.2lf = %.2lf * 2 ^ %d\n", x, fraction, e);
#endif
    
#ifdef TEST_DOT
// Lua中常出现宏中的语句以逗号的形式分割语句。原因是因为这些宏常用函数参数或者判断语句，不能以分号分割。
// 如lua_numbertointeger中的(, 1)，是为了执行赋值语句，以及忽略这个语句对判断的影响
    int n = 5;
    int m = 0;
    if (!(n >= -4 && n < 4 && ((void)(*(&m) = 1), 1))) {
        return 0;
    }
    printf("m = %d\n", m);
#endif
    
    return 0;
}

#endif
