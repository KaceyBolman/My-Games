
// mouseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mouse.h"
#include "mouseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////ȫ�ֱ����빦�ܺ���////////////////////////
#include <iostream>
#include <time.h>
#define ID_TIMER 3

BOOL *pbuttons_value;
bool isplaying = false;
int mytime = 30;
int myscore = 0;
int currentradio = -1;
CButton *buttons[9];
CmouseDlg *dlg;
CString *pscore, *ptime;

int random() {
	srand((unsigned)time(NULL));
	return rand()%(8-0+1)+0;  //����[a,b]֮�����������ķ�����rand()%(b-a+1)+a;
}

void newradio() {
	currentradio = random();
	*pbuttons_value = currentradio;
}

void WINAPI count(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime) {	//ÿ��1s��һ
	if (isplaying) {
		mytime--;
		WCHAR buf[5];
		wsprintf(buf, _T("%d"), mytime);
		*ptime = buf;
		dlg->UpdateData(false);
		if (mytime == 0) {
			dlg->OnBnClickedStart();
		}
	}
}

void check(int n) {
	if (isplaying) {
		if (n == currentradio) {
			myscore++;
			newradio();
		} else {
			myscore--;
		}
		WCHAR buf[5];
		wsprintf(buf, _T("%d"), myscore);
		*pscore = buf;
	}
	dlg->UpdateData(false);
}


/////////////////////////////////////////////////////////////////

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


// CmouseDlg �Ի���




CmouseDlg::CmouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmouseDlg::IDD, pParent)
	, m_buttons_value(FALSE)
	, m_time(_T(""))
	, m_score(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_RADIO1, m_buttons);
	DDX_Radio(pDX, IDC_RADIO1, m_buttons_value);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Text(pDX, IDC_SCORE, m_score);
}

BEGIN_MESSAGE_MAP(CmouseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CmouseDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_END, &CmouseDlg::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_RADIO1, &CmouseDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CmouseDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CmouseDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CmouseDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CmouseDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CmouseDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CmouseDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CmouseDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CmouseDlg::OnBnClickedRadio9)
END_MESSAGE_MAP()


// CmouseDlg ��Ϣ�������

BOOL CmouseDlg::OnInitDialog()
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

	//////////////////////////////////////////////////////////////////////////////////
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_buttons_value = -1;
	pbuttons_value = &m_buttons_value;
	pscore = &m_score;
	ptime = &m_time;
	UpdateData(false);
	dlg = this;
	buttons[0] = (CButton*)GetDlgItem(IDC_RADIO1);
	buttons[1] = (CButton*)GetDlgItem(IDC_RADIO2);
	buttons[2] = (CButton*)GetDlgItem(IDC_RADIO3);
	buttons[3] = (CButton*)GetDlgItem(IDC_RADIO4);
	buttons[4] = (CButton*)GetDlgItem(IDC_RADIO5);
	buttons[5] = (CButton*)GetDlgItem(IDC_RADIO6);
	buttons[6] = (CButton*)GetDlgItem(IDC_RADIO7);
	buttons[7] = (CButton*)GetDlgItem(IDC_RADIO8);
	buttons[8] = (CButton*)GetDlgItem(IDC_RADIO9);
	//////////////////////////////////////////////////////////////////////////////////

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmouseDlg::OnPaint()
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
HCURSOR CmouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmouseDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!isplaying) {
		mytime = 31;
		myscore = 0;
		m_time = _T("30");
		m_score = _T("0");
		UpdateData(false);
		m_start.SetWindowTextW(_T("����"));
		newradio();
		::SetTimer(this->m_hWnd, ID_TIMER, 1000, count);
	} else {
		::KillTimer(this->m_hWnd, ID_TIMER);
		currentradio = -1;
		m_buttons_value = -1;
		UpdateData(false);
		m_start.SetWindowTextW(_T("��ʼ"));
		WCHAR buf2[50];
		wsprintf(buf2, _T("��ĵ÷���%d"), myscore);
		::MessageBox(NULL, buf2, _T("��Ϸ����"), MB_ICONINFORMATION);
	}
	isplaying = !isplaying;
}


void CmouseDlg::OnBnClickedEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CmouseDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(0);
}


void CmouseDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(1);
}


void CmouseDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(2);
}


void CmouseDlg::OnBnClickedRadio4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(3);
}


void CmouseDlg::OnBnClickedRadio5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(4);
}


void CmouseDlg::OnBnClickedRadio6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(5);
}


void CmouseDlg::OnBnClickedRadio7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(6);
}


void CmouseDlg::OnBnClickedRadio8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(7);
}


void CmouseDlg::OnBnClickedRadio9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (currentradio != m_buttons_value)
		m_buttons_value = currentradio;
	check(8);
}
