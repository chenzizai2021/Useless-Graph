#ifndef __ExDraw__
#define __ExDraw__

inline void ULGswap(slong&a,slong&b)
{slong tmp=a;
 a=b;
 b=tmp;
}
inline void Line(ExBMP&EBMP,slong stx,slong sty,slong enx,slong eny,const byte&R=255,const byte&G=255,const byte&B=255,const byte&T=255)
{LINE_START_PLACE:
 if(abs(enx-stx)>abs(eny-sty))
   {if(stx>enx)
      {ULGswap(stx,enx);
       ULGswap(sty,eny);
	  }
	if(stx<0)
	  {sty=(-stx)*(eny-sty)/(enx-stx)+sty;
	   stx=0;
	   goto LINE_START_PLACE;
	  }
	if(stx>=EBMP.W)return;
	if(enx<0)return;
	if(enx>=EBMP.W)
	  {eny=((slong)EBMP.W-1-stx)*(eny-sty)/(enx-stx)+sty;
	   enx=EBMP.W-1;
	   goto LINE_START_PLACE;
	  }
	for(slong i=stx;i<=enx;i++)
       {EBMP.Setpix(i,(i-stx)*(eny-sty)/(enx-stx)+sty,R,G,B,T);
       }
   }
 else
   {if(sty>eny)
      {ULGswap(sty,eny);
       ULGswap(stx,enx);
	  }
	if(sty<0)
	  {stx=(0-sty)*(enx-stx)/(eny-sty)+stx;
	   sty=0;
	   goto LINE_START_PLACE;
	  }
	if(sty>=EBMP.H)return;
	if(eny<0)return;
	if(eny>=EBMP.H)
	  {enx=((slong)EBMP.H-1-sty)*(enx-stx)/(eny-sty)+stx;
	   eny=EBMP.H-1;
	   goto LINE_START_PLACE;
	  }
    for(slong i=sty;i<=eny;i++)
       {EBMP.Setpix((i-sty)*(enx-stx)/(eny-sty)+stx,i,R,G,B,T);
       }
   }
}
#endif
