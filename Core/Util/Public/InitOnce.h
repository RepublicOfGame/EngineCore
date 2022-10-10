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

#define InitOnce(Func) const static Util::Once __OnceVar (Func)
