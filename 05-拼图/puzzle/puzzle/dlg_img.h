#pragma once


// dlg_img �Ի���

class dlg_img : public CDialogEx
{
	DECLARE_DYNAMIC(dlg_img)

public:
	dlg_img(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~dlg_img();

// �Ի�������
	enum { IDD = IDD_DIALOG_IMG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
