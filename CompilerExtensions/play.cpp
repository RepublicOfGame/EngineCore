#define Refl __attribute__((annotate("reflect")))

typedef int MyType1;
typedef MyType1 MyType2;

class SuerBase {
    int q;
};

class MyBaseClass1 : virtual SuerBase {
    int aa;
};

class MyBaseClass2 : virtual SuerBase {
    int bb;
};

class MyClass : virtual MyBaseClass1, virtual MyBaseClass2 {
public:
    Refl MyType2 testField;

    MyClass() {}

    virtual void myMethod() const {};
    static const int myStaticField;

    static int myStaticMethod();
};
