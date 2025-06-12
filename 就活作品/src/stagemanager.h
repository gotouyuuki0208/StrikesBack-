//==========================
// 
// �X�e�[�W�Ǘ�[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

//include
#include<list>
#include"objectgame.h"

//�O���錾
class CPlayer;
class CDarkBg;

//�N���X�̒�`
class CStageManager
{
public:
	enum class STAGE
	{
		STAGE_NONE = 0,
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
	void StageReset();//�X�e�[�W�����Z�b�g
	void Load();//�X�e�[�W�̃I�u�W�F�N�g����
	void DeleteAll();//�S�ẴI�u�W�F�N�g���폜
	void DeleteObj(CObjectgame& obj);//�I�u�W�F�N�g���폜
	void ChangeStage();//�X�e�[�W�̐؂�ւ�
private:

	//�����o�֐�
	void JsonBuildingLoad();
	void JsonEnemyLoad();
	void JsonFildLoad();
	void JsonWeaponLoad();
	void JsonItemLoad();

	//�����o�ϐ�
	list<CObjectgame*> m_Obj;//�I�u�W�F�N�g���X�g
	list<CObjectgame*>::iterator m_ObjIte;//�I�u�W�F�N�g���X�g�C�e���[�^�[
	CDarkBg* m_DarkBg;//�Ó]�̂��߂̍��|���S��
	CPlayer* m_player;//�v���C���[�̏��
	STAGE m_Stage;//�X�e�[�W�̔ԍ�
	bool m_Change;//�X�e�[�W���؂�ւ����������
	int m_Rast;//�ŏI�X�e�[�W�̔ԍ�
};

#endif