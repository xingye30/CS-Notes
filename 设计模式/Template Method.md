设计模式 Template Method
```
// Application framwork
class CDocument
{
public：
  void OnFileOpen()
  {
    ...
    Serialize(); //this->Serialize();  (*(this->vptr)[n])    (this);
    ...
  }
  virtual void Serialize() { };  
};

// Application
class CMyDoc : public CDocument
{
  virtual Serialize() { ... }
};

main()
{
  CMyDoc myDoc;
  ...
  myDoc.OnFileOpen(); //CDocument::OnFileOpen(&myDoc)
}
```