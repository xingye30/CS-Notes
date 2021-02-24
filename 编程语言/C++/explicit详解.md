# explicit详解

## explicit for ctors taking one argument

```C++
struct Complex
{
  int real. image;
  Complex(int re, int im = 0) : real(re), imag(im)
  { }
}

```
