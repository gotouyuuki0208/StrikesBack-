//==========================
// 
// �Q�[���S�̊Ǘ�[GameManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//include
#include"player.h"
#include"boss.h"

//�N���X�̒�`
class CGameManager
{
public:

	enum class GAME
	{
		NONE = 0,
		CLEAR,
		OVER,
	};
	

	//�����o�֐�
	CGameManager();//�R���X�g���N�^
	~CGameManager();//�f�X�g���N�^
	void a();
	void SetGame(GAME game);//�Q�[���̃N���A����ݒ�
	GAME GetGame();//�Q�[���̃N���A�����擾
	void Init();//����������
	void Uninit();//�I������
	void SetDirection();//���o�̐ݒ�
	bool GetDirection();//���o�����擾
	void GetBossInfo();//�{�X�̏����擾
	bool GetChange();//�؂�ւ�蔻����擾
	void SetChange();//�؂�ւ�蔻������Z�b�g
private:

	//�����o�֐�
	void GetPlayerInfo();//�v���C���[�̏����擾
	void SetCamera();//�J�������Ǐ]����Ώۂ�ݒ�
	void StartBossBattle();//�{�X��J�n���̉��o

	//�����o�ϐ�
	GAME GameClear;//�Q�[���̃N���A���
	CPlayer* m_player;//�v���C���[�̏��
	CBoss* m_boss;//�{�X�̏��
	bool m_Direction;//���o��������
	bool m_StageChamge;//�X�e�[�W���؂�ւ����������
	int m_count;
};

#endif