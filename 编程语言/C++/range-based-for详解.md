# ranged-base-for 详解

使用形式
```
for (decl : coll) {
  statement
}
```

```C++
vector<double> vec;
...
for (auto elem : vec) {   //pass by value
  cout << elem << endl;
}

for (auto& elem : vec) {   //pass by reference
  elem *= 3;
}
```

实质
```C++
for (decl : coll) {
  statement
}
//转化为
for (auto _pos = coll.begin(), _end = coll.end(); _pos != _end; ++_pos) {
  decl = *_pos;
  statement
}
//或
for (auto _pos= begin(coll), _end = end(coll); _pos != _end; ++_pos) { //both begin() and end() are global
  decl = *_pos;  
  statement
}

template<typename T>
void printElements(cosnt T& coll)
{
  for (const auto& elem : coll) {
    cout << elem << endl;
  }
}
//转化为 
for(auto _pos = coll.begin(); _pos != coll.end(); ++_pos) {
  const auto& elem = *_pos;
  cout << elem << endl;
}
```

在 range-based-for 中，初始化 decl 可能会用到 non explicit 类型转换
```
class C
{
public:
  explicit C(const string& s); //explicit type conversion from strings
  ...
};

vector<string> vs;
for (const C& elem : vs) { //Error, no conversion from string to C defined 
  cout << elem << endl;
}
```
