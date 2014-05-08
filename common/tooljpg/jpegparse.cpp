

#include "internal.h"
//#include "../terminal/terminal/main/main.h"

#define GETDWORD(base,offset) (((UINT32)(*((UINT8 *)base+offset))<< 24) + ((UINT32)(*((UINT8 *)base+offset+1))<<16) + 	\
								((UINT32)(*((UINT8 *)base+offset+2))<< 8) + ((UINT32)(*((UINT8 *)base+offset+3))))
#define GETDWORD_INV(base,offset) (((UINT32)(*((UINT8 *)base+offset+3))<< 24) + ((UINT32)(*((UINT8 *)base+offset+2))<<16) + 	\
								((UINT32)(*((UINT8 *)base+offset+1))<< 8) + ((UINT32)(*((UINT8 *)base+offset))))

#define GETBYTE(base,offset) ((unsigned char)(*((unsigned char *)base+offset)))
#define GETWORD(base,offset) ((unsigned short)(*((unsigned char *)base+offset)<< 8) + (unsigned short)*((unsigned char *)base+offset+1))
#define GETWORD_INV(base,offset) ((unsigned short)(*((unsigned char *)base+offset+1)<< 8) + (unsigned short)*((unsigned char *)base+offset))

#define SETBYTE(base, offset, val)	\
		{												\
			(*((unsigned char *)base+offset)) = (unsigned char)val;		\
			offset++;									\
		}

#define SETWORD(base, offset, val)		\
		{								\
			(*((unsigned char *)base+offset)) = (unsigned char)((((unsigned short)val)>> 8)&0xff);	\
			(*((unsigned char *)base+offset+1)) = (unsigned char)val;						\
			offset += 2;													\
		}

#define SETWORD_INV(base, offset, val)		\
		{								\
			(*((unsigned char *)base+offset+1)) = (unsigned char)((((unsigned short)val)>> 8)&0xff);	\
			(*((unsigned char *)base+offset)) = (unsigned char)val;						\
			offset += 2;												\
		}

enum JPEG_MARKERenum {			
/* JPEG marker codes */
  M_SOF0   = 0xc0,
  M_SOF1   = 0xc1,
  M_SOF2   = 0xc2,
  M_SOF3   = 0xc3,

  M_SOF5   = 0xc5,
  M_SOF6   = 0xc6,
  M_SOF7   = 0xc7,

  M_JPG    = 0xc8,
  M_SOF9   = 0xc9,
  M_SOF10  = 0xca,
  M_SOF11  = 0xcb,

  M_SOF13  = 0xcd,
  M_SOF14  = 0xce,
  M_SOF15  = 0xcf,

  M_DHT    = 0xc4,

  M_DAC    = 0xcc,

  M_RST0   = 0xd0,
  M_RST1   = 0xd1,
  M_RST2   = 0xd2,
  M_RST3   = 0xd3,
  M_RST4   = 0xd4,
  M_RST5   = 0xd5,
  M_RST6   = 0xd6,
  M_RST7   = 0xd7,

  M_SOI    = 0xd8,
  M_EOI    = 0xd9,
  M_SOS    = 0xda,
  M_DQT    = 0xdb,
  M_DNL    = 0xdc,
  M_DRI    = 0xdd,
  M_DHP    = 0xde,
  M_EXP    = 0xdf,

  M_APP0   = 0xe0,
  M_APP1   = 0xe1,
  M_APP2   = 0xe2,
  M_APP3   = 0xe3,
  M_APP4   = 0xe4,
  M_APP5   = 0xe5,
  M_APP6   = 0xe6,
  M_APP7   = 0xe7,
  M_APP8   = 0xe8,
  M_APP9   = 0xe9,
  M_APP10  = 0xea,
  M_APP11  = 0xeb,
  M_APP12  = 0xec,
  M_APP13  = 0xed,
  M_APP14  = 0xee,
  M_APP15  = 0xef,

  M_JPG0   = 0xf0,
  M_JPG13  = 0xfd,
  M_COM    = 0xfe
};

