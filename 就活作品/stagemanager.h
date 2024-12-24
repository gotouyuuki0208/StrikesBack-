//==========================
// 
// �X�e�[�W�Ǘ�[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

#include"darkbg.h"

//�N���X�̒�`
class CStageManager
{
public:
	enum class STAGE
	{
		STAGE_FIRST,//�X�e�[�W1
		STAGE_SECOND,//�X�e�[�W2
		STAGE_BOSS,//�{�X�X�e�[�W
	};

	//�����o�֐�
	CStageManager();//�R���X�g���N�^
	~CStageManager();//�f�X�g���N�^
	void SetStage();//�X�e�[�W��ݒ�
	STAGE GetStage();//�X�e�[�W���擾
	bool GetChange();//�؂�ւ�蔻����擾
	void ChangeReset();//�؂�ւ�蔻������Z�b�g
	void Uninit();//�I������
	bool ChangeObject();//�I�u�W�F�N�g�ύX�^�C�~���O
	void StageReset();
private:

	//�����o�ϐ�
	STAGE m_Stage;//�X�e�[�W�̔ԍ�
	bool m_Change;//�X�e�[�W���؂�ւ����������
	CDarkBg* m_DarkBg;
	int m_Rast;
};

#endif