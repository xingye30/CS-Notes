# reference 详解

<font color="#dd0000">object和其reference的大小相同、地址也相同（全部都是假象）</font><br />
```C++
int x = 0;
int* p = &x;
int& r = x; //r代表x，现在r、x都是0
//sizeof(r) == sizeof(x)
//&x = &r

int x2 = 5;
r = x2; //r不能重新代表其他物体，现在r、x都是5
int& r2 = r; //现在r2是5，r2代表r，也相当于代表x

typedef struct Stag { int a, b, c, d; } S;
int main() {
  double x = 0;
  double* p = &x; //p指向x，p的值是x的地址
  double& r = x; //r代表x，现在r，x都是0
  
  cout << sizeof(x) << endl;  //8
  cout << sizeof(p) << endl;  //4
  cout << sizeof(r) << endl;  //8
  cout << p << endl;  //0065FDFC
  cout << *p << endl;  //0
  cout << x << endl;  //0
  cout << r << endl;  //0
  cout << &x << endl;  //0065FDFC
  cout << &r << endl;  //0065FDFC
  
  S s;
  S& rs = s;
  cout << sizeof(s) << endl;  //16
  cout << sizeof(rs) << endl;  //16
  cout << &s << endl;  //0065FDE8
  cout << &rs << endl;  //0065FDE8
}
```

## 引用与指针

引用相当于常指针

区别：
- 引用必须初始化，而指针可以不初始化
- 引用不能为空，而指针可以为空
- 指针可以随时改变指向，但是引用只能指向初始化时指向的对象，无法改变


## 参数传递

参数传递：pass by value vs. pass by reference (to const)
- 缺省情况 C++ 以 pass by value （继承 C 的方式）传递对象至（或来自）函数。函数参数都是以实际参数的复件为初值，调用端所获得的也是函数返回值的一个复件
- reference 往往以指针的形式实现，传递的是指针
- <font color="#dd0000">对象为内置类型，STL 的迭代器和函数对象时，pass by value 高效一些</font><br />

pass by value 耗时的原因：类的对象作为函数参数时，如果使用值传递，要先拷贝一份实参的副本，需要调用类的拷贝构造函数，函数结束时副本被销毁，需要调用析构函数

pass by reference 的优势：
- 没有任何构造函数或析构函数被调用，因为没有任何对象被新建
- 可以在参数声明中加上 const，防止传入的对象被修改
- 避免 slicing （对象切割）问题（子类对象被切割成父类对象，功能缺失）

返回值传递：return by value vs. return by reference (to const)
- 如果要 return 的东西不是一个 local object，则可以 return by reference
- 传递者无需知道接收者是以 reference 形式接收

temp object（临时对象）：typename();
- 用构造函数作为隐式类型转换函数时，会创建临时对象
- 建立一个没有命名的非堆（non-heap）对象，也就是无名对象时，会产生临时对象
- 函数返回一个对象值时，会产生临时对象，函数中的返回值会以值拷贝的形式拷贝到被调函数栈中的一个临时对象


```
void func1(Cls* pobj) { pobj->xxx(); }
void func2(Cls pobj) { pobj.xxx(); }
void func3(Cls& pobj) { pobj.xxx(); }
//func2和func3 被调用端写法相同

Cls obj;
func1(&obj);
func2(obj);
func3(obj);
//func2和func3 调用端写法相同

//以下被视为same signature，所以二者不能同时存在
double imag(const double& im) const { ... }
double imag(const double im) const { ... } //Ambiguity
       ---------------------------- 这部分叫signature
```


## 右值引用

右值引用就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值

右值引用可实现转移语义（Move Sementics）和精确传递（Perfect Forwarding），它的主要目的有两个方面：
- 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率
- 能够更简洁明确地定义泛型函数
