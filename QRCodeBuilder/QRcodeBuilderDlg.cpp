
// QRcodeBuilderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRcodeBuilder.h"
#include "QRcodeBuilderDlg.h"
#include "Print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQRcodeBuilderDlg �Ի���////////////////////////////////////////////////////////////////////////////////////////////////////////////

CQRcodeBuilderDlg::CQRcodeBuilderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQRcodeBuilderDlg::IDD, pParent)
	, m_nMargin(2)
	, m_nSize(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQRcodeBuilderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQRcodeBuilderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_BUILDER, &CQRcodeBuilderDlg::OnBnClickedButtonBuilder)
	ON_COMMAND(ID_32771, &CQRcodeBuilderDlg::OnSetSize)
	ON_COMMAND(ID_32773, &CQRcodeBuilderDlg::OnMargin)
	ON_COMMAND(ID_32774, &CQRcodeBuilderDlg::OnDB_Delete)
	ON_COMMAND(ID_32775, &CQRcodeBuilderDlg::OnSelect)
	ON_COMMAND(ID_32778, &CQRcodeBuilderDlg::OnPrint)
	ON_COMMAND(ID_32779, &CQRcodeBuilderDlg::OnPrintPreview)
END_MESSAGE_MAP()


// CQRcodeBuilderDlg ��Ϣ�������

BOOL CQRcodeBuilderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQRcodeBuilderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQRcodeBuilderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();	
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQRcodeBuilderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQRcodeBuilderDlg::OnBnClickedButtonBuilder()
{
	char text[100] = {0};

	UINT num = GetDlgItemInt(IDC_EDIT_NUM);
	if (num == 0)
	{
		MessageBoxA("��������������","��ʾ",MB_OK);
		return;
	}

	GetDlgItemTextA(IDC_EDIT_SERIAL, text, 100);

	QRencoder qrencoder;
	qrencoder.SetMargin(m_nMargin);
	qrencoder.SetSize(m_nSize);
	qrencoder.SetColor(RGB(255,255,255),RGB(255,0,0));

	if (qrencoder.EncodeString(text))
	{
		qrencoder.Preview(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());
		char outfile[120];
		sprintf(outfile, ".\\picture\\%s.bmp", text);
		qrencoder.SaveBmp2(outfile);
	}

	//UINT serial = strtoul(text,NULL,10);
	//for (UINT i = 0; i < num; i++)
	//{
	//	sprintf(text,"%X",serial);

	//	QRCODE_INFO record = {0};
	//	strcpy(record.serial, text);
	//	if (!db_qrcode(DB_INSERT, &record))
	//	{
	//		char info[120];
	//		sprintf(info, "�����к�[%s]�Ѵ���!", text);
	//		MessageBoxA(info, "ERROR", MB_OK);
	//		return;
	//	}

	//	if (qrencoder.EncodeString(text))
	//	{
	//		qrencoder.Preview(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());

	//		char outfile[120];
	//		sprintf(outfile, ".\\picture\\%s.bmp", text);
	//		qrencoder.SaveBmp2(outfile);
	//	}
	//	serial++;
	//}

	MessageBoxA("�������ɶ�ά����ɣ�","��ʾ", MB_OK | MB_ICONINFORMATION);
}
void CQRcodeBuilderDlg::OnSetSize()
{
	CSetSizeDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_nSize = dlg.GetSize();
	}
}

void CQRcodeBuilderDlg::OnMargin()
{
	CSetMarginDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_nMargin = dlg.GetMargin();
	}
}

void CQRcodeBuilderDlg::OnDB_Delete()
{
	if (MessageBoxA("ȷ��Ҫ������ݿ��ڵ����ݣ�","������ݿ�",MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{
		if (db_qrcode(DB_DELETE))
		{
			MessageBoxA("�����ɹ���", "��ʾ", MB_ICONINFORMATION | MB_OK);
		}
	}
}

void CQRcodeBuilderDlg::OnSelect()
{
	CSelectDlg dlg(this);
	dlg.DoModal();
}

void CQRcodeBuilderDlg::OnPrint()
{
	// TODO: �ڴ���������������
	CPrintFrame print(NULL);
}

void CQRcodeBuilderDlg::OnPrintPreview()
{
	// TODO: �ڴ���������������
	CPrintFrame printpreview((CFrameWnd*)this,true);
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���////////////////////////////////////////////////////////////////////////////////////////////////////////

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CSetSizeDlg �Ի���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSetSizeDlg, CDialog)

CSetSizeDlg::CSetSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetSizeDlg::IDD, pParent)
	, m_nSize(10)
{
	
}

CSetSizeDlg::~CSetSizeDlg()
{
}

void CSetSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SET_SIZE, m_nSize);
}

