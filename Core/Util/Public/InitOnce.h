#pragma once


namespace Util{
    typedef void(*OnceFunc)();

    template<typename T>
    struct Once {
        explicit Once(T Runnable){
            Runnable();
        }
    };
}

#define CONCAT(a,b) a##b
#define InitOnce(Func) static Util::Once<typeof(Func)> CONCAT(OnceVar, __COUNTER__) (Func)
