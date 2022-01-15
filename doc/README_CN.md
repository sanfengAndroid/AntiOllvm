## 目录说明
保存 `AntiOllvm` 软件使用说明

## 软件帮助截图
![help](img/help_img.png)

## 参数介绍
- `--buy` 查看有关购买信息
- `-s` 关闭程序部分额外输出，目前无额外输出内容

- `-m|--mode` 设置输入文件的模式，`bin` 模式代表文件是正常可解析的二进制格式，没有加壳等，可以正常读取文件的架构、文件类型、起始函数、虚拟地址、符号表等等。`raw` 模式是资源模式，需要用户自己设置文件的解析方式才能读取，如设置 `-a` 文件目标指令集架构，`-e` 大小端等等。默认是 `bin` 模式

- `-p|--pdb` 输入文件的调试信息，便于更好的分析函数，没有则忽略。
- `--config` 设置软件配置文件路径，默认路径使用当前软件目录下的 `config/decompiler-config.json`，使用默认配置即可。
- `-l` 输出优化后的 `LLVM 位码`，可用来检查错误。

- `--select-ranges` 设置输入文件解码的范围，虚拟起始地址 - 虚拟结束地址，通常一个函数设置一个范围，避免解码不必要的指令。如果是 `bin` 模式则是正常读取到的函数地址，`raw` 模式是相对于 `--raw-section-vma` 的偏移，即起始地址 = 函数在文件位置 raw-section-vma。注意如果解码函数是Arm Thumb函数则需要 起始地址 + 1，用来标识该函数是Thumb模式，否者会被认为是Arm模式导致解码错误。

- `--select-functions` 设置解码函数名称，仅适用于 `bin` 模式，该函数必须在符号表中。

- `--function-args-num` 修改函数的参数数量，如果解码的函数数量多于实际参数，则可以手动设置参数数量，生成更加优化的结果。格式为：函数起始地址=数量，方法名称=数量
- `--bogus-opt-rule` 指定虚假控制流的匹配规则，详细帮助见下面
- `-a|--arch` 设置输入文件的目标指令集架构，`raw` 模式必须设置
- `-e|--endian` 设置输入文件的大小端，`raw` 模式必须设置
- `-b|--bit-size` 设置了 `-a` 后会自动调整位大小，可以不用管
- `--raw-section-vma` `raw` 模式设置文件的起始虚拟地址
- `--raw-entry-point` `raw` 模式设置入口函数的虚拟地址，目前不解码入口函数
- `--ar-index`、`--ar-name` 选择解码归档文件中的索引或名字，例如静态库文件，实际混淆中基本不使用
- `--timeout` 设置软件运行超时时间（单位秒），默认不限制
- `--max-memory` 限制使用最大内存(单位Kb)，默认 实际内存/ 2
- `--no-memory-limit` 关闭内存使用限制
- `-h` 查看帮助信息
- `--version` 查看版本信息

## 使用注意
- 软件仅解码 `--select-functions`，`--select-ranges` 设置的函数，不支持全部解码
- 当一个函数太大时，最好每次只解码一个函数，避免占用内存太多，函数太大内部数据分析占用内存较大，且计算次数较多，请耐心等待

## bogus-opt-rule 规则
- 它是用来配置去除虚假流的规则，实际上软件内部是优先运行 `Z3` 优化，经过 `Z3` 优化已去除大部分的虚假控制流，但是有些不可达代码块没有完全删除
- 自带默认配置如下，文件整体是 JSON 格式，内部包含多个匹配规则
  ```Json
  {
    "standardOllvm_0":{
      "enable":true,
      "comment":"Standard OLLVM produces optimizations for global variables < 10",
      "code":"ICVib2d1c19zdGF0ZSA9IGxvYWQgaTMyLCBpMzIqIEBib2d1c19nbG9iYWwsIGFsaWduIDQKICVjb25kID0gaWNtcCBzZ3QgaTMyICVib2d1c19zdGF0ZSwgJWNvbnN0YW50CiAlY29uc3RhbnRfMSA9IGFkZCBuc3cgaTMyICVjb25zdGFudCwgMQogJWNvbmQubm90ID0gaWNtcCBzbHQgaTMyICVib2d1c19zdGF0ZSwgJWNvbnN0YW50XzEKICVzdGF0ZV90ID0gc2VsZWN0IGkxICVjb25kLm5vdCwgaTMyICVzdGF0ZTAsIGkzMiAlc3RhdGUxCiAlc3RhdGUgPSBzZWxlY3QgaTEgJWNvbmQsIGkzMiAlc3RhdGVfdCwgaTMyICVzdGF0ZTE=",
      "replace":{
        "%bogus_state":0
      },
      "global_constant_propagate":{                        
        "enable": true,
        "@bogus_global": 0
          },
      "got":true,
      "swap_select_cond":true
    }
  }
  ```
