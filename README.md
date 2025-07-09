# my-cpp-tutorial

> 在macOS arm64机器上不要用gcc编译，会找不到标准库。就用clang和clang++。

### 1 QUICK START

```shell
git clone --recurse-submodules git@github.com:Bannirui/my-cpp-tutorial.git
```

### 2 imgui

imgui本身不是cmake项目，fork到自己仓库用cmake组织，然后作为submodule添加到当前项目中

### 3 设置拒绝子模块变更

`vim .git/hooks/pre-commit`

```shell
#!/bin/sh
if git diff --cached --name-only | grep "^Hazel/vendor"; then
  echo "❌ Submodule changes are not allowed!"
  exit 1
fi
```

`chmod +x .git/hooks/pre-commit`