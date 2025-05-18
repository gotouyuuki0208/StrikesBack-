//==========================
// 
// �{�X�퉉�o�̊Ǘ�[direction.h]
// Author Yuki Goto
//
//==========================
#ifndef _DIRECTION_H_
#define _DIRECTION_H_

//�O���錾
class CDirectionBg;
class CBoss;

//�N���X�̒�`
class CDirection
{
public:

	//�����o�֐�
	CDirection();//�R���X�g���N�^
	~CDirection();//�f�X�g���N�^
	void Update();//�X�V����
	bool GetEnd();//�I��������擾
	void GetBossInfo();//�{�X�̏����擾
private:
	//�����o�֐�
	void UpdateBg();//�w�i�X�V
	void BossEndMotion();//�{�X�̃��[�V�������I������������

	//�����o�ϐ�
	CDirectionBg* m_Bg[2];//�w�i�̏��
	CBoss* m_boss;//�{�X�̏��
	bool m_ExistenceBg;//��ʓ��ɔw�i�����邩����
	bool m_End;//���o�I������
	bool m_BossMotionEnd;//�{�X�̃��[�V�����I������
};

#endif