enum EXIFTAGenum {
/* EXIF TAG codes */
	EXIF_TAG_INTEROPERABILITY_INDEX		= 0x0001,
	EXIF_TAG_INTEROPERABILITY_VERSION	= 0x0002,
	EXIF_TAG_IMAGE_WIDTH 			= 0x0100,
	EXIF_TAG_IMAGE_LENGTH 			= 0x0101,
	EXIF_TAG_BITS_PER_SAMPLE 		= 0x0102,
	EXIF_TAG_COMPRESSION 			= 0x0103,
	EXIF_TAG_PHOTOMETRIC_INTERPRETATION 	= 0x0106,
	EXIF_TAG_FILL_ORDER 			= 0x010a,
	EXIF_TAG_DOCUMENT_NAME 			= 0x010d,
	EXIF_TAG_IMAGE_DESCRIPTION 		= 0x010e,
	EXIF_TAG_MAKE 				= 0x010f,
	EXIF_TAG_MODEL 				= 0x0110,
	EXIF_TAG_STRIP_OFFSETS 			= 0x0111,
	EXIF_TAG_ORIENTATION 			= 0x0112,
	EXIF_TAG_SAMPLES_PER_PIXEL 		= 0x0115,
	EXIF_TAG_ROWS_PER_STRIP 		= 0x0116,
	EXIF_TAG_STRIP_BYTE_COUNTS		= 0x0117,
	EXIF_TAG_X_RESOLUTION 			= 0x011a,
	EXIF_TAG_Y_RESOLUTION 			= 0x011b,
	EXIF_TAG_PLANAR_CONFIGURATION 		= 0x011c,
	EXIF_TAG_RESOLUTION_UNIT 		= 0x0128,
	EXIF_TAG_TRANSFER_FUNCTION 		= 0x012d,
	EXIF_TAG_SOFTWARE 			= 0x0131,
	EXIF_TAG_DATE_TIME			= 0x0132,
	EXIF_TAG_ARTIST				= 0x013b,
	EXIF_TAG_WHITE_POINT			= 0x013e,
	EXIF_TAG_PRIMARY_CHROMATICITIES		= 0x013f,
	EXIF_TAG_TRANSFER_RANGE			= 0x0156,
	EXIF_TAG_JPEG_PROC			= 0x0200,
	EXIF_TAG_JPEG_INTERCHANGE_FORMAT	= 0x0201,
	EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH	= 0x0202,
	EXIF_TAG_YCBCR_COEFFICIENTS		= 0x0211,
	EXIF_TAG_YCBCR_SUB_SAMPLING		= 0x0212,
	EXIF_TAG_YCBCR_POSITIONING		= 0x0213,
	EXIF_TAG_REFERENCE_BLACK_WHITE		= 0x0214,
	EXIF_TAG_RELATED_IMAGE_FILE_FORMAT	= 0x1000,
	EXIF_TAG_RELATED_IMAGE_WIDTH		= 0x1001,
	EXIF_TAG_RELATED_IMAGE_LENGTH		= 0x1002,
	EXIF_TAG_CFA_REPEAT_PATTERN_DIM		= 0x828d,
	EXIF_TAG_CFA_PATTERN			= 0x828e,
	EXIF_TAG_BATTERY_LEVEL			= 0x828f,
	EXIF_TAG_COPYRIGHT			= 0x8298,
	EXIF_TAG_EXPOSURE_TIME			= 0x829a,
	EXIF_TAG_FNUMBER			= 0x829d,
	EXIF_TAG_IPTC_NAA			= 0x83bb,
	EXIF_TAG_EXIF_IFD_POINTER		= 0x8769,
	EXIF_TAG_INTER_COLOR_PROFILE		= 0x8773,
	EXIF_TAG_EXPOSURE_PROGRAM		= 0x8822,
	EXIF_TAG_SPECTRAL_SENSITIVITY		= 0x8824,
	EXIF_TAG_GPS_INFO_IFD_POINTER		= 0x8825,
	EXIF_TAG_ISO_SPEED_RATINGS		= 0x8827,
	EXIF_TAG_OECF				= 0x8828,
	EXIF_TAG_EXIF_VERSION			= 0x9000,
	EXIF_TAG_DATE_TIME_ORIGINAL		= 0x9003,
	EXIF_TAG_DATE_TIME_DIGITIZED		= 0x9004,
	EXIF_TAG_COMPONENTS_CONFIGURATION	= 0x9101,
	EXIF_TAG_COMPRESSED_BITS_PER_PIXEL	= 0x9102,
	EXIF_TAG_SHUTTER_SPEED_VALUE		= 0x9201,
	EXIF_TAG_APERTURE_VALUE			= 0x9202,
	EXIF_TAG_BRIGHTNESS_VALUE		= 0x9203,
	EXIF_TAG_EXPOSURE_BIAS_VALUE		= 0x9204,
	EXIF_TAG_MAX_APERTURE_VALUE		= 0x9205,
	EXIF_TAG_SUBJECT_DISTANCE		= 0x9206,
	EXIF_TAG_METERING_MODE			= 0x9207,
	EXIF_TAG_LIGHT_SOURCE			= 0x9208,
	EXIF_TAG_FLASH				= 0x9209,
	EXIF_TAG_FOCAL_LENGTH			= 0x920a,
	EXIF_TAG_SUBJECT_AREA			= 0x9214,
	EXIF_TAG_MAKER_NOTE			= 0x927c,
	EXIF_TAG_USER_COMMENT			= 0x9286,
	EXIF_TAG_SUB_SEC_TIME			= 0x9290,
	EXIF_TAG_SUB_SEC_TIME_ORIGINAL		= 0x9291,
	EXIF_TAG_SUB_SEC_TIME_DIGITIZED		= 0x9292,
	EXIF_TAG_FLASH_PIX_VERSION		= 0xa000,
	EXIF_TAG_COLOR_SPACE			= 0xa001,
	EXIF_TAG_PIXEL_X_DIMENSION		= 0xa002,
	EXIF_TAG_PIXEL_Y_DIMENSION		= 0xa003,
	EXIF_TAG_RELATED_SOUND_FILE		= 0xa004,
	EXIF_TAG_INTEROPERABILITY_IFD_POINTER	= 0xa005,
	EXIF_TAG_FLASH_ENERGY			= 0xa20b,
	EXIF_TAG_SPATIAL_FREQUENCY_RESPONSE	= 0xa20c,
	EXIF_TAG_FOCAL_PLANE_X_RESOLUTION	= 0xa20e,
	EXIF_TAG_FOCAL_PLANE_Y_RESOLUTION	= 0xa20f,
	EXIF_TAG_FOCAL_PLANE_RESOLUTION_UNIT	= 0xa210,
	EXIF_TAG_SUBJECT_LOCATION		= 0xa214,
	EXIF_TAG_EXPOSURE_INDEX			= 0xa215,
	EXIF_TAG_SENSING_METHOD			= 0xa217,
	EXIF_TAG_FILE_SOURCE			= 0xa300,
	EXIF_TAG_SCENE_TYPE			= 0xa301,
	EXIF_TAG_NEW_CFA_PATTERN		= 0xa302,
	EXIF_TAG_CUSTOM_RENDERED		= 0xa401,
	EXIF_TAG_EXPOSURE_MODE			= 0xa402,
	EXIF_TAG_WHITE_BALANCE			= 0xa403,
	EXIF_TAG_DIGITAL_ZOOM_RATIO		= 0xa404,
	EXIF_TAG_FOCAL_LENGTH_IN_35MM_FILM	= 0xa405,
	EXIF_TAG_SCENE_CAPTURE_TYPE		= 0xa406,
	EXIF_TAG_GAIN_CONTROL			= 0xa407,
	EXIF_TAG_CONTRAST			= 0xa408,
	EXIF_TAG_SATURATION			= 0xa409,
	EXIF_TAG_SHARPNESS			= 0xa40a,
	EXIF_TAG_DEVICE_SETTING_DESCRIPTION	= 0xa40b,
	EXIF_TAG_SUBJECT_DISTANCE_RANGE		= 0xa40c,
	EXIF_TAG_IMAGE_UNIQUE_ID		= 0xa420
};

