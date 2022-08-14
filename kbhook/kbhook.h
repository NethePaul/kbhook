#pragma once
#include"pch.h"
#ifdef KBHOOK_EXPORTS
#define API extern "C" __declspec(dllexport)
#elif
#define API extern "C" __declspec(dllimport)
#endif

constexpr auto VK_IGNORE = 0x88;
constexpr auto VK_SEND = 0x89;
constexpr auto WM_SENDBACK = WM_USER + 1;

API void __stdcall init(HHOOK hook, HWND hwnd);
API LRESULT CALLBACK hook(int, WPARAM, LPARAM);



#undef API