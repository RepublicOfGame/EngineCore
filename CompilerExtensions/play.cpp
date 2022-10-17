#define Refl __attribute__((annotate("reflect")))

typedef int MyType1;
typedef MyType1 MyType2;

class SuerBase {
    Refl int q;
};

class MyBaseClass1 : SuerBase {
    Refl int aa;
};

class MyBaseClass2 : SuerBase {
    int bb;
};

class MyClass : MyBaseClass1 {
public:
    Refl int a = 0;
    Refl MyType2 testField;

    MyClass() {}

    virtual void myMethod() const {};
    static const int myStaticField;

    static int myStaticMethod();
};