enum EXIFFORMATenum {
/* EXIF Format Type */
	EXIF_FORMAT_BYTE       =  1,
	EXIF_FORMAT_ASCII      =  2,
	EXIF_FORMAT_SHORT      =  3,
	EXIF_FORMAT_LONG       =  4,
	EXIF_FORMAT_RATIONAL   =  5,
	EXIF_FORMAT_SBYTE      =  6,
	EXIF_FORMAT_UNDEFINED  =  7,
	EXIF_FORMAT_SSHORT     =  8,
	EXIF_FORMAT_SLONG      =  9,
	EXIF_FORMAT_SRATIONAL  = 10,
	EXIF_FORMAT_FLOAT      = 11,
	EXIF_FORMAT_DOUBLE     = 12
};

enum EXIFBYTEORDER {
	EXIF_BYTE_ORDER_MOTOROLA = 0x1,
	EXIF_BYTE_ORDER_INTEL = 0x2
};

//lbuf yuv mode
enum V5B_LBUF_YUVenum
{
	V5B_LBUF_YUV_422	= 0x0,
	V5B_LBUF_YUV_420	= 0x1,
	V5B_LBUF_YUV_411	= 0x2,
	V5B_LBUF_YUV_400	= 0x3,
	V5B_LBUF_YUV_444	= 0x4
};

