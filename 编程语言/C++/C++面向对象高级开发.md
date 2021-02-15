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
- 传递者无需知道接收者是以reference形式接收

temp object（临时对象）：typename();
- 用构造函数作为隐式类型转换函数时，会创建临时对象
- 建立一个没有命名的非堆（non-heap）对象，也就是无名对象时，会产生临时对象
- 函数返回一个对象值时，会产生临时对象，函数中的返回值会以值拷贝的形式拷贝到被调函数栈中的一个临时对象


friend（友元）
- 类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员
- 尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数
- 友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元
- 如果要声明函数为一个类的友元，需要在类定义中该函数原型前使用关键字 friend
- 相同class的各个object互为friends

操作符重载：

this指针详解：
- 一、问题
  - 1.一个类中的不同对象在调用自己的成员函数时，其实它们调用的是同一段函数代码，那么成员函数如何知道要访问哪个对象的数据成员呢？
    - 没错，就是通过this指针。每个对象都拥有一个this指针，this指针记录对象的内存地址，当我们调用成员函数时，成员函数默认第一个参数为T* const register this，大多数编译器通过ecx寄存器传递this指针，通过 this 这个隐式参数可以访问该对象的数据成员。
  - 2.类的成员函数为什么不能用static和const同时修饰？
    - 类中用const修饰的函数通常用来防止修改对象的数据成员，函数末尾的const是用来修饰this指针，防止在函数内对数据成员进行修改，而静态函数中是没有this指针的，无法访问到对象的数据成员，与C++ static语义冲突，所以不能。
- 二、this指针注意点
  - C++中this关键字是一个指向对象自己的一个常量指针，不能给this赋值
  - 只有成员函数才有this指针，友元函数不是类的成员函数，没有this指针
  - 静态函数也是没有this指针的，静态函数如同静态变量一样，不属于具体的哪一个对象
  - this指针作用域在类成员函数内部，在类外也无法获取
  - this指针并不是对象的一部分，this指针所占的内存大小是不会反应在sizeof操作符上的
- 三、this指针的使用
  - 1.在类的非静态成员函数中返回类对象本身的时候，直接使用 return *this
  - 2.修改类成员变量或参数与成员变量名相同时，如this->a = a 
  - 3.在class定义时要用到类型变量自身时，因为这时候还不知道变量名，就用this这样的指针来使用变量自身


complex类
```C++
#ifndef __COMPLEX__
#define __COMPLEX__

class complex 
{
public:
    complex(double r = 0, double i = 0)
    : re(r), im(i)
    {   }

    double real() const { return re; }
    double imag() const { return im; }

    complex& operator += (const complex& r);
    complex& operator -= (const complex& r);
    complex& operator *= (const complex& r);
    complex& operator /= (const complex& r);

private:
    double re;
    double im;

    friend complex& __doapl(complex* ths, const complex& r);
    friend complex& __doami(complex* ths, const complex& r);
    friend complex& __doaml(complex* ths, const complex& r);
};

complex& __doapl(complex* ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im; 
    return *ths;
}

complex& complex::operator += (const complex& r)
{
    return __doapl(this, r);
}

complex& __doami(complex* ths, const complex& r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

complex& complex::operator -= (const complex& r)
{
    return  __doami(this, r);
}

complex& __doaml(complex* ths, const complex& r)
{
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}

complex& complex::operator *= (const complex& r)
{
    return __doami(this, r);
}

inline double real(const complex& r)
{
    return r.real();
}

inline double imag(const complex& r)
{
    return r.imag();
}

inline complex operator + (const complex& x, const complex& y)
{
    return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex operator + (double x, const complex& y)
{
    return complex(x + real(y), imag(y));
}

inline complex operator + (const complex& x, double y)
{
    return complex(real(x) + y, imag(x));
}

inline complex operator - (const complex& x, const complex& y)
{
    return complex(real(x) - real(y), imag(x) - imag(y));
}

inline complex operator - (const complex& x, double y)
{
    return complex(real(x) - y, imag(x));
}

inline complex operator - (double x, const complex& y)
{
    return complex(x - real(y), imag(y));
}

inline complex operator * (const complex& x, const complex& y)
{
    return complex(real(x) * real(y) - imag(x) * imag(y), real(x) * imag(y) + imag(x) * real(y));
}

inline complex operator * (const complex& x, double y)
{
    return complex(real(x) * y, imag(x));
}

inline complex operator * (double x, const complex& y)
{
    return complex(x * real(y), imag(y));
}

inline complex operator / (const complex& x, double y)
{
    return complex(real(x) / y, imag(x) / y);
}

inline complex operator + (const complex& r)
{
    return r;
}

inline complex operator - (const complex& r)
{
    return complex(-real(r), -imag(r));
}

inline bool operator == (const complex& x, const complex& y)
{
    return (real(x) == real(y) && imag(x) == imag(y));
}

inline bool operator == (const complex& x, double y)
{
    return (real(x) == y && imag(x) == 0);
}

inline bool operator == (double x, const complex& y)
{
    return (x == real(y) && imag(y) == 0);
}

inline bool operator != (const complex& x, const complex& y)
{
    return (real(x) != real(y) || imag(x) != imag(y));
}

inline bool operator != (const complex& x, double y)
{
    return (real(x) != y || imag(x) != 0);
}

inline bool operator != (double x, const complex& y)
{
    return (x != real(y) || imag(y) != 0);
}

#include <cmath>

inline complex polar (double r, double t)
{
  return complex (r * cos (t), r * sin (t));
}

inline complex conj (const complex& x) 
{
  return complex (real (x), -imag (x));
}

inline double norm (const complex& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}

#include <iostream>
using namespace std;

inline ostream& operator << (ostream& os, const complex& r)
{
    return os << real(r) << " + j" << imag(r); 
}

#endif
```
