//==========================
// 
// �Q�[����ʂ̏���[game.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAME_H_
#define _GAME_H_

//include
#include"scene.h"
#include"edit.h"
#include"player.h"
#include"boss.h"
#include"playerhpgauge.h"
#include"bosshpgauge.h"

//�Q�[���N���X�̒�`
class CGame :public CScene
{
public:

	//�����o�֐�
	CGame();//�R���X�g���N�^
	~CGame() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
private:

	//�����o�֐�
	void DebugSelect();//�f�o�b�O�̎�ނ�I��
	void UseEdit();//�z�u�c�[���̎g�p
	void ChangeStage();//�X�e�[�W�̐؂�ւ�
	void DisplayUI();//UI�\��

	//�����o�ϐ�
	CEdit* m_Edit;//�I�u�W�F�N�g�z�u�N���X�̏��
	CPlayer* m_player;//�v���C���[�̏��
	CBoss* m_Boss;//�{�X�̏��
	CPlayerHPGauge* m_PlalyerHPGauge;//�v���C���[��HP�Q�[�W�̏��
	CBossHPGauge* m_BossHPGauge;//�{�X��HP�Q�[�W�̏��
	int m_playerlife;
};

#endif 