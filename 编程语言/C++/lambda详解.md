# lambda详解

C++11 引入了 lambda，允许定义一个 inline 函数体，可以用作一个参数或者对象
```C++
[...](...)mutable throwSpec -> retType {}
```

```C++
[]{
  std::cout << "hello lambda" << std::endl;
}(); //prints "hello lambda"

auto I = []{
  std::cout << "hello lambda" << std::endl;
};
I(); //prints "hello lambda"
```

[] 是 lambda introducer，用来获取在 lambda 内部可以访问的非静态对象
- [=] 表示外部作用域以值传递的方式传递到 lambda 内
- [&] 表示外部作用域以引用传递的方式传递到 lambda 内
```C++
auto qqq = [x, &y]{ ... } // pass y by reference and all other objects by value
```

mutable、throwSpec、retType 都是可选项
- mutable：当对象通过值传递进 lambda 时，对对象拥有写权限
- throwSpec：是否抛出异常 
- retType：返回值，如果没有定义，编译器会自动推导出返回值
- 如果三个中有一个存在，必须写 ()

```C++
int id = 0;
auto f = [id]() mutable { //如果没有写 mutable，不能 ++id
  std::cout << "id: " << id << std::endl;
  ++id; //OK
};


id = 42;
f(); //id : 0
f(); //id : 1
f(); //id : 2
std::cout << id << std::endl; //42
//如果改成 [&id] 输出变为 42 43 44 45


//相当于匿名函数对象
class Functor {
private:
  int id; //copy of outside id
public:
  void operator()(){
    std::cout << "id: " << id << std::endl;
    ++id;
  }
};
```


