#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char far_jmp[10] = {0x78, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00};//403018
char secret[8] = {0,}; //40337c

void __declspec(naked) go_read() // 0x401000
{
	__asm{
		//__emit 0x49		//mov r12, 0x12345678
		//__emit 0xc7
		//__emit 0xc4
		//__emit 0x78
		//__emit 0x56
		//__emit 0x34
		//__emit 0x12

		__emit 0x90
		__emit 0x90
		__emit 0x90
		__emit 0x90
		__emit 0x90
		__emit 0x90
		__emit 0x90

		__emit 0x4c		//mov qword ptr ds:[0x40337c], r12
		__emit 0x89
		__emit 0x25
		__emit 0x6e
		__emit 0x23
		__emit 0x00
		__emit 0x00		//40100d

		__emit 0xb8		// mov eax, 403018h
		__emit 0x18
		__emit 0x30
		__emit 0x40
		__emit 0x00

		__emit 0x48
		__emit 0xff
		__emit 0x28
		
	}
}

void __declspec(naked) go_write() // 0x401020
{
	__asm{
		//__emit 0xcc
		__emit 0x49		//mov r12, 0x12345678
		__emit 0xc7
		__emit 0xc4
		__emit 0x78
		__emit 0x56
		__emit 0x34
		__emit 0x12

		__emit 0xb8		// mov eax, 403018h
		__emit 0x18
		__emit 0x30
		__emit 0x40
		__emit 0x00

		__emit 0x48
		__emit 0xff
		__emit 0x28
		
	}
}

void main()
{
	printf("go_read: %p\n", go_read);
	printf("go_write: %p\n", go_write);
	*(unsigned int *)far_jmp = 0x00401064;
	__asm{
		__emit 0xea
		__emit 0x20
		__emit 0x10
		__emit 0x40
		__emit 0x00
		__emit 0x33
		__emit 0x00
	}
L1://00401064
	printf("write data ok\n");
	system("pause");
	//printf("L: %p\n");
	*(unsigned int *)far_jmp = 0x0040108c;
	__asm{
		__emit 0xea
		__emit 0x00
		__emit 0x10
		__emit 0x40
		__emit 0x00
		__emit 0x33
		__emit 0x00
	}
L2: //0040108c
	
	printf("back to x86\n");
	printf("%p\n", *(int *)secret);
	system("pause");
}