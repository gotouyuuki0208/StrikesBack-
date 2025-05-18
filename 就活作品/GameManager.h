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

//�O���錾
class CDirection;

//�N���X�̒�`
class CGameManager
{
public:

	//�Q�[���̏�
	enum class GAME
	{
		NONE = 0,//�Q�[����
		CLEAR,//�Q�[���N���A
		OVER,//�Q�[���I�[�o�[
	};

	//�����o�֐�
	CGameManager();//�R���X�g���N�^
	~CGameManager();//�f�X�g���N�^
	void Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void SetGame(GAME game);//�Q�[���̃N���A����ݒ�
	GAME GetGame();//�Q�[���̃N���A�����擾
	void ChangePlayGame(bool play);//�L�����N�^�[����̔����ύX
	bool GetPlayGame();//�V�ׂ��Ԃ��擾
	void SetDirection();//���o���ɕύX
private:

	//�����o�֐�
	void SetTutorial();//�`���[�g���A���̐ݒ�
	void StartTutorial();//�Q�[���J�n���̑�������\��
	void EndTutorial();//��������\���̏I��
	void GetPlayerInfo();//�v���C���[�̏����擾
	void SetCamera();//�J�����̐ݒ�
	void StartBossBattle();//�{�X��J�n���̉��o

	//�����o�ϐ�
	CPlayer* m_player;//�v���C���[�̏��
	CDirection* m_direction;//���o�̏��
	GAME m_GameClear;//�Q�[���̃N���A���
	bool m_Direction;//���o��������
	bool m_PlayGame;//�Q�[����V�ׂ邩����(false:�V�ׂȂ� true:�V�ׂ�)
	bool m_GameStartTutorial;//�Q�[���̊J�n���̑��������\������������
	int m_count;//�t���[�����J�E���g
};

#endif