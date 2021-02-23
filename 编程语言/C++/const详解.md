# const 详解

常类型是指使用类型修饰符 const 说明的类型，常类型的变量或对象的值是不能被更新的

<font color="#dd0000">const 类型的变量定义时必须进行初始化</font><br />

const 常量与 #define 宏定义常量的区别:
- const 常量具有类型，编译器可以进行安全检查，define 宏定义没有数据类型，只是简单的字符串替换，不能进行安全检查
- const 定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是像 #define 一样给出的是立即数
- const 定义的常量在程序运行过程中只有一份拷贝，而 #define 定义的常量在内存中有若干个拷贝

<font color="#dd0000">const 对象默认为文件局部变量， 非 const 变量默认为 extern</font><br />， 要使const变量能够在其他文件中访问，必须在文件中显式地指定它为extern

## 指针与const

指向常量的指针 
- 对于指向常量的指针，不能通过指针来修改对象的值
- <font color="#dd0000">必须使用 const * 类型的指针保存 const 对象的地址</font><br />
- 允许把非 const 对象的地址赋值给 const 对象的指针，如果要修改指针所指向的对象值，必须通过其他方式修改，不能直接通过当前指针直接修改
```C++
// const 位于 * 的左侧，const 用来修饰指针所指向的变量，即指针指向为常量
const char * p;   
char const * p;
```

常指针
- const指针必须进行初始化，且const指针的值不能修改
```C++
// const 位于 * 的右侧，const 修饰指针本身，即指针本身是常量
char * const ptr = &p;
```

指向常量的常指针
```C++
const int * const ptr = &p; 
```

## 常量成员函数（const member functions）:

将 const 关键字放在类成员函数的参数列表之后，表示该函数为常量成员函数

可以在类内定义函数，也可以在类外定义，都要使用关键字 const

<font color="#dd0000">在一个类中，任何不会修改数据成员的函数都应该声明为const类型</font><br />
- 如果不添加 const 关键字，普通的成员函数的 this 指针的类型是 MyClass* const，即 this 本身是常量，但是其指向的类型是非常量，这就意味着我们不能把 this 绑定到一个常量对象上
- 如果要把 this 绑定到一个常量对象上，必须要把 this 定义成 const MyClass* const，即指向常量的常量指针
- 在类成员函数的参数列表之后添加const关键字，就相当于把this定义成const MyClass* const
- 因为常量成员函数中的 this 类型是 const MyClass* const，所以不能通过 this 来修改成员变量

调用规则：
- <font color="#dd0000">如果通过常量对象调用类的成员函数，该成员函数必须是常量成员函数</font><br />
- 因为可以将一个非常量赋值给常量，所以非常量对象可以调用常量成员函数，也可以调用非常量成员函数
- <font color="#dd0000">当成员函数的常量和非常量版本同时存在，常量对象只会调用常量版本，非常量对象只会调用非常量版本</font><br /> 