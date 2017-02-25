#pragma once

class Solider {
	public:
		CStatic *m_cs_solider;	//ͼƬ�ؼ�ָ��
		HBITMAP hbs[16];	//����ͼƬ
		HANDLE hthreads[4];	//���Ŷ����߳�
		bool runnings[4];		//���Ŷ����̼߳�¼��־
		int directions;	//��Ӧkeyup��Ϣ�����÷���ͼƬ����ͣ���Ŷ����߳�

		Solider();
		void SetCStatic(CStatic *m_solider);
		void SetSoliderDirection(int direction);		//�̶����ŷ��򶯻�
		void PlaySoliderDirection(int direction);	//���ò��ŷ��򶯻�
};