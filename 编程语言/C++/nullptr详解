# nullptr详解

C++11 可以使用 nullptr 代替 0 或者 NULL 来指定空指针，这个特性可以避免一个空指针被错误解释成一个整数值
```C++
void f(int);
void f(void*);
f(0); //calls f(int)
f(NULL); //calls f(int) if NULL is 0, ambuguous otherwise
f(nullptr); //calls f(void*)
```

nullptr 是一个新的关键字，它会自动转换成每一个指针类型而不是整数类型

nullptr 的类型是一个基本数据类型 std::nullptr_t，因此可以为传递空指针的情况重载操作符

```C++
// stddef.h
typedef decltype(nullptr) nullptr_t
```
