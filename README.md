# my-cpp-tutorial

> 在macOS arm64机器上不要用gcc编译，会找不到标准库。就用clang和clang++。

### 1 QUICK START

```shell
git clone git@github.com:Bannirui/my-cpp-tutorial.git

chmod +x ./build.sh

./build.sh
```

### 2 imgui

imgui本身不是cmake项目

- fork到自己仓库用cmake组织，添加到当前项目中
- 直接添加到当前项目进行编译库