#include <windows.h>
#include <iostream>
#include"ULG.h"
using namespace std;
const int W=200,H=200;
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

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
 WNDCLASSEX wc;
 HWND hwnd;
 MSG Msg;
 memset(&wc,0,sizeof(wc));
 wc.cbSize=sizeof(WNDCLASSEX);
 wc.lpfnWndProc=WndProc;
 wc.hInstance=hInstance;
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
 wc.lpszClassName="WindowClass";
 wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
 wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
 if(!RegisterClassEx(&wc))
   {MessageBox(NULL,"Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
    return 0;
   }
 RECT ret={0,0,W,H};
 UINT dwStyleex=WS_EX_TOPMOST,dwStyle=WS_VISIBLE|WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX;
 AdjustWindowRectEx(&ret,dwStyle,false,dwStyleex);
 hwnd=CreateWindowEx(dwStyleex,"WindowClass","Caption",dwStyle,
      CW_USEDEFAULT, /* x */
      CW_USEDEFAULT, /* y */
      ret.right-ret.left, /* width */
      -ret.top+ret.bottom, /* height */
      NULL,NULL,hInstance,NULL);
 if(hwnd== NULL)
   {MessageBox(NULL,"Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
    return 0;
   }
 ExBMP a(W,H);
 int R=0,G=0,B=0;
 int Ra=1,Ga=0,Ba=0;
 while(1)
 {if(PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
    {if(Msg.message==WM_QUIT)break;
     TranslateMessage(&Msg);
     DispatchMessage(&Msg);
	}
  for(ulong i=0;i<W;i++)
     for(ulong j=0;j<H;j++)
        {a.Setpix(i,j,R,G,B);
		}
  R+=Ra;
  G+=Ga;
  B+=Ba;
  if(R==255)
    {Ra=0;
     Ga=1;
	}
  if(G==255)
    {Ga=0;
     Ba=1;
	}
  if(B==255)
    {Ba=0;
	 Ra=-1;
	}
  if(R==0&&Ra==-1)
    {Ra=0;
     Ga=-1;
	}
  if(G==0&&Ga==-1)
    {Ga=0;
     Ba=-1;
	}
  if(B==0&&Ba==-1)
    {Ba=0;
     Ra=1;
	}
  Print(hwnd,a);
 }
 return Msg.wParam;
}
