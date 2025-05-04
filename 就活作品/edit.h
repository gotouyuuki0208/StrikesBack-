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
	void Load(int Stage);//�z�u����ǂݍ���
	void Save(int Stage);//�z�u���������o��
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
	void ChangeObject();//�I�u�W�F�N�g��ύX
	CObjectgame* SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�
	void ChangeType();//�I�u�W�F�N�g�̎�ނ�ݒ�
	void Rotate();//������ς���
	void KeepInfo();//����ۑ�
	void SwitchEditMode();//�ҏW���[�h�̐؂�ւ�
	void StageChange();//�X�e�[�W��ύX

	void EnemyLoad(int Stage);//�G�̔z�u����ǂݍ���
	void EnemySave(int Stage);//�G�̔z�u���������o��
	void BuildingLoad(int Stage);//�����̔z�u����ǂݍ���
	void BuildingSave(int Stage);//�����̔z�u���������o��
	void WeaponLoad(int Stage);//����̔z�u����ǂݍ���
	void WeaponSave(int Stage);//����̔z�u���������o��
	void ItemLoad(int Stage);//�A�C�e���̔z�u����ǂݍ���
	void ItemSave(int Stage);//�A�C�e���̔z�u���������o��
	void FildLoad(int Stage);//�t�B�[���h�̔z�u����ǂݍ���
	void FildSave(int Stage);//�t�B�[���h�̔z�u���������o��

	//�����o�ϐ�
	list<CObjectgame*> m_Object;//�z�u�I�u�W�F�N�g���X�g
	list<CObjectgame*>::iterator m_Objectite;//�z�u�I�u�W�F�N�g���X�g�C�e���[�^�[
	Keep m_EditObjectKeep;//�ҏW���̃I�u�W�F�N�g��ۑ�
	CObjectgame* m_EditObject;//���ݕҏW���Ă���I�u�W�F�N�g
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_scale;//�X�P�[��
	D3DXVECTOR3 m_rot;//����
	bool m_EditMode;//�ҏW���[�h(false:�V�K�I�u�W�F�N�g true:�z�u�ς݃I�u�W�F�N�g)
	int m_ObjectType;//�I�u�W�F�N�g�̎��
	bool m_MoveDirection;//�ړ�����(false:Z�ړ� true:Y�ړ�)
	bool m_SwitchInput;//���͕��@(false:Press true:Trigger)
	bool m_move;//�ړ��̕ҏW(false:�ʒu true:����)
	bool m_Camera;//�J�����̈ʒu
	bool m_ChangeScale;//�X�P�[���ύX
};
#endif