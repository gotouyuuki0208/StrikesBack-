//==========================
// 
// �G�̏�ԊǗ�[enemystate.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemystate.h"
#include"enemyattackstate.h"
#include "weakenemy.h"

//�ÓI�����o������
const int CEnemyDamageState::DAMEGE_FLAME = 54;//�_���[�W��Ԃ��I������܂ł̃t���[����
const int CEnemyDamageBrrowState::BRROW_FLAME = 50;//�_���[�W��Ԃ��I������܂ł̃t���[����
//==============================================================================
//�G�̏�ԃN���X
//==============================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyStateBase::CEnemyStateBase() :
	m_pEnemy(nullptr)//�G�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyStateBase::~CEnemyStateBase()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CEnemyStateBase::SetOwner(CWeakEnemy* enemy)
{
	m_pEnemy = enemy;
}

//==========================
//�X�e�[�g�̏��L�҂��擾
//==========================
CWeakEnemy* CEnemyStateBase::GetOwner()
{
	return m_pEnemy;
}

//========================================================================================================
//����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyMovabeState::CEnemyMovabeState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyMovabeState::~CEnemyMovabeState()
{

}

//==========================
//�J�n
//==========================
void CEnemyMovabeState::Start()
{
	
}

//==========================
//�X�V
//==========================
void CEnemyMovabeState::Update()
{
	//�s���\������
	m_pEnemy->JudgeMovable();

	if (m_pEnemy->GetMovable())
	{//�s���\

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CEnemyMovabeState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//�ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyNeutralState::CEnemyNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyNeutralState::~CEnemyNeutralState()
{

}

//==========================
//�J�n
//==========================
void CEnemyNeutralState::Start()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);
}

//==========================
//�X�V
//==========================
void CEnemyNeutralState::Update()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);

	if (m_pEnemy->GetDamage())
	{//�_���[�W���󂯂�

		m_pEnemy->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->JudgeDush())
	{//�����ċ߂Â��͈͂ɂ���

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyDushState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeWalk()
		||m_pEnemy->GetAttackable())
	{//�����ċ߂Â��͈͂ɂ��邩�U���\�̂Ƃ�

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyMoveState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

}

//==========================
//�I��
//==========================
void CEnemyNeutralState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//�ړ���ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyMoveState::CEnemyMoveState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyMoveState::~CEnemyMoveState()
{

}

//==========================
//�J�n
//==========================
void CEnemyMoveState::Start()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//�X�V
//==========================
void CEnemyMoveState::Update()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::MOVE);

	//�ړ�����
	m_pEnemy->Walk();
	m_pEnemy->Move();

	if (m_pEnemy->GetDamage())
	{//�_���[�W���󂯂�

		m_pEnemy->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->JudgeDush())
	{//�����ċ߂Â����

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyDushState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->GetAttackable()
		&& !m_pEnemy->JudgeAttackRange())
	{//�U���\���U���͈͂ɂ���

		//�U����ԂɕύX
		auto NewState = DBG_NEW CEnemyAttackState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeStop()
		&& !m_pEnemy->GetAttackable())
	{//��~����͈͂ɂ��邩�U���ł��Ȃ�

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CEnemyMoveState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//�_���[�W��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyDamageState::CEnemyDamageState():
	m_DmageCount(0)//�_���[�W���󂯂Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyDamageState::~CEnemyDamageState()
{

}

//==========================
//�J�n
//==========================
void CEnemyDamageState::Start()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);
}

//==========================
//�X�V
//==========================
void CEnemyDamageState::Update()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);

	//�_���[�W���󂯂Ă���̃t���[�����𐔂���
	m_DmageCount++;

	if (m_DmageCount >= DAMEGE_FLAME)
	{
		m_DmageCount = 0;
		m_pEnemy->ResetDamageNum();//��e�񐔂�������
		m_pEnemy->SetDamage(false);

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);

		return;
	}

	if (m_pEnemy->GetDamageNum() >= 3)
	{//�A����3���e����

		m_pEnemy->SetDamage(false);

		//������я�ԂɕύX
		auto NewState = DBG_NEW CEnemyDamageBrrowState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->GetDamage())
	{//�_���[�W���󂯂�

		m_pEnemy->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CEnemyDamageState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//�_�b�V����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyDushState::CEnemyDushState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyDushState::~CEnemyDushState()
{

}

//==========================
//�J�n
//==========================
void CEnemyDushState::Start()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DUSH);
}

