
// QRcodeBuilder.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "QRcodeBuilder.h"
#include "QRcodeBuilderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQRcodeBuilderApp

BEGIN_MESSAGE_MAP(CQRcodeBuilderApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQRcodeBuilderApp ����

CQRcodeBuilderApp::CQRcodeBuilderApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CQRcodeBuilderApp ����

CQRcodeBuilderApp theApp;


// CQRcodeBuilderApp ��ʼ��

BOOL CQRcodeBuilderApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//��ʼ�����ݿ�
	CreateDirectoryA("database",NULL);//�������ݿ��ļ���
	CreateDirectoryA("picture",NULL);//������ά��ͼƬ�ļ���
	FILE* fp = fopen("database\\qrcode.db", "rb");
	//���û�д������ݿ��򴴽�
	if (fp == NULL)
	{
		if (!db_qrcode(DB_CREATE_TABLE))
		{
			::MessageBoxA(NULL, "�������ݿ�ʧ�ܣ�", "ERROR", MB_OK);
			return FALSE;
		}
	}

	CQRcodeBuilderDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
