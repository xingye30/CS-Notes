# decltype 详解

使用 decltype 可以让编译器推导出一个对象或表达式的类型
```C++
map<string, float> coll;
decltype(coll):value_type elem; //map<string, float>::value_type elem;
```


decltype 的用法：
- 定义返回类型
- metaprogramming
- 传递 lambda 的类型

有时候返回值的类型取决于关于参数的表达式
```C++
template<typename T1, typename T2>
decltype(x + y) add(T1 x, T2 y); //Error decltyeoe时，x 和 y还未定义

template<typename T1, typename T2>
auto add(T1 x, T2 y)->decltype(x + y);
```

```C++
template<typename T>
void test18_decltype(T obj)
{
  //传进来的应该是容器
  typedef typename decltype(obj)::iterator iType; //typedef typename T::iterator iType;
  decltype(obj) anotherObj(obj);
}
//test18_decltype(complex<int>()); //编译失败
```

面对 lambda，我们手上往往只有 object，没有 type，要获得其 type 就得借助于 decltype
```C++
auto cmp = [](const Person& p1, const Person& p2) {
              return p1.lastname() < p2.lastname() ||
              (p1.lastname() == p2.lastname() && p1.firstname() < p2.firstname());
            };
std::set<Person, dec;type(cmp)> coll(cmp);
```