void CJpegParse::JpegParse(unsigned char* ptr, int length, PTJpegIndex pinfo)
{
	int i = 0;
	unsigned short len;

	memset(pinfo, 0, sizeof(TJpegIndex));
	pinfo->YUVType = JPEG_UNKNOWN;
	pinfo->thumbinfo.thumbtype = NO_THUMBNAIL;

	//try to find the 1st marker SOI
	while(i < length)
	{
		if(ptr[i]==0xff)
		{
			if(ptr[i+1]==0xd8)
			{
				break;
			}
		}
		i++;
	}

	//find the SOI marker, start parsing
	while(i < length)
	{
		if(ptr[i] == 0xff)
		{
			do
			{
				i++;
			}
			while(ptr[i]==0xff);
			
			switch(ptr[i])
			{
			case M_SOI:
				pinfo->sop = i-1;
				break;
			case M_APP0:
				len = this->GetJfifInfo(ptr, i+1, &pinfo->thumbinfo);
				i  += len;
				break;
			case M_APP1:
				len = this->GetExifInfo(ptr, i+1, &pinfo->thumbinfo);
				i	+= len;
				break;
			case M_SOF0:
				len = this->GetSOF0(pinfo, ptr+i+1);
				if(len == 0)
				{
					pinfo->YUVType = JPEG_UNKNOWN;
					pinfo->eop = i;
					return;
				}
				i += len;
				break;
			case M_DQT:
				len = this->GetDQT(pinfo, ptr+i+1);
				if(len == 0)
				{
					pinfo->YUVType = JPEG_UNKNOWN;
					pinfo->eop = i;
					return;
				}
				i += len;
				break;
			case M_DHT:
				len = this->GetDHT(pinfo, ptr+i+1);
				if(len == 0)
				{
					pinfo->YUVType = JPEG_UNKNOWN;
					pinfo->eop = i;
					return;
				}
				i += len;
				break;
			case M_SOS:
				if (pinfo->HTCount != 4)
				{
					pinfo->YUVType = JPEG_UNKNOWN;
					pinfo->eop = i;
					return;
				}
				len = this->GetSOS(pinfo, ptr+i+1);
				if(len)
				{
					i += len;
					pinfo->offset = i+1;
				}
				//after SOS, there is only EOI exist;
				while(i < (length-1))
				{
					if(ptr[i]==0xff)
					{
						if(ptr[i+1]==0xd9)
						{
							pinfo->eop = i+2;
							return;
						}
						
					}
					i++;
				}
				break;
			case M_EOI:
				pinfo->eop = i+1;
				return;
			case M_SOF1:		/* Extended sequential, Huffman */
			case M_SOF2:		/* Progressive, Huffman */
			case M_SOF9:		/* Extended sequential, arithmetic */
			case M_SOF10:		/* Progressive, arithmetic */
			case M_SOF3:		/* Lossless, Huffman */
			case M_SOF5:		/* Differential sequential, Huffman */
			case M_SOF6:		/* Differential progressive, Huffman */
			case M_SOF7:		/* Differential lossless, Huffman */
			case M_SOF11:		/* Lossless, arithmetic */
			case M_SOF13:		/* Differential sequential, arithmetic */
			case M_SOF14:		/* Differential progressive, arithmetic */
			case M_SOF15:		/* Differential lossless, arithmetic */
			case M_JPG:			/* Reserved for JPEG extensions */
								/* Currently unsupported SOFn types */
								/* set YUV_TYPE = unknown */
				len = this->GetSOF_Unsupport(pinfo, ptr+i+1);
				i += len;
				break;
			case M_COM:
				len = this->GetComment(pinfo, ptr+i+1);
				i += len;
				break;
			case M_DAC:			/* Define arithmetic coding conditioning */
			case M_DRI:			/* Define restart interval */
			case M_APP2:		/* Reserved for application segments */
			case M_APP3:
			case M_APP4:
			case M_APP5:
			case M_APP6:
			case M_APP7:
			case M_APP8:
			case M_APP9:
			case M_APP10:
			case M_APP11:
			case M_APP12:
			case M_APP13:
			case M_APP14:
			case M_APP15:
			case M_RST0:		/* these are all parameterless */
			case M_RST1:
			case M_RST2:
			case M_RST3:
			case M_RST4:
			case M_RST5:
			case M_RST6:
			case M_RST7:
			case M_DNL:			/* Ignore DNL ... perhaps the wrong thing */
				len = this->ByPassMarker(ptr+i+1);			/* Currently unsupported, bypass! */
				i += len;
				break;
			default:
								/* error! You could show error here */
								/* set YUVType = Unknown, and return */
				break;
			}
		}
		i++;
	}
	pinfo->eop = i;
}


unsigned long CJpegParse::GetImageVwc(unsigned char fmt, TSize size)
{
	TSize size1;

	this->GetJpegSize(fmt, size, &size1);
	return this->GetYuvSize(fmt, size1) >> 2;
}

unsigned long CJpegParse::GetYuvSize(unsigned char yuvfmt, TSize size)
{
	unsigned long len;

	len = (UINT32)size.cx & 0xffff;
	len *= (UINT32)size.cy & 0xffff;
	switch(yuvfmt)
	{
	case V5B_LBUF_YUV_422:
		len <<= 1;
		break;
	case V5B_LBUF_YUV_420:
	case V5B_LBUF_YUV_411:
		len *= 3;
		len >>= 1;
		break;
	case V5B_LBUF_YUV_444:
		len *= 3;
		break;
	case V5B_LBUF_YUV_400:
	default:
		break;
	}
	return len;
}

