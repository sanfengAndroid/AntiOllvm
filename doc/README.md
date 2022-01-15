## directory description
Save the `AntiOllvm` software instructions

## Chinese Documentation
[点击](README_CN.md)


## Software help screenshot
![help](img/help_img.png)

##Parameter introduction

- `-s` Turn off the extra output of the program part, there is no extra output at present

- `-m|--mode` Set the mode of the input file, `bin` mode means that the file is in a normal parseable binary format, without packing, etc., you can normally read the file's architecture, file type, start function, virtual Addresses, symbol tables, etc. The `raw` mode is a resource mode, and the user needs to set the parsing method of the file to read it, such as setting the `-a` file target instruction set architecture, `-e` size end and so on. Default is `bin` mode

- `-p|--pdb` Input the debug information of the file for better analysis of the function, otherwise ignore it.
- `--config` Set the software configuration file, just use the default configuration.
- `-l` Output optimized `LLVM bitcode`, which can be used to check for errors.

- `--select-ranges` Set the range of input file decoding, virtual start address - virtual end address, usually a function sets a range to avoid decoding unnecessary instructions. If it is `bin` mode, it is the function address read normally, `raw` mode is the offset relative to `--raw-section-vma`, that is, the starting address = function in the file position raw-section-vma . Note that if the decoding function is an Arm Thumb function, the start address + 1 is required to indicate that the function is in Thumb mode, otherwise it will be regarded as Arm mode and cause a decoding error.

- `--select-functions` Set the decoding function name, only for `bin` mode, the function must be in the symbol table.

- `function-args-num` Modify the number of parameters of the function. If the number of decoded functions is more than the actual parameters, you can manually set the number of parameters to generate more optimized results. The format is: function start address=num, function name=num
- `--bogus-opt-rule` specifies the matching rule for bogus control flow, see below for details 
- `-a|--arch` set the target instruction set architecture of the input file, `raw` mode must be set
- `-e|--endian` sets the size endian of the input file, `raw` mode must be set
- `-b|--bit-size` After setting `-a`, the bit size will be adjusted automatically, you can ignore it
- `--raw-section-vma` `raw` mode sets the starting virtual address of the file
- `--raw-entry-point` `raw` mode sets the virtual address of the entry function, currently the entry function is not decoded
- `--ar-index`, `--ar-name` Select the index or name in the decoded archive file, such as static library file, which is basically not used in actual obfuscation
- `--timeout` Set the software running timeout (in seconds), the default is not limited
- `--max-memory` limit the use of the maximum memory (unit Kb), the default actual memory / 2
- `--no-memory-limit` turn off memory usage limit
- `-h` to see help information
- `--version` View version information

## Usage Notes
- The software only decodes the functions set by `--select-functions` and `--select-ranges`, and does not support all decoding
- When a function is too large, it is best to decode only one function at a time to avoid taking up too much memory. If the function is too large, the internal data analysis takes up a lot of memory, and the number of calculations is large, please wait patiently 

