# HOI4 Patcher

这是一个用于自动为Hearts of Iron IV (HOI4)游戏执行文件打补丁的工具。

## 构建要求

- CMake 3.20或更高版本
- 支持C++20的现代C++编译器（如Visual Studio 2019/2022, GCC 10+, Clang 10+）

## 构建步骤

1. 创建构建目录：
```bash
mkdir build
cd build
```

2. 生成构建文件：
```bash
cmake ..
```

3. 编译项目：
```bash
cmake --build .
```

编译完成后，可执行文件将位于`build/bin`目录下。

## 使用方法

1. 将编译好的`hoi4_patcher.exe`放在HOI4游戏主目录下（与hoi4.exe同目录）
2. 运行`hoi4_patcher.exe`
3. 程序将自动检测并应用补丁

## 注意事项

- 在运行补丁程序前，建议备份原始的hoi4.exe文件
- 确保有足够的磁盘空间和管理员权限
