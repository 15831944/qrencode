#pragma once

class CPrintView;

// CPrintFrame 框架

class CPrintFrame : public CFrameWnd
{
public:
	CPrintFrame(CFrameWnd* hWnd = NULL, bool bPrintPreview = false);
	virtual ~CPrintFrame();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();

private:
	CFrameWnd*  m_pOldFrame;
	CPrintView* m_pView;
	bool m_bPrintPreview;
};


// CPrintView 视图

class CPrintView : public CView
{
	DECLARE_DYNCREATE(CPrintView)

protected:
	CPrintView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPrintView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图

	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFilePrintPreview();
};


// CPrintPreviewView 视图

class CPrintPreviewView : public CPreviewViewEx
{
	DECLARE_DYNCREATE(CPrintPreviewView)

protected:
	CPrintPreviewView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPrintPreviewView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


