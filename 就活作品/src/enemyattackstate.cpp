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
#include"weakenemy.h"

//�ÓI�����o�ϐ�������
const int CEnemyAttackStateBase::LEFT_HAND = 5;//����̔ԍ�
const int CEnemyAttackStateBase::RIGHT_HAND = 8;//�E��̔ԍ�
//const int CAttackStateBase::WIDTH = 20;//�O�Ղ̉��̕�����
//const int CAttackStateBase::VERTICAL = 20;//�O�Ղ̏c�̕�����
//const D3DXVECTOR3 CAttackStateBase::TRAJECTORY_SIZE = { 5.0f,5.0f ,0.0f };//�O�Ղ̑傫��
const int CEnemyAttackStateBase::HITFLAME = 18;//�f��U���̓����蔻��̃t���[����
//========================================================================================================
//��ԊǗ��N���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyAttackStateMachine::CEnemyAttackStateMachine() :
	m_State(nullptr)//�v���C���[�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyAttackStateMachine::~CEnemyAttackStateMachine()
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
void CEnemyAttackStateMachine::ChangeState(CEnemyAttackStateBase* NewState)
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
void CEnemyAttackStateMachine::Update()
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
CEnemyAttackStateBase::CEnemyAttackStateBase()
	//m_Trajectory(nullptr)//�O�Ղ̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyAttackStateBase::~CEnemyAttackStateBase()
{

}

//==========================
//�J�n
//==========================
void CEnemyAttackStateBase::Start()
{

}

//==========================
//�X�V
//==========================
void CEnemyAttackStateBase::Update()
{

}

//==========================
//�I��
//==========================
void CEnemyAttackStateBase::Uninit()
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
CAttackEnemyState::CAttackEnemyState() :
	m_OwnerState(nullptr)//�X�e�[�g�̏��L��
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackEnemyState::~CAttackEnemyState()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CAttackEnemyState::SetOwner(CEnemyAttackState* State)
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
CFirstEnemyAttackState::CFirstEnemyAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstEnemyAttackState::~CFirstEnemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CFirstEnemyAttackState::Start()
{
	//�U�������������
	m_OwnerState->GetOwner()->ResetAttack();
}

//==========================
//�X�V
//==========================
void CFirstEnemyAttackState::Update()
{
	//���[�V�����̐ݒ�
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() < HITFLAME)
	{//�U���J�n����20�t���[���ȉ�
		
		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitPlayer(RIGHT_HAND);
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CSecondEnemyAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
	else
	{
		//�U���I��
		m_OwnerState->ChangeCombo();

		//�U���̃N�[���^�C����ݒ�
		m_OwnerState->GetOwner()->SetCoolTime(300);
	}
}

//==========================
//�I��
//==========================
void CFirstEnemyAttackState::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondEnemyAttackState::CSecondEnemyAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondEnemyAttackState::~CSecondEnemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CSecondEnemyAttackState::Start()
{
	//�U�������������
	m_OwnerState->GetOwner()->ResetAttack();

	//������ύX
	m_OwnerState->GetOwner()->ChangeDirection();

	//���[�V�������Đ�
	m_OwnerState->GetOwner()->ChangePlayMotion(true);
}

//==========================
//�X�V
//==========================
void CSecondEnemyAttackState::Update()
{
	//���[�V�����ύX
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() < HITFLAME)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitPlayer(LEFT_HAND);
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CRastEnemyAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
	else
	{
		//�U���I��
		m_OwnerState->ChangeCombo();

		//�U���̃N�[���^�C����ݒ�
		m_OwnerState->GetOwner()->SetCoolTime(300);
	}
}

//==========================
//�I��
//==========================
void CSecondEnemyAttackState::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastEnemyAttackState::CRastEnemyAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastEnemyAttackState::~CRastEnemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CRastEnemyAttackState::Start()
{
	//�U�������������
	m_OwnerState->GetOwner()->ResetAttack();

	//������ύX
	m_OwnerState->GetOwner()->ChangeDirection();

	//���[�V�������Đ�
	m_OwnerState->GetOwner()->ChangePlayMotion(true);
}

//==========================
//�X�V
//==========================
void CRastEnemyAttackState::Update()
{
	//���[�V�����̕ύX
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);

	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitPlayer(RIGHT_HAND);
	}
	else
	{
		//�U���I��
		m_OwnerState->ChangeCombo();

		//�U���̃N�[���^�C����ݒ�
		m_OwnerState->GetOwner()->SetCoolTime(300);
	}
}

//==========================
//�I��
//==========================
void CRastEnemyAttackState::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CFirstSmallWeaponEnemyAttack::CFirstSmallWeaponEnemyAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CFirstSmallWeaponEnemyAttack::~CFirstSmallWeaponEnemyAttack()
{

}

//==========================
//�J�n
//==========================
void CFirstSmallWeaponEnemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//�X�V
//==========================
void CFirstSmallWeaponEnemyAttack::Update()
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
void CFirstSmallWeaponEnemyAttack::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CSecondSmallWeaponEnemyAttack::CSecondSmallWeaponEnemyAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSecondSmallWeaponEnemyAttack::~CSecondSmallWeaponEnemyAttack()
{

}

//==========================
//�J�n
//==========================
void CSecondSmallWeaponEnemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//�X�V
//==========================
void CSecondSmallWeaponEnemyAttack::Update()
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
void CSecondSmallWeaponEnemyAttack::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CRastSmallWeaponEnemyAttack::CRastSmallWeaponEnemyAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CRastSmallWeaponEnemyAttack::~CRastSmallWeaponEnemyAttack()
{

}

//==========================
//�J�n
//==========================
void CRastSmallWeaponEnemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//�X�V
//==========================
void CRastSmallWeaponEnemyAttack::Update()
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
void CRastSmallWeaponEnemyAttack::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}