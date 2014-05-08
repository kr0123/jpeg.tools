#include "toolconvert/generaltools.h"
#include "tooljpg/jpegenc.h"
#include "tooljpg/jpegdec.h"

#include "convert.h"

int JpegEncoder(char *src, char *dst, int width, int height, int qf, int format)
{
	CJpegEncoder enc;
	int len;

	enc.SetJpegQf(qf);
	enc.SetJpegSize(width, height);
	enc.SetYuvFmt(format);
	enc.Open();
	len = enc.getVwc();
	enc.Write(src, len);
	len = enc.Read(dst, len);
	return len;
}

int JpegDecoder(char *src, int len, char *dst)
{
	CJpegDecoder tools;
	TJpegIndex info;

	tools.JpegParse((unsigned char*)src, len, &info);
	if(info.YUVType == JPEG_UNKNOWN)
		return 0;
	tools.Open(&info);
	tools.Write(src, len);
	return tools.Read(dst, info.vwc << 2);
}

int main( int argc, char *argv[] )
{
	int ret = 0;
	CGeneralTools tools;

//	tools.DataConvert( "RGB32.bmp", "RGB32.rgb", 320, 240, BMP, RGB32, 1, 0, 80 );
//	tools.DataConvert( "RGB32.rgb", "RGB24.rgb", 320, 240, RGB32, RGB24, 1, 0, 80 );
//	tools.DataConvert( "RGB24.rgb", "RGB24-1.jpg", 320, 240, RGB24, JPEG444, 1, 0, 80 );
//	tools.DataConvert( "RGB24.rgb", "RGB24.yuv", 320, 240, RGB24, YUV444, 1, 0, 80 );
//	tools.DataConvert( "RGB24.yuv", "RGB24-blk.yuv", 320, 240, YUV444, YUV444BLK, 1, 0, 80 );
//	tools.DataConvert( "RGB24-blk.yuv", "RGB24-yuv444.yuv", 320, 240, YUV444BLK, YUV444, 1, 0, 80 );
//	tools.DataConvert( "RGB24-yuv444.yuv", "RGB24-yuv444blk.yuv", 320, 240, YUV444, YUV444BLK, 1, 0, 80 );
//	tools.DataConvert( "RGB24-yuv444blk.yuv", "RGB24-2.jpg", 320, 240, YUV444BLK, JPEG444, 1, 0, 80 );

	tools.DataConvert( "RGB32.bmp", "RGB32.rgb", 128, 32, BMP, RGB32, 1, 0, 80 );
	tools.DataConvert( "RGB32.rgb", "RGB24.rgb", 128, 32, RGB32, RGB24, 1, 0, 80 );
	tools.DataConvert( "RGB24.rgb", "RGB24-1.jpg", 128, 32, RGB24, JPEG444, 1, 0, 80 );
	tools.DataConvert( "RGB24.rgb", "RGB24.yuv", 128, 32, RGB24, YUV444, 1, 0, 80 );
	tools.DataConvert( "RGB24.yuv", "RGB24-blk.yuv", 128, 32, YUV444, YUV444BLK, 1, 0, 80 );
	tools.DataConvert( "RGB24-blk.yuv", "RGB24-yuv444.yuv", 128, 32, YUV444BLK, YUV444, 1, 0, 80 );
	tools.DataConvert( "RGB24-yuv444.yuv", "RGB24-yuv444blk.yuv", 128, 32, YUV444, YUV444BLK, 1, 0, 80 );
	tools.DataConvert( "RGB24-yuv444blk.yuv", "RGB24-2.jpg", 128, 32, YUV444BLK, JPEG444, 1, 0, 80 );

	return ret;
}
