//设计模式 Adapter
template<class T>
class queue {
  ...
protected:
  deque<T> c; //底层容器
public:
  //以下完全利用c的操作函数完成
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  reference back() { return c.back(); }
  void push(const value_type& x) { c.push_back(x); }
  void pop() { c.pop_front(); }
}
```