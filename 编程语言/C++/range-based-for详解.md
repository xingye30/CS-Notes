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
