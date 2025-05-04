//==========================
// 
// �U���̏�ԊǗ�[attackstate.h]
// Author Yuki Goto
//
//==========================
#ifndef ATTACKSTATE_H_
#define ATTACKSTATE_H_

//�O���錾
class CAttackState;
class CTrajectory;
//==============================================================================
//���N���X
//==============================================================================
class CAttackStateBase
{
public:
	//�萔
	static const int LEFT_HAND;//����̔ԍ�
	static const int RIGHT_HAND;//�E��̔ԍ�
	static const int WIDTH;//�O�Ղ̉��̕�����
	static const int VERTICAL;//�O�Ղ̏c�̕�����
	static const D3DXVECTOR3 TRAJECTORY_SIZE;//�O�Ղ̑傫��
	static const int HITFLAME;//�f��U���̓����蔻��̃t���[����

	//�����o�֐�
	CAttackStateBase();//�R���X�g���N�^
	~CAttackStateBase();//�f�X�g���N�^
	virtual void Start();//�J�n
	virtual void Update();//�X�V
	virtual void Uninit();//�I��
	void CreateTrajectory(D3DXVECTOR3 pos);//�O�Ղ̐���
	void TrajectoryPos(D3DXVECTOR3 pos);//�O�Ղ̈ʒu��ݒ�
private:

	//�����o�ϐ�
	CTrajectory* m_Trajectory;//�O�Ղ̏��
};

//==============================================================================
//�U���̏�ԃN���X
//==============================================================================
class CAttackPlayerStateBase :public CAttackStateBase
{
public:

	//�����o�֐�
	CAttackPlayerStateBase();//�R���X�g���N�^
	~CAttackPlayerStateBase();//�f�X�g���N�^
	void SetOwner(CAttackState* State);//�X�e�[�g�̏����҂�ݒ�

protected:

	//�����o�ϐ�
	CAttackState* m_OwnerState;//�X�e�[�g�̏��L��
};

//==============================================================================
//��ԊǗ��N���X
//==============================================================================
class CAttackStateMachine
{
public:

	//�����o�֐�
	CAttackStateMachine();//�R���X�g���N�^
	~CAttackStateMachine();//�f�X�g���N�^
	void ChangeState(CAttackPlayerStateBase* NewState);//��Ԃ̕ύX
	void Update();//�X�V

private:

	//�����o�ϐ�
	CAttackPlayerStateBase* m_State;//�v���C���[�̏��

};

//==============================================================================
//�f��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstAttackState :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CFirstAttackState();//�R���X�g���N�^
	~CFirstAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondAttackState :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CSecondAttackState();//�R���X�g���N�^
	~CSecondAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastAttackState :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CRastAttackState();//�R���X�g���N�^
	~CRastAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//���蕐��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstBigWeaponAttack :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CFirstBigWeaponAttack();//�R���X�g���N�^
	~CFirstBigWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondBigWeaponAttack :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CSecondBigWeaponAttack();//�R���X�g���N�^
	~CSecondBigWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastBigWeaponAttack :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CRastBigWeaponAttack();//�R���X�g���N�^
	~CRastBigWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//1��ڂ̍U��
class CFirstSmallWeaponAttack :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CFirstSmallWeaponAttack();//�R���X�g���N�^
	~CFirstSmallWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CSecondSmallWeaponAttack :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CSecondSmallWeaponAttack();//�R���X�g���N�^
	~CSecondSmallWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CRastSmallWeaponAttack :public CAttackPlayerStateBase
{
public:
	//�����o�֐�
	CRastSmallWeaponAttack();//�R���X�g���N�^
	~CRastSmallWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

#endif