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
class CHitEnemy;

//�N���X�̒�`
class CGameManager
{
public:

	//�Q�[���̏�
	enum class GAME
	{
		NONE = 0,	//�Q�[����
		CLEAR,		//�Q�[���N���A
		OVER,		//�Q�[���I�[�o�[
	};

	//�����o�֐�
	CGameManager();					//�R���X�g���N�^
	~CGameManager();				//�f�X�g���N�^
	void Init();					//����������
	void Uninit();					//�I������
	void Update();					//�X�V����
	void SetGame(GAME game);		//�Q�[���̃N���A����ݒ�
	GAME GetGame();					//�Q�[���̃N���A�����擾
	void ChangePlayGame(bool play);	//�L�����N�^�[����̔����ύX
	bool GetPlayGame();				//�V�ׂ��Ԃ��擾
	void SetDirection();			//���o���ɕύX
	bool GetDirection();			//���o�����擾
	int GetWave();					//���݂̃E�F�[�u���擾
	void AddWave();					//�E�F�[�u�𑝂₷
	void AddActiveEnemy();			//�s�����Ă�G�̐��𑝂₷
	void SubActiveEnemy();			//�s�����Ă�G�̐������炷
	int GetActiveEnemy();				//�s�����̓G�̐����擾
private:

	//�����o�֐�
	void SetTutorial();		//�`���[�g���A���̐ݒ�
	void StartTutorial();	//�Q�[���J�n���̑�������\��
	void EndTutorial();		//��������\���̏I��
	void GetPlayerInfo();	//�v���C���[�̏����擾
	void SetCamera();		//�J�����̐ݒ�
	void StartBossBattle();	//�{�X��J�n���̉��o
	void CmeraLookOn();		//�J�����̃��b�N�I��
	void WaveUpdate();		//�E�F�[�u�̍X�V
	void JudgeEnemyBeing(); //�G�����݂��Ă邩����

	//�����o�ϐ�
	CPlayer* m_player;			//�v���C���[�̏��
	CDirection* m_direction;	//���o�̏��
	CHitEnemy* Enemy;

	GAME m_GameClear;			//�Q�[���̃N���A���
	bool m_Direction;			//���o��������
	bool m_PlayGame;			//�Q�[����V�ׂ邩����(false:�V�ׂȂ� true:�V�ׂ�)
	bool m_GameStartTutorial;	//�Q�[���̊J�n���̑��������\������������
	int m_count;				//�t���[�����J�E���g
	bool m_CameraLookOn;		//�J�������G�����b�N�I�����邩
	int m_NowWave;				//���݂̃E�F�[�u
	int m_ActiveEnemy;			//���ݍs�����Ă�G�̐�
	bool m_EnemyBeing;			//�G�����݂��Ă�
};

#endif