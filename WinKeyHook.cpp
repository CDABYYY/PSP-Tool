#include "WinKeyHook.h"
//静态变量类外初始化
HHOOK WinKeyHook::keyborard_hook_ = NULL;
std::function<void(int)> WinKeyHook::m_pressFunc = NULL;
std::function<void(int)> WinKeyHook::m_releaseFunc = NULL;
WinKeyHook::WinKeyHook()
{
	Q_ASSERT(!keyborard_hook_);
	//构造函数里把keyHookEvent函数的地址当钩子写入到windows消息循环
	keyborard_hook_ = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)keyHookEvent, GetModuleHandle(NULL), 0);
}

WinKeyHook::~WinKeyHook()
{
	//析构函数中释放这个钩子
	if (nullptr != keyborard_hook_)
	{
		UnhookWindowsHookEx(keyborard_hook_);
	}
}

void WinKeyHook::SetKeyPressCallBack(const std::function<void(int)> func)
{
	m_pressFunc = func;
}

void WinKeyHook::SetKeyReleaseCallBack(const std::function<void(int)> func)
{
	m_releaseFunc = func;
}

LRESULT CALLBACK WinKeyHook::keyHookEvent(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(keyborard_hook_, code, wParam, lParam);
	if (wParam == WM_KEYDOWN)
	{
		//用户按下了键盘按键
		if(m_pressFunc != NULL)
		m_pressFunc(((KBDLLHOOKSTRUCT*)lParam)->vkCode);
	}
	else if (wParam == WM_KEYUP)
	{
		//用户抬起了键盘按键
		if (m_releaseFunc != NULL)
			m_releaseFunc(((KBDLLHOOKSTRUCT*)lParam)->vkCode);
	}
	return CallNextHookEx(keyborard_hook_, code, wParam, lParam);
}