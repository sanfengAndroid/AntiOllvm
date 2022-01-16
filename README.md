# AntiOllvm
### Automatically deobfuscate binaries and generate new binaries.

## Chinese Help
中文帮助点击 [帮助](README_CN.md)

## Decriptor

Software obfuscation protection is very common these days. Although this protects the rights and interests of normal developers, it also provides convenience for the authors of malware and viruses. They can also use obfuscation to protect malware. This is a security analyst. A great hindrance, they have to spend a lot of time to analyze and sort out the logic, AntiOllvm provides automatic de-obfuscation function, which greatly reduces unnecessary analysis time, and it is not only de-obfuscation.

This software uses [retdec](https://github.com/avast/retdec) to convert binary code to `LLVM IR` code, optimize and remove the obfuscated part, and use [LLVM](https://github.com/llvm/llvm-project) recompile it to generate a new binary file corresponding to the symbol address of the original binary file, and at the same time ensure the semantic correctness of the code, the original obfuscated function body must be larger than the unobfuscated function body, so after optimization Recompile writes code to original file location and fixes relocations using global variables. 


## Official website [https://antiollvm.com](https://antiollvm.com) (coming soon) 

## Software purchase

|    				| China |Other Regions|Binding Device|Number of Bindings|Features Restrictions 					  |Follow-up Feature Restrictions|     Bonus     |Windows x64| Linux  x64       |macOS      		  |
|:--:				|:----: |:------:	  |:------:		 |:------:			|:------: 							   	  |:----------:					 |:-------------:|:----: 	 |:-----: 		   |:----:  		  |
|Trial				|   \   |    \   	  |   \    		 |    \   			|Only Arm, does not support recompilation |   \        					 |       \       | Support   |Subsequent opening|Subsequent opening|
|Annual subscription|9600￥ |  1650\$	  |  1 device  	 |    3 time  		|  None     							  |Additional charges may apply  | Now-01/18/2023| Support   |Subsequent opening|Subsequent opening|
|Permanent			|38000￥|  6800\$	  |  1 device    |   15 times   	|  None     							  | None 						 |     Unlimited | Support   |Subsequent opening|Subsequent opening|

- Purchase example
   - For example, if you purchase 1 year on 01/15/2022, the actual validity period is 01/15/2022 - 01/18/2024, and if you purchase two years, the validity period is 01/15/2022 - 01/18/2025 and so on.
   - For example, if you purchase 1 year on 06/01/2022, the validity period is 06/01/2022 - 01/18/2024
   - Purchase after 01/18/2023, such as 02/01/2023 purchase for one year, the validity period is 02/01/2023 - 02/01/2024
   - There is no limit to the validity period if you purchase the permanent version
- Binding device restrictions
   - At present, both annual and permanent users can only bind one device at the same time.
- Example of binding times
   - The number of bindings will not be deducted for the first binding of the device
   - For example, if you want to change computer after binding computer A, you must first unbind it on computer A and then bind it on computer B. At the same time, the number of bindings will be deducted once. When the number of bindings is 0, the device cannot be changed.
   - Computer A can be windows/linux/mac, computer B can also be windows/linux/mac, that is to say, it can be bundled with the same system, or it can be bundled with different systems 

- Contact information
   - Telegram Group [t.me/antiollvm](https://t.me/antiollvm)
   - Email beichenzhizuoshi@163.com
   - WeChat public account: sanfengAndroid逆向安全
   - QQ group: [839141004](https://jq.qq.com/?_wv=1027&k=vNKrvgND)
- At present, there may be some problems. The first purchase gift is valid until 01/18/2023. If you encounter any problems, you can report it through the contact information above. Please be patient and wait for the repair.
- Trial version download [click](https://github.com/sanfengAndroid/AntiOllvm/releases/tag/antiollvm-trial)
- Download the official version, please contact me through the above contact information 

## Current development timeline
1. Add [goron](https://github.com/amimo/goron) version of indirect jump to de-obfuscate
2. Enable `mac x86`, `mac arm`, `Linux X64` versions

Please follow the official account or join the above `TG` `QQ` group for the latest news 

## Using help
[Click](doc/README.md) 

## Development progress

| Architecture | ELF | COFF | Mach-O |
| :----:       | :-: | :--: | :----: |
| Arm          | Yes |      | Yes    |
| Arm64        | Yes |      | Yes    |
| X86          |     |      |        |
| X86_64       |     |      |        | 

## Instructions for use

- This project is a paid project, and this repository will only store the source code and binary files of the description files and some test samples
- Everyone is welcome to provide samples (the more complex the better) to my mailbox [beichenzhizuoshi@163.com](https://mail.163.com/), you can also submit **issues** in this warehouse with samples and instructions , please indicate **binary architecture and file format** in the title when sending the sample The **obfuscation difficulty level (1-3)**, I will reply you with the deobfuscated binary after the deobfuscation passed 

## Disclaimer
AntiOllvm is a software that automatically de-obfuscates binary files. It is suitable for software security researchers and software security enthusiasts to use security products for learning and research. Do not use it for unauthorized and illegal purposes.

When you use this security product for research/testing, you should ensure that the behavior complies with local laws and regulations and has sufficient authorization. If you have any illegal behavior in the process of using this security product, you shall bear the corresponding consequences by yourself, and we will not bear any legal and joint responsibility.

Before you use this security product, please read it carefully and fully understand the contents, limitations, disclaimers or other terms involving your significant rights and interests. Unless you have fully read, fully understood and accepted all the terms of this agreement, please do not use this security product.

Your use behavior or your acceptance of this Agreement in any other express or implied manner shall be deemed that you have read and agreed to be bound by this Agreement. 

## directory description

- Each test directory contains the corresponding test source code, and the preset static library (not obfuscated, obfuscated), the bin in the corresponding directory generates binary files related to the architecture and file format, binary files and static libraries Without `-obf` suffix is generated without obfuscation, with `-obf` suffix is generated after obfuscation, with `-anti` in the binary directory is the de-obfuscated binary output.
- For the description of each test item, please refer to the `doc` directory document in the corresponding directory
- [OpenSSL Test](OpenSSLTest/doc/README_CN.md)
- [Arm64 Test](Arm64Test/README_CN.md) 


## [personal blog](https://sanfengandroid.github.io/blog)

Including technical article sharing, software instructions, video demonstrations, etc. 

## Software Future

- Open `X86`, `X86_64` deobfuscation support
- IDA plugin, convenient de-obfuscation, better optimized de-obfuscation using IDA analysis results
- Develop simulation execution to realize cross-platform binary file tracking operation on PC, such as algorithm analysis, etc.
- IDA virtual debugging, built on simulated execution.

## Quote

### retdec [https://github.com/avast/retdec](https://github.com/avast/retdec)

### LLVM [https://github.com/llvm/llvm-project](https://github.com/llvm/llvm-project/)

