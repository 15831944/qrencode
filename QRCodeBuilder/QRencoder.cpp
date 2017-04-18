//QRencoder.cpp:

#include "stdafx.h"
#include "QRencoder.h"

EXTERN_C
{
#include "..\\QRencode\\qrencode.h"
};
#ifdef _DEBUG
#pragma comment(lib,"..\\Debug\\qrencode.lib")
#else
#pragma comment(lib,"..\\Release\\qrencode.lib")
#endif


#define INCHES_PER_METER (100.0/2.54)

QRencoder::QRencoder()
: m_size(1)
, m_margin(0)
, m_pData(NULL)
, m_pBmi(NULL)
{
	m_bgcolor.rgbBlue = 255;
	m_bgcolor.rgbGreen = 255;
	m_bgcolor.rgbRed = 255;
	m_bgcolor.rgbReserved = 255;

	m_fgcolor.rgbBlue = 0;
	m_fgcolor.rgbGreen = 0;
	m_fgcolor.rgbRed = 0;
	m_fgcolor.rgbReserved = 255;
}

QRencoder::~QRencoder()
{
	if (m_pBmi)
	{
		free(m_pBmi);
		m_pBmi = NULL;
	}
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}
}

bool QRencoder::EncodeString(const char* text)
{
	if (!text || strlen(text) == 0)
		return false;

	QRcode* qrcode;

	qrcode = QRcode_encodeString(text, 0, QR_ECLEVEL_H, QR_MODE_8, 1);
	if (!qrcode)
		return false;

	int realwidth = (qrcode->width + m_margin * 2) * m_size;
	int pitch = ((realwidth + 7) / 8 + 3) / 4 * 4;

	if (m_pBmi)
	{
		free(m_pBmi);
		m_pBmi = NULL;
	}
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}

	m_pBmi = (unsigned char*)malloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2);
	m_pData = (unsigned char*)malloc(pitch * realwidth);
	unsigned char* pDataTmp = m_pData;

	BITMAPINFOHEADER* bmih = (BITMAPINFOHEADER*)m_pBmi;
	memset(bmih, 0, sizeof(BITMAPINFOHEADER));
	bmih->biBitCount = 1;
	bmih->biClrImportant = 0;
	bmih->biClrUsed = 0;
	bmih->biCompression = BI_RGB;
	bmih->biHeight = -realwidth;
	bmih->biPlanes = 1;
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biSizeImage = pitch * realwidth;
	bmih->biWidth = realwidth;
	bmih->biXPelsPerMeter = 0;
	bmih->biYPelsPerMeter = 0;

	RGBQUAD* pPalette = (RGBQUAD*)(m_pBmi+sizeof(BITMAPINFOHEADER));
	memset(pPalette, 0, sizeof(RGBQUAD) * 2);
	pPalette[0].rgbBlue = 0;
	pPalette[0].rgbGreen = 0;
	pPalette[0].rgbRed = 0;
	pPalette[0].rgbReserved = 0;
	pPalette[1].rgbBlue = 255;
	pPalette[1].rgbGreen = 255;
	pPalette[1].rgbRed = 255;
	pPalette[1].rgbReserved = 0;

	unsigned char* row = (unsigned char *)malloc(pitch);

	unsigned char *pSrc, *pDst;
	int bit;
	/* top margin */
	memset(row, 0xff, pitch);
	for(unsigned int y = 0; y < m_margin * m_size; y++) 
	{
		memcpy(pDataTmp, row, pitch);
		pDataTmp += pitch;
	}

	/* data */
	pSrc = qrcode->data;
	for(int y = 0; y < qrcode->width; y++) 
	{
		bit = 7;
		memset(row, 0xff, pitch);
		pDst = row;
		pDst += m_margin * m_size / 8;
		bit = 7 - (m_margin * m_size % 8);
		for(int x = 0; x < qrcode->width; x++) 
		{
			for(unsigned int xx = 0; xx < m_size; xx++) 
			{
				*pDst ^= (*pSrc & 0x01) << bit;
				bit--;
				if(bit < 0) {
					pDst++;
					bit = 7;
				}
			}
			pSrc++;
		}
		for(unsigned int yy = 0; yy < m_size; yy++) 
		{
			memcpy(pDataTmp, row, pitch);
			pDataTmp += pitch;
		}
	}

	/* bottom margin */
	memset(row, 0xff, pitch);
	for(unsigned int y = 0; y < m_margin * m_size; y++) 
	{
		memcpy(pDataTmp, row, pitch);
		pDataTmp += pitch;
	}

	free(row);
	QRcode_free(qrcode);

	//�ڶ�ά�������������˵��
	HDC nulldc = GetDC(NULL);
	HDC memdc = ::CreateCompatibleDC(nulldc);
	HBITMAP bitmap = ::CreateCompatibleBitmap(nulldc, realwidth, realwidth);
	ReleaseDC(NULL, nulldc);

	::SelectObject(memdc, bitmap);
	::SetDIBits(memdc, bitmap, 0, realwidth, m_pData, (BITMAPINFO*)m_pBmi, DIB_RGB_COLORS);

	RECT textrc = {m_margin*m_size, realwidth - m_margin * m_size, realwidth-m_margin*m_size, realwidth};

	HFONT font;  
	LOGFONT lf;  //��������ṹ�� 
	lf.lfHeight=0;
	lf.lfWidth=16;
	lf.lfEscapement=0;  
	lf.lfOrientation=0;  
	lf.lfItalic=false;  
	lf.lfUnderline=false;  
	lf.lfStrikeOut=false;  
	lf.lfCharSet=DEFAULT_CHARSET;  
	lf.lfOutPrecision=0;  
	lf.lfWeight=400;  //0-1000,1000�ӵ����  
	lf.lfClipPrecision=0;  
	lf.lfQuality=0;  
	lf.lfPitchAndFamily=0;   
	strcpy(lf.lfFaceName,"Times New Roman");  //����ʹ���壬���壬΢���ź�  �ȵ���������  ����Arial  Times New Roman ��Ӣ������  
	font=CreateFontIndirect(&lf);  
	SelectObject(memdc,font);
	::SetTextColor(memdc, RGB(0,0,0));
	::DrawTextA(memdc, text, -1, &textrc, DT_CENTER);

	::GetDIBits(memdc, bitmap, 0, realwidth, m_pData, (BITMAPINFO*)m_pBmi, DIB_RGB_COLORS);

	DeleteObject(font);
	DeleteObject(bitmap);
	::DeleteDC(memdc);

	return true;
}

