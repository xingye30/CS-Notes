# auto 详解

在定义变量或对象时可以使用auto而不用指定特定的类型，编译器通过参数推导得出类型

auto用于类型特别长或者非常复杂的表达式

```C++
list<string> c;
...
list<string>::iterator ite;
ite = find(c.begin(), c.end(), target);

list<string> c;
...
auto ite = find(c.begin(), c.end(), target);

list<string> c;
...
auto ite; //错误
ite = find(c.begin(), c.end(), target);

auto I = [](int x)->bool {
  ...
};
```

