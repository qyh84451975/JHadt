#ifndef __LOBJECT__
#define __LOBJECT__

#define BIT_ISCOLLECTABLE (1 << 6)
// 标记一个t为可回收的
#define ctb(t) ((t) | BIT_ISCOLLECTABLE)

// Lua中所有数据类型都可用TValue表示
#define rttype(o) ((o)->tt_)
// 根据tt_的第7位判断是否需要回收
#define iscollectable(o) (rttype(o) & BIT_ISCOLLECTABLE)

#endif /* __LOBJECT__ */