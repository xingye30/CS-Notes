设计模式 Prototype
```
enum imageType
{
  LSAT, SPOT
};

class Image
{
public:
  virtual void draw() = 0;
  static Image* findAndClone(imageType);
protected:
  virtual imageType returnType() = 0;
  virtual Image* clone() = 0;
  //As each subclass of Image is declared, it registers its prototype
  static void addPrototype(Image* image)
  {
    _prototypes[_nextSlot++] = image;
  }
private:
  //addPrototype() saves each registered prototype
  static Image* _prototpes[10];
  static int _nextSlot;
};

Image* Image::_prototypes[];
int Image::_nextSlot;

//Client calls this public static member function when it need an instance of an Image subclass
Image* Image::findAndClone(imageType type)
{
  for (int i = 0; i < _nextSlot; i++)
    if (_prototypes[i]->returnType() == Type)
      return _prototypes[i]->clone();
}

class LandSatImage : public Image
{
public:
  imageType returnType() {
    return LSAT;
  }
  void draw() {
    cout << "LandSatImage::draw" << _id << endl;
  }
  //when clone() is called, call the one-argument ctor with a dummy arg
  Image* clone() {
    return new LandSatImage(1);
  }
protected:
  //This is only called from clone()
  LandSatImage(int dummy) {
    _id = _cout++;
  }
private:
  //Mechanism for initializing an Image subclass - this causes the default ctor to be called, which registers the subclass's prototype
  static LandSatImage() {
    addPrototype(this);
  }
  //Nominal "state" per instance mechanism
  int _id;
  static int _count;
};

//Register the subclass's prototype
LandSatImage LandSatImage::_landSatImage;
//Initialize the "state" per instance mechanism
int LandSatImage::_count = 1;
```