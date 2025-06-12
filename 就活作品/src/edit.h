//==========================
// 
// �I�u�W�F�N�g�z�u[edit.h]
// Author Yuki Goto
//
//==========================
#ifndef _EDIT_H_
#define _EDIT_H_

//include
#include"objectgame.h"
#include <list>

//�I�u�W�F�N�g�z�u�N���X�̒�`
class CEdit
{
public:
	
	//�萔
	static const float MOVE;//�ړ���
	static const float SCALE;//�X�P�[��

	//�����o�֐�
	CEdit();//�R���X�g���N�^
	~CEdit();//�f�X�g���N�^
	HRESULT Init();//�����ݒ�
	void Update();//�X�V����
	void Uninit();//�I������
	void Load();//�z�u����ǂݍ���
	void Save();//�z�u���������o��
	void DeleteAll();//���X�g�̑S�ẴI�u�W�F�N�g���폜
private:

	//�ۑ�������
	struct Keep
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rot;
		int ObjectType;
	};

	//�����o�֐�
	void Move();//�ړ�
	void Scale();//�X�P�[���ύX
	void Rotate();//������ς���
	void Content();//�I�u�W�F�N�g��z�u
	
	CObjectgame* SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�
	void ChangeType();//�I�u�W�F�N�g�̎�ނ�ݒ�
	void KeepInfo();//����ۑ�
	void SwitchEditMode();//�ҏW���[�h�̐؂�ւ�
	void StageChange();//�X�e�[�W��ύX

	void CameraFollow();//�J�������Ǐ]���邩�ݒ�
	void CameraPos();//�J�����̈ʒu

	void CreateImGuiWindow();//ImGui�̃E�B���h�E�𐶐�
	void ObjectImGui();//�I�u�W�F�N�g�Ɋւ��鑀��
	void CameraImGui();//�J�����Ɋւ��鑀��

	void JsonFildSave();
	void JsonEnemySave();
	void JsonWeaponSave();
	void JsonItemSave();
	void JsonBuildingSave();

	void JsonEnemyLoad();
	void JsonFildLoad();
	void JsonWeaponLoad();
	void JsonItemLoad();
	void JsonBuildingLoad();

	//�����o�ϐ�
	list<CObjectgame*> m_Object;//�z�u�I�u�W�F�N�g���X�g
	list<CObjectgame*>::iterator m_Objectite;//�z�u�I�u�W�F�N�g���X�g�C�e���[�^�[
	Keep m_EditObjectKeep;//�ҏW���̃I�u�W�F�N�g��ۑ�
	CObjectgame* m_EditObject;//���ݕҏW���Ă���I�u�W�F�N�g
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_camerapos;//�ʒu
	D3DXVECTOR3 m_scale;//�X�P�[��
	D3DXVECTOR3 m_rot;//����
	bool m_EditMode;//�ҏW���[�h(false:�V�K�I�u�W�F�N�g true:�z�u�ς݃I�u�W�F�N�g)
	bool m_MoveDirection;//�ړ�����(false:Z�ړ� true:Y�ړ�)
	bool m_SwitchInput;//���͕��@(false:Press true:Trigger)
	bool m_move;//�ړ��̕ҏW(false:�ʒu true:����)
	bool m_Camera;//�J�����̈ʒu
	bool m_ChangeScale;//�X�P�[���ύX
	int m_ObjectType;//�I�u�W�F�N�g�̎��
	float m_ChangePosNum;//�ړ�����ʒu�̐��l
	float m_ChangeScaleNum;//�ύX����X�P�[���̐��l
	int m_wave;
};
#endif