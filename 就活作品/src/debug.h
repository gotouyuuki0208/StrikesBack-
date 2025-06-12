//==========================
// 
// �f�o�b�O���[debug.h]
// Author Yuki Goto
//
//==========================
#ifndef _DEBUG_H_
#define _DEBUG_H_

//�N���X�̒�`
class CDebug
{
public:
	//�����o�֐�
	CDebug();//�R���X�g���N�^
	~CDebug();//�f�X�g���N�^
	void Reset();//�f�o�b�O�������Z�b�g
	bool GetPlayerTest();//�v���C���[�̃e�X�g
	void StartPlayerTest();//�v���C���[�̃e�X�g�J�n
	void FinishPlayerTest();//�v���C���[�̃e�X�g�I��
	bool GetBossTest();//�{�X�̃e�X�g
	void StartBossTest();//�{�X�̃e�X�g�J�n
	void FinishBossTest();//�{�X�̃e�X�g�I��
	bool GetBattleTest();//�퓬�̃e�X�g
	void StartBattleTest();//�퓬�̃e�X�g�J�n
	void FinishBattleTest();//�퓬�̃e�X�g�I��

	bool GetEdit();//�z�u�c�[��
	void StartEdit();//�z�u�c�[���̎g�p�J�n
	void FinishEdit();//�z�u�c�[���̎g�p�I��
private:
	//�����o�ϐ�
	bool m_TestPlayer;//�v���C���[�̃e�X�g
	bool m_TestBoss;//�{�X�̃e�X�g
	bool m_TestBattle;//�퓬�̃f�o�b�O
	bool m_UseEdit;//�z�u�c�[���g�p����
};
#endif