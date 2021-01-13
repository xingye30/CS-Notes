# linux内核分析与应用

## linux操作系统概述

操作系统设计目的：
+ 提高资源利用率
+ 方便用户使用
  
linux/unix设计理念：机制与策略分离
+ 机制-提供什么样的功能
+ 策略-如何使用这些功能
  
系统调用：隔离变化

单内核
微内核

链表定义
```
struct list_head {
    struct list_head *next, *prev;
};
```

链表初始化
```
#define LIST_HEAD_INIT(name) {
    &(name), &(name)
} /* 初始化为空链表，头尾都指向自己 */
```

链表声明并初始化
```
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name);
```

判断链表为空
```
static inline int list_empty(const struct list_head *head) 
{
    return head->next == head;
}
```

链表插入
```
static inline void __list_add(struct list_head *new, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{

}

static inline void list_add()
{

}
```

链表遍历
```
#define list_for_each(pos, head)\
    for (pos = (head)->next; pos != (head); pos = pos->next)

//由pos获取数据
#define list_entry(ptr, type, member)\
    ((type*)((char*)(ptr) - (unsigned long)(&((type*)0)->member)))
/* type-结构体类型  ptr-成员member所在的位置  member-结构体成员*/
```

哈希表定义
‵‵‵
struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **prev;
};
```

