# AntiOllvm

### 自动化去除二进制文件混淆并生成新的二进制文件

## 描述

&emsp;&emsp;现如今软件混淆保护很常见,这虽然保护了正常开发者的权益但同时也给那些恶意软件和病毒的作者提供了便利，他们也可以借助混淆来保护恶意软件，而这对安全分析人员是一个极大的阻碍，他们不得不花费大量的时间来分析理清逻辑，AntiOllvm 提供自动化去混淆功能,大大减少了不必要的分析时间，同时它不仅仅是去混淆。

&emsp;&emsp;本软件使用 [retdec](https://github.com/avast/retdec) 将二进制代码转换为 `LLVM IR` 代码后优化去掉混淆部分，并使用 [LLVM](https://github.com/llvm/llvm-project) 将其重新编译生成与原二进制文件符号地址相对应的新二进制文件，并同时确保代码的语义正确性，原混淆的函数体肯定大于未混淆时的函数体，因此在优化后重新编译将代码写入原文件位置并修复使用全局变量的重定位。

## 官方网站 [https://antiollvm.com](https://antiollvm.com)(即将开启)

## 软件购买

|    |  中国 |其它地区|绑定设备|换绑次数|功能限制 			|后续功能限制|    额外赠送   |Windows x64| Linux x64 |macOS	  |
|:--:|:----: |:------:|:------:|:------:|:------: 			|:----------:|:-------------:|:----: 	 |:-----: 	 |:----:  |
|试用|   \   |    \   |   \    |    \   |仅Arm,不支持重编译 |   \        |       \       | 	  支持   |后续开放	 |后续开放|
|包年|9600￥ |  1650\$|  1台   |    3   |  无     			|可能额外收费| 现在-2023.1.18| 	  支持   |后续开放	 |后续开放|
|永久|38000￥|  6800\$|  1台   |   15   |  无     			| 无额外收费 |     无限制    | 	  支持   |后续开放	 |后续开放|
- 购买举例
  - 例如在 2022.01.15号购买1年，则实际使用有效期是 2022.01.15 - 2024.01.18，购买两年则有效期是 2022.01.15 - 2025.01.18 以此类推
  - 例如在 2022.06.01 号购买1年,则有效期是 2022.06.01 - 2024.01.18
  - 在2023.01.18号以后购买，如 2023.02.01购买一年，则有效期是 2023.02.01 - 2024.02.01
  - 购买永久版本则不限制有效期
- 绑定设备限制
  - 目前包年和永久用户一个授权都只能同时绑定一台设备，如果要切换设备则需要换绑，并且扣除换绑次数
- 绑定次数举例
  - 首次绑定使用设备不扣除绑定次数
  - 例如绑定 A 电脑后现在要换电脑，则要先在 A 电脑解绑后再在 B 电脑上绑定，同时扣除一次绑定次数，当绑定次数为 0 时则不能再换绑设备
  - A 电脑可以是windows/linux/mac，B 电脑也可以是windows/linux/mac，也就是说可以同系统换绑，也可以不同系统换绑

- 联系方式
  - Telegram Group [TG](https://t.me/antiollvm)
  - 邮箱联系 beichenzhizuoshi@163.com
  - 微信公众号: sanfengAndroid逆向安全
  - QQ群: [839141004](https://jq.qq.com/?_wv=1027&k=vNKrvgND)
- 目前可能存在一些问题，因此首次购买赠送现在至2023.1.18的有效期，遇到问题可以在上面联系方式反馈，请耐心等待修复。

- 7天试用版仅支持 `Arm` 指令集，且不包含重编译功能
- 试用版下载 [点击](https://github.com/sanfengAndroid/AntiOllvm/releases/tag/antiollvm-trial)
- 正式版下载，请通过以上联系方式联系我


## 使用帮助
[点击查看](doc/README_CN.md)

## 目前开发时间线
1. 添加 [goron](https://github.com/amimo/goron) 版本的间接跳转去混淆
2. 开启 `mac x86`、`mac arm`、`Linux X64` 版本  

请关注公众号或加入上面的 `TG` `QQ`群获取最新消息

## 公众号

**关注我的公众号可以第一时间收到我的动态**

![](https://cdn.jsdelivr.net/gh/sanfengAndroid/sanfengAndroid.github.io@main/images/wechat_channel.png)

## 开发进度

|  架构  | ELF | COFF | Mach-O |
| :----: | :-: | :--: | :----: |
|  Arm   | Yes |      |  Yes   |
| Arm64  | Yes |      |  Yes   |
|  X86   |     |      |        |
| X86_64 |     |      |        |

## 使用说明

- 该项目是收费项目，本仓库只会存放说明文件和一些测试样本的源码和二进制文件
- 欢迎大家提供样本（越复杂越好）到我的邮箱 [beichenzhizuoshi@163.com](https://mail.163.com/)，也可在本仓库提交 **issues** 附带样本及说明，发送样本时请在标题上注明 **二进制架构及文件格式** 例如 **Arm-ELF 测试样本**, 内容上注明被混淆的 **函数名称或地址**，和你自认为的 **混淆难度等级（1-3）**，我会在去混淆通过后回复你去混淆后的二进制文件

## 免责申明
&emsp;&emsp;AntiOllvm是一款自动化去除二进制文件混淆的软件，适用于软件安全研究员、软件安全爱好者用于学习研究为主的安全产品，切勿用于未授权的非法用途。  

&emsp;&emsp;您在使用该安全产品进行研究/测试时，您应确保该行为符合当地的法律法规，并且拥有足够的授权。如您在使用该安全产品的过程中存在任何非法行为，您需自行承担相应后果，我们将不承担任何法律及连带责任。  

&emsp;&emsp;您在使用该安全产品前，请您务必审慎阅读，充分理解各条款内容、限制、免责条款或者其他涉及您重大权益的条款。除非您已充分阅读、完全理解并接受本协议所有条款，否者，请您不要使用该安全产品。  

&emsp;&emsp;您的使用行为或者您以其它任何明示或者默示方式表示接受本协议，即视为您已阅读并同意本协议的约束。

## 目录说明

- 每个测试目录下包含了对应的测试源代码，和预置的静态库（未混淆，已混淆），对应目录下的 bin 生成了与架构和文件格式相关的二进制文件，二进制文件与静态库不带 `-obf` 后缀的是未混淆生成的，带 `-obf` 后缀是混淆后生成的，二进制目录下带 `-anti` 是去混淆后的二进制输出。
- 具体每个测试项目的说明请查看对应目录下的 `doc` 目录文档
- [OpenSSL 测试](OpenSSLTest/doc/README.md)
- [Arm64 测试](Arm64Test/README.md)


## [个人博客](https://sanfengandroid.github.io/blog)

包含技术文章分享，软件使用说明,视频演示等等

## 软件未来

- 开放`X86`,`X86_64` 去混淆支持
- IDA 插件，便捷式去混淆，使用 IDA 分析结果更好优化去混淆
- 开发模拟执行，实现在 PC 上实现跨平台二进制文件跟踪运行，例如算法分析等等
- IDA 虚拟调试，建立在模拟执行上

## 引用

### retdec [https://github.com/avast/retdec](https://github.com/avast/retdec)

### LLVM [https://github.com/llvm/llvm-project](https://github.com/llvm/llvm-project/)


