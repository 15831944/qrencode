
// QRcodeBuilderDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"


// CQRcodeBuilderDlg 对话框//////////////////////////////////////////////////////////////////////////////////////////
class CQRcodeBuilderDlg : public CDialog
{
// 构造
public:
	CQRcodeBuilderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QRCODEBUILDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

//添加数据成员
private:
	unsigned int m_nMargin;
	unsigned int m_nSize;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

// CAboutDlg 对话框///////////////////////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

// CSetSizeDlg 对话框////////////////////////////////////////////////////////////////////////////////////////////

class CSetSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetSizeDlg)

public:
	CSetSizeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetSizeDlg();

// 对话框数据
	enum { IDD = IDD_SET_SIZE };

	UINT GetSize() const {return m_nSize;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	unsigned int m_nSize;
};


// CMarginDlg 对话框////////////////////////////////////////////////////////////////////////////////////////////////////

class CSetMarginDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetMarginDlg)

public:
	CSetMarginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetMarginDlg();

// 对话框数据
	enum { IDD = IDD_SET_MARGIN };

	UINT GetMargin() const {return m_nMargin;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	unsigned int m_nMargin;
};


// CSelectDlg 对话框////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelectDlg();

// 对话框数据
	enum { IDD = IDD_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
