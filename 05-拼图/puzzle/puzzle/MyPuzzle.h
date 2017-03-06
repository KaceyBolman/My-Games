
class CpuzzleDlg;

class MyPuzzle {
	public:
		int puzzles[4][4];		//�����Թ�����
		int bx, by;					//�հ�����
		int dx, dy;					//�ѻ�ͼ����
		bool israndom;		//����ƶ��ж�
		CStatic *pics[16];		//�ؼ�ָ��
		CpuzzleDlg *dlg;		//�Ի���ָ��

		MyPuzzle();
		void SetDlg(CpuzzleDlg *wnddlg);
		void RandomMove();
		int GetBlankDirection(int x, int y);
		void MovePic(int x, int y);
		bool IsSamePoint(int x, int y);
		bool IsWin();
		void DrawFrame(int x, int y);
		void EraseFrame();
		void EraseBlank();
};


