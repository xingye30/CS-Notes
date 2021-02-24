# Uniform Initialization

初始化可能发生在（）、｛｝、=
```C++
Rect r1 = {3, 7, 20, 25, &area, &print};
Rect r1{3, 7, 20, 25};
int ia[6] = {27, 210, 12, 47, 109, 83};
```

C++11 引入了 uniform unitialization 的概念， 任何初始化动作可以使用一种共同语法：｛｝
- 编译器看到｛t1, t2, ..., tn｝便做出一个 initializaer_list<T>，它关联至一个 array<T, n>， 调用函数时该 array 内的元素可被编译器分解逐一传给函数
- 若函数参数是个 initializer_list<T>，调用函数时 array 内的元素不会被编译器分解

```C++
int values[]{1, 2, 3};
vector<int> v{2, 3, 5, 7, 11, 13, 17};
vector<string> cities{
  "Berlin", "New York", "London", "Braunschweig", "Cairo", "Cologne"
};
// 这形成一个 initializer_list<string>，背后有个 array<string, 6>
// 调用 vector<string> ctors 时编译器找到一个 vector<string> ctor 接收 tializer_list<string>
// 所有容器都有如此 ctor

complex<double> c{4.0, 3.0}; //equivalent to c(4.0, 3.0)
// 这形成一个 initializer_list<double>，背后有个 array<double, 2>
// 调用 complex<double> ctors 时该 array 内的两个元素被分解传给 ctor
// complex<double> 并无任何 ctor 接收 initializer_list<double>
```

## Initializer Lists

initializer list 强制进行值初始化：基本数据类型被初始化为 0 ，指针类型被初始化为 nullptr

```C++
int i;  // i has undefined value
int j{};  // j is initialized by 0
int *p;  // p has undefined value
int *q{}; //q us ubutuakuzed by nullptr
```

使用｛｝时不允许 narrowing initializations（窄化转换）
```C++
int x1(5.3); //OK
int x2 = 5.3; //OK
int x3{5.3}; //Error
```

为了支持用户自定义类型的 initializer lists， C++11 提供了类模版 std::initializer_list<>
```C+++
void print (std::initializer_list<int> vals)
{
  for (auto p = vals.begin(); p != valse.end(); ++p) { // a list of values
    std::cout << *p << "\n";
  }
}
```

当同时有特定数量参数和 initializer list 的构造函数版本时，initializer list 版本优先
```C++
class P
{
public:
  P(int a, int b) 
  {
    cout << "P(int, int), a =" << a << ", b = " << b << endl;
  }
  
  P(initializer_list<int> initlist)
  {
    cout << "P(initializer_list<int>), values = ";
    for (auto i : initlist)
      cout << i << ' ';
    cout << endl;
  }
};

P p(77, 5);  // P(int, int), a = 77, b = 5
P q{77, 5};  // P(initializer_list<int>), values =77 5
P r{77, 5, 42};  // P(initializer_list<int>), values =77 5 42
P s = {77, 5};  // P(initializer_list<int>), values =77 5
//如果没有 P(initializer_list<int> initlist)，P(int a, int b) 会被调用来初始化 q 和 s， 而 r 是非法的
```

initializer_list 对象关联着一个 array 但没有包含这个 array，因此拷贝 initializer_list 对象会导致两个对象关联相同的底层数据，是浅拷贝

这个 array 的生命周期和 initializer_list 对象一样
```C++
template<class _E>
class initializer_list
{
public:
  typedef _E value_type;
  typedef const _E& reference;
  typedef const _E& const_reference;
  typedef size_t size_type;
  typedef const _E* iterator;
  typedef const _E* const_iterator;
  
private:
  iterator _M_array;
  size_type _M_len;
  
  // The compiler can call a private constructor
  constexpr initializer_list(const_iterator __a, size_type __l)
  : _M_array(__a), _M_len(__l){ }
  
public:
  constexpr initializer_list() noexcept
  : _M_array(0), _N_len(0) { }
  
  // Number of elements
  constexpr size_type
  size() const noexcept { return _M_len; }
  
  // First element
  constexpr const_iterator
  begin() const noexcept { return _M_array; }
  
  // One past the last element
  constexpr const_iterator
  end() const noexcept { return begin(); }
};
```

```C++
#include <initializer_list>

vector(initializer_list<value_type> __l,
       const allocator_type& __a = allocator _type())
    :_Base(__a)
{ _M_range_initialize(__I.begin(), __I.end(), random_access_iterator_tag()); }

vector& operator=(initializer_list<value_type> __U)
{ this->assign(__I.begin(), __I.end()); return *this; }

void insert(iterator __position, initializer_list<value_type> __I)
{ this->insert(__position, __I.begin(), __I.end()); }

void assign(initailizer_list<value_type> __I)
{ this->assign(__I.begin(), __I.end()); }

vector<int> v1 { 2, 5, 7, 13, 69, 83, 50 };
vector<int> v2 ( { 2, 5, 7, 13, 69, 83, 50 } );
vector<int> v3;
v3 = { 2, 5, 7, 13, 69, 83, 50 };
v3.insert(v3.begin() + 2, { 0 , 1, 2, 3, 4});

for (auto i : v3)
  cout << i << ' ';
cout << endl;  //2 5 0  1 2 3 4 7 13 69 83 50


template<typename _Tp>
  inline _Tp
  min(initializer_list<_Tp> __l)
  { return *std::min_element(__l.begin(), __l.end()); }

template<typename _Tp>
  inline _Tp
  max(initializer_list<_Tp> __l)
  { return *std::max_element(__l.begin(), __l.end()); }

cout << max( {string("Ace"), string("Stacy"), string("Sabrina"), string("Barkley")}); //Stacy
cout << min( {string("Ace"), string("Stacy"), string("Sabrina"), string("Barkley")}); //Ace
cout << max( {54, 16, 48, 5} ); //54
cout << min( {54, 16, 48, 5} ); //5
```
