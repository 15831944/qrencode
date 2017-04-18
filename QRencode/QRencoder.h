//QRencoder.h:

#pragma once

#ifdef QRENCODE_EXPORTS
#define QRENCODE_API __declspec(dllexport)
#else
#define QRENCODE_API __declspec(dllimport)
#endif

#include <Windows.h>

class QRENCODE_API QRencoder
{
public:
	QRencoder();
	~QRencoder();

public:
	void SetSize(unsigned int size) { m_size = size; }	//ÿ������ռ����λ����ʼ��Ϊ1
	void SetMargin(unsigned int margin) { m_margin = margin; }	//�߾��ʼ��Ϊ0
	void SetColor(DWORD dwBgcolor, DWORD dwFgcolor) { m_dwBgcolor = dwBgcolor; m_dwFgcolor = dwFgcolor; }

	bool EncodeString(const char* text);
	void Save(const char* outfile);
	void SaveBmp2(const char* outfile);
	void Preview(HWND hWnd, int width = -1);	//Ĭ��Ϊ-1��ʾ��ʵ�ʴ�С��ʾ

private:
	unsigned int m_size;
	unsigned int m_margin;
	DWORD m_dwBgcolor;
	DWORD m_dwFgcolor;

	unsigned char* m_pData;
	unsigned char* m_pBmi;
};