unsigned short CJpegParse::GetJpegBlockNum(unsigned char fmt, TSize size)
{
	TSize size1;

	this->GetJpegSize(fmt, size, &size1);
	switch(fmt)
	{
	case JPEG_422:
		size1.cx >>= 2;
		break;
	case JPEG_420:
		size1.cx >>= 2;
		size1.cx += size1.cx >> 1;
		break;
	case JPEG_411:
		size1.cx >>= 3;
		size1.cx += size1.cx >> 1;
		break;
	case JPEG_400:
		size1.cx >>= 3;
		break;
	case JPEG_444:
		size1.cx >>= 2;
		size1.cx += size1.cx >> 1;
		break;
	default:
		break;
	}
	return size1.cx;
}

unsigned char CJpegParse::GetComponent(unsigned char fmt, unsigned short *comp)
{
	unsigned char compnum = 0x23;

	comp[0] = 0x120b;
	comp[1] = 0x5104;
	comp[2] = 0x5104;
	switch(fmt)
	{
	case JPEG_422:
		break;
	case JPEG_420:
		comp[0] = 0x2213;
		break;
	case JPEG_411:
		comp[0] = 0x1413;
		break;
	case JPEG_400:
		compnum = 0x11;
		comp[0] = 0x1107;
		comp[1] = 0;
		comp[2] = 0;
		break;
	case JPEG_444:
		compnum = 0x11;
		comp[0] = 0x1107;
		break;
	default:
		break;
	}
	return compnum;
}

void CJpegParse::GetJpegSize(unsigned char fmt, TSize size, TSize *size1)
{
	switch(fmt)
	{
	case JPEG_422:
		size1->cx = ((size.cx + 15) >> 4) << 4;
		size1->cy = ((size.cy + 7) >> 3) << 3;
		break;
	case JPEG_420:
		size1->cx = ((size.cx + 15) >> 4) << 4;
		size1->cy = ((size.cy + 15) >> 4) << 4;
		break;
	case JPEG_411:
		size1->cx = ((size.cx + 31) >> 5) << 5;
		size1->cy = ((size.cy + 7) >> 3) << 3;
		break;
	case JPEG_400:
	case JPEG_444:
		size1->cx = ((size.cx + 7) >> 3) << 3;
		size1->cy = ((size.cy + 7) >> 3) << 3;
		break;
	default:
		break;
	}
}


unsigned short CJpegParse::GetSOF0(PTJpegIndex pinfo, unsigned char* ptr)
{
	unsigned short len = GETWORD(ptr,0);

	pinfo->data_precision = ptr[2];
	pinfo->ImageSize.cy = GETWORD(ptr,3);
	pinfo->ImageSize.cx = GETWORD(ptr,5);
	pinfo->CompCount = ptr[7];
	if(pinfo->CompCount == 1)
	{
		if((ptr[8]-1) > 3)
			return 0;
		pinfo->YUVType = JPEG_400;
		pinfo->Comp[ ptr[8]-1 ] = GetCompFrmSOF(ptr+9);;
	}
	else
	{
		if( ((ptr[11] - 1) > 3) || ((ptr[14] - 1) > 3) || ((ptr[8] - 1) > 3) )
			return 0;
		pinfo->Comp[ ptr[8]-1 ] = GetCompFrmSOF(ptr+9);
		if((ptr[9] == 0x21) || (ptr[9] == 0x12))
			pinfo->YUVType = JPEG_422;
		else if(ptr[9] == 0x22)
			pinfo->YUVType = JPEG_420;
		else if(ptr[9] == 0x41)
			pinfo->YUVType = JPEG_411;
		else if(ptr[9] == 0x11)
			pinfo->YUVType = JPEG_444;
		else
			return 0;
		pinfo->Comp[ ptr[11]-1 ] = GetCompFrmSOF(ptr+12);
		pinfo->Comp[ ptr[14]-1 ] = GetCompFrmSOF(ptr+15);
	}
	this->GetJpegSize(pinfo->YUVType, pinfo->ImageSize, &(pinfo->JpgSize));
	pinfo->vwc = this->GetImageVwc(pinfo->YUVType, pinfo->JpgSize);
	pinfo->blkcount = this->GetJpegBlockNum(pinfo->YUVType, pinfo->JpgSize);

	return len;
}


unsigned short CJpegParse::GetSOF_Unsupport(PTJpegIndex pinfo, unsigned char* ptr)
{
	unsigned short len = ((unsigned short)ptr[0] << 8) + (unsigned short)ptr[1];
	
	//unsupported pic, set everything to zero, YUVType to unknown and bypass the length
	pinfo->data_precision = 0;
	pinfo->ImageSize.cy = 0;
	pinfo->ImageSize.cx = 0;
	pinfo->CompCount = 0;
	pinfo->YUVType = JPEG_UNKNOWN;
	return len;
}


