/* ***** BEGIN LICENSE BLOCK *****   
 * Source last modified: $Id: sqvh_table_6.c,v 1.1.1.1 2007/12/07 08:11:47 zpxu Exp $ 
 * 
 * REALNETWORKS CONFIDENTIAL--NOT FOR DISTRIBUTION IN SOURCE CODE FORM   
 * Portions Copyright (c) 1995-2005 RealNetworks, Inc.   
 * All Rights Reserved.   
 *   
 * The contents of this file, and the files included with this file, 
 * are subject to the current version of the RealNetworks Community 
 * Source License (the "RCSL"), including Attachment G and any 
 * applicable attachments, all available at 
 * http://www.helixcommunity.org/content/rcsl.  You may also obtain 
 * the license terms directly from RealNetworks.  You may not use this 
 * file except in compliance with the RCSL and its Attachments. There 
 * are no redistribution rights for the source code of this 
 * file. Please see the applicable RCSL for the rights, obligations 
 * and limitations governing use of the contents of the file. 
 *   
 * This file is part of the Helix DNA Technology. RealNetworks is the 
 * developer of the Original Code and owns the copyrights in the 
 * portions it created. 
 *   
 * This file, and the files included with this file, is distributed 
 * and made available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY 
 * KIND, EITHER EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS 
 * ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET 
 * ENJOYMENT OR NON-INFRINGEMENT. 
 *   
 * Technology Compatibility Kit Test Suite(s) Location:   
 * https://rarvcode-tck.helixcommunity.org   
 *   
 * Contributor(s):   
 *   
 * ***** END LICENSE BLOCK ***** */   

/*-------------------------------------------------------------------------*
 *	FileName : sqvh_table_6.c												   *
 *																		   *
 *	Huffman lookup table(s) generated by utility for huffman tree(s) 	   *
 *		sqvh_table_6 of real audio decoder.									   *
 *																		   *
 *																		   *
 *  NOTE : SQVH_TABLE_6_BIT_COUNT no. of bits should be read in the			   *
 *			DecodeNextSymbolFromTree() function for the table			   *
 *																		   *
 *-------------------------------------------------------------------------*/


#ifdef _HUFFMAN_TABLES_

#include "sqvh_table_6.h"

#pragma DATA_ALIGN( RA_TNI_sqvh_table_6, 2 )	 // align on 32-bit boundary
  
#ifdef CONST_TABLE_DMA
#pragma DATA_SECTION( RA_TNI_sqvh_table_6, "CONST_TABLE_DMA_SECTION") 
#endif 
  
  
const HuffmanTableNode RA_TNI_sqvh_table_6[] = { 
	{  0 , 1  },
	{  0 , 1  },
	{  0 , 1  },
	{  0 , 1  },
	{  0 , 1  },
	{  0 , 1  },
	{  0 , 1  },
	{  0 , 1  },
	{  1 , 4  },
	{  2 , 4  },
	{  4 , 4  },
	{  8 , 4  },
	{  16 , 4  },
	{  16 , -4 },
	{  24 , -4 },
	{  32 , -4 },

	{  3 , 2  },
	{  3 , 2  },
	{  5 , 2  },
	{  5 , 2  },
	{  6 , 2  },
	{  6 , 2  },
	{  9 , 2  },
	{  9 , 2  },

	{  10 , 2  },
	{  10 , 2  },
	{  12 , 2  },
	{  12 , 2  },
	{  17 , 2  },
	{  17 , 2  },
	{  20 , 2  },
	{  20 , 2  },

	{  24 , 2  },
	{  24 , 2  },
	{  18 , 3  },
	{  8 , -3 },
	{  16 , -3 },
	{  24 , -3 },
	{  32 , -3 },
	{  40 , -3 },

	{  7 , 1  },
	{  7 , 1  },
	{  7 , 1  },
	{  7 , 1  },
	{  11 , 1  },
	{  11 , 1  },
	{  11 , 1  },
	{  11 , 1  },

	{  14 , 1  },
	{  14 , 1  },
	{  14 , 1  },
	{  14 , 1  },
	{  19 , 1  },
	{  19 , 1  },
	{  19 , 1  },
	{  19 , 1  },

	{  22 , 1  },
	{  22 , 1  },
	{  22 , 1  },
	{  22 , 1  },
	{  26 , 1  },
	{  26 , 1  },
	{  26 , 1  },
	{  26 , 1  },

	{  28 , 1  },
	{  28 , 1  },
	{  28 , 1  },
	{  28 , 1  },
	{  13 , 2  },
	{  13 , 2  },
	{  21 , 2  },
	{  21 , 2  },

	{  25 , 2  },
	{  25 , 2  },
	{  30 , 2  },
	{  30 , 2  },
	{  15 , 3  },
	{  27 , 3  },
	{  29 , 3  },
	{  8 , -3 },

	{  23 , 1  },
	{  23 , 1  },
	{  23 , 1  },
	{  23 , 1  },
	{  31 , 1  },
	{  31 , 1  },
	{  31 , 1  },
	{  31 , 1  }

};

#endif // _HUFFMAN_TABLES_