- 具体规则解释如下
  ```Json
  {
    "standardOllvm_0":{         // 自定义规则名称
      "enable":true,            // true开启该规则，否者不匹配
      "comment":"Standard OLLVM produces optimizations for global variables < 10",     // 自定义注释
      "code":"ICVib2d1c19zdGF0ZSA9IGxvYWQgaTMyLCBpMzIqIEBib2d1c19nbG9iYWwsIGFsaWduIDQKICVjb25kID0gaWNtcCBzZ3QgaTMyICVib2d1c19zdGF0ZSwgJWNvbnN0YW50CiAlY29uc3RhbnRfMSA9IGFkZCBuc3cgaTMyICVjb25zdGFudCwgMQogJWNvbmQubm90ID0gaWNtcCBzbHQgaTMyICVib2d1c19zdGF0ZSwgJWNvbnN0YW50XzEKICVzdGF0ZV90ID0gc2VsZWN0IGkxICVjb25kLm5vdCwgaTMyICVzdGF0ZTAsIGkzMiAlc3RhdGUxCiAlc3RhdGUgPSBzZWxlY3QgaTEgJWNvbmQsIGkzMiAlc3RhdGVfdCwgaTMyICVzdGF0ZTE=", // 整体匹配的 LLVM IR 代码，是Base64编码，具体规则见下面分析
      "replace":{             // 替换列表
        "%bogus_state":0      // 要替换的变量列表, 格式为: 变量名称 = 值, 其中 `%`为局部变量，`@`为全局变量,与LLVM规则相同
      },
      "global_constant_propagate":{   // 全局常量的传播，如果规则匹配则会将该全局变量的所有引用全部替换为常量                     
        "enable": true,               // 控制是否开启常量传播
        "@bogus_global": 0            // 要替换的全局变量: 变量名称 = 值
          },
      "got":true,                     // 是否是got全局变量，如果是got变量则要加载两次
      "swap_select_cond":true         // 是否可以交换 select 指令的操作数
    }
  }
  ```
- 默认配置 `code` 如下:
  ```llvm
  %bogus_state = load i32, i32* @bogus_global, align 4  
  %cond = icmp sgt i32 %bogus_state, %constant
  %constant_1 = add nsw i32 %constant, 1
  %cond.not = icmp slt i32 %bogus_state, %constant_1
  %state_t = select i1 %cond.not, i32 %state0, i32 %state1
  %state = select i1 %cond, i32 %state_t, i32 %state1
  ```
  它是标准的 LLVM IR 代码，代码中所有局部变量都必须要有名称，否者无法识别局部变量，局部变量 `%` 开头，全局变量 `@` 开头，上面的代码翻译为伪代码就是
  ```cpp
    int y;
    void fun(){
      int constant,state0,state1; // 任意值
      int bogus_state = y;
      bool cond = bogus_state > constant;
      int constant_1 = constant + 1;
      bool cond_not = bogus_state < constant_1;
      int state_t = cond_not ? state0: state1;
      int state = cond ? state_t : state1;
    }
  ```
  例如实际ollvm混淆中
  ```c
    int y;
    void main(){
      int state0 = 0x12345;
      int state1 = 0x23456;
      int state;
      if(y < 9 + 1){
        state = state0; // 分支1
        ...
      }else{
        state = state1; // 分支2
        ...
      }
      if(y > 9){
        state = state;  // 分支3
        ...
      }else{
        state = state1; // 分支4
        ...
      }
    
    }
  ```
  这里不管 y的值是多少最终 state 都是 0x23456,因此如果我们能识别它是一个无用的虚假控制变量则可以简化它。这是 Z3 优化不完全导致,虽然最终不影响指令的正确性,但是在后续去除平坦化时可能会出错,因为我们不知道 y 的值则会假设 y < 10 和 y >=10 两种情况,这样就可能走到 `分支2` 和 `分支3`这两个本不该执行的路径,从而多保留了这不可达分支。

- 匹配规则是以匹配`code`中的最后一条指令为准，当指令相同时就会查找它的使用值，按照该引用链往上查找如果匹配则按照规则替换值
- 具体匹配规则如下,代码中总共包含以下几种元素  
  - 定义的局部变量,出现在等号左侧,它可以匹配任意一个局部变量
  - 未定义的全局变量,如 `%constant`,它可以匹配任意一个局部变量和任意一个常量
  - 全局变量,如  `@bogus_global`,它可以匹配任意一个全局变量
  - 常量 如上面的 `add nsw i32 %constant, 1` 中的`1`,只能匹配常量本身
  - 指令码,则匹配自身指令
- 当满足规则时会进行替换,替换如下
  - 规则 `"%bogus_state":0` 则将所有使用到 `%bogus_state` 的地方替换为 `0`
  - 规则全局变量传播`"@bogus_global": 0` 则将所有 `load i32, i32* @bogus_global` 的指令的结果替换为 `0`,这个全局变量可能在方法其它地方使用,或者在其它方法使用,我们都将替换所有加载指令为0
  - 开启 `got` 时,替换如下指令为0
    ```llvm
      %1 = load i32*, i32** @bogus_global
      %2 = load i32, i32* %1
    ```
    这相当于 `ELF` 中的 `got` 表,第一次加载得到全局变量的真实地址,第二次加载才得到全局变量的值
  - `swap_select_cond` 交换 select 指令的两个操作数, 即 `state_t` 与 `state1` 交换,同时匹配
    ```llvm
      %state = select i1 %cond, i32 %state_t, i32 %state1
      %state = select i1 %cond, i32 %state1, i32 %state_t
    ```
    其中一个满足则认定为匹配



## 使用示例
- 去混淆正常二进制文件
  ```shell
  antiollvm.exe .\libnative-lib.so --select-ranges 0x26300-0x26698,0x1b89c-0x1c918 --select-functions JNI_OnLoad
  ```
- 去混淆二进制资源文件
  ```shell
  antiollvm.exe -m raw -a arm -e little --raw-section-vma 0 --raw-entry-point 0 --select-ranges 0x1000-0x2000 libtest.so 
  ```

## 试用版限制
- 只支持 `Arm` 指令集
- 每次只能设置一个 `select-ranges/select-functions`
- 不支持混淆太复杂或太大的函数
- 不支持重编译二进制代码，仅输出优化后的 `LLVM IR`
- 有效期 7 天
