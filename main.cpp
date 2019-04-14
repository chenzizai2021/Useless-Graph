#include <windows.h>
#include"ULG.h"
#include"ExDraw.hpp"
using namespace std;
const int W=640,H=480;
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{switch(Message)
 {case WM_DESTROY:
    {PostQuitMessage(0);
     break;
    }
  default:
    return DefWindowProc(hwnd,Message,wParam,lParam);
 }
 return 0;
}
HWND hwnd;
ExBMP a(W,H);
bool DrawDic=0;
DWORD WINAPI PRI(LPVOID lpParamter)
{while(true)
 {if(DrawDic)
    {Print(hwnd,a);
     DrawDic=0;
	}
 }
 return 0L;
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
 WNDCLASSEX wc;
 MSG Msg;
 memset(&wc,0,sizeof(wc));
 wc.cbSize=sizeof(WNDCLASSEX);
 wc.lpfnWndProc=WndProc;
 wc.hInstance=hInstance;
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
 wc.lpszClassName="ULG";
 wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
 wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
 if(!RegisterClassEx(&wc))
   {MessageBox(NULL,"Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
    return 0;
   }
 RECT ret={0,0,W,H};
 UINT dwStyleex=WS_EX_TOPMOST,dwStyle=WS_VISIBLE|WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX;
 AdjustWindowRectEx(&ret,dwStyle,false,dwStyleex);
 hwnd=CreateWindowEx(dwStyleex,"ULG","ULG",dwStyle,
      CW_USEDEFAULT, /* x */
      CW_USEDEFAULT, /* y */
      ret.right-ret.left, /* width */
      -ret.top+ret.bottom, /* height */
      NULL,NULL,hInstance,NULL);
 if(hwnd== NULL)
   {MessageBox(NULL,"Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
    return 0;
   }
 for(int i=0;i<W;i++)
    for(int j=0;j<H;j++)
       a.Setpix(i,j,255,255,255);
 int i=0,clr[3]={0,0,255},now=0;
 HANDLE PRIT = CreateThread(NULL, 0,PRI, NULL, 0, NULL);
 DrawDic=1;
 while(1)
 {if(PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
    {if(Msg.message==WM_QUIT)break;
     TranslateMessage(&Msg);
     DispatchMessage(&Msg);
	}
  if(1)
    {Line(a,0,i,i,H/2,clr[0],clr[1],clr[2]);
     i++;
     clr[now]++;
     clr[(now+2)%3]--;
     if(clr[now]==255)
       now=(now+1)%3;
     DrawDic=1;
    }
 }
 CloseHandle(PRIT);
 return Msg.wParam;
}
