# EngineCore

#### 工程结构

```shell
├── Application               应用层
│   └── main.cpp
├── Core                      引擎核心
│   └── Net                   网络通信层
│   └── Serialization         序列化
├── CompilerPlugin            Clang 编译器插件
├── Test                      单元测试
```

#### CMake Info
- Compiler
  - GCC 11+ With C++23

- 第三方依赖
  - OpenSSL
  - Libevent release-2.1.12-stable
  - GoogleTest release-1.12.1