BEGIN_MESSAGE_MAP(CSetSizeDlg, CDialog)
END_MESSAGE_MAP()


// CSetSizeDlg ��Ϣ�������

// CSetMarginDlg�Ի���//////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSetMarginDlg, CDialog)

CSetMarginDlg::CSetMarginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetMarginDlg::IDD, pParent)
	, m_nMargin(2)
{
	
}

CSetMarginDlg::~CSetMarginDlg()
{
}

void CSetMarginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SET_MARGIN, m_nMargin);
}

BEGIN_MESSAGE_MAP(CSetMarginDlg, CDialog)
END_MESSAGE_MAP()
// CSetMarginDlg��Ϣ�������


// CSelectDlg �Ի���/////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSelectDlg, CDialog)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{
	
}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECT, m_List);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlStarttime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_ctrlEndtime);
}

BOOL CSelectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List.InsertColumn(0, "�к�", LVCFMT_CENTER, 50);
	m_List.InsertColumn(1, "���к�", LVCFMT_CENTER, 150);
	m_List.InsertColumn(2, "��������", LVCFMT_CENTER, 150);
	m_List.InsertColumn(3, "��ע��Ϣ", LVCFMT_CENTER, 300);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_BYSERIAL, &CSelectDlg::OnBnClickedButtonSelectByserial)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_BYDATE, &CSelectDlg::OnBnClickedButtonSelectBydate)
END_MESSAGE_MAP()


// CSelectDlg ��Ϣ�������

void CSelectDlg::OnBnClickedButtonSelectByserial()
{
	QRCODE_INFO inout;

	GetDlgItemTextA(IDC_EDIT_SELECT_SERIAL, inout.serial, 32);

	if (db_qrcode(DB_SELECT, &inout))
	{
		m_List.DeleteAllItems();
		char tmp[10];
		sprintf(tmp,"%d",1);
		m_List.InsertItem(0, tmp);
		m_List.SetItemText(0, 1, inout.serial);
		m_List.SetItemText(0, 2, inout.date);
		m_List.SetItemText(0, 3, inout.info);
	}
	else
	{
		MessageBoxA("δ�ҵ�ָ�����к���Ϣ��","��ʾ",MB_OK | MB_ICONINFORMATION);
	}
}

void CSelectDlg::OnBnClickedButtonSelectBydate()
{
	QRCODE_RECORDS records;

	//char starttime[20];
	//char endtime[20];
	//GetDlgItemTextA(IDC_DATETIMEPICKER1, starttime, 20);
	//GetDlgItemTextA(IDC_DATETIMEPICKER2, endtime, 20);

	SYSTEMTIME starttime,endtime;
	m_ctrlStarttime.GetTime(&starttime);
	m_ctrlEndtime.GetTime(&endtime);

	char szStarttime[32];
	char szEndtime[32];
	sprintf_s(szStarttime, sizeof(szStarttime), "%04d-%02d-%02d", starttime.wYear, starttime.wMonth, starttime.wDay);
	sprintf_s(szEndtime, sizeof(szEndtime), "%04d-%02d-%02d", endtime.wYear, endtime.wMonth, endtime.wDay);

	if (db_qrcode(DB_SELECT_ALL, NULL, szStarttime, szEndtime, &records))
	{
		int size = records.size();
		if (size == 0)
		{
			MessageBoxA("δ�ҵ�ָ��ʱ����ڶ�ά��������Ϣ��","��ʾ",MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			m_List.DeleteAllItems();
			for (int i = 0; i < size; i++)
			{
				QRCODE_INFO* p = &(records[i]);
				char tmp[10];
				sprintf(tmp,"%d",i+1);
				m_List.InsertItem(i, tmp);
				m_List.SetItemText(i, 1, p->serial);
				m_List.SetItemText(i, 2, p->date);
				m_List.SetItemText(i, 3, p->info);
			}
		}
	}
	else
	{
		MessageBoxA("��ѯʧ�ܣ�","����",MB_OK | MB_ICONERROR);
	}
}