void QRencoder::Preview(HWND hWnd)
{
	if (!m_pBmi || !m_pData)
		return;

	int width = ((BITMAPINFO*)m_pBmi)->bmiHeader.biWidth;
	RECT rc;
	GetClientRect(hWnd, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	::StretchDIBits(::GetDC(hWnd), (w-width)/2, (h-width)/2 , width, width, 0, 0, width, width, m_pData, (BITMAPINFO*)m_pBmi, DIB_RGB_COLORS, SRCCOPY);
}

void QRencoder::Save(const char* outfile)
{
	if (!m_pBmi || !m_pData)
		return;

	BITMAPINFO* pB = (BITMAPINFO*)m_pBmi;
	HDC nulldc = GetDC(NULL);
	HDC memdc = ::CreateCompatibleDC(nulldc);
	HBITMAP bitmap = ::CreateCompatibleBitmap(nulldc, pB->bmiHeader.biWidth, -pB->bmiHeader.biHeight);
	ReleaseDC(NULL, nulldc);
	::SelectObject(memdc, bitmap);
	::SetDIBits(memdc, bitmap, 0, -pB->bmiHeader.biHeight, m_pData, pB, DIB_RGB_COLORS);

	CImage image;
	image.Attach(bitmap);
	image.Save(outfile);
	image.Detach();

	DeleteObject(bitmap);
	DeleteDC(memdc);
}

//void QRencoder::SavePNG(const char* outfile)
//{
//	if (!qrcode)
//		return;
//
//	int realwidth = (qrcode->width + m_margin * 2) * m_size;
//	unsigned char* row = (unsigned char *)malloc((realwidth + 7) / 8);
//	if(row == NULL) {
//		fprintf(stderr, "Failed to allocate memory.\n");
//		exit(EXIT_FAILURE);
//	}
//	
//	FILE *fp;
//	if(outfile[0] == '-' && outfile[1] == '\0') {
//		fp = stdout;
//	} else {
//		fp = fopen(outfile, "wb");
//		if(fp == NULL) {
//			fprintf(stderr, "Failed to create file: %s\n", outfile);
//			perror(NULL);
//			exit(EXIT_FAILURE);
//		}
//	}
//
//	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//	if(png_ptr == NULL) {
//		fprintf(stderr, "Failed to initialize PNG writer.\n");
//		exit(EXIT_FAILURE);
//	}
//
//	png_infop info_ptr = png_create_info_struct(png_ptr);
//	if(info_ptr == NULL) {
//		fprintf(stderr, "Failed to initialize PNG write.\n");
//		exit(EXIT_FAILURE);
//	}
//
//	if(setjmp(png_jmpbuf(png_ptr))) {
//		png_destroy_write_struct(&png_ptr, &info_ptr);
//		fprintf(stderr, "Failed to write PNG image.\n");
//		exit(EXIT_FAILURE);
//	}
//
//	png_init_io(png_ptr, fp);
//	png_set_write_fn(png_ptr, fp, png_write_data, png_flush);
//
//	png_color palette[2];
//	palette[0].red   = m_fgcolor.rgbRed;
//	palette[0].green = m_fgcolor.rgbGreen;
//	palette[0].blue  = m_fgcolor.rgbBlue;
//	palette[1].red   = m_bgcolor.rgbRed;
//	palette[1].green = m_bgcolor.rgbGreen;
//	palette[1].blue  = m_bgcolor.rgbBlue;
//
//	png_byte alpha_values[2];
//	alpha_values[0] = m_fgcolor.rgbReserved;
//	alpha_values[1] = m_bgcolor.rgbReserved;
//
//	png_set_PLTE(png_ptr, info_ptr, palette, 2);
//	png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);
//	png_set_IHDR(png_ptr, info_ptr,
//		realwidth, realwidth,
//		1,
//		PNG_COLOR_TYPE_PALETTE,
//		PNG_INTERLACE_NONE,
//		PNG_COMPRESSION_TYPE_DEFAULT,
//		PNG_FILTER_TYPE_DEFAULT);
//	png_set_pHYs(png_ptr, info_ptr,
//		72 * INCHES_PER_METER,
//		72 * INCHES_PER_METER,
//		PNG_RESOLUTION_METER);
//	png_write_info(png_ptr, info_ptr);
//
//	unsigned char *p, *q;
//	int bit;
//	/* top margin */
//	memset(row, 0xff, (realwidth + 7) / 8);
//	for(unsigned int y = 0; y < m_margin * m_size; y++) 
//	{
//		png_write_row(png_ptr, row);
//	}
//
//	/* data */
//	p = qrcode->data;
//	for(int y = 0; y < qrcode->width; y++) 
//	{
//		bit = 7;
//		memset(row, 0xff, (realwidth + 7) / 8);
//		q = row;
//		q += m_margin * m_size / 8;
//		bit = 7 - (m_margin * m_size % 8);
//		for(int x = 0; x < qrcode->width; x++) 
//		{
//			for(unsigned int xx = 0; xx < m_size; xx++) 
//			{
//				*q ^= (*p & 1) << bit;
//				bit--;
//				if(bit < 0) {
//					q++;
//					bit = 7;
//				}
//			}
//			p++;
//		}
//		for(unsigned int yy = 0; yy < m_size; yy++) 
//		{
//			png_write_row(png_ptr, row);
//		}
//	}
//
//	/* bottom margin */
//	memset(row, 0xff, (realwidth + 7) / 8);
//	for(unsigned int y = 0; y < m_margin * m_size; y++) 
//	{
//		png_write_row(png_ptr, row);
//	}
//
//	png_write_end(png_ptr, info_ptr);
//	png_destroy_write_struct(&png_ptr, &info_ptr);
//
//	fclose(fp);
//	free(row);
//}
//

//void QRencoder::png_write_data(png_structp png_ptr, png_bytep data, png_size_t length)
//{
//	png_uint_32 check;
//
//	if (png_ptr == NULL)
//		return;
//
//	check = fwrite(data, 1, length, (png_FILE_p)(png_ptr->io_ptr));
//
//	if (check != length)
//		png_error(png_ptr, "Write Error");
//}
//
//void QRencoder::png_flush(png_structp png_ptr)
//{
//	png_FILE_p io_ptr;
//
//	if (png_ptr == NULL)
//		return;
//
//	io_ptr = (png_FILE_p)(png_ptr->io_ptr);
//	fflush(io_ptr);
//}