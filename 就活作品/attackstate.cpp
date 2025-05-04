//==========================
// 
// �U���̏�ԊǗ�[attackstate.h]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"attackstate.h"
#include"trajectory.h"
#include "playerstate.h"

//�ÓI�����o�ϐ�������
const int CAttackStateBase::LEFT_HAND = 5;//����̔ԍ�
const int CAttackStateBase::RIGHT_HAND = 8;//�E��̔ԍ�
const int CAttackStateBase::WIDTH = 20;//�O�Ղ̉��̕�����
const int CAttackStateBase::VERTICAL = 20;//�O�Ղ̏c�̕�����
const D3DXVECTOR3 CAttackStateBase::TRAJECTORY_SIZE = { 5.0f,5.0f ,0.0f };//�O�Ղ̑傫��
const int CAttackStateBase::HITFLAME = 18;//�f��U���̓����蔻��̃t���[����
//========================================================================================================
//��ԊǗ��N���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAttackStateMachine::CAttackStateMachine() :
	m_State(nullptr)//�v���C���[�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackStateMachine::~CAttackStateMachine()
{
	if (m_State != nullptr)
	{
		delete m_State;
		m_State = nullptr;
	}
}

//==========================
//��Ԃ̕ύX
//==========================
void CAttackStateMachine::ChangeState(CAttackPlayerStateBase* NewState)
{
	if (m_State != nullptr)
	{
		m_State->Uninit();
		m_State = nullptr;
	}

	m_State = NewState;

	m_State->Start();
}

//==========================
//�X�V
//==========================
void CAttackStateMachine::Update()
{
	if (m_State != nullptr)
	{
		m_State->Update();
	}
}

//========================================================================================================
//���N���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAttackStateBase::CAttackStateBase():
m_Trajectory(nullptr)//�O�Ղ̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackStateBase::~CAttackStateBase()
{

}

//==========================
//�J�n
//==========================
void CAttackStateBase::Start()
{

}

//==========================
//�X�V
//==========================
void CAttackStateBase::Update()
{

}

//==========================
//�I��
//==========================
void CAttackStateBase::Uninit()
{
	if (m_Trajectory != nullptr)
	{
		m_Trajectory->Uninit();
		m_Trajectory = nullptr;
	}

	delete this;
}

//==========================
//�O�Ղ̐���
//==========================
void CAttackStateBase::CreateTrajectory(D3DXVECTOR3 pos)
{
	if (m_Trajectory != nullptr)
	{//�O�Ղ���������Ă���
		return;
	}

	//�O�Ղ𐶐�
	m_Trajectory = CTrajectory::Create(pos, TRAJECTORY_SIZE, WIDTH, VERTICAL);
}

//==========================
//�O�Ղ̈ʒu��ݒ�
//==========================
void CAttackStateBase::TrajectoryPos(D3DXVECTOR3 pos)
{
	if (m_Trajectory == nullptr)
	{//�O�Ղ���������Ă��Ȃ�
		return;
	}

	//�V�����ʒu��ݒ�
	m_Trajectory->SetNewPos(pos);
}

//========================================================================================================
//�v���C���[�̍U����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAttackPlayerStateBase::CAttackPlayerStateBase():
	m_OwnerState(nullptr)//�X�e�[�g�̏��L��
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackPlayerStateBase::~CAttackPlayerStateBase()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CAttackPlayerStateBase::SetOwner(CAttackState* State)
{
	m_OwnerState = State;
}

//==============================================================================
//�f��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CFirstAttackState::CFirstAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstAttackState::~CFirstAttackState()
{

}

//==========================
//�J�n
//==========================
void CFirstAttackState::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);
	
	//�v���C���[�̃p�[�c�̃}�g���b�N�X���擾
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//�O�Ղ𐶐�
	CreateTrajectory({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });
}

//==========================
//�X�V
//==========================
void CFirstAttackState::Update()
{
	//�v���C���[�̃p�[�c�̃}�g���b�N�X���擾
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//�O�Ղ̐V�����ʒu��ݒ�
	TrajectoryPos({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame()<= HITFLAME)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitEnemy(RIGHT_HAND);
	}

	if (m_OwnerState->GetCombo())
	{//�U���{�^�������͂��ꂽ

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CSecondAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CFirstAttackState::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondAttackState::CSecondAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondAttackState::~CSecondAttackState()
{

}

//==========================
//�J�n
//==========================
void CSecondAttackState::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);

	//�v���C���[�̃p�[�c�̃}�g���b�N�X���擾
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(LEFT_HAND)->GetMtxWorld();

	//�O�Ղ𐶐�
	CreateTrajectory({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });
}

//==========================
//�X�V
//==========================
void CSecondAttackState::Update()
{
	//�v���C���[�̃p�[�c�̃}�g���b�N�X���擾
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(LEFT_HAND)->GetMtxWorld();

	//�O�Ղ̐V�����ʒu��ݒ�
	TrajectoryPos({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitEnemy(LEFT_HAND);
	}
	
	if (m_OwnerState->GetCombo())
	{//�U���{�^�������͂��ꂽ

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CRastAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CSecondAttackState::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastAttackState::CRastAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastAttackState::~CRastAttackState()
{

}

//==========================
//�J�n
//==========================
void CRastAttackState::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);

	//�v���C���[�̃p�[�c�̃}�g���b�N�X���擾
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//�O�Ղ𐶐�
	CreateTrajectory({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });
}

//==========================
//�X�V
//==========================
void CRastAttackState::Update()
{
	//�v���C���[�̃p�[�c�̃}�g���b�N�X���擾
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//�O�Ղ̐V�����ʒu��ݒ�
	TrajectoryPos({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitEnemy(RIGHT_HAND);
	}
}

//==========================
//�I��
//==========================
void CRastAttackState::Uninit()
{
	CAttackStateBase::Uninit();
}

//==============================================================================
//���蕐��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CFirstBigWeaponAttack::CFirstBigWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstBigWeaponAttack::~CFirstBigWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CFirstBigWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK);
}

//==========================
//�X�V
//==========================
void CFirstBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//�U���{�^�������͂��ꂽ

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CSecondBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CFirstBigWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondBigWeaponAttack::CSecondBigWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondBigWeaponAttack::~CSecondBigWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CSecondBigWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK2);
}

//==========================
//�X�V
//==========================
void CSecondBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//�U���{�^�������͂��ꂽ

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CRastBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CSecondBigWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastBigWeaponAttack::CRastBigWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastBigWeaponAttack::~CRastBigWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CRastBigWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK3);
}

//==========================
//�X�V
//==========================
void CRastBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//�I��
//==========================
void CRastBigWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CFirstSmallWeaponAttack::CFirstSmallWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstSmallWeaponAttack::~CFirstSmallWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CFirstSmallWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//�X�V
//==========================
void CFirstSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//�U���{�^�������͂��ꂽ

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CSecondSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CFirstSmallWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondSmallWeaponAttack::CSecondSmallWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondSmallWeaponAttack::~CSecondSmallWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CSecondSmallWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//�X�V
//==========================
void CSecondSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//�U���{�^�������͂��ꂽ

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CRastSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CSecondSmallWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastSmallWeaponAttack::CRastSmallWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastSmallWeaponAttack::~CRastSmallWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CRastSmallWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//�X�V
//==========================
void CRastSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//�I��
//==========================
void CRastSmallWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}