# EngineCore

### 工程结构

```shell
├── Application               应用层
│   └── main.cpp
├── Core                      引擎核心
│   └── Net                   网络通信层
│   └── Serialization         序列化
├── CompilerExtensions        Clang 编译器插件
├── Test                      单元测试
```

### CMake Info

- Compiler
    - GCC 11+ With C++23

- 第三方依赖
    - OpenSSL
    - Libevent release-2.1.12-stable
    - GoogleTest release-1.12.1
    - LLVM 13.0+

### Build

#### Windows

**1. 先安装 OpenSSL 和 LLVM 的预编译产物**

- Win64 OpenSSL v3.0.5(不是 Lite)
    - https://slproweb.com/products/Win32OpenSSL.html
- LLVM-15.0.2-win64.exe
    - https://github.com/llvm/llvm-project/releases/tag/llvmorg-15.0.2

**2. 添加环境变量**

⚠ 添加完后重启 IDE

```
D:\Program Files\LLVM\bin
D:\Program Files\LLVM\lib
```

**3. 修改源文件根目录下的 CMakeLists.txt**

```
# LLVM
SET(LLVM_DIR C:/Program\ Files/LLVM)
# OpenSSL
SET(OPENSSL_ROOT_DIR C:/Program Files/OpenSSL-Win64)
SET(OPENSSL_LIBRARIES C:/Program Files/OpenSSL-Win64/lib)
```

#### Linux & MacOS

自行摸索