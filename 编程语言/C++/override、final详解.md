# override、final详解

override 告诉编译器此函数是重载，如果没有重载，编译器会报错
```C++
struct Base {
  virtual void vfunc(float) { }
};

struct Derived1 : Base {
  virtual void vfunc(int); // 本意想重写vfuc，不小心重载了一个新的虚函数
};

struct Derived1 : Base {
  virtual void vfunc(int) override; //Error
  
  virtual void vfunc(float) override; 
};
```

final 修饰类表示不允许被继承，修饰函数表示不允许被重写
```C++
struct Base1 final {};
struct Derived1 : Base1 {}; //Error

struct Base2 ｛
  virtual void f() final;
};
struct Derived2 : Base2 {
  void f(); //Error
};


```


