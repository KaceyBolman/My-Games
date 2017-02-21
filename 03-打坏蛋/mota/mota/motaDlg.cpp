
// motaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mota.h"
#include "motaDlg.h"
#include "afxdialogex.h"
#include "Solider.h"

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


// CmotaDlg �Ի���




CmotaDlg::CmotaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmotaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmotaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOLIDER, m_solider);
	DDX_Control(pDX, IDC_KNIGHT, m_knight);
}

BEGIN_MESSAGE_MAP(CmotaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CmotaDlg ��Ϣ�������
Solider solider;
Knight knight;
HBITMAP hbs[16];
HBITMAP hbk[2];
HANDLE hthreads[5];
HANDLE hthreadk;
int direction = 0;
bool running[5];
CStatic *psoldier, *pknight;
DWORD WINAPI SoliderStand(LPVOID lpParam) {
	while (true) {
		solider.Stand();
		::Sleep(20);
	}
	return 0;
}

DWORD WINAPI SoliderUp(LPVOID lpParam) {
	while (true) {
		solider.Up();
		::Sleep(20);
	}
	return 0;
}

DWORD WINAPI SoliderDown(LPVOID lpParam) {
	while (true) {
		solider.Down();
		::Sleep(20);
	}
	return 0;
}

DWORD WINAPI SoliderLeft(LPVOID lpParam) {
	while (true) {
		solider.Left();
		::Sleep(20);
	}
	return 0;
}

DWORD WINAPI SoliderRight(LPVOID lpParam) {
	while (true) {
		solider.Right();
		::Sleep(20);
	}
	return 0;
}

void SetSoliderDirction(int direction) {
	for (int i = 0; i < 5; i++) {
		if (running[i]) {
			::SuspendThread(hthreads[i]);
			running[i] = false;
		}
	}
	running[direction] = true;
	::ResumeThread(hthreads[direction]);
}

DWORD WINAPI KnightStand(LPVOID lpParam) {
	while (true) {
		knight.Stand();
		::Sleep(20);
	}
	return 0;
}

BOOL CmotaDlg::OnInitDialog()
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
	psoldier = &m_solider;
	pknight = &m_knight;

	hbk[0] = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP17),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE) ;
	hbk[1] = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP18),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE) ;
	for (int i = 0; i < 16; i++)
		hbs[i] = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(132+i),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE) ;

	solider.Set(&m_solider, hbs);
	knight.Set(&m_knight, hbk);

	hthreadk = ::CreateThread(NULL, 0, KnightStand, NULL, 0, NULL);	//knight��ʼ״̬ΪStand
	for (int i = 1; i < 5; i++)
		running[i] = false;
	running[0] = true;	//solider��ʼ״̬ΪStand
	hthreads[0] = ::CreateThread(NULL, 0, SoliderStand, NULL, 0, NULL);
	hthreads[1] = ::CreateThread(NULL, 0, SoliderUp, NULL, CREATE_SUSPENDED, NULL);
	hthreads[2] = ::CreateThread(NULL, 0, SoliderDown, NULL, CREATE_SUSPENDED, NULL);
	hthreads[3] = ::CreateThread(NULL, 0, SoliderLeft, NULL, CREATE_SUSPENDED, NULL);
	hthreads[4] = ::CreateThread(NULL, 0, SoliderRight, NULL, CREATE_SUSPENDED, NULL);	
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmotaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmotaDlg::OnPaint()
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
HCURSOR CmotaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int random(int b, int a) {
	CTime t = CTime::GetCurrentTime();
	int n = t.GetMinute() * 60 + t.GetSecond();
	while(n-- > 0)
	{
		rand();
	}
	return rand()%b + a;
}


void CheckCollision()
{
	RECT rect, rect1, rect2;
	psoldier->GetWindowRect(&rect1);
	pknight->GetWindowRect(&rect2);
	int collision = IntersectRect(&rect, &rect1, &rect2);
	while (collision){
		TRACE("collision\n");
		int x = random(235, 30);
		int y = random(155, 0);
		pknight->MoveWindow(x, y, 32, 32);
		psoldier->GetWindowRect(&rect1);
		pknight->GetWindowRect(&rect2);
		collision = IntersectRect(&rect, &rect1, &rect2);
	}
}

BOOL CmotaDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN ) {
		CRect rects,  dlgrect;
		GetWindowRect(&dlgrect);
		int dlgwidth = dlgrect.right-dlgrect.left;
		int dlgheight = dlgrect.bottom-dlgrect.top;
		m_solider.GetWindowRect(&rects);//��ȡ�ؼ�����Ļ����
		ScreenToClient(&rects);//ת��Ϊ�Ի����ϵĿͻ�����

		switch (pMsg->wParam) {
			case VK_UP:
				if (rects.top >= 3) {
					rects.top -= 3;
					rects.bottom -= 3;
				}
				m_solider.MoveWindow(rects);
				SetSoliderDirction(1);
				break;
			case VK_DOWN:
				if (rects.bottom <= dlgheight-30) {
					rects.top += 3;
					rects.bottom += 3;
				}
				m_solider.MoveWindow(rects);
				SetSoliderDirction(2);
				break;
			case VK_LEFT:
				if (rects.left >= 3) {
					rects.left -= 3;
					rects.right -= 3;
				}
				m_solider.MoveWindow(rects);
				SetSoliderDirction(3);
				direction = 3;
				break;
			case VK_RIGHT:
				if (rects.right <= dlgwidth - 8) {
					rects.right += 3;
					rects.left += 3;
				}
				m_solider.MoveWindow(rects);
				SetSoliderDirction(4);
				direction = 4;
				break;
			default:
				break;
		}
		CheckCollision();
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


