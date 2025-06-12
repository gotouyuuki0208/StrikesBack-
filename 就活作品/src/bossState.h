//==========================
// 
// �{�X�̏�ԊǗ�[bossState.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSSSTATE_H_
#define _BOSSSTATE_H_

//include
#include"characterstate.h"

//�O���錾
class CBoss;
class CBossAttackStateMachine;
class CAttackBossStateBase;
//==============================================================================
//�G�̏�ԃN���X
//==============================================================================
class CBossStateBase :public CStateBase
{
public:
	//�����o�֐�
	CBossStateBase();//�R���X�g���N�^
	~CBossStateBase();//�f�X�g���N�^
	void SetOwner(CBoss* boss);//�X�e�[�g�̏����҂�ݒ�
	CBoss* GetOwner();//�X�e�[�g�̏��L�҂��擾
protected:

	//�����o�ϐ�
	CBoss* m_pBoss;//�G�̏��
};

//==============================================================================
//���o��ԃN���X
//==============================================================================
class CBossDirectionState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossDirectionState();//�R���X�g���N�^
	~CBossDirectionState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
	int m_count;
};

//==============================================================================
//�ҋ@��ԃN���X
//==============================================================================
class CBossNeutralState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossNeutralState();//�R���X�g���N�^
	~CBossNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//���蕐�펝���ҋ@��ԃN���X
//==============================================================================
class CBossBigWeaponNeutralState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossBigWeaponNeutralState();//�R���X�g���N�^
	~CBossBigWeaponNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐�펝���ҋ@��ԃN���X
//==============================================================================
class CBossSmallWeaponNeutralState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossSmallWeaponNeutralState();//�R���X�g���N�^
	~CBossSmallWeaponNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//���蕐�펝���ړ���ԃN���X
//==============================================================================
class CBossWeaponMoveState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossWeaponMoveState();//�R���X�g���N�^
	~CBossWeaponMoveState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�ړ���ԃN���X
//==============================================================================
class CBossMoveState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossMoveState();//�R���X�g���N�^
	~CBossMoveState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�K�[�h��ԃN���X
//==============================================================================
class CBossGuardState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossGuardState();//�R���X�g���N�^
	~CBossGuardState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐�펝���K�[�h��ԃN���X
//==============================================================================
class CBossSmallWeaponGuardState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossSmallWeaponGuardState();//�R���X�g���N�^
	~CBossSmallWeaponGuardState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�_���[�W��ԃN���X
//==============================================================================
class CBossDamageState :public CBossStateBase
{
public:
	//�萔
	static const int DAMEGE_FLAME;//�_���[�W��Ԃ��I������܂ł̃t���[����

	//�����o�֐�
	CBossDamageState();//�R���X�g���N�^
	~CBossDamageState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_DmageCount;//�_���[�W���󂯂Ă���̃t���[����
};

//==============================================================================
//�_�b�V����ԃN���X
//==============================================================================
class CBossDushState :public CBossStateBase
{
public:
	//�����o�֐�
	CBossDushState();//�R���X�g���N�^
	~CBossDushState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//������я�ԃN���X
//==============================================================================
class CBossDamageBrrowState :public CBossStateBase
{
public:
	//�萔
	static const int BRROW_FLAME;//�_���[�W��Ԃ��I������܂ł̃t���[����

	//�����o�֐�
	CBossDamageBrrowState();//�R���X�g���N�^
	~CBossDamageBrrowState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_DmageCount;//�_���[�W���󂯂Ă���̃t���[����
};

//==============================================================================
//�U����ԃN���X
//==============================================================================
class CBossAttackState :public CBossStateBase
{
public:

	//�����o�֐�
	CBossAttackState();//�R���X�g���N�^
	~CBossAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
	void ChangeCombo();//�R���{������擾
	void ResetInfo();//����������
	void ChangeAttack(CAttackBossStateBase* State);//�U����ύX
	int GetFrame();//�U���t���[�������擾
	bool GetCombo();//�R���{������擾
private:

	//�����o�ϐ�
	int m_FlameCount;//�U���̃t���[����
	bool m_Combo;//�R���{����
	CBossAttackStateMachine* m_AttackStateMachine;//�U���̏�ԊǗ�
};

#endif