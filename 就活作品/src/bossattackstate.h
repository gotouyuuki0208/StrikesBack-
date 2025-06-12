//==========================
// 
// �{�X�U���̏�ԊǗ�[bossattackstate.h]
// Author Yuki Goto
//
//==========================
#ifndef BOSSATTACKSTATE_H_
#define BOSSATTACKSTATE_H_

//�O���錾
class CBossAttackState;
//==============================================================================
//���N���X
//==============================================================================
class CBossAttackStateBase
{
public:
	//�萔
	static const int LEFT_HAND;//����̔ԍ�
	static const int RIGHT_HAND;//�E��̔ԍ�
	static const int HITFLAME;//�f��U���̓����蔻��̃t���[����

	//�����o�֐�
	CBossAttackStateBase();//�R���X�g���N�^
	~CBossAttackStateBase();//�f�X�g���N�^
	virtual void Start();//�J�n
	virtual void Update();//�X�V
	virtual void Uninit();//�I��
};

//==============================================================================
//�U���̏�ԃN���X
//==============================================================================
class CAttackBossStateBase :public CBossAttackStateBase
{
public:

	//�����o�֐�
	CAttackBossStateBase();//�R���X�g���N�^
	~CAttackBossStateBase();//�f�X�g���N�^
	void SetOwner(CBossAttackState* State);//�X�e�[�g�̏����҂�ݒ�

protected:

	//�����o�ϐ�
	CBossAttackState* m_OwnerState;//�X�e�[�g�̏��L��
};

//==============================================================================
//��ԊǗ��N���X
//==============================================================================
class CBossAttackStateMachine
{
public:

	//�����o�֐�
	CBossAttackStateMachine();//�R���X�g���N�^
	~CBossAttackStateMachine();//�f�X�g���N�^
	void ChangeState(CAttackBossStateBase* NewState);//��Ԃ̕ύX
	void Update();//�X�V

private:

	//�����o�ϐ�
	CAttackBossStateBase* m_State;//�v���C���[�̏��

};

//==============================================================================
//�f��U���N���X
//==============================================================================

//1��ڂ̍U��
class CBossFirstAttackState :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossFirstAttackState();//�R���X�g���N�^
	~CBossFirstAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CBossSecondAttackState :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossSecondAttackState();//�R���X�g���N�^
	~CBossSecondAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CBossRastAttackState :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossRastAttackState();//�R���X�g���N�^
	~CBossRastAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//���蕐��U���N���X
//==============================================================================

//1��ڂ̍U��
class CBossFirstBigWeaponAttack :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossFirstBigWeaponAttack();//�R���X�g���N�^
	~CBossFirstBigWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CBossSecondBigWeaponAttack :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossSecondBigWeaponAttack();//�R���X�g���N�^
	~CBossSecondBigWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CBossRastBigWeaponAttack :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossRastBigWeaponAttack();//�R���X�g���N�^
	~CBossRastBigWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//1��ڂ̍U��
class CBossFirstSmallWeaponAttack :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossFirstSmallWeaponAttack();//�R���X�g���N�^
	~CBossFirstSmallWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//2��ڂ̍U��
class CBossSecondSmallWeaponAttack :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossSecondSmallWeaponAttack();//�R���X�g���N�^
	~CBossSecondSmallWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//3��ڂ̍U��
class CBossRastSmallWeaponAttack :public CAttackBossStateBase
{
public:
	//�����o�֐�
	CBossRastSmallWeaponAttack();//�R���X�g���N�^
	~CBossRastSmallWeaponAttack();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

#endif