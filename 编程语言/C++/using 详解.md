# using 详解

## Type Alias

type alias 和 typedef 等价，可以出现在块作用域，类作用域和 namespace 作用域

```C++
// typedef void (*func)(int, int);
using func = void(*)(int, int);

void example(int, int) {}
func fn = example;
```

type alias 经常被用来隐藏一个模版参数
```C++
template<class CharT> using mystring = std::basic_string<CharT, std::char_traits<CharT>>;

mystring<char> str;
```

type alias can introduce a member typedef name
```C++
template<typename T>
struct Container {
  using value_type = T; // typedef T value_type;
};

template<typename Cntr>
void fn2(const Cntr& c) 
{
  typename Cntr::value_type n;
}
```

using-directives for namespace
```C++
using namespace std;
```

using-declarations for namespace members
```C++
using std::cout;
```

using-declarations for class members
```C++
protected:
  using _Base::_M_allocate;
  using _Base::_M_deallocate;
  using _Base::_S_nword;
  using _Base::_M_get_Bit_allocator;
```