unsigned short CJpegParse::GetDQT(PTJpegIndex pinfo, unsigned char* ptr)
{
	unsigned short len, i = 0;
	unsigned char	n;
	
	len = GETWORD(ptr,0);
	
	i += 2;
	while(i < len)
	{
		if(ptr[i] & 0xf0)		//16 bit precision
		{
			n = ptr[i] & 0xf;
			if(n > 3)
				return 0;
			pinfo->QTPrecision[n] = 16;
			pinfo->QT[n] = ptr+i+1;
			i += 1 + (64 << 1);
		}
		else		//8 bit precision
		{
			n = ptr[i] & 0xf;
			if(n > 3)
				return 0;
			pinfo->QTPrecision[n] = 8;
			pinfo->QT[n] = ptr+i+1;
			i += 1 + 64;
		}
		pinfo->QTCount++;
	}
	return len;
}
unsigned short CJpegParse::GetDHT(PTJpegIndex pinfo, unsigned char* ptr)
{
	unsigned short len, j, n, k, HTLen;
	unsigned char *pd = ptr+2;
//	int tablen[4] = {0x1c, 0xb2, 0x1c, 0xb2};
	
	j = 0;
	len = GETWORD(ptr,0);

	while(j < len-3)
	{
		HTLen = 0;
		n = pd[j] & 0xf;
		k = pd[j] & 0xf0;
		n <<= 1;
		n += k >> 4;
		if(n > 3)
			return 0;
		j++;
		pinfo->HT[n] = pd+j;
		k = j + 16;
		while(j < k)
		{
			HTLen = HTLen + (unsigned short)(pd[j]);
			j++;
		}
		pinfo->HTLen[n] = (unsigned char)(16 + HTLen);
//		if (pinfo->HTLen[n] != tablen[n])
//			return 0;
		j = j+HTLen;
		pinfo->HTCount++;
	}
	return len;
}

unsigned short CJpegParse::GetSOS(PTJpegIndex pinfo, unsigned char* ptr)
{
	unsigned short len;
	unsigned char i, k, n, ac, dc, count, *pbuf = ptr+3;	
	
	len = GETWORD(ptr,0);
	count = ptr[2];
	if(len != 6 + (count << 1))
		return 0;
	
	for(i = 0; i < count; i++)
	{
		k = i << 1;
		n = pbuf[k]-1;
		if(n > 3)
			return 0;
		ac = pbuf[k+1] & 0xf;
		dc = pbuf[k+1] & 0xf0;
		if(!ac)
			pinfo->Comp[n] |= 0x2;
		if(!dc)
			pinfo->Comp[n] |= 0x1;
	}
	return len;
}

unsigned short CJpegParse::GetCompFrmSOF(unsigned char *buf)
{
	unsigned char	h, v, n;
	unsigned short	val = 0;
	
	h = (buf[0] & 0x70) >> 4;
	v = buf[0] & 0x3;
	n = buf[1];
	val = (unsigned short)(h | (v << 4) | (n << 6)) << 8;
	n = h*v << 2;
	val |= (unsigned short)n;
	return val;
}

unsigned short CJpegParse::GetComment(PTJpegIndex pinfo, unsigned char *ptr)
{
	unsigned short len = GETWORD(ptr, 0);

	pinfo->frmcnt = GETWORD_INV(ptr, 2);
	pinfo->qf = GETBYTE(ptr, 25);

	return len;
}

unsigned short CJpegParse::ByPassMarker(unsigned char* ptr)
{
	unsigned short len = GETWORD(ptr,0);
	return len;
}


unsigned short CJpegParse::GetJfifInfo(unsigned char* ptr, int point, PTThumbNail pthumbinfo)
{
	UINT32  i;
	UINT16 len;
	UINT8 isJFIF, isJFXX;
	UINT8 extensioncode;

	i      =   point;
	len    =   GETWORD(ptr, point);
	i     +=    2;
	//pjfifinfo->fieldLen =  len;
	if( (ptr[i] == 'J') && (ptr[i+1] == 'F') 
		&& (ptr[i+2] == 'I') && (ptr[i+3] == 'F')
		&& (ptr[i+4] == 0) )
		isJFIF = 1;
	else
		isJFIF = 0;
	if(ptr[i] == 'J' && ptr[i+1] == 'F' 
		&& ptr[i+2] == 'X' && ptr[i+3] == 'X'
		&& ptr[i+4] == 0)
		isJFXX = 1;
	else 
		isJFXX = 0;

	i += 5;
	if(isJFIF)
	{	
		i += 7;		
		pthumbinfo->thumbWidth = ptr[i];
		i++;		
		pthumbinfo->thumbHeight = ptr[i];
		i++;
		pthumbinfo->thumblen = len - 0x10;
			
		if(pthumbinfo->thumblen)
		{
			pthumbinfo->thumbtype = THUMBNAIL_JFIF;
			pthumbinfo->thumbfmt = RGB24;
			pthumbinfo->pthumbbuf = ptr + i;			
		}
	}
	if(isJFXX)
	{		
		extensioncode  =  ptr[i];
		switch(extensioncode)
		{
		case 0x10:
			pthumbinfo->thumbfmt = JPEG422;
			pthumbinfo->pthumbbuf = ptr + point + 0x08;
			pthumbinfo->thumblen = len - 0x08;			
			break;
		case 0x11:
			pthumbinfo->thumbfmt = RGB8;
			pthumbinfo->thumbWidth = ptr[i + 1];
			pthumbinfo->thumbHeight = ptr[i + 2];
			pthumbinfo->ppalette = ptr + point + 0x0a;
			pthumbinfo->pthumbbuf = ptr + point + 0x0a + 0x300;
			pthumbinfo->thumblen = len - 0x0a - 0x300;			
			break;
		case 0x13:
			pthumbinfo->thumbfmt = RGB24;
			pthumbinfo->thumbWidth = ptr[i + 1];
			pthumbinfo->thumbHeight = ptr[i + 2];
			pthumbinfo->pthumbbuf = ptr + point + 0x0a;
			pthumbinfo->thumblen = len - 0x0a;			
			break;
		default: 
			break;
		}
		if(pthumbinfo->thumblen)
			pthumbinfo->thumbtype = THUMBNAIL_JFXX;
	}
	return len;
}


