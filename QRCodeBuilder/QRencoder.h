//QRencoder.h:

#pragma once

class QRencoder
{
public:
	QRencoder();
	~QRencoder();

public:
	void SetSize(unsigned int size) { m_size = size; }
	void SetMargin(unsigned int margin) { m_margin = margin; }
	void SetColor(RGBQUAD* bgcolor, RGBQUAD* fgcolor) { memcpy(&m_bgcolor, bgcolor, sizeof(RGBQUAD)); memcpy(&m_fgcolor, fgcolor, sizeof(RGBQUAD));}

	bool EncodeString(const char* text);
	void Save(const char* outfile);
	void Preview(HWND hWnd);

private:
	unsigned int m_size;
	unsigned int m_margin;
	RGBQUAD m_bgcolor;
	RGBQUAD m_fgcolor;

	unsigned char* m_pData;
	unsigned char* m_pBmi;
};