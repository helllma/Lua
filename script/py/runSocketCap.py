#!/usr/bin/env python
#coding=gbk
import win32api
import win32con
import time
import string

from ctypes import *

kernel32 = windll.kernel32
#定义数据结构中的字段类型

WORD      = c_ushort
DWORD     = c_ulong
LPBYTE    = POINTER(c_ubyte)
LPTSTR    = POINTER(c_char)
HANDLE    = c_void_p
#定义函数中的初始化变量值

CREATE_NEW_CONSOLE    = 0x00000010
PROCESS_ALL_ACCESS    = 0x001F0FFF
INFINITE              = 0xFFFFFFFF

#STARTUPINFO数据结构

class STARTUPINFO(Structure):
    _fields_ = [
        ("cb",            DWORD),       
        ("lpReserved",    LPTSTR),
        ("lpDesktop",     LPTSTR), 
        ("lpTitle",       LPTSTR),
        ("dwX",           DWORD),
        ("dwY",           DWORD),
        ("dwXSize",       DWORD),
        ("dwYSize",       DWORD),
        ("dwXCountChars", DWORD),
        ("dwYCountChars", DWORD),
        ("dwFillAttribute",DWORD),
        ("dwFlags",       DWORD),
        ("wShowWindow",   WORD),
        ("cbReserved2",   WORD),
        ("lpReserved2",   LPBYTE),
        ("hStdInput",     HANDLE),
        ("hStdOutput",    HANDLE),
        ("hStdError",     HANDLE),
        ]

#PROCESS_INFORMATION数据结构
class PROCESS_INFORMATION(Structure):
    _fields_ = [
        ("hProcess",    HANDLE),
        ("hThread",     HANDLE),
        ("dwProcessId", DWORD),
        ("dwThreadId",  DWORD),
        ]

 


class debugger():
    def __init__(self):
        #pass
        self.h_process = None
        self.pid = None
        self.debugger_active = False

    def load(self,path_to_exe):

        #实例化上述两个数据结构，并设置标志，这里是现实在桌面上（也可以隐藏，因设置的标志不同而不同）
        creation_flags = CREATE_NEW_CONSOLE
        startupinfo = STARTUPINFO()
        process_information = PROCESS_INFORMATION()
        startupinfo.dwFlags = 0x1
        startupinfo.wShowWindow = 0x0
        startupinfo.cb = sizeof(startupinfo)
        #调用win32中的函数CreateProcessA打开所给应用程序

        if kernel32.CreateProcessA(path_to_exe,
                                   None,
                                   None,
                                   None,
                                   None,
                                   creation_flags,
                                   None,
                                   None,
                                   byref(startupinfo),
                                   byref(process_information)):
            print "[*] We have successfully launched the process!"
            print "[*] PID: %d" % process_information.dwProcessId
        else:
            print "[*] Error: 0xx." % kernel32.GetLastError()
        #return process_information.dwProcessId
'''键位码表：
字母和数字键     数字小键盘的键       功能键         其它键 
      键   键码   键   键码     键   键码    键      键码 
      A   65       0   96        F1   112     Backspace    8 
      B   66       1   97        F2   113     Tab       9 
      C   67       2   98        F3   114     Clear      12 
      D   68       3   99        F4   115     Enter      13 
      E   69       4   100       F5   116     Shift      16 
      F   70       5   101       F6   117     Control     17 
      G   71       6   102       F7   118      Alt       18 
      H   72       7   103       F8   119     Caps Lock    20 
      I   73       8   104       F9   120     Esc       27 
      J   74       9   105       F10  121     Spacebar    32 
      K   75       *   106       F11  122     Page Up     33 
      L   76       +   107       F12  123     Page Down    34 
      M   77       Enter 108       --   --      End       35 
      N   78       -   109       --   --       Home      36 
      O   79       .   110       --   --      Left Arrow   37 
      P   80       /   111       --   --      Up Arrow    38 
      Q   81       --   --       --   --      Right Arrow   39 
      R   82       --   --       --   --      Down Arrow    40 
      S   83       --   --       --   --      Insert      45 
      T   84       --   --       --   --      Delete      46 
      U   85       --   --       --   --      Help       47 
      V   86       --   --       --   --      Num Lock     144 
      W   87          
      X   88      
      Y   89      
      Z   90      
      0   48      
      1   49      
      2   50       
      3   51       
      4   52       
      5   53       
      6   54       
      7   55       
      8   56       
      9   57
'''
#输入字符串转换为对应按键事件。
def InputString(text):
    text=string.upper(text)
    for char in text:
        win32api.keybd_event(ord(char),0,0,0)

if __name__ == "__main__":
    debugger = debugger()
    debugger.load("C:\\Program Files\\SocksCapV2\\sc32.exe")

time.sleep(0.5)
InputString('ipcc')
#发送tab
win32api.keybd_event(9,0,0,0)
InputString('9c25d527ff')
#发送Enter
win32api.keybd_event(13,0,0,0)
