//==========================
// 
// �X�e�[�W�Ǘ�[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

#include"darkbg.h"
#include<list>
#include"objectgame.h"

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
	void StageReset();//
	void Load();//�X�e�[�W�̃I�u�W�F�N�g����
	void DeleteAll();//�S�ẴI�u�W�F�N�g���폜
	void DeleteObj(CObjectgame& obj);//�I�u�W�F�N�g���폜
private:

	//�����o�֐�
	void FildLoad();//�t�B�[���h�̏���ǂݍ���
	void EnemyLoad();//�G�̔z�u����ǂݍ���
	void BuildingLoad();//�����̏���ǂݍ���
	void WeaponLoad();//����̏���ǂݍ���
	void ItemLoad();//�A�C�e���̏���ǂݍ���

	//�����o�ϐ�
	STAGE m_Stage;//�X�e�[�W�̔ԍ�
	bool m_Change;//�X�e�[�W���؂�ւ����������
	CDarkBg* m_DarkBg;
	int m_Rast;
	list<CObjectgame*> m_Obj;//�I�u�W�F�N�g���X�g
	list<CObjectgame*>::iterator m_ObjIte;//�I�u�W�F�N�g���X�g�C�e���[�^�[
	
};

#endif