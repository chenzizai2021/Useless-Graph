#ifndef __WindowsPrint__
#define __WindowsPrint__

#include<windows.h>
void Print(HWND hwnd,const ExBMP&show,const ulong&x=0,const ulong&y=0)
{ulong nLB=(show.W*3+3)/4*4;
 byte *pda=new byte[nLB*show.H];
 for(int i=0;i<show.W;i++)
    {for(int j=0;j<show.H;j++)
        {pda[j*nLB+i*3]=show.constB(i,j);
         pda[j*nLB+i*3+1]=show.constG(i,j);
         pda[j*nLB+i*3+2]=show.constR(i,j);
        }
    }
 const ulong W=show.W,H=show.H;
 HDC tmp=GetDC(hwnd);
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
 SetDIBits(tmp,bmp,0,H,pda,&bmpInfo,DIB_RGB_COLORS);
 BitBlt(tmp,x,y,W,H,r,0,0,SRCCOPY);
 DeleteObject(bmp);
 DeleteDC(r);
 ReleaseDC(hwnd,tmp);
 DeleteDC(tmp);
 delete[]pda;
}

#endif
