# PeriSci Hello (v0.1.5)

这是 PeriSci 的最小可运行示例，用于验证：
- `core` 可以编译成库
- `api` 依赖 `core` 且可以编译成库
- 示例程序只 `#include <perisci/api/api.hpp>` 即可运行

## 构建方式（从仓库根目录）

建议使用 out-of-source build，并推荐 Ninja（单配置）：

### Debug（推荐）

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

### Release

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

> 说明：`cmake -S . -B build` 会自动创建 `build/` 目录，无需手动 `mkdir build`。

## 运行

使用顶层 CMake 的常见布局（bin/lib）时，可执行文件位于：

```
./build/bin/perisci-hello
```

预期输出类似：

```
Hello, PeriSci!
Version: 0.1.5
Build: PeriSci (api) v0.1.5
```

## 运行测试（推荐）

```
ctest --test-dir build --output-on-failure
```