# bogus-opt-rule
- It is used to configure the rules for removing spurious flows. In fact, the software runs `Z3` optimization first. After `Z3` optimization, most of the spurious control flows have been removed, but some unreachable code blocks are not completely removed.
- The default configuration is as follows. The whole file is in JSON format and contains multiple matching rules. 
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
- Specific rules are explained below
  ```Json
  {
    "standardOllvm_0":{       // custom rule name
      "enable":true,          // true enables the rule, otherwise it does not match
      "comment":"Standard OLLVM produces optimizations for global variables < 10", // custom comments
      "Code": "ICVib2d1c19zdGF0ZSA9IGxvYWQgaTMyLCBpMzIqIEBib2d1c19nbG9iYWwsIGFsaWduIDQKICVjb25kID0gaWNtcCBzZ3QgaTMyICVib2d1c19zdGF0ZSwgJWNvbnN0YW50CiAlY29uc3RhbnRfMSA9IGFkZCBuc3cgaTMyICVjb25zdGFudCwgMQogJWNvbmQubm90ID0gaWNtcCBzbHQgaTMyICVib2d1c19zdGF0ZSwgJWNvbnN0YW50XzEKICVzdGF0ZV90ID0gc2VsZWN0IGkxICVjb25kLm5vdCwgaTMyICVzdGF0ZTAsIGkzMiAlc3RhdGUxCiAlc3RhdGUgPSBzZWxlY3QgaTEgJWNvbmQsIGkzMiAlc3RhdGVfdCwgaTMyICVzdGF0ZTE =",  // the overall match LLVM IR code, Base64 encoding, specific rules see below Analysis
      "replace":{           // replace list
        "%bogus_state":0    // A list of variables to be replaced, the format is: variable name = value, where `%` is a local variable and `@` is a global variable, the same as LLVM rules
      },
      "global_constant_propagate":{   // Propagation of global constants, if the rule matches, all references to the global variable will be replaced with constants
        "enable": true,       // Controls whether to enable constant propagation
        "@bogus_global": 0    // global variable to replace: variable name = value
          },
      "got":true,             // Whether it is a got global variable, if it is a got variable, it will be loaded twice
      "swap_select_cond":true // Whether the operands of the select instruction can be swapped
    }
  }
  ```` 
- The default configuration `code` is as follows:
   ````llvm
   %bogus_state = load i32, i32* @bogus_global, align 4
   %cond = icmp sgt i32 %bogus_state, %constant
   %constant_1 = add nsw i32 %constant, 1
   %cond.not = icmp slt i32 %bogus_state, %constant_1
   %state_t = select i1 %cond.not, i32 %state0, i32 %state1
   %state = select i1 %cond, i32 %state_t, i32 %state1
   ```` 
  It is standard LLVM IR code. All local variables in the code must have names. Otherwise, local variables cannot be recognized. Local variables begin with `%` and global variables begin with `@`. The above code translated into pseudo code is
   ````cpp
     int y;
     void fun(){
       int constant,state0,state1; // any value
       int bogus_state = y;
       bool cond = bogus_state > constant;
       int constant_1 = constant + 1;
       bool cond_not = bogus_state < constant_1;
       int state_t = cond_not ? state0: state1;
       int state = cond ? state_t : state1;
     }
   ```` 
  For example, in the actual olvm confusion
   ````c
     int y;
     void main(){
       int state0 = 0x12345;
       int state1 = 0x23456;
       int state;
       if(y < 9 + 1){
         state = state0; // branch 1
         ...
       }else{
         state = state1; // branch 2
         ...
       }
       if(y > 9){
         state = state; // branch 3
         ...
       }else{
         state = state1; // branch 4
         ...
       }
    
     }
   ```` 
   Here the final state is 0x23456 no matter what the value of y is, so it can be simplified if we can identify it as a useless bogus control variable. This is caused by the incomplete optimization of Z3. Although it does not affect the correctness of the instruction in the end, it may make mistakes in the subsequent removal of flattening, because we do not know the value of y and assume two cases of y < 10 and y >= 10, In this way, it is possible to go to `branch 2` and `branch 3`, which should not be executed, thus retaining the unreachable branch. 

- The matching rule is based on matching the last instruction in `code`. When the instruction is the same, it will find its use value, and follow the reference chain to find it. If it matches, replace the value according to the rules
- The specific matching rules are as follows, the code contains the following elements in total
  - The defined local variable, which appears on the left side of the equal sign, can match any local variable
  - Undefined global variables, such as `%constant`, which can match any local variable and any constant
  - Global variables, such as `@bogus_global`, which can match any global variable
  - Constants such as `1` in `add nsw i32 %constant, 1` above, can only match the constant itself
  - Instruction code, it matches its own instruction
- When the rule is met, it will be replaced, the replacement is as follows
  - The rule `"%bogus_state":0` replaces all uses of `%bogus_state` with `0`
  - The rule global variable propagation `"@bogus_global": 0` will replace the result of all `load i32, i32* @bogus_global` instructions with `0`, this global variable may be used elsewhere in the method, or used in other methods , we will replace all load instructions with 0
  - When `got` is enabled, replace the following commands with 0
    ````llvm
      %1 = load i32*, i32** @bogus_global
      %2 = load i32, i32* %1
    ````
    This is equivalent to the `got` table in `ELF`. The real address of the global variable is obtained after the first load, and the value of the global variable is obtained after the second load.
  - `swap_select_cond` swaps the two operands of the select instruction, ie `state_t` and `state1`, while matching
    ````llvm
      %state = select i1 %cond, i32 %state_t, i32 %state1
      %state = select i1 %cond, i32 %state1, i32 %state_t
    ````
    One of them is consider
    
## Usage example
- Deobfuscate normal binaries
   ```shell
   antiollvm.exe .\libnative-lib.so --select-ranges 0x26300-0x26698,0x1b89c-0x1c918 --select-functions JNI_OnLoad
   ````
- Deobfuscate binary resource files
  ```shell
  antiollvm.exe -m raw -a arm -e little --raw-section-vma 0 --raw-entry-point 0 --select-ranges 0x1000-0x2000 libtest.so 
  ```` 

## Trial Limitations
- Only supports `Arm` instruction set
- Only one `select-ranges/select-functions` can be set at a time
- Does not support obfuscating functions that are too complex or too large
- Recompile binary code is not supported, only output optimized `LLVM IR`
- Valid for 7 days 