unsigned short CJpegParse::GetExifInfo(unsigned char* ptr, int point, PTThumbNail pthumbinfo)
{
	UINT32 i;
	UINT16 len;

	i = point;
	len = GETWORD(ptr, i);
	i += 2;

	if(ptr[i] == 'E' && ptr[i+1] == 'x' 
		&& ptr[i+2] == 'i' && ptr[i+3] == 'f'
		&& ptr[i+4] == 0 && ptr[i+5] == 0)
	{
		i += 6;
		ParseExif(ptr+i, pthumbinfo);
	}

	return len;
}


void CJpegParse::ParseExif(unsigned char* ptr, PTThumbNail pthumbinfo)
{
	UINT32 i = 0;
	UINT16 byteOrder;
	UINT32 ifdOffset;
	
	byteOrder = GETWORD(ptr, i);
	i += 2;

	if(byteOrder == 0x4949)
		pthumbinfo->byteOrder = EXIF_BYTE_ORDER_INTEL;
	else if(byteOrder == 0x4D4D)
		pthumbinfo->byteOrder = EXIF_BYTE_ORDER_MOTOROLA;
	else		
		return;		

	i += 2;												//skip '2A00'
	
	ifdOffset = ExifGetDword(ptr+i, pthumbinfo->byteOrder);

	ifdOffset = GetIFD0(ptr, ifdOffset, pthumbinfo);

	if(ifdOffset != 0)
		ifdOffset = GetIFD1(ptr, ifdOffset, pthumbinfo);
}

int CJpegParse::GetIFD0(unsigned char* ptr, int point, PTThumbNail pthumbinfo)
{
	UINT16 number;
	UINT32 i = point;
	UINT32 ifd1Offset = 0;

	number = ExifGetWord(ptr+i, pthumbinfo->byteOrder);
	i += 2;

	i += number * 12;										//skip the 12-byte field Interoperability arrays

	ifd1Offset = ExifGetDword(ptr+i, pthumbinfo->byteOrder);

	return ifd1Offset;
}

int CJpegParse::GetIFD1(unsigned char* ptr, int point, PTThumbNail pthumbinfo)
{
	UINT8 unit = 0;
	UINT16 number, j;	
	UINT16	tag, type;
	UINT32	i, nextIfdOffset = 0;
	UINT32	count, offset = 0;	

	TExifIFD1 ifd1info;

    memset(&(ifd1info), 0, sizeof(TExifIFD1));
	i = point;
	number = ExifGetWord(ptr+i, pthumbinfo->byteOrder);
	i += 2;
	
	for(j = 0; j < number; j++)
	{
		tag = ExifGetWord(ptr+i, pthumbinfo->byteOrder);
		i += 2;
		type = ExifGetWord(ptr+i, pthumbinfo->byteOrder);
		i += 2;
		count = ExifGetDword(ptr+i, pthumbinfo->byteOrder);
		i += 4;
		switch(type)
		{
			case EXIF_FORMAT_BYTE:
			case EXIF_FORMAT_SBYTE:
			case EXIF_FORMAT_UNDEFINED:
			case EXIF_FORMAT_ASCII:
				unit = 1;
				offset = (UINT32)ptr[i];
				break;
			case EXIF_FORMAT_SHORT:
			case EXIF_FORMAT_SSHORT:
				unit = 2;
				offset = (UINT32)ExifGetWord(ptr+i, pthumbinfo->byteOrder);
				break;
			case EXIF_FORMAT_LONG:
			case EXIF_FORMAT_SLONG:
				unit = 4;
				offset = ExifGetDword(ptr+i, pthumbinfo->byteOrder);
				break;
			case EXIF_FORMAT_RATIONAL:
			case EXIF_FORMAT_SRATIONAL:
			case EXIF_FORMAT_FLOAT:
			case EXIF_FORMAT_DOUBLE:
				//currently, we don't need these cases, just bypass them
			default:
				//error
				unit = 0;
				offset = 0;
				break;
		}
		
		switch(tag)				//current support tag data size less than 4, so offset is not used,but it can be extended easily
		{
			case EXIF_TAG_COMPRESSION:
				ifd1info.compression = (UINT16)offset;
				break;
			case EXIF_TAG_IMAGE_WIDTH:
				pthumbinfo->thumbWidth = ifd1info.thumbWidth = offset;
				break;
			case EXIF_TAG_IMAGE_LENGTH:
				pthumbinfo->thumbHeight = ifd1info.thumbHeight = offset;
				break;			
			case EXIF_TAG_PHOTOMETRIC_INTERPRETATION:
				ifd1info.PhotometricInterpretation = (UINT16)offset;
				break;
			case EXIF_TAG_YCBCR_SUB_SAMPLING:
				ifd1info.YCbCrSubSampling = (UINT16)offset;
				break;
			case EXIF_TAG_JPEG_INTERCHANGE_FORMAT:
				ifd1info.JPEGInterchangeFormat = offset;				
				break;
			case EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH:				
				ifd1info.JPEGInterchangeFormatLength = offset;
				break;			
			case EXIF_TAG_STRIP_OFFSETS:			//do not support strip store
				ifd1info.StripOffsets = offset;				
				break;
			case EXIF_TAG_STRIP_BYTE_COUNTS:				
				ifd1info.StripByteCounts = offset;
				break;
			case EXIF_TAG_PLANAR_CONFIGURATION:
				ifd1info.PlanarConfiguration = (UINT16)offset;
				break;

			case EXIF_TAG_ROWS_PER_STRIP:				
			case EXIF_TAG_BITS_PER_SAMPLE:				
			case EXIF_TAG_SAMPLES_PER_PIXEL:								
			case EXIF_TAG_YCBCR_POSITIONING:			
				break;
			default:									//currently, we don't need others' info
				break;
		}
		i += 4;	
	}	

	pthumbinfo->thumbtype = THUMBNAIL_EXIF;
	if (ifd1info.compression == 6)
	{
		pthumbinfo->thumbfmt = JPEG422;
		
		pthumbinfo->pthumbbuf = (UINT8*)ptr + ifd1info.JPEGInterchangeFormat;
		pthumbinfo->thumblen = ifd1info.JPEGInterchangeFormatLength;
	}
	else if (ifd1info.compression == 1)				//no compression
	{
		pthumbinfo->pthumbbuf = (UINT8*)ptr + ifd1info.StripOffsets;
		pthumbinfo->thumblen = ifd1info.StripByteCounts;

		if (ifd1info.PhotometricInterpretation == 2)	// RGB
		{
			if (ifd1info.PlanarConfiguration == 1)
				pthumbinfo->thumbfmt = RAW_RGB;
			else
				pthumbinfo->thumbfmt = RAW_RGB_RpGpBp;
		}
		else			//YCbCr
		{
			if (ifd1info.YCbCrSubSampling == 0x22)
			{
                if (ifd1info.PlanarConfiguration == 1)
					pthumbinfo->thumbfmt = YCbCr420_YYYYCbCr;
				else
					pthumbinfo->thumbfmt = YCbCr420_YpCbpCrp;
			}
			else
			{
				if (ifd1info.PlanarConfiguration == 1)
					pthumbinfo->thumbfmt = YCbCr422_YYCbCr;
				else
					pthumbinfo->thumbfmt = YCbCr422_YpCbpCrp;
			}
		}
	}
	else
		pthumbinfo->thumbtype = NO_THUMBNAIL;
    
	nextIfdOffset = ExifGetDword(ptr+i, pthumbinfo->byteOrder);

	return nextIfdOffset;
}

unsigned short CJpegParse::ExifGetWord(unsigned char* ptr, UINT8 order)
{
	if (!ptr) 
		return 0;
	switch(order)
	{
		case EXIF_BYTE_ORDER_MOTOROLA:
			return GETWORD(ptr, 0);
		case EXIF_BYTE_ORDER_INTEL:
			return GETWORD_INV(ptr, 0);
		default:
			return 0;
	}
}

int CJpegParse::ExifGetDword(unsigned char* ptr, UINT8 order)
{
	if (!ptr) 
		return 0;
	switch(order)
	{
        case EXIF_BYTE_ORDER_MOTOROLA:
			return GETDWORD(ptr, 0);
        case EXIF_BYTE_ORDER_INTEL:
			return GETDWORD_INV(ptr, 0);
		default:
			return 0;
	}
}

