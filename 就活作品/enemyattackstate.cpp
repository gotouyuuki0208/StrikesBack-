//==========================
// 
// �G�̍U���̏�ԊǗ�[enemyattackstate.h]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"enemyattackstate.h"
#include"trajectory.h"

//�ÓI�����o�ϐ�������
//const int CAttackStateBase::LEFT_HAND = 5;//����̔ԍ�
//const int CAttackStateBase::RIGHT_HAND = 8;//�E��̔ԍ�
//const int CAttackStateBase::WIDTH = 20;//�O�Ղ̉��̕�����
//const int CAttackStateBase::VERTICAL = 20;//�O�Ղ̏c�̕�����
//const D3DXVECTOR3 CAttackStateBase::TRAJECTORY_SIZE = { 5.0f,5.0f ,0.0f };//�O�Ղ̑傫��
//========================================================================================================
//��ԊǗ��N���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEenemyAttackStateMachine::CEenemyAttackStateMachine() :
	m_State(nullptr)//�v���C���[�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CEenemyAttackStateMachine::~CEenemyAttackStateMachine()
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
void CEenemyAttackStateMachine::ChangeState(CEenemyAttackStateBase* NewState)
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
void CEenemyAttackStateMachine::Update()
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
CEenemyAttackStateBase::CEenemyAttackStateBase()
	//m_Trajectory(nullptr)//�O�Ղ̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CEenemyAttackStateBase::~CEenemyAttackStateBase()
{

}

//==========================
//�J�n
//==========================
void CEenemyAttackStateBase::Start()
{

}

//==========================
//�X�V
//==========================
void CEenemyAttackStateBase::Update()
{

}

//==========================
//�I��
//==========================
void CEenemyAttackStateBase::Uninit()
{
	/*if (m_Trajectory != nullptr)
	{
		m_Trajectory->Uninit();
		m_Trajectory = nullptr;
	}*/

	delete this;
}

////==========================
////�O�Ղ̐���
////==========================
//void CAttackStateBase::CreateTrajectory(D3DXVECTOR3 pos)
//{
//	if (m_Trajectory != nullptr)
//	{//�O�Ղ���������Ă���
//		return;
//	}
//
//	//�O�Ղ𐶐�
//	m_Trajectory = CTrajectory::Create(pos, TRAJECTORY_SIZE, WIDTH, VERTICAL);
//}
//
////==========================
////�O�Ղ̈ʒu��ݒ�
////==========================
//void CAttackStateBase::TrajectoryPos(D3DXVECTOR3 pos)
//{
//	if (m_Trajectory == nullptr)
//	{//�O�Ղ���������Ă��Ȃ�
//		return;
//	}
//
//	//�V�����ʒu��ݒ�
//	m_Trajectory->SetNewPos(pos);
//}

//========================================================================================================
//�v���C���[�̍U����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAttackEenemyState::CAttackEenemyState() :
	m_OwnerState(nullptr)//�X�e�[�g�̏��L��
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackEenemyState::~CAttackEenemyState()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CAttackEenemyState::SetOwner(CEnemyAttackState* State)
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
CFirstEenemyAttackState::CFirstEenemyAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstEenemyAttackState::~CFirstEenemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CFirstEenemyAttackState::Start()
{

}

//==========================
//�X�V
//==========================
void CFirstEenemyAttackState::Update()
{
	//���[�V�����̐ݒ�
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() < 20)
	{//�U���J�n����20�t���[���ȉ�
		
		//�U���̓����蔻��
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttacKRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion();//���[�V�������~

		auto NewState = DBG_NEW CSecondEenemyAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
	else
	{
		//�U���I��
		m_OwnerState->ChangeCombo();
	}
}

//==========================
//�I��
//==========================
void CFirstEenemyAttackState::Uninit()
{
	CEenemyAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondEenemyAttackState::CSecondEenemyAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondEenemyAttackState::~CSecondEenemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CSecondEenemyAttackState::Start()
{
	//������ύX
	m_OwnerState->GetOwner()->ChangeDirection();

	//���[�V�������Đ�
	m_OwnerState->GetOwner()->ChangePlayMotion();
}

//==========================
//�X�V
//==========================
void CSecondEenemyAttackState::Update()
{
	//���[�V�����ύX
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() < 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttacKRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion();//���[�V�������~

		auto NewState = DBG_NEW CRastEenemyAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
	else
	{
		//�U���I��
		m_OwnerState->ChangeCombo();
	}
}

//==========================
//�I��
//==========================
void CSecondEenemyAttackState::Uninit()
{
	CEenemyAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastEenemyAttackState::CRastEenemyAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastEenemyAttackState::~CRastEenemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CRastEenemyAttackState::Start()
{
	//������ύX
	m_OwnerState->GetOwner()->ChangeDirection();

	//���[�V�������Đ�
	m_OwnerState->GetOwner()->ChangePlayMotion();
}

//==========================
//�X�V
//==========================
void CRastEenemyAttackState::Update()
{
	//���[�V�����̕ύX
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		//m_OwnerState->GetOwner()->HitEnemy(RIGHT_HAND);
	}
	else
	{
		//�U���I��
		m_OwnerState->ChangeCombo();
	}
}

//==========================
//�I��
//==========================
void CRastEenemyAttackState::Uninit()
{
	CEenemyAttackStateBase::Uninit();
}

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CFirstSmallWeaponEenemyAttack::CFirstSmallWeaponEenemyAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstSmallWeaponEenemyAttack::~CFirstSmallWeaponEenemyAttack()
{

}

//==========================
//�J�n
//==========================
void CFirstSmallWeaponEenemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//�X�V
//==========================
void CFirstSmallWeaponEenemyAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		//m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		//m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//�I��
//==========================
void CFirstSmallWeaponEenemyAttack::Uninit()
{
	CEenemyAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondSmallWeaponEenemyAttack::CSecondSmallWeaponEenemyAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondSmallWeaponEenemyAttack::~CSecondSmallWeaponEenemyAttack()
{

}

//==========================
//�J�n
//==========================
void CSecondSmallWeaponEenemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//�X�V
//==========================
void CSecondSmallWeaponEenemyAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		//m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		//m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//�I��
//==========================
void CSecondSmallWeaponEenemyAttack::Uninit()
{
	CEenemyAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastSmallWeaponEenemyAttack::CRastSmallWeaponEenemyAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastSmallWeaponEenemyAttack::~CRastSmallWeaponEenemyAttack()
{

}

//==========================
//�J�n
//==========================
void CRastSmallWeaponEenemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//�X�V
//==========================
void CRastSmallWeaponEenemyAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		//m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		//m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//�I��
//==========================
void CRastSmallWeaponEenemyAttack::Uninit()
{
	CEenemyAttackStateBase::Uninit();
}