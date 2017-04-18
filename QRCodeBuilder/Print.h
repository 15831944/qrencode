#pragma once

class CPrintView;

// CPrintFrame ���

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


// CPrintView ��ͼ

class CPrintView : public CView
{
	DECLARE_DYNCREATE(CPrintView)

protected:
	CPrintView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPrintView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ

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


// CPrintPreviewView ��ͼ

class CPrintPreviewView : public CPreviewViewEx
{
	DECLARE_DYNCREATE(CPrintPreviewView)

protected:
	CPrintPreviewView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


