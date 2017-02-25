#pragma once

#include "Solider.h"
#include "Knight.h"

class CmotaExDlg;

class MyGame {
	private:
		int caughtnum;
		int dlgwidth;  	//���ڴ�С
		int dlgheight;
		CRect rects; 	//�ؼ�λ��
		CRect rectk; 
		CRect rectdlg; 
		CmotaExDlg *dlg;	//����ָ��

	public:
		Solider solider;
		Knight knight;
		MyGame();
		void SetDlg(CmotaExDlg *dlg);
		void SoliderUp();		//���Ŷ���
		void SoliderDown();
		void SoliderLeft();
		void SoliderRight();
		void SoliderStop();	//ֹͣ���Ŷ���

		void KnightUp();
		void KnightDown();
		void KnightLeft();
		void KnightRight();

		bool IsCollision();
		void CheckCollision();
		void SoliderIsCaught();
		void MoveKnight();
		void SetSoliderPos(int x, int y);
		void GetSoliderPos();
		void GetKnightPos();
};