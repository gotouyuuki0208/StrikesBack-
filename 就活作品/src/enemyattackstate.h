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
class CEnemyAttackStateBase
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
	CEnemyAttackStateBase();//�R���X�g���N�^
	~CEnemyAttackStateBase();//�f�X�g���N�^
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
class CAttackEnemyState :public CEnemyAttackStateBase
{
public:

	//�����o�֐�
	CAttackEnemyState();//�R���X�g���N�^
	~CAttackEnemyState();//�f�X�g���N�^
	void SetOwner(CEnemyAttackState* State);//�X�e�[�g�̏����҂�ݒ�

protected:

	//�����o�ϐ�
	CEnemyAttackState* m_OwnerState;//�X�e�[�g�̏��L��
};

//==============================================================================
//��ԊǗ��N���X
//==============================================================================
class CEnemyAttackStateMachine
{
public:

	//�����o�֐�
	CEnemyAttackStateMachine();//�R���X�g���N�^
	~CEnemyAttackStateMachine();//�f�X�g���N�^
	void ChangeState(CEnemyAttackStateBase* NewState);//��Ԃ̕ύX
	void Update();//�X�V

private:

	//�����o�ϐ�
	CEnemyAttackStateBase* m_State;//�v���C���[�̏��

};

//==============================================================================
//�f��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstEnemyAttackState :public CAttackEnemyState
{
public:
	//�����o�֐�
	CFirstEnemyAttackState();//�R���X�g���N�^
	~CFirstEnemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondEnemyAttackState :public CAttackEnemyState
{
public:
	//�����o�֐�
	CSecondEnemyAttackState();//�R���X�g���N�^
	~CSecondEnemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastEnemyAttackState :public CAttackEnemyState
{
public:
	//�����o�֐�
	CRastEnemyAttackState();//�R���X�g���N�^
	~CRastEnemyAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstSmallWeaponEnemyAttack :public CAttackEnemyState
{
public:
	//�����o�֐�
	CFirstSmallWeaponEnemyAttack();//�R���X�g���N�^
	~CFirstSmallWeaponEnemyAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondSmallWeaponEnemyAttack :public CAttackEnemyState
{
public:
	//�����o�֐�
	CSecondSmallWeaponEnemyAttack();//�R���X�g���N�^
	~CSecondSmallWeaponEnemyAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastSmallWeaponEnemyAttack :public CAttackEnemyState
{
public:
	//�����o�֐�
	CRastSmallWeaponEnemyAttack();//�R���X�g���N�^
	~CRastSmallWeaponEnemyAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

#endif