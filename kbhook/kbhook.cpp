#include "pch.h"
#include "kbhook.h"
#include<fstream>

#pragma data_seg("shared")
HHOOK _hook = 0;
HWND hwnd = 0;
bool ignoring = 0;
#pragma data_seg()
#pragma comment(linker, "/SECTION:shared,RWS")

LRESULT CALLBACK hook(int c, WPARAM w, LPARAM l)
{
	if (c == HC_ACTION) {
		if (hwnd) {
			auto msg = (l & (1 << 31)) ? WM_KEYUP : WM_KEYDOWN;
			if (w == VK_IGNORE) {
				ignoring = msg == WM_KEYDOWN;
			}
			else if (w == VK_SEND)
				PostMessageA(hwnd, WM_SENDBACK, 0, 0);
			else if(!ignoring)
				PostMessageA(hwnd, msg, w, l);
		}
	}
	if (w >= 0x88 && w <= 0x8F)return 1;//

	return CallNextHookEx(_hook, c, w, l);
}

bool __stdcall init(HHOOK a, HWND b) {
	if (hwnd)return hwnd == b;
	_hook = a;
	hwnd = b;
	return true;
}