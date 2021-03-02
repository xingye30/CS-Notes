# =default，=delete详解

如果你自己定义了一个构造函数，那么编译器就不会再给你生成合成的版本

=default:
- 如果你强制加上 =default，就可以显示要求编译器生成合成版本的构造函数
- 在类内用 =default 修饰成员的声明时，合成的函数将隐式地声明为内联的，如果不希望合成的成员是内联函数，应该只对成员的类外定义使用 = default
- =default 只能用于具有合成版本的成员函数：默认构造函数或拷贝控制成员

```C++
class Zoo
{
public:
  Zoo(int i1, int i2) : d1(i1), d2(i2) { }
  Zoo(const Zoo&) = delete;
  Zoo(Zoo&&) = default;
  Zoo& operator=(const Zoo&) = defualt;
  Zoo& operator=(const Zoo&&) = delete;
  virtual ~Zoo() { }
private:
  int d1, d2;
};
```

```C++
class Foo
{
public:
  Foo(int i) : _i(i) { }
  Foo() = defualt; //和上一个并存
  
  Foo(const Foo& x) : _i(x._i) { }
  //Foo(const Foo&) = defualt; //Error 只能有一个拷贝构造
  //Foo(const Foo&) = delete; //Error 已经自定义了拷贝构造
  
  Foo& operator=(const Foo& x) { _i = x._i; return *this; }
  //Foo& operator=(const Foo& x) = default; //Error 只能有一个拷贝赋值
  //Foo& operator=(const Foo& x) = delete; //Error 已经自定义了拷贝赋值
  
  //void func1() = default; //Error func1 can not be default
  void func2() = delete; //ok
  
  //~Foo() = delete; //这会造成使用Foo object时出错
  ~Foo() = default;
 
private:
  int _i;
}
```

如果没有声明 Big-Three，编译器会自动声明合成版本的一个 copy ctor、一个 copy assignmnet operator 和一个 dtor

如果没有声明任何 ctor， 编译器还会自动声明一个default ctor

所有这些函数都是 public 且 inline

只有当这些函数被调用，他们才会被编译器合成

default ctor 和 dtor 主要是给编译器一个地方来放藏身幕后的 code， 像调用 base classes 以及 non-static members 的 ctors 和 dtors

编译器合成的 dtor 是 non-virtual 的，除非这个 class 的 base class 含有 virtual dtor

copy ctor 和 copy assign operator 的合成版本只是单纯将 source object 的每一个 non-static data member 拷贝到 destination object 

```C++
class Empty { };

class Empty {
public:
  Empty() { ... }
  Empty(const Empty& rhs) { ... }
  Empty& operator=(const Empty& rhs) { ... }
  ~Empty() { ... }
};
```

一个类如果有 pointer member，几乎肯定要自定义 Big-Three

一个类如果没有 pointer member，绝大多数无需自定义 Big-Three


=delete：
- =delete 将函数定义为删除的函数，告诉编译器不要定义它
  - 删除的函数：虽然声明了它们，但不能以任何的方式使用它们
- =delete 必须出现在函数第一次声明的时候
- =delete 适用于任何函数

可以通过将拷贝构造函数和拷贝赋值运算符定义为删除的函数来阻止拷贝
```C++
struct NoCopy {
  NoCopy() = default;
  NoCopy(const NoCopy&) = delete; //no copy
  NoCopy &operator=(const NoCopy&) = delete; //no assignment
  ~NoCopy() = default;
};
```

析构函数不能是删除的成员：
- 如果析构函数被删除，就无法销毁此类型的对象了
- 如果析构函数被删除，编译器不允许定义该类型的变量或创建该类型的临时对象
- 如果一个类有某个成员的类型删除了析构函数，也不能定义该类型的变量或临时对象
- 对于删除了析构函数的类型，可以动态分配这种类型的对象，但是不能释放这些对象
```C++
struct NoDtor {
  NoDtor() = default;
  ~NoDtor() = delete; //can't destroy objects of type NoDtor
};
NoDtor nd; //Error NoDtor destructor is deleted
NoDtor *p = new NoDtor(); //ok but can't delete
delete p; //Error NoDtor destructor is deleted
```

合成的拷贝控制成员可能是删除的：
- 如果类的某个成员的析构函数是删除的或不可访问的，则类的合成的析构函数被定义为删除的
- 如果类的某个成员的拷贝构造函数或析构函数是删除的或不可访问的，则类的合成拷贝构造函数被定义为删除的
- 如果类的某个成员的拷贝赋值运算符是删除的或不可访问的，或是类有一个 const 的或引用成员，则类的合成拷贝赋值运算符被定义为删除的
- 如果类的某个成员的析构函数是删除的或不可访问的，或是类有一个引用成员，它没有类内初始化器，或是类有一个 const 成员，它没有类内初始化器且其类型未显示定义默认构造函数，则该类的默认构造函数被定义为删除的

如果有一个类有数据成员不能默认构造、拷贝、复制或销毁，则对应的成员函数被定义为删除的

本质上，当不可能拷贝、赋值或销毁类的成员时，类的合成拷贝控制成员就被定义为删除的

C++11 之前，通过将拷贝构造函数和拷贝赋值运算符声明为私有的来阻止拷贝：
```C++
class PrivateCopy {
private:
  PrivateCopy(const PrivateCopy&);
  PrivateCopy& operator=(const PrivateCopy&);
public:
  PrivateCopy() = default;
  ~PrivateCopy();
};
// 此 class 不允许被 ordinary user code copy，但仍可以被 friends 和 members copy
// 若要完全禁止，不但必须把 copy controls 放到 private 内，而且不可以定义它
// 声明但不定义一个成员函数是合法的
```

```C++
namespace boost {
namespace noncopyable_
{
  class noncopyable
  {
  protected:
    noncopyable() {}
    ~noncopyable() {}
  private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
  };
}

typedef noncopyable_::noncopyable noncopyable;
}
```