# C++面向对象高级开发

Object Based（基于对象）：面对的是单一class的设计
Object Oriented（面向对象）：面对的是多重classes的设计，classes和classes之间的关系

Classes的两个经典分类：
- Class without pointer members
- Class with pointer members

头文件中的防卫式声明
```C++
#ifndef __COMPLEX__
#define __COMPLEX__

#endif
```

inline（内联）函数：
- inline 只适合函数体内代码简单的函数使用
- inline 函数仅仅是一个对编译器的建议
- 内联函数要在调用点展开，所以编译器必须随处可见内联函数的定义，这要求每个调用了内联函数的文件都出现了该内联函数的定义，所以最好将内联函数定义放在头文件中
- 定义在类中的成员函数默认都是内联的, 如果在类中未给出成员函数定义，而又想内联该函数的话，那在类外要加上 inline
- 关键字 inline 必须与函数定义体放在一起才能使函数成为内联，仅将 inline 放在函数声明前面不起任何作用
- 内联是以代码膨胀（复制）为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率
  + 如果函数体内的代码比较长，使用内联将导致内存消耗代价较高
  + 如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大
  + 类的构造函数和析构函数可能会隐藏一些行为，如"偷偷地"执行了基类或成员对象的构造函数和析构函数，所以不要随便地将构造函数和析构函数的定义体放在类声明中


访问修饰符：
- 一个类可以有多个 public、protected 或 private 标记区域，每个标记区域在下一个标记区域开始之前或者在遇到类主体结束右括号之前都是有效的。
- class的成员和类的默认访问修饰符是 private， 而struct的成员和类的默认访问修饰符是public
- 公有（public）成员在程序中类的外部是可访问的 
- 私有（private）成员变量或函数在类的外部是不可访问的，只有类和友元函数可以访问私有成员
- 受保护（protected）成员变量或函数与私有成员十分相似，但其在派生类（即子类）中是可访问的。

构造函数：
- 类的构造函数是类的一种特殊的成员函数，它会在每次创建类的新对象时执行
- 构造函数的名称与类的名称相同，并且没有返回值

析构函数：
- 类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行
- 析构函数的名称与类的名称相同，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数
- 析构函数有助于在跳出程序前释放资源

默认实参：
- 有函数声明时，默认参数可以放在函数声明或者定义中，但只能放在二者之一
- 没有函数声明时，默认参数在函数定义时指定
- 一旦某个参数开始指定默认值，它右边的所有参数都必须指定默认值
- 在调用具有默认参数的函数时，若某个实参默认，其右边的所有实参都应该默认

拷贝构造函数调用时机：
- 用已经创建好的对象初始化新的对象
- 以值传递的方式对函数参数进行传值
- 以值方式返回局部对象

函数重载：在同一作用域中声明几个类似的同名函数
- 函数名称必须相同
- 参数列表必须不同（个数不同、类型不同、参数排列顺序不同等）
- 函数的返回类型可以相同也可以不相同
- 仅仅返回类型不同不足以成为函数的重载


单例模式（Singleton）：构造函数放在private区域
```C++
class A {
public:
  static A& getInstance();
  setup() { ... }
private:
  A();
  A(const A& rhs);
  ...
};

A& A::getInstance()
{
  static A a;
  return a;
}

A::getInstance().setup();
```

常量成员函数（const member functions）:
- 将const关键字放在类成员函数的参数列表之后，表示该函数为常量成员函数
- 可以在类内定义函数，也可以在类外定义，都要使用关键字const
- 如果不添加const关键字，此时constFunc()是普通的成员函数，此时this的类型是MyClass* const，即this本身是常量，但是其指向的类型是非常量。
这就意味着我们不能把this绑定到一个常量对象上。如果要把this绑定到一个常量对象上，必须要把this定义成const MyClass* const，即指向常量的常量。
在类成员函数的参数列表之后添加const关键字，就相当于把this定义成const MyClass* const。
- 如果通过常量对象调用类的成员函数，该成员函数必须是常量成员函数
- 因为可以将一个非常量赋值给常量，所以非常量对象可以调用常量成员函数
- 因为常量成员函数中的this类型是const MyClass* const，所以不能通过this来修改成员变量


参数传递：pass by value vs. pass by reference (to const)
- 缺省情况C++以pass-by-value（继承C的方式）传递对象至（或来自）函数。函数参数都是以实际参数的复件为初值，调用端所获得的也是函数返回值的一个复件
- pass-by-value耗时的原因：类的对象作为函数参数时，如果使用值传递，要先拷贝一份实参的副本，需要调用类的拷贝构造函数，函数结束时副本被销毁，需要调用析构函数
- pass-by-reference的优势：
  - 没有任何构造函数或析构函数被调用，因为没有任何对象被新建
  - 可以在参数声明中加上const，防止传入的对象被修改
  - 避免slicing（对象切割）问题（子类对象被切割成父类对象，功能缺失）
- reference往往以指针的形式实现，传递的是指针，对象为内置类型，STL的迭代器和函数对象，pass-by-value高效一些


返回值传递：return by value vs. return by reference (to const)
- 如果要return的东西，运行这个函数之前已经有一块memory可以存放这个东西，则可以return by reference
- 如果事先没有memory存放这个东西，那么只能传回一个local object


friend（友元）
- 类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员
- 尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数
- 友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元
- 如果要声明函数为一个类的友元，需要在类定义中该函数原型前使用关键字 friend
- 相同class的各个object互为friends

complex类
```C++
class complex   // class head
{               // class body
public:
  complex (double r = 0, double i = 0) //默认实参
    : re (r), im (u)  //初值列
  { }
  complex& operator += (const complex&);
  double real () const { return re; } //常量成员函数
  double imag () const { return im; }
private:
  double re, im;
  
  friend complex& __doapl (complex*, const complex&);
}
```
