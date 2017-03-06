
// puzzleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "puzzle.h"
#include "puzzleDlg.h"
#include "afxdialogex.h"
#include "MyPuzzle.h"
#include "dlg_img.h"

#define MY_TIMER 123

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpuzzleDlg �Ի���




CpuzzleDlg::CpuzzleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpuzzleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICBK, img_bk);
}

BEGIN_MESSAGE_MAP(CpuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CpuzzleDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_DIFF, &CpuzzleDlg::OnBnClickedButtonDiff)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_START, &CpuzzleDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// CpuzzleDlg ��Ϣ�������
MyPuzzle mp;
BOOL CpuzzleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	mp.SetDlg(this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CpuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CpuzzleDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CpuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CpuzzleDlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}

dlg_img imgdlg;
void CpuzzleDlg::OnBnClickedButtonDiff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (imgdlg.m_hWnd == NULL)
		imgdlg.Create(IDD_DIALOG_IMG, this);
	imgdlg.ShowWindow(SW_SHOW);
}


void CpuzzleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint   p;
	GetCursorPos(&p);
	ScreenToClient(&p);

	if (16 <= p.y && 25 <= p.x) {
		int y = (p.y - 16)/90;
		int x = (p.x - 25)/90;
		if (0 <= x && x <= 3 && 0 <= y && y <= 3) {
			if (!mp.IsSamePoint(x, y)) {
				mp.EraseFrame();
				::Sleep(20);
				mp.DrawFrame(x,y);
			}
		}
	}

	TRACKMOUSEEVENT TrackMouseEvent;  //�������뿪
	TrackMouseEvent.cbSize = sizeof(TrackMouseEvent);
	TrackMouseEvent.dwFlags = TME_LEAVE;
	TrackMouseEvent.hwndTrack = GetSafeHwnd();
	TrackMouseEvent.dwHoverTime = HOVER_DEFAULT;
	_TrackMouseEvent(&TrackMouseEvent);

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CpuzzleDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pos;   
	GetCursorPos(&pos);  //��ȡ��ǰ���λ��   
  
	for (int i = 0; i < 15; i++) {
		CRect rc;
		mp.pics[i]->GetWindowRect(&rc); 
		if (rc.PtInRect(pos)) {   
			SetCursor(LoadCursor(NULL, IDC_HAND)); 
			return TRUE; 
		}   
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CpuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint   p;
	GetCursorPos(&p);
	ScreenToClient(&p);

	if (16 <= p.y && 25 <= p.x ) {
		int y = (p.y - 16)/90;
		int x = (p.x - 25)/90;
		if (0 <= x && x <= 3 && 0 <= y && y <= 3) {
			mp.MovePic(x,y);
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					TRACE("%2d ", mp.puzzles[i][j]);
				TRACE("\n");
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CpuzzleDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mp.israndom = true;
	SetTimer(MY_TIMER,200,NULL);
}

#define RANDOMTIMES 50
int clicksum = 0;
void CpuzzleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == MY_TIMER) {
		mp.RandomMove();
		clicksum++;
	}
	if (clicksum > RANDOMTIMES) {
		clicksum = 0;
		KillTimer(MY_TIMER);
		mp.israndom = false;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CpuzzleDlg::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	mp.EraseFrame();
	CDialogEx::OnMouseLeave();
}
