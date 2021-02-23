
Object Oriented Programming(OOP), Object Oriented Design(OOD)
- Inheritance（继承）
- Composition（复合）
- Delegation（委托）

composition（复合）：表示has-a

composition（复合）关系下的构造和析构：
- 构造由内而外：Container的构造函数首先调用Component的default构造函数，然后才执行自己
```C++
Container::Container(...) : Component() { ... };
```
- 析构由外而内：Container的析构函数首先执行自己，然后才调用Component的析构函数
```C++
Container::~Container() : ~Component() { ... };
```

Delegation（委托）：Composition by reference
```
// Handle/Body
// pimpl point to implement
// class String对外不变，class StringRep实现可以随时变动
// 编译防火墙：class String不用重新编译，只要重新编译class StringRep
class StringRep;
class String {
public:
  String();
  String(const char* s);
  String(const String& s);
  String& operator=(const Strubg& s);
  ~String();
  ...
private:
  StringRep* rep; //pimpl
};

class StringRep {
friend class String;
  StringRep(const char* s);
  ~StringRep();
  int count; //reference counting
  char* rep;
};
```

Inheritance（继承）：表示is-a
```
struct _List_node_base
{
  _List_node_base* _M_next;
  _List_node_base* _M_prev;
};

template<typename _Tp>
struct _List_node
  : public _List_node_base
{
  _Tp _M_data;
}
```

Inheritance（继承）关系下的构造和析构：
- 构造由内而外：Derived的构造函数首先调用Base的default构造函数，然后才执行自己
```C++
Derived::Derived(...) : Base() { ... };
```
- 析构由外而内：Derived的析构函数首先执行自己，然后才调用Base的析构函数
```C++
Derived::~Derived() : ~Base() { ... };
```

base class的dtor必须是virtual，否则会出现undefined behavior

Inheritance（继承）with virtual functions（虚函数）
- non-virtual函数：你不希望derived class重新定义（override，重写）它
- virtual函数：你希望derived class重新定义（override，重写）它，且你对它已有默认定义
- pure virtual函数：你希望derived class一定要重新定义（override，重写）它，且你对它没有默认定义
```
class Shape {
public:
  virtual void draw() const=0; //pure virtual
  virtual void error(const std::string& msg); //impure virtual
  int objectID() const; //non-virtual
  ...
};

class Rectangle : public Shape { ... };
class Ellipse : public Shape { ... };
```