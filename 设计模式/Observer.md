设计模式 Observer
```
class Subject 
{
  int m_value;
  vector<Observer*> m_views;
public:
  void attach(Observer* obs)
  {
    m_views.push_back(obs);
  }
  void set_val(int value)
  {
    m_value = value;
    notify();
  }
  void notify()
  {
    for (int i = 0; i < m_views.size(); ++i)
      m_views[i]->update(this, m_value);
  }
};

class Observer
{
public:
  virtual void update(Subject* sub, int value) = 0;  
};
```