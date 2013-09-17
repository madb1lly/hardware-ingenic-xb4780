/*
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if HAVE_MALLOC_H
#include <malloc.h>
#endif

#include "../libjzcommon/com_config.h"
#include "libmpcodecs/img_format.h"
#include "libmpcodecs/mp_image.h"
#include "../libjzcommon/t_vputlb.h"

#include "libvo/fastmemcpy.h"
#include "libavutil/mem.h"
extern int use_jz_buf;
#undef printf
void mp_image_alloc_planes(mp_image_t *mpi) {
  // IF09 - allocate space for 4. plane delta info - unused
  unsigned char* data;
  int w,h,cw,ch,size;  
  w = mpi->width + 2*EDGE_WIDTH;
  h = mpi->height + 2*EDGE_WIDTH;
  cw = mpi->chroma_width + 2*EDGE_WIDTH;
  ch = mpi->chroma_height + 2*EDGE_WIDTH;

  int w_aln;
  int blk_w;
  blk_w = (w + 15)>>4;
  w_aln = blk_w*256;

  if(use_jz_buf)
    if (mpi->imgfmt == IMGFMT_IF09) {
#ifdef JZ_LINUX_OS
      mpi->planes[0]=jz4740_alloc_frame(NULL,256,mpi->bpp*mpi->width*(mpi->height+2)/8+
					mpi->chroma_width*mpi->chroma_height);
#else
      mpi->planes[0]=av_malloc(mpi->bpp*mpi->width*(mpi->height+2)/8+
			       mpi->chroma_width*mpi->chroma_height);
#endif
    }else{
#ifdef JZ_LINUX_OS
      data = jz4740_alloc_frame(NULL,256,mpi->bpp*w*(h+2)/8);
      mpi->planes[0]=data + (w/16)*256*(EDGE_WIDTH/16) + 256*(EDGE_WIDTH/16); 
#else
      mpi->planes[0]=av_malloc(mpi->bpp*mpi->width*(mpi->height+2)/8);
#endif
    }else
    if (mpi->imgfmt == IMGFMT_IF09) {
#ifdef JZ_LINUX_OS
      mpi->planes[0]=jz4740_alloc_frame(NULL,256,mpi->bpp*mpi->width*(mpi->height+2)/8+
					mpi->chroma_width*mpi->chroma_height);
#else
      mpi->planes[0]=av_malloc(mpi->bpp*mpi->width*(mpi->height+2)/8+
			       mpi->chroma_width*mpi->chroma_height);
#endif
    }else{
#ifdef JZ_LINUX_OS
      data = jz4740_alloc_frame(NULL,256,mpi->bpp*w*(h+2)/8);
      mpi->planes[0]=data + (w/16)*256*(EDGE_WIDTH/16) + 256*(EDGE_WIDTH/16); 
#else
      mpi->planes[0]=av_malloc(mpi->bpp*mpi->width*(mpi->height+2)/8);
#endif
    }

  if (mpi->flags&MP_IMGFLAG_PLANAR) {
    if(use_jz_buf){
      int bpp = IMGFMT_IS_YUVP16(mpi->imgfmt)? 2 : 1;
      // YV12/I420/YVU9/IF09. feel free to add other planar formats here...
      mpi->stride[0]=bpp*w_aln;
      mpi->stride[3]=bpp*mpi->chroma_width;
      if(mpi->num_planes > 2){
	mpi->stride[1]=(mpi->stride[0])>>1;
	mpi->stride[2]=bpp*mpi->width;
	if(mpi->flags&MP_IMGFLAG_SWAPPED){
	  // I420/IYUV  (Y,U,V)
	  mpi->planes[1]=mpi->planes[0]+mpi->stride[0]*mpi->height;
	  mpi->planes[2]=mpi->planes[1]+mpi->stride[1]*mpi->chroma_height;
	  if (mpi->num_planes > 3)
            mpi->planes[3]=mpi->planes[2]+mpi->stride[2]*mpi->chroma_height;
	} else {
	  mpi->planes[1] =((int)((mpi->planes[0] + w*h) + 256) & ~(256-1));
	
	  mpi->planes[2] = ((int)(mpi->planes[1] +w*(ch-EDGE_WIDTH)-256*(EDGE_WIDTH/16) + 256) & ~(256-1));
	  //if (mpi->num_planes > 3)
	  mpi->planes[3]=((int)((mpi->planes[2]+mpi->width*mpi->height)+256) & ~(256-1));
	}
      } else {
	// NV12/NV21
	mpi->stride[1]=mpi->chroma_width;
	mpi->planes[1]=mpi->planes[0]+mpi->stride[0]*mpi->height;
      }
    }else{
      int bpp = IMGFMT_IS_YUVP16(mpi->imgfmt)? 2 : 1;
      // YV12/I420/YVU9/IF09. feel free to add other planar formats here...
      mpi->stride[0]=mpi->stride[3]=bpp*mpi->width;
      if(mpi->num_planes > 2){
	mpi->stride[1]=mpi->stride[2]=bpp*mpi->chroma_width;
	if(mpi->flags&MP_IMGFLAG_SWAPPED){
	  // I420/IYUV  (Y,U,V)
	  mpi->planes[1]=mpi->planes[0]+mpi->stride[0]*mpi->height;
	  mpi->planes[2]=mpi->planes[1]+mpi->stride[1]*mpi->chroma_height;
	  if (mpi->num_planes > 3)
            mpi->planes[3]=mpi->planes[2]+mpi->stride[2]*mpi->chroma_height;
	} else {
	  // YV12,YVU9,IF09  (Y,V,U)
	  mpi->planes[2]=mpi->planes[0]+mpi->stride[0]*mpi->height;
	  mpi->planes[1]=mpi->planes[2]+mpi->stride[1]*mpi->chroma_height;
	  if (mpi->num_planes > 3)
            mpi->planes[3]=mpi->planes[1]+mpi->stride[1]*mpi->chroma_height;
	}
      } else {
	// NV12/NV21
	mpi->stride[1]=mpi->chroma_width;
	mpi->planes[1]=mpi->planes[0]+mpi->stride[0]*mpi->height;
      }
    }
  } else {
    mpi->stride[0]=mpi->width*mpi->bpp/8;
    if (mpi->flags & MP_IMGFLAG_RGB_PALETTE)
      {
#ifdef JZ_LINUX_OS
	mpi->planes[1] = jz4740_alloc_frame(NULL,256,1024);
#else
	mpi->planes[1] = av_malloc(1024);
#endif
      }
  }  
  mpi->flags|=MP_IMGFLAG_ALLOCATED;
}

mp_image_t* alloc_mpi(int w, int h, unsigned long int fmt) {
  mp_image_t* mpi = new_mp_image(w,h);

  mp_image_setfmt(mpi,fmt);
  mp_image_alloc_planes(mpi);

  return mpi;
}

void copy_mpi(mp_image_t *dmpi, mp_image_t *mpi) {
  if(mpi->flags&MP_IMGFLAG_PLANAR){
    memcpy_pic(dmpi->planes[0],mpi->planes[0], mpi->w, mpi->h,
	       dmpi->stride[0],mpi->stride[0]);
    memcpy_pic(dmpi->planes[1],mpi->planes[1], mpi->chroma_width, mpi->chroma_height,
	       dmpi->stride[1],mpi->stride[1]);
    memcpy_pic(dmpi->planes[2], mpi->planes[2], mpi->chroma_width, mpi->chroma_height,
	       dmpi->stride[2],mpi->stride[2]);
  } else {
    memcpy_pic(dmpi->planes[0],mpi->planes[0],
	       mpi->w*(dmpi->bpp/8), mpi->h,
	       dmpi->stride[0],mpi->stride[0]);
  }
}

void mp_image_setfmt(mp_image_t* mpi,unsigned int out_fmt){
    mpi->flags&=~(MP_IMGFLAG_PLANAR|MP_IMGFLAG_YUV|MP_IMGFLAG_SWAPPED);
    mpi->imgfmt=out_fmt;
    // compressed formats
    if(out_fmt == IMGFMT_MPEGPES ||
       out_fmt == IMGFMT_ZRMJPEGNI || out_fmt == IMGFMT_ZRMJPEGIT || out_fmt == IMGFMT_ZRMJPEGIB ||
       IMGFMT_IS_VDPAU(out_fmt) || IMGFMT_IS_XVMC(out_fmt)){
	mpi->bpp=0;
	return;
    }
    mpi->num_planes=1;
    if (IMGFMT_IS_RGB(out_fmt)) {
	if (IMGFMT_RGB_DEPTH(out_fmt) < 8 && !(out_fmt&128))
	    mpi->bpp = IMGFMT_RGB_DEPTH(out_fmt);
	else
	    mpi->bpp=(IMGFMT_RGB_DEPTH(out_fmt)+7)&(~7);
	return;
    }
    if (IMGFMT_IS_BGR(out_fmt)) {
	if (IMGFMT_BGR_DEPTH(out_fmt) < 8 && !(out_fmt&128))
	    mpi->bpp = IMGFMT_BGR_DEPTH(out_fmt);
	else
	    mpi->bpp=(IMGFMT_BGR_DEPTH(out_fmt)+7)&(~7);
	mpi->flags|=MP_IMGFLAG_SWAPPED;
	return;
    }
    mpi->flags|=MP_IMGFLAG_YUV;
    mpi->num_planes=3;
    if (mp_get_chroma_shift(out_fmt, NULL, NULL)) {
        mpi->flags|=MP_IMGFLAG_PLANAR;
        mpi->bpp = mp_get_chroma_shift(out_fmt, &mpi->chroma_x_shift, &mpi->chroma_y_shift);
        mpi->chroma_width  = mpi->width  >> mpi->chroma_x_shift;
        mpi->chroma_height = mpi->height >> mpi->chroma_y_shift;
    }
    switch(out_fmt){
    case IMGFMT_I420:
    case IMGFMT_IYUV:
	mpi->flags|=MP_IMGFLAG_SWAPPED;
    case IMGFMT_YV12:
	return;
    case IMGFMT_420A:
    case IMGFMT_IF09:
	mpi->num_planes=4;
    case IMGFMT_YVU9:
    case IMGFMT_444P:
    case IMGFMT_422P:
    case IMGFMT_411P:
    case IMGFMT_440P:
    case IMGFMT_444P16_LE:
    case IMGFMT_444P16_BE:
    case IMGFMT_422P16_LE:
    case IMGFMT_422P16_BE:
    case IMGFMT_420P16_LE:
    case IMGFMT_420P16_BE:
	return;
    case IMGFMT_Y800:
    case IMGFMT_Y8:
	/* they're planar ones, but for easier handling use them as packed */
	mpi->flags&=~MP_IMGFLAG_PLANAR;
	mpi->num_planes=1;
	return;
    case IMGFMT_UYVY:
	mpi->flags|=MP_IMGFLAG_SWAPPED;
    case IMGFMT_YUY2:
	mpi->bpp=16;
	mpi->num_planes=1;
	return;
    case IMGFMT_NV12:
	mpi->flags|=MP_IMGFLAG_SWAPPED;
    case IMGFMT_NV21:
	mpi->flags|=MP_IMGFLAG_PLANAR;
	mpi->bpp=12;
	mpi->num_planes=2;
	mpi->chroma_width=(mpi->width>>0);
	mpi->chroma_height=(mpi->height>>1);
	mpi->chroma_x_shift=0;
	mpi->chroma_y_shift=1;
	return;
    }
    mp_msg(MSGT_DECVIDEO,MSGL_WARN,"mp_image: unknown out_fmt: 0x%X\n",out_fmt);
    mpi->bpp=0;
}

mp_image_t* new_mp_image(int w,int h){
    mp_image_t* mpi = malloc(sizeof(mp_image_t));
    if(!mpi) return NULL; // error!
    memset(mpi,0,sizeof(mp_image_t));
    mpi->width=mpi->w=w;
    mpi->height=mpi->h=h;
    return mpi;
}

void free_mp_image(mp_image_t* mpi){
    if(!mpi) return;
    if(mpi->flags&MP_IMGFLAG_ALLOCATED){
	/* becouse we allocate the whole image in once */
#ifdef JZ_LINUX_OS
#else
	if(mpi->planes[0]) av_free(mpi->planes[0]);
	if (mpi->flags & MP_IMGFLAG_RGB_PALETTE)
	    av_free(mpi->planes[1]);
#endif
    }
    free(mpi);
}
