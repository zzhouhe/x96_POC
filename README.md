# x96_POC
A poc of embedding x64 code into x86 PE file.

1. Run x64 code in a x86 .exe file.
2. Save a 8-byte value in r12 register, so that it can not be detected form the x86 virtual memory space.

The compiled .exe file can run under Win10(x64, 1903), it depends on the version of x86 ntdll.dll in the system.