//==========================
//�X�V
//==========================
void CEnemyDushState::Update()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DUSH);

	//�ړ�����
	m_pEnemy->Dush();
	m_pEnemy->Move();

	if (m_pEnemy->GetDamage())
	{//�_���[�W���󂯂�

		m_pEnemy->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->JudgeWalk())
	{//�����ċ߂Â����

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyMoveState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeStop())
	{//��~����͈͂ɂ��邩�U���ł��Ȃ�

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CEnemyDushState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//������я�ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyDamageBrrowState::CEnemyDamageBrrowState() :
	m_DmageCount(0)//�_���[�W���󂯂Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyDamageBrrowState::~CEnemyDamageBrrowState()
{

}

//==========================
//�J�n
//==========================
void CEnemyDamageBrrowState::Start()
{
	//���[�V������ݒ�
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DAMAGEBLOW);
}

//==========================
//�X�V
//==========================
void CEnemyDamageBrrowState::Update()
{
	//�ړ�����
	m_pEnemy->Move();

	m_DmageCount++;

	if (m_pEnemy->GetLife() <= 0)
	{//���C�t��0

		if (m_DmageCount >= 30)
		{
			m_pEnemy->ChangePlayMotion(false);//���[�V�������~
			m_pEnemy->SubPartsCol();//�F�𔖂�����
		}
	}
	else if (m_DmageCount >= BRROW_FLAME)
	{
		m_DmageCount = 0;
		m_pEnemy->ResetDamageNum();//��e�񐔂�������
		m_pEnemy->SetDamage(false);

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CEnemyDamageBrrowState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//�U����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CEnemyAttackState::CEnemyAttackState():
m_FlameCount(0),//�U���̃t���[����
m_Combo(true),//�R���{����
m_EenemyAttackStateMachine(nullptr)//�U���̏�ԊǗ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CEnemyAttackState::~CEnemyAttackState()
{

}

//==========================
//�J�n
//==========================
void CEnemyAttackState::Start()
{
	m_EenemyAttackStateMachine = DBG_NEW CEenemyAttackStateMachine;

	
	if (m_pEnemy->GetEnemyType()==CEnemy::ENEMY_TYPE::HitEnemy)
	{//�f��̓G

		auto NewState = DBG_NEW CFirstEenemyAttackState;
		ChangeAttack(NewState);
	}
	else
	{//�Ў蕐��
		auto NewState = DBG_NEW CFirstSmallWeaponEenemyAttack;
		ChangeAttack(NewState);
	}
}

//==========================
//�X�V
//==========================
void CEnemyAttackState::Update()
{
	if (m_pEnemy->GetDamage())
	{//�_���[�W���󂯂�

		//�U���o���Ȃ���ԂɕύX
		m_pEnemy->ChangeAttackable();

		//�U���̃N�[���^�C����ݒ�
		m_pEnemy->SetCoolTime(300);

		m_pEnemy->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	m_FlameCount++;
	m_EenemyAttackStateMachine->Update();	

	if (m_Combo)
	{//�U�����͏I��
		return;
	}

	if (m_pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::HitEnemy)
	{//�f��̓G

		//�U���o���Ȃ���ԂɕύX
		m_pEnemy->ChangeAttackable();

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CEnemyAttackState::Uninit()
{
	if (m_EenemyAttackStateMachine != nullptr)
	{
		delete m_EenemyAttackStateMachine;
		m_EenemyAttackStateMachine = nullptr;
	}

	CEnemyStateBase::Uninit();
}

//==========================
//�R���{������擾
//========================== 
void CEnemyAttackState::ChangeCombo()
{
	m_Combo=!m_Combo;
}

//==========================
//����������
//==========================
void CEnemyAttackState::ResetInfo()
{
	m_FlameCount = 0;
}

//==========================
//�U����ύX
//==========================
void CEnemyAttackState::ChangeAttack(CAttackEenemyState* State)
{
	State->SetOwner(this);
	m_EenemyAttackStateMachine->ChangeState(State);
}

//==========================
//�U���t���[�������擾
//==========================
int CEnemyAttackState::GetFrame()
{
	return m_FlameCount;
}
