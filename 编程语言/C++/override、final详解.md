# override、final详解

C++11 允许派生类显示地注明它使用某个成员函数覆盖了它继承的虚函数
- 在形参列表后面、或者在 const 成员函数的 const 关键字后面、或者在引用成员函数的引用限定符后面添加一个关键字 override
- override 告诉编译器此函数是覆盖了它继承的虚函数，如果没有覆盖，编译器会报错
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

final 修饰类表示不允许被继承，修饰函数表示不允许被覆盖
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

final 和 override 说明符出现在形参列表（包括任何 const 或引用修饰符）以及尾置返回类型之后