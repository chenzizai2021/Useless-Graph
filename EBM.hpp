#ifndef __ExBMPGrap__
#define __ExBMPGrap__

using namespace std;
//////////////////
//              //
//图形库基础部分//
//              // 
//////////////////

//////////////
//透明度合并// 
//////////////
byte alpha(const byte&_one,const byte&_another)
{return (byte)((ushort)_one+(ushort)_another-((ushort)_one*(ushort)_another/(ushort)255));}
////////////
//颜色合并// 
////////////
byte merge(const byte&_one,const byte&_another,const byte&__one,const byte&__another,const byte&__end)
{return (byte)(((ushort)_one*((ushort)255-(ushort)__another)*((ushort)__one/(ushort)255)+(ushort)_another*((ushort)__another))/(ushort)__end);
}
////////
//空位//
////////
byte byte_null;
//////////////
//图像结构体//
////////////// 
struct ExBMP
{byte *c,*a;
 ulong W,H;
 ExBMP(const ulong&_W,const ulong&_H)
 {W=_W;H=_H;
  c=new byte [W*H*3];
  a=new byte [W*H];
  memset(a,(byte)255,W*H);
 }
 ~ExBMP()
 {delete[]c;
  delete[]a;
 }
 void SetWH(const ulong&_W,const ulong&_H)
 {delete[]c;
  delete[]a;
  W=_W;H=_H;
  c=new byte [W*H*3];
  a=new byte [W*H];
  memset(a,(byte)255,W*H);
 }
 inline byte&pixB(const ulong&x,const ulong&y)
 {return(x>=W||y>=H)?byte_null:c[(y*W+x)*3];
 }
 inline byte&pixG(const ulong&x,const ulong&y)
 {return(x>=W||y>=H)?byte_null:c[(y*W+x)*3+1];
 }
 inline byte&pixR(const ulong&x,const ulong&y)
 {return(x>=W||y>=H)?byte_null:c[(y*W+x)*3+2];
 }
 inline byte constpixB(const ulong&x,const ulong&y)const
 {return(x>=W||y>=H)?byte_null:c[(y*W+x)*3];
 }
 inline byte constpixG(const ulong&x,const ulong&y)const
 {return(x>=W||y>=H)?byte_null:c[(y*W+x)*3+1];
 }
 inline byte constpixR(const ulong&x,const ulong&y)const
 {return(x>=W||y>=H)?byte_null:c[(y*W+x)*3+2];
 }
 inline byte&alpha(const ulong&x,const ulong&y)
 {return(x>=W||y>=H)?byte_null:a[y*W+x];
 }
 inline byte constalpha(const ulong&x,const ulong&y)const
 {return(x>=W||y>=H)?byte_null:a[y*W+x];
 }
 inline void Setpix(const ulong&x,const ulong&y,const byte&R,const byte&G,const byte&B,const byte&alpha=255)
 {if(x>=W||y>=H)
    {return;
    }
  else
    {const ulong apos=(y*W+x),pos=apos*3;
	 c[pos]=B;
     c[pos+1]=G;
     c[pos+2]=R;
     a[apos]=alpha;
    }
 }
};
////////////
//合并图像//
//////////// 
void merge(ExBMP&_back,const ExBMP&_top,const ulong&x,const ulong&y)
{for(ulong i=0;i<_top.W;i++)
    for(ulong j=0;j<_top.H;j++)
       {if(i+x>=_back.W||j+y>=_back.H)continue;
	    byte _end=alpha(_back.constalpha(i+x,j+y),_top.constalpha(i,j));
        if(_end)_back.Setpix(i+x,j+y,merge(_back.constpixR(i+x,j+y),_top.constpixR(i,j),_back.constalpha(i+x,j+y),_top.constalpha(i,j),_end),merge(_back.constpixG(i+x,j+y),_top.constpixG(i,j),_back.constalpha(i+x,j+y),_top.constalpha(i,j),_end),merge(_back.constpixB(i+x,j+y),_top.constpixB(i,j),_back.constalpha(i+x,j+y),_top.constalpha(i,j),_end),_end);
        else _back.Setpix(i+x,j+y,255,255,255,0);
       }
}
////////////
//截取图像// 
////////////
ExBMP GetRect(const ExBMP&_from,const ulong&x,const ulong&y,const ulong&W,const ulong&H)
{ExBMP ret(W,H);
 for(ulong i=0;i<W;i++)
    for(ulong j=0;j<H;j++)
       {ret.Setpix(i,j,_from.constpixR(i+x,j+y),_from.constpixG(i+x,j+y),_from.constpixB(i+x,j+y),_from.constalpha(i+x,j+y));
       }
 return ret;
}
#endif
