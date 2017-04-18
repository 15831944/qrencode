// Print.cpp : 实现文件
//

#include "stdafx.h"
#include "Print.h"


// CPrintFrame

CPrintFrame::CPrintFrame(CFrameWnd* hWnd, bool bPrintPreview)
: m_pOldFrame(hWnd)
, m_pView(NULL)
, m_bPrintPreview(bPrintPreview)
{
	if ( !Create(NULL, "打印预览"))
	{
		TRACE0("Failed to create view window! ");
	}
}

CPrintFrame::~CPrintFrame()
{
	m_pOldFrame->ShowWindow(SW_SHOW);	
}


BEGIN_MESSAGE_MAP(CPrintFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPrintFrame 消息处理程序
int CPrintFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CCreateContext context;
	context.m_pCurrentFrame = this;
	context.m_pCurrentDoc = NULL;
	context.m_pLastView = NULL;
	context.m_pNewViewClass = RUNTIME_CLASS(CPrintView);

	m_pView = (CPrintView*)CreateView(&context);
	if (!m_pView)
		return -1;

	SetActiveView(m_pView);

	AfxGetApp()->m_pMainWnd = this;
	
	if (m_bPrintPreview)
	{
		m_pOldFrame->ShowWindow(SW_HIDE);
		ShowWindow(SW_SHOWMAXIMIZED);
		m_pView->SendMessage(WM_COMMAND,ID_FILE_PRINT_PREVIEW);
	}
	else
	{
		m_pView->SendMessage(WM_COMMAND,ID_FILE_PRINT);
	}

	return 0;
}

void CPrintFrame::OnClose()
{
	AfxGetApp()->m_pMainWnd = m_pOldFrame;
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);

	CFrameWnd::OnClose();
}


// CPrintView

IMPLEMENT_DYNCREATE(CPrintView, CView)

CPrintView::CPrintView()
{

}

CPrintView::~CPrintView()
{
}

BEGIN_MESSAGE_MAP(CPrintView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()


// CPrintView 绘图

void CPrintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}

void CPrintView::OnFilePrintPreview()
{
	CPrintPreviewState* pState = new CPrintPreviewState;
	//pState->lpfnCloseProc = _AfxPrintPreviewCloseProc; //设置打印预览窗口关闭时的调用函数
	if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this, RUNTIME_CLASS(CPrintPreviewView), pState))
	{
		TRACE0("Error, DoPrintPreview failed. \n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;
	}
}

BOOL CPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPrintView 诊断

#ifdef _DEBUG
void CPrintView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPrintView 消息处理程序


// CPrintPreviewView

IMPLEMENT_DYNCREATE(CPrintPreviewView, CPreviewViewEx)

CPrintPreviewView::CPrintPreviewView()
{

}

CPrintPreviewView::~CPrintPreviewView()
{
}

BEGIN_MESSAGE_MAP(CPrintPreviewView, CPreviewViewEx)
END_MESSAGE_MAP()


// CPrintPreviewView 诊断

#ifdef _DEBUG
void CPrintPreviewView::AssertValid() const
{
	CPreviewViewEx::AssertValid();
}

#ifndef _WIN32_WCE
void CPrintPreviewView::Dump(CDumpContext& dc) const
{
	CPreviewViewEx::Dump(dc);
}
#endif
#endif //_DEBUG


// CPrintPreviewView 消息处理程序
