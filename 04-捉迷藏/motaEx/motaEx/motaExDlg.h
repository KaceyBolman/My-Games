// motaExDlg.h : ͷ�ļ�
//
#pragma once
#include "MyGame.h"
#include "afxwin.h"

// CmotaExDlg �Ի���
class CmotaExDlg : public CDialogEx
{
// ����
public:
	CmotaExDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MOTAEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	MyGame mygame;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_solider;
	CStatic m_knight;
};
