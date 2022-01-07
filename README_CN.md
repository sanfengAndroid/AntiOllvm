# AntiOllvm

### 去除 Ollvm 混淆并生成与原始文件对应的二进制文件

## 公众号

**关注我的公众号可以第一时间收到我的动态**

![](https://cdn.jsdelivr.net/gh/sanfengAndroid/sanfengAndroid.github.io@main/images/wechat_channel.png)

## 描述

&emsp;&emsp;目前大量的恶意软件为了防止被分析，都加入了一定的保护措施，其中 **混淆** 对二进制文件分析影响巨大，例如恶意软件使用修改版算法与混淆加密了一个文件，如果你想还原文件就可能会分析它的算法，但是算法跟混淆结合后产生大量的无效指令以及 CFG 平坦化，这样会大大的增加分析时间。

&emsp;&emsp;本软件使用 [retdec](https://github.com/avast/retdec) 将二进制代码转换为 `LLVM IR` 代码后优化去掉混淆部分，并使用 [LLVM](https://github.com/llvm/llvm-project) 将其重新编译生成与原二进制文件符号地址相对应的新二进制文件，大部分情况下新二进制文件可以直接运行。并且尽最大可能完整的还原它的语义。

&emsp;&emsp;原混淆的函数体肯定大于未混淆时的函数体，因此在优化后重新编译将代码写入原文件位置并修复使用变量的重定位

## 开发进度

|  架构  | ELF | COFF | Mach-O |
| :----: | :-: | :--: | :----: |
|  Arm   | Yes |      |   Yes  |
| Arm64  | Yes |      |   Yes  |
|  X86   |     |      |        |
| X86_64 |     |      |        |

## 使用说明

- 该项目是收费项目，本仓库只会存放说明文件和一些测试样本的源码和二进制文件
- 目前还未提供可购买版本，鉴于目前不够稳定，样本量较少，后续稳定后会推出正式可购买版本
- 欢迎大家提供样本（越复杂越好）到我的邮箱 [beichenzhizuoshi@163.com](https://mail.163.com/)，也可在本仓库提交 **issues** 附带样本及说明，目前只接受 `Arm` 架构的 `ELF` 样本，发送样本时请在标题上注明 **二进制架构及文件格式** 例如 **Arm-ELF 测试样本**, 内容上注明被混淆的 **函数名称或地址**，和你自认为的 **混淆难度等级（1-3）**，我会在去混淆通过后回复你去混淆后的二进制文件

## 目录说明

- 每个测试目录下包含了对应的测试源代码，和预置的静态库（未混淆，已混淆），对应目录下的 bin 生成了与架构和文件格式相关的二进制文件，二进制文件与静态库不带 `-obf` 后缀的是未混淆生成的，带 `-obf` 后缀是混淆后生成的，二进制目录下带 `-anti` 是去混淆后的二进制输出。
- 具体每个测试项目的说明请查看对应目录下的 `doc` 目录文档
- [OpenSSL 测试](OpenSSLTest/doc/README_CN.md)
- [Arm64 测试](Arm64Test/README_CN.md)

## 软件购买
软件会在近期内发布版本，请关注上方公众号，或关注本仓库。开放后会第一时间更新

## [个人博客](https://sanfengandroid.github.io/)
包含技术文章分享，软件使用说明,视频演示等等

## 软件未来
- 开放`X86`,`X86_64` 去混淆支持
- IDA 插件，便捷式去混淆，使用IDA分析结果更好优化去混淆
- 开发模拟执行，实现在PC上实现跨平台二进制文件跟踪运行，例如算法分析等等
- IDA 虚拟调试，建立在模拟执行上


## 引用

### retdec [https://github.com/avast/retdec](https://github.com/avast/retdec)

### LLVM [https://github.com/llvm/llvm-project](https://github.com/llvm/llvm-project/)
