//==========================
// 
// �v���C���[�̏�ԊǗ�[playerstate.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERSTATE_H_
#define _PLAYERSTATE_H_

//include
#include"characterstate.h"

//�O���錾
class CPlayer;
class CAttackStateMachine;
class CAttackPlayerStateBase;

//==============================================================================
//�v���C���[�̏�ԃN���X
//==============================================================================
class CPlayerStateBase :public CStateBase
{
public:
	//�����o�֐�
	CPlayerStateBase();//�R���X�g���N�^
	~CPlayerStateBase();//�f�X�g���N�^
	void SetOwner(CPlayer* player);//�X�e�[�g�̏����҂�ݒ�
	CPlayer* GetOwner();//�X�e�[�g�̏��L�҂��擾
protected:

	//�����o�ϐ�
	CPlayer* m_pPlayer;//�v���C���[�̏��
};

//==============================================================================
//�ҋ@��ԃN���X
//==============================================================================
class CNeutralState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CNeutralState();//�R���X�g���N�^
	~CNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//���蕐�펝���ҋ@��ԃN���X
//==============================================================================
class CBigWeaponNeutralState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CBigWeaponNeutralState();//�R���X�g���N�^
	~CBigWeaponNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐�펝���ҋ@��ԃN���X
//==============================================================================
class CSmallWeaponNeutralState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CSmallWeaponNeutralState();//�R���X�g���N�^
	~CSmallWeaponNeutralState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//���蕐�펝���ړ���ԃN���X
//==============================================================================
class CBigWeaponMoveState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CBigWeaponMoveState();//�R���X�g���N�^
	~CBigWeaponMoveState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�ړ���ԃN���X
//==============================================================================
class CMoveState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CMoveState();//�R���X�g���N�^
	~CMoveState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�_�b�V����ԃN���X
//==============================================================================
class CDushState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CDushState();//�R���X�g���N�^
	~CDushState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�K�[�h��ԃN���X
//==============================================================================
class CGuardState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CGuardState();//�R���X�g���N�^
	~CGuardState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�Ў蕐�펝���K�[�h��ԃN���X
//==============================================================================
class CSmallWeaponGuardState :public CPlayerStateBase
{
public:
	//�����o�֐�
	CSmallWeaponGuardState();//�R���X�g���N�^
	~CSmallWeaponGuardState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�U����ԃN���X
//==============================================================================
class CAttackState :public CPlayerStateBase
{
public:

	//�萔
	static const int INPUT_START_FLAME;//���͎�t�J�n�t���[����
	static const int INPUT_FINISH_FLAME;//���͎�t�I���t���[����
	static const int RESET_FLAME;//�R���{�̏�񃊃Z�b�g�t���[����
	
	//�����o�֐�
	CAttackState();//�R���X�g���N�^
	~CAttackState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
	bool GetCombo();//�R���{������擾
	void ResetInfo();//����������
	void ChangeAttack(CAttackPlayerStateBase* State);//�U����ύX
	int GetFrame();//�U���t���[�������擾
private:

	//�����o�ϐ�
	int m_FlameCount;//�U���̃t���[����
	bool m_Combo;//�R���{����
	CAttackStateMachine* m_AttackStateMachine;//�U���̏�ԊǗ�
};

//==============================================================================
//�_���[�W��ԃN���X
//==============================================================================
class CDamageState :public CPlayerStateBase
{
public:
	//�萔
	static const int DAMEGE_FLAME;//�_���[�W��Ԃ��I������܂ł̃t���[����

	//�����o�֐�
	CDamageState();//�R���X�g���N�^
	~CDamageState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_DmageCount;//�_���[�W���󂯂Ă���̃t���[����
};

//==============================================================================
//������я�ԃN���X
//==============================================================================
class CDamageBrrowState :public CPlayerStateBase
{
public:
	//�萔
	static const int BRROW_FLAME;//�_���[�W��Ԃ��I������܂ł̃t���[����

	//�����o�֐�
	CDamageBrrowState();//�R���X�g���N�^
	~CDamageBrrowState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_DmageCount;//�_���[�W���󂯂Ă���̃t���[����
};

//==============================================================================
//���퓊����ԃN���X
//==============================================================================
class CWeaponThrowState :public CPlayerStateBase
{
public:
	
	//�����o�֐�
	CWeaponThrowState();//�R���X�g���N�^
	~CWeaponThrowState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��
};

//==============================================================================
//�����ԃN���X
//==============================================================================
class CAvoidanceState :public CPlayerStateBase
{
public:
	//�萔
	static const int AVOIDANCE_FLAME;//����t���[����

	//�����o�֐�
	CAvoidanceState();//�R���X�g���N�^
	~CAvoidanceState();//�f�X�g���N�^
	void Start()override;//�J�n
	void Update()override;//�X�V
	void Uninit()override;//�I��

private:

	//�����o�ϐ�
	int m_AvoidanceCount;//������Ă���̃t���[����
};
#endif