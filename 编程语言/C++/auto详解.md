# auto 详解

```C++
list<string> c;
...
list<string>::iterator ite;
ite = find(c.begin(), c.end(), target);

list<string> c;
...
auto ite = find(c.begin(), c.end(), target);

list<string> c;
...
auto ite; //错误
ite = find(c.begin(), c.end(), target);
```
