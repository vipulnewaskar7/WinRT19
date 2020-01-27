# COM ClassFactory Demo

## Steps to run

### DLL Server

#### **1. Build and create dll file**   
>_**Kindly use 64-bit command prompt**   
>**Since we have to create 64-bit dll and client**_

```D:\WinRT19\01-CMD\Assignment-11> cd ClassFactoryDllServerWithRegFile```   
```D:\WinRT19\01-CMD\Assignment-11\ClassFactoryDllServerWithRegFile> cl.exe ClassFactoryDllServerWithRegFile.cpp /LD /link user32.lib kernel32.lib gdi32.lib ole32.lib /DEF:ClassFactoryDllServerWithRegFile.def /SUBSYSTEM:WINDOWS /MACHINE:X64```

This will generate **.obj, .dll, .lib, .exp** files.   
Copy **.dll** file to desired location.   
   
#### **2. Reg file edit**   
Please copy absolute path of .dll file at specified place in .reg file.   
>_**Remember use double back-slash (\\\\), instead of single one (\\)**_

### Client
#### **3. Client program build and compile.**   
   
```D:\WinRT19\01-CMD\Assignment-11> cd ClientOfClassFactoryDllServerWithRegFile```   
```D:\WinRT19\01-CMD\Assignment-11\ClientOfClassFactoryDllServerWithRegFile> cl.exe ClientOfClassFactoryDllServerWithRegFile.cpp /link user32.lib kernel32.lib gdi32.lib ole32.lib /SUBSYSTEM:WINDOWS /MACHINE:X64```   

This will generate a **.exe**, which will use **.dll** generated in earlier step.   