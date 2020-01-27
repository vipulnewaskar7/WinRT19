# COM Containment Demo

## Steps to run

### DLL Server (Inner)

#### **1-a. Build and create inner dll file**   
>_**Kindly use 64-bit command prompt**   
>**Since we have to create 64-bit dll and client**_

```D:\WinRT19\01-CMD\Assignment-12> cd ContainmentWithRegFile\Server\ContainmentInnerComponentWithRegFile```   
```D:\WinRT19\01-CMD\Assignment-12\ContainmentWithRegFile\Server\ContainmentInnerComponentWithRegFile> cl.exe ContainmentInnerComponentWithRegFile.cpp /LD /link user32.lib kernel32.lib gdi32.lib ole32.lib /DEF:ContainmentInnerComponentWithRegFile.def /SUBSYSTEM:WINDOWS /MACHINE:X64```

This will generate **.obj, .dll, .lib, .exp** files for inner component.   
Copy **.dll** file to desired location.

### DLL Server (Outer)

#### **1-b. Build and create outer dll file**   

```D:\WinRT19\01-CMD\Assignment-12> cd ContainmentWithRegFile\Server\ContainmentOuterComponentWithRegFile```   
```D:\WinRT19\01-CMD\Assignment-12\ContainmentWithRegFile\Server\ContainmentOuterComponentWithRegFile> cl.exe ContainmentOuterComponentWithRegFile.cpp /LD /link user32.lib kernel32.lib gdi32.lib ole32.lib /DEF:ContainmentOuterComponentWithRegFile.def /SUBSYSTEM:WINDOWS /MACHINE:X64```

This will generate **.obj, .dll, .lib, .exp** files for outer component.   
Copy **.dll** file to desired location.
   
#### **2. Reg file edit**   
Please copy absolute paths of both .dll files at specified place in .reg file.   
>_**Remember use double back-slash (\\\\), instead of single one (\\)**_

### Client
#### **3. Client program build and compile.**   
   
```D:\WinRT19\01-CMD\Assignment-12> cd ContainmentWithRegFile\Client```   
```D:\WinRT19\01-CMD\Assignment-12\ContainmentWithRegFile\Client> cl.exe ClientOfContainmentComponentWithRegFile.cpp.cpp /link user32.lib kernel32.lib gdi32.lib ole32.lib /SUBSYSTEM:WINDOWS /MACHINE:X64```   

This will generate a **.exe**, which will use **.dll** generated in earlier step.   