From Inner Aggregation Server Project Folder : run ->

cl.exe AggregationInnerComponentWithRegFile.cpp /LD /link user32.lib kernel32.lib gdi32.lib ole32.lib /DEF:AggregationInnerComponentWithRegFile.def /SUBSYSTEM:WINDOWS /MACHINE:X64
-------------------------------------------------------------
From Outer Aggregation Server Project Folder : run ->

cl.exe AggregationOuterComponentWithRegFile.cpp /LD /link user32.lib kernel32.lib gdi32.lib ole32.lib /DEF:AggregationOuterComponentWithRegFile.def /SUBSYSTEM:WINDOWS /MACHINE:X64
-------------------------------------------------------------
Copy DLLs to System32 Folder
Merge Registry
-------------------------------------------------------------
From Client Project : run ->

cl.exe ClientOfAggregationComponentWithRegFile.cpp /link user32.lib kernel32.lib gdi32.lib ole32.lib /SUBSYSTEM:WINDOWS /MACHINE:X64