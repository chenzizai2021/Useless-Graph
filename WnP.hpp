#ifndef __SHOWMAIN__
#define __SHOWMAIN__

#include<windows.h>
//#include"ExBMP.hpp"
//#include"ExBMPInf.h"
void Show(HWND hwnd,BYTE pData[],int W,int H,int x,int y)
{HDC tmp=GetDC(hwnd);
 HDC r=CreateCompatibleDC(tmp);
 HBITMAP bmp=CreateCompatibleBitmap(tmp,W,H);
 SelectObject(r,bmp);
 BITMAPINFO bmpInfo;
 bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
 bmpInfo.bmiHeader.biWidth = W;
 bmpInfo.bmiHeader.biHeight = -H;
 bmpInfo.bmiHeader.biPlanes = 1;
 bmpInfo.bmiHeader.biBitCount = 24;
 bmpInfo.bmiHeader.biCompression = BI_RGB;
 bmpInfo.bmiHeader.biSizeImage = 0;
 bmpInfo.bmiHeader.biXPelsPerMeter = 3000;
 bmpInfo.bmiHeader.biYPelsPerMeter = 3000;
 bmpInfo.bmiHeader.biClrUsed = 0;
 bmpInfo.bmiHeader.biClrImportant = 0;
 SetDIBits(tmp,bmp,0,H,pData,&bmpInfo,DIB_RGB_COLORS);
 BitBlt(tmp,x,y,W,H,r,0,0,SRCCOPY);
 DeleteObject(bmp);
 DeleteDC(r);
 ReleaseDC(hwnd,tmp);
 DeleteDC(tmp);
}
void Print(HWND hwnd,const ExBMP&show,const ulong&x=0,const ulong&y=0)
{ulong nLB=(show.W*3+3)/4*4;
 byte *pda=new byte[nLB*show.H];
 for(ulong i=0;i<show.W;i++)
    {for(ulong j=0;j<show.H;j++)
        {const ulong pos=j*nLB+i*3;
		 pda[pos]=show.constpixB(i,j);
         pda[pos+1]=show.constpixG(i,j);
         pda[pos+2]=show.constpixR(i,j);
        }
    }
 Show(hwnd,pda,show.W,show.H,x,y);
 delete[]pda;
}

#endif
