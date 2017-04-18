
// QRcodeBuilderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"


// CQRcodeBuilderDlg �Ի���//////////////////////////////////////////////////////////////////////////////////////////
class CQRcodeBuilderDlg : public CDialog
{
// ����
public:
	CQRcodeBuilderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QRCODEBUILDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

//������ݳ�Ա
private:
	unsigned int m_nMargin;
	unsigned int m_nSize;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBuilder();
	afx_msg void OnSetSize();
	afx_msg void OnMargin();
	afx_msg void OnDB_Delete();
	afx_msg void OnSelect();
	afx_msg void OnPrint();
	afx_msg void OnPrintPreview();
};

// CAboutDlg �Ի���///////////////////////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

// CSetSizeDlg �Ի���////////////////////////////////////////////////////////////////////////////////////////////

class CSetSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetSizeDlg)

public:
	CSetSizeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetSizeDlg();

// �Ի�������
	enum { IDD = IDD_SET_SIZE };

	UINT GetSize() const {return m_nSize;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	unsigned int m_nSize;
};


// CMarginDlg �Ի���////////////////////////////////////////////////////////////////////////////////////////////////////

class CSetMarginDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetMarginDlg)

public:
	CSetMarginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetMarginDlg();

// �Ի�������
	enum { IDD = IDD_SET_MARGIN };

	UINT GetMargin() const {return m_nMargin;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	unsigned int m_nMargin;
};


// CSelectDlg �Ի���////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectDlg();

// �Ի�������
	enum { IDD = IDD_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_List;
	CDateTimeCtrl m_ctrlStarttime;
	CDateTimeCtrl m_ctrlEndtime;
public:
	afx_msg void OnBnClickedButtonSelectByserial();
	afx_msg void OnBnClickedButtonSelectBydate();
};
