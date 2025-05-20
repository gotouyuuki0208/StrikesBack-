//==========================
// 
// �U���̏�ԊǗ�[attackstate.h]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"bossattackstate.h"
#include"bossState.h"
#include"boss.h"

//�ÓI�����o�ϐ�������
const int CBossAttackStateBase::LEFT_HAND = 5;//����̔ԍ�
const int CBossAttackStateBase::RIGHT_HAND = 8;//�E��̔ԍ�
const int CBossAttackStateBase::HITFLAME = 18;//�f��U���̓����蔻��̃t���[����
//========================================================================================================
//��ԊǗ��N���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossAttackStateMachine::CBossAttackStateMachine() :
	m_State(nullptr)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossAttackStateMachine::~CBossAttackStateMachine()
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
void CBossAttackStateMachine::ChangeState(CAttackBossStateBase* NewState)
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
void CBossAttackStateMachine::Update()
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
CBossAttackStateBase::CBossAttackStateBase()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossAttackStateBase::~CBossAttackStateBase()
{

}

//==========================
//�J�n
//==========================
void CBossAttackStateBase::Start()
{

}

//==========================
//�X�V
//==========================
void CBossAttackStateBase::Update()
{

}

//==========================
//�I��
//==========================
void CBossAttackStateBase::Uninit()
{
	delete this;
}

//========================================================================================================
//�{�X�̍U����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAttackBossStateBase::CAttackBossStateBase() :
	m_OwnerState(nullptr)//�X�e�[�g�̏��L��
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackBossStateBase::~CAttackBossStateBase()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CAttackBossStateBase::SetOwner(CBossAttackState* State)
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
CBossFirstAttackState::CBossFirstAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossFirstAttackState::~CBossFirstAttackState()
{

}

//==========================
//�J�n
//==========================
void CBossFirstAttackState::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);
}

//==========================
//�X�V
//==========================
void CBossFirstAttackState::Update()
{
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
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CBossSecondAttackState;
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
void CBossFirstAttackState::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossSecondAttackState::CBossSecondAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossSecondAttackState::~CBossSecondAttackState()
{

}

//==========================
//�J�n
//==========================
void CBossSecondAttackState::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);
}

//==========================
//�X�V
//==========================
void CBossSecondAttackState::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//�U���J�n����20�t���[���ȉ�

		//�U���̓����蔻��
		m_OwnerState->GetOwner()->HitPlayer(LEFT_HAND);
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CBossRastAttackState;
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
void CBossSecondAttackState::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossRastAttackState::CBossRastAttackState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossRastAttackState::~CBossRastAttackState()
{

}

//==========================
//�J�n
//==========================
void CBossRastAttackState::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);
}

//==========================
//�X�V
//==========================
void CBossRastAttackState::Update()
{
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
void CBossRastAttackState::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//==============================================================================
//���蕐��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossFirstBigWeaponAttack::CBossFirstBigWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossFirstBigWeaponAttack::~CBossFirstBigWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CBossFirstBigWeaponAttack::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK);
}

//==========================
//�X�V
//==========================
void CBossFirstBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�����蔻��
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CBossSecondBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CBossFirstBigWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossSecondBigWeaponAttack::CBossSecondBigWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossSecondBigWeaponAttack::~CBossSecondBigWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CBossSecondBigWeaponAttack::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK2);
}

//==========================
//�X�V
//==========================
void CBossSecondBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�����蔻��
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CBossRastBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CBossSecondBigWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossRastBigWeaponAttack::CBossRastBigWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossRastBigWeaponAttack::~CBossRastBigWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CBossRastBigWeaponAttack::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK3);
}

//==========================
//�X�V
//==========================
void CBossRastBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�����蔻��
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
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
void CBossRastBigWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//==============================================================================
//�Ў蕐��U���N���X
//==============================================================================

//=============================1��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossFirstSmallWeaponAttack::CBossFirstSmallWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossFirstSmallWeaponAttack::~CBossFirstSmallWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CBossFirstSmallWeaponAttack::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//�X�V
//==========================
void CBossFirstSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�����蔻��
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CBossSecondSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CBossFirstSmallWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================2��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossSecondSmallWeaponAttack::CBossSecondSmallWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossSecondSmallWeaponAttack::~CBossSecondSmallWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CBossSecondSmallWeaponAttack::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//�X�V
//==========================
void CBossSecondSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�����蔻��
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//�U���͈͂Ƀv���C���[������

		m_OwnerState->ResetInfo();//�U���̏���������
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//���[�V�������~

		auto NewState = DBG_NEW CBossRastSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CBossSecondSmallWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================3��ڂ̍U��======================================

//==========================
//�R���X�g���N�^
//==========================
CBossRastSmallWeaponAttack::CBossRastSmallWeaponAttack()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossRastSmallWeaponAttack::~CBossRastSmallWeaponAttack()
{

}

//==========================
//�J�n
//==========================
void CBossRastSmallWeaponAttack::Start()
{
	//�U���q�b�g���������
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//�X�V
//==========================
void CBossRastSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//�U���J�n����10�t���[���ȉ�

		//�U�����̈ړ�
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//�U���J�n����20�t���[���ȉ�

		//�����蔻��
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
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
void CBossRastSmallWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}