// maptester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <cstdio>
#include <random>
#include <ctime>

#define WIN32_LEAN_AND_MEAN

int main()
{
	srand(time(0));
	int magic = rand() % 1000;

	printf("magic number: %d\n", magic);

	void* mem = nullptr;
	mem = VirtualAlloc(NULL, sizeof(int), MEM_COMMIT, PAGE_READWRITE);
	printf("allocated memory at 0x%X\n Last Error: 0x%X\n", (DWORD)mem, GetLastError());
	memcpy(mem, &magic, sizeof(int));
	printf("copied magic number\n");

	system("pause");

    return 0;
}

