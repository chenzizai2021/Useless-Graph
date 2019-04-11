#ifndef __ExBitMap__
#define __ExBitMap__
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
{byte *c;
 ulong W,H;
 ExBMP(const ulong&_W,const ulong&_H)
 {W=_W;H=_H;
  c=new byte [W*H*4];
  memset(c,(byte)255,W*H);
 }
 ~ExBMP()
 {delete[]c;
 }
 void SetWH(const ulong&_W,const ulong&_H)
 {delete[]c;
  W=_W;H=_H;
  c=new byte [W*H*4];
  memset(c,(byte)255,W*H);
 }
 byte&R(const ulong&x,const ulong&y)
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4];
 }
 byte&G(const ulong&x,const ulong&y)
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4+1];
 }
 byte&B(const ulong&x,const ulong&y)
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4+2];
 }
 byte constR(const ulong&x,const ulong&y)const
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4];
 }
 byte constG(const ulong&x,const ulong&y)const
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4+1];
 }
 byte constB(const ulong&x,const ulong&y)const
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4+2];
 }
 byte&alpha(const ulong&x,const ulong&y)
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4+3];
 }
 byte constalpha(const ulong&x,const ulong&y)const
 {if(x>=W||y>=H)return byte_null;
  else return c[(y*W+x)*4+3];
 }
 void Setpix(const ulong&x,const ulong&y,const byte&R,const byte&G,const byte&B,const byte&alpha=255)
 {if(x>=W||y>=H)
    {return;
    }
  else
    {c[(y*W+x)*4]=R;
     c[(y*W+x)*4+1]=G;
     c[(y*W+x)*4+2]=B;
     c[(y*W+x)*4+3]=alpha;
    }
 }
};
////////////
//合并图像//
//////////// 
ExBMP&merge(const ExBMP&_back,const ExBMP&_top,const ulong&x,const ulong&y)
{ulong W=_back.W>_top.W?_back.W:_top.W;
 ulong H=_back.H>_top.H?_back.H:_top.H;
 ExBMP ret(W+x,H+y);
 for(ulong i=0;i<_top.W;i++)
    for(ulong j=0;j<_top.H;j++)
       {if(i+x>=_back.W||j+y>=_back.H)break;
	    byte _end=alpha(_back.constalpha(i+x,j+y),_top.constalpha(i,j));
        if(_end)ret.Setpix(i+x,j+y,merge(_back.constR(i+x,j+y),_top.constR(i,j),_back.constalpha(i+x,j+y),_top.constalpha(i,j),_end),merge(_back.constG(i+x,j+y),_top.constG(i,j),_back.constalpha(i+x,j+y),_top.constalpha(i,j),_end),merge(_back.constB(i+x,j+y),_top.constB(i,j),_back.constalpha(i+x,j+y),_top.constalpha(i,j),_end),_end);
        else ret.Setpix(i+x,j+y,255,255,255,0);
       }
 return ret;
}
////////////
//截取图像// 
////////////
ExBMP&GetRect(const ExBMP&_from,const ulong&x,const ulong&y,const ulong&W,const ulong&H)
{ExBMP ret(W,H);
 for(ulong i=0;i<W;i++)
    for(ulong j=0;j<H;j++)
       {ret.Setpix(i,j,_from.constR(i+x,j+y),_from.constG(i+x,j+y),_from.constB(i+x,j+y),_from.constalpha(i+x,j+y));
       }
 return ret;
}
#endif
