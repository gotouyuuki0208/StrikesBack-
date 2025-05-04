//==========================
// 
// �G�̍U���̏�ԊǗ�[enemyattackstate.h]
// Author Yuki Goto
//
//==========================
#ifndef ENEMYATTACKSTATE_H_
#define ENEMYATTACKSTATE_H_

//include
#include "enemystate.h"

//�O���錾
class CEnemyAttackState;
//class CTrajectory;
//==============================================================================
//���N���X
//==============================================================================
class CEenemyAttackStateBase
{
public:
	//�萔
	static const int LEFT_HAND;//����̔ԍ�
	static const int RIGHT_HAND;//�E��̔ԍ�
	static const int HITFLAME;//�f��U���̓����蔻��̃t���[����
	//static const int WIDTH;//�O�Ղ̉��̕�����
	//static const int VERTICAL;//�O�Ղ̏c�̕�����
	//static const D3DXVECTOR3 TRAJECTORY_SIZE;//�O�Ղ̑傫��

	//�����o�֐�
	CEenemyAttackStateBase();//�R���X�g���N�^
	~CEenemyAttackStateBase();//�f�X�g���N�^
	virtual void Start();//�J�n
	virtual void Update();//�X�V
	virtual void Uninit();//�I��
	//void CreateTrajectory(D3DXVECTOR3 pos);//�O�Ղ̐���
	//void TrajectoryPos(D3DXVECTOR3 pos);//�O�Ղ̈ʒu��ݒ�
private:

	//�����o�ϐ�
	//CTrajectory* m_Trajectory;//�O�Ղ̏��
};

//==============================================================================
//�U���̏�ԃN���X
//==============================================================================
class CAttackEenemyState :public CEenemyAttackStateBase
{
public:

	//�����o�֐�
	CAttackEenemyState();//�R���X�g���N�^
	~CAttackEenemyState();//�f�X�g���N�^
	void SetOwner(CEnemyAttackState* State);//�X�e�[�g�̏����҂�ݒ�

protected:

	//�����o�ϐ�
	CEnemyAttackState* m_OwnerState;//�X�e�[�g�̏��L��
};

//==============================================================================
//��ԊǗ��N���X
//==============================================================================
class CEenemyAttackStateMachine
{
public:

	//�����o�֐�
	CEenemyAttackStateMachine();//�R���X�g���N�^
	~CEenemyAttackStateMachine();//�f�X�g���N�^
	void ChangeState(CEenemyAttackStateBase* NewState);//��Ԃ̕ύX
	void Update();//�X�V

private:

	//�����o�ϐ�
	CEenemyAttackStateBase* m_State;//�v���C���[�̏��

};

//==============================================================================
//�f��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstEenemyAttackState :public CAttackEenemyState
{
public:
	//�����o�֐�
	CFirstEenemyAttackState();//�R���X�g���N�^
	~CFirstEenemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondEenemyAttackState :public CAttackEenemyState
{
public:
	//�����o�֐�
	CSecondEenemyAttackState();//�R���X�g���N�^
	~CSecondEenemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastEenemyAttackState :public CAttackEenemyState
{
public:
	//�����o�֐�
	CRastEenemyAttackState();//�R���X�g���N�^
	~CRastEenemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstSmallWeaponEenemyAttack :public CAttackEenemyState
{
public:
	//�����o�֐�
	CFirstSmallWeaponEenemyAttack();//�R���X�g���N�^
	~CFirstSmallWeaponEenemyAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondSmallWeaponEenemyAttack :public CAttackEenemyState
{
public:
	//�����o�֐�
	CSecondSmallWeaponEenemyAttack();//�R���X�g���N�^
	~CSecondSmallWeaponEenemyAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastSmallWeaponEenemyAttack :public CAttackEenemyState
{
public:
	//�����o�֐�
	CRastSmallWeaponEenemyAttack();//�R���X�g���N�^
	~CRastSmallWeaponEenemyAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

#endif