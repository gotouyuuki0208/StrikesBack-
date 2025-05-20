//==========================
// 
// �{�X�̏�ԊǗ�[bossState.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bossState.h"
#include "boss.h"
#include "bossattackstate.h"
#include"manager.h"

//�ÓI�����o������
const int CBossDamageState::DAMEGE_FLAME = 54;//�_���[�W��Ԃ��I������܂ł̃t���[����
const int CBossDamageBrrowState::BRROW_FLAME = 50;//�_���[�W��Ԃ��I������܂ł̃t���[����
//==============================================================================
//�G�̏�ԃN���X
//==============================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossStateBase::CBossStateBase() :
	m_pBoss(nullptr)//�G�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossStateBase::~CBossStateBase()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CBossStateBase::SetOwner(CBoss* enemy)
{
	m_pBoss = enemy;
}

//==========================
//�X�e�[�g�̏��L�҂��擾
//==========================
CBoss* CBossStateBase::GetOwner()
{
	return m_pBoss;
}

//========================================================================================================
//���o��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossDirectionState::CBossDirectionState()
{
	m_count = 0;
}

//==========================
//�f�X�g���N�^
//==========================
CBossDirectionState::~CBossDirectionState()
{

}

//==========================
//�J�n
//==========================
void CBossDirectionState::Start()
{
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::BOSS_DIRECTION);
}

//==========================
//�X�V
//==========================
void CBossDirectionState::Update()
{	
	if (m_pBoss->GetMotion() == CMotionModel::MOTION_TYPE::NEUTRAL)
	{
		//���[�V������ݒ�
		m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);
	}

	//�s���\������
	m_pBoss->JudgeMovable();

	if (CManager::GetInstance()->GetGameManager()->GetPlayGame()
		&& !CManager::GetInstance()->GetGameManager()->GetDirection())
	{//�s���\

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossSmallWeaponNeutralState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossDirectionState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossNeutralState::CBossNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossNeutralState::~CBossNeutralState()
{

}

//==========================
//�J�n
//==========================
void CBossNeutralState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);
}

//==========================
//�X�V
//==========================
void CBossNeutralState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);

	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeDush())
	{//�����ċ߂Â��͈͂ɂ���

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossDushState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->JudgeWalk()
		|| m_pBoss->GetAttackable())
	{//�����ċ߂Â��͈͂ɂ��邩�U���\�̂Ƃ�

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossMoveState;
		m_pBoss->ChangeState(NewState);
		return;
	}

}

//==========================
//�I��
//==========================
void CBossNeutralState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�Ў蕐�폊���ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossSmallWeaponNeutralState::CBossSmallWeaponNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossSmallWeaponNeutralState::~CBossSmallWeaponNeutralState()
{

}

//==========================
//�J�n
//==========================
void CBossSmallWeaponNeutralState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);
}

//==========================
//�X�V
//==========================
void CBossSmallWeaponNeutralState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);

	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeWalk())
	{//�����ċ߂Â����

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossMoveState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	if (m_pBoss->JudgeDush())
	{//�����ċ߂Â����

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossDushState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->GetAttackable()&& !m_pBoss->JudgeAttackRange())
	{//�U���\���U���͈͂ɂ���

		//�U����ԂɕύX
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossSmallWeaponNeutralState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//���蕐�폊���ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossBigWeaponNeutralState::CBossBigWeaponNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossBigWeaponNeutralState::~CBossBigWeaponNeutralState()
{

}

//==========================
//�J�n
//==========================
void CBossBigWeaponNeutralState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);
}

//==========================
//�X�V
//==========================
void CBossBigWeaponNeutralState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);

	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeDush()||m_pBoss->JudgeWalk())
	{//�ړ��͈͂ɂ���

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CBossWeaponMoveState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	else if (m_pBoss->GetAttackable() && !m_pBoss->JudgeAttackRange())
	{//�U���\���U���͈͂ɂ���

		//�U����ԂɕύX
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossBigWeaponNeutralState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�ړ���ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossMoveState::CBossMoveState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossMoveState::~CBossMoveState()
{

}

//==========================
//�J�n
//==========================
void CBossMoveState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//�X�V
//==========================
void CBossMoveState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::MOVE);

	//�ړ�����
	m_pBoss->Walk();
	m_pBoss->Move();

	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeDush() ||
		(m_pBoss->GetAttackable() && m_pBoss->GetNextAttack() && !m_pBoss->GetWeapon()))
	{//�����ċ߂Â���Ԃ��U���\�Ŏ��̍U��������U���ŕ���������Ă��Ȃ�

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossDushState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->GetAttackable()
		&& !m_pBoss->JudgeAttackRange())
	{//�U���\���U���͈͂ɂ���

		//�U����ԂɕύX
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->JudgeStop()
		&& !m_pBoss->GetAttackable())
	{//��~����͈͂ɂ��邩�U���ł��Ȃ�

		//��~����Ƃ��̍s����ݒ�
		m_pBoss->PlayerNearAction();

		if (m_pBoss->GetGuard())
		{//�K�[�h����

			if (m_pBoss->GetWeapon())
			{//���폊��

				//���폊���K�[�h��ԂɕύX
				auto NewState = DBG_NEW CBossSmallWeaponGuardState;
				m_pBoss->ChangeState(NewState);
				return;
			}
			else
			{//���햢����

				//�K�[�h��ԂɕύX
				auto NewState = DBG_NEW CBossGuardState;
				m_pBoss->ChangeState(NewState);
				return;
			}
			
		}
		else
		{
			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CBossNeutralState;
			m_pBoss->ChangeState(NewState);
			return;
		}

	}
}

//==========================
//�I��
//==========================
void CBossMoveState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//���펝���ړ���ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossWeaponMoveState::CBossWeaponMoveState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossWeaponMoveState::~CBossWeaponMoveState()
{

}

//==========================
//�J�n
//==========================
void CBossWeaponMoveState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONMOVE);
}

//==========================
//�X�V
//==========================
void CBossWeaponMoveState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONMOVE);

	//�ړ�����
	m_pBoss->Walk();
	m_pBoss->Move();

	if (m_pBoss->JudgeStop()
		&& !m_pBoss->GetAttackable())
	{//��~����͈͂ɂ��邩�U���ł��Ȃ�


		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossBigWeaponNeutralState;
		m_pBoss->ChangeState(NewState);
		return;


	}
	else if (m_pBoss->GetAttackable() && !m_pBoss->JudgeAttackRange())
	{//�U���\���U���͈͂ɂ���

		//�U����ԂɕύX
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossWeaponMoveState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�K�[�h��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossGuardState::CBossGuardState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossGuardState::~CBossGuardState()
{

}

//==========================
//�J�n
//==========================
void CBossGuardState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::GUARD);
}

//==========================
//�X�V
//==========================
void CBossGuardState::Update()
{

	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::GUARD);

	if (m_pBoss->GetDamageNum() >= 3)
	{//�A����3���e����
		m_pBoss->ResetDamageNum();//��e�񐔂�������
	}

	if (!m_pBoss->JudgeGuard())
	{//�K�[�h����͈͂ɂ��Ȃ�

		//�K�[�h�̏������Z�b�g
		m_pBoss->GuardReset();

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossGuardState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�Ў蕐�펝���K�[�h��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossSmallWeaponGuardState::CBossSmallWeaponGuardState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossSmallWeaponGuardState::~CBossSmallWeaponGuardState()
{

}

//==========================
//�J�n
//==========================
void CBossSmallWeaponGuardState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);
}

//==========================
//�X�V
//==========================
void CBossSmallWeaponGuardState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);

	if (!m_pBoss->JudgeGuard())
	{//�K�[�h����͈͂ɂ��Ȃ�

		//�K�[�h�̏������Z�b�g
		m_pBoss->GuardReset();

		//�Ў蕐�펝���ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossSmallWeaponNeutralState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossSmallWeaponGuardState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�_���[�W��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossDamageState::CBossDamageState() :
	m_DmageCount(0)//�_���[�W���󂯂Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossDamageState::~CBossDamageState()
{

}

//==========================
//�J�n
//==========================
void CBossDamageState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);
}

//==========================
//�X�V
//==========================
void CBossDamageState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);

	//�_���[�W���󂯂Ă���̃t���[�����𐔂���
	m_DmageCount++;

	if (m_DmageCount >= DAMEGE_FLAME)
	{
		m_DmageCount = 0;
		m_pBoss->ResetDamageNum();//��e�񐔂�������
		m_pBoss->SetDamage(false);

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);

		return;
	}

	if (m_pBoss->GetDamageNum() >= 3)
	{//�A����3���e����

		m_pBoss->SetDamage(false);

		//������я�ԂɕύX
		auto NewState = DBG_NEW CBossDamageBrrowState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBossDamageState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�_�b�V����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossDushState::CBossDushState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossDushState::~CBossDushState()
{

}

//==========================
//�J�n
//==========================
void CBossDushState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DUSH);
}

//==========================
//�X�V
//==========================
void CBossDushState::Update()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DUSH);

	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if(m_pBoss->GetAttackable() && m_pBoss->GetNextAttack() && !m_pBoss->GetWeapon())
	{//�U���\�Ŏ��̍U��������U���ŕ���������Ă��Ȃ�

		//����̕����Ɉړ�
		m_pBoss->WeaponMove();

		if (m_pBoss->GetWeapon())
		{//����������Ă���
			
			if (!m_pBoss->GetWeaponType())
			{//�Ў蕐��

				//�Ў蕐�펝���ҋ@��ԂɕύX
				auto NewState = DBG_NEW CBossSmallWeaponNeutralState;
					m_pBoss->ChangeState(NewState);
					return;
			}
			else if (m_pBoss->GetWeaponType())
			{//���蕐��

				//���蕐�펝���ҋ@��ԂɕύX
				auto NewState = DBG_NEW CBossBigWeaponNeutralState;
				m_pBoss->ChangeState(NewState);
				return;
			}
		}
	}
	else
	{
		if (m_pBoss->JudgeWalk())
		{//�����ċ߂Â����

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CBossMoveState;
			m_pBoss->ChangeState(NewState);
			return;
		}
		else if (m_pBoss->JudgeStop())
		{//��~����͈͂ɂ��邩�U���ł��Ȃ�

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CBossNeutralState;
			m_pBoss->ChangeState(NewState);
			return;
		}

		//�v���C���[�Ɉړ�
		m_pBoss->Dush();
	}

	//�l��ύX
	m_pBoss->Move();
	
}

//==========================
//�I��
//==========================
void CBossDushState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//������я�ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossDamageBrrowState::CBossDamageBrrowState() :
	m_DmageCount(0)//�_���[�W���󂯂Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossDamageBrrowState::~CBossDamageBrrowState()
{

}

//==========================
//�J�n
//==========================
void CBossDamageBrrowState::Start()
{
	//���[�V������ݒ�
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DAMAGEBLOW);
}

//==========================
//�X�V
//==========================
void CBossDamageBrrowState::Update()
{
	//�ړ�����
	m_pBoss->Move();

	m_DmageCount++;

	if (m_pBoss->GetLife() <= 0)
	{//���C�t��0

		if (m_DmageCount >= 30)
		{
			m_pBoss->ChangePlayMotion(false);//���[�V�������~
			//m_pBoss->SubPartsCol();//�F�𔖂�����
		}
	}
	else if (m_DmageCount >= BRROW_FLAME)
	{
		m_DmageCount = 0;
		m_pBoss->ResetDamageNum();//��e�񐔂�������
		m_pBoss->SetDamage(false);

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);

		return;
	}
}

//==========================
//�I��
//==========================
void CBossDamageBrrowState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//�U����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBossAttackState::CBossAttackState() :
	m_FlameCount(0),//�U���̃t���[����
	m_Combo(true),//�R���{����
	m_AttackStateMachine(nullptr)//�U���̏�ԊǗ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossAttackState::~CBossAttackState()
{

}

//==========================
//�J�n
//==========================
void CBossAttackState::Start()
{
	m_AttackStateMachine = DBG_NEW CBossAttackStateMachine;

	if (!m_pBoss->GetNextAttack())
	{//�f��U��

		auto NewState = DBG_NEW CBossFirstAttackState;
		ChangeAttack(NewState);
	}
	else
	{//����U��

		if (m_pBoss->GetWeaponType())
		{//���蕐��

			auto NewState = DBG_NEW CBossFirstBigWeaponAttack;
			ChangeAttack(NewState);
		}
		else
		{//�Ў蕐��

			auto NewState = DBG_NEW CBossFirstSmallWeaponAttack;
			ChangeAttack(NewState);
		}
	}
}

//==========================
//�X�V
//==========================
void CBossAttackState::Update()
{
	if (m_pBoss->GetDamage())
	{//�_���[�W���󂯂�

		//�U���o���Ȃ���ԂɕύX
		m_pBoss->ChangeAttackable();

		//�U���̃N�[���^�C����ݒ�
		m_pBoss->SetCoolTime(300);

		m_pBoss->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	m_FlameCount++;

	if (m_AttackStateMachine != nullptr)
	{
		m_AttackStateMachine->Update();
	}

	if (m_pBoss->GetWeaponBreak())
	{
		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);
	}

	if (m_Combo)
	{//�U�����͏I��
		return;
	}

	//�U���o���Ȃ���ԂɕύX
	m_pBoss->ChangeAttackable();

	//�ҋ@��ԂɕύX
	auto NewState = DBG_NEW CBossNeutralState;
	m_pBoss->ChangeState(NewState);
	return;
}

//==========================
//�I��
//==========================
void CBossAttackState::Uninit()
{
	if (m_AttackStateMachine != nullptr)
	{
		delete m_AttackStateMachine;
		m_AttackStateMachine = nullptr;
	}

	CBossStateBase::Uninit();
}

//==========================
//�R���{������擾
//========================== 
void CBossAttackState::ChangeCombo()
{
	m_Combo = !m_Combo;
}

//==========================
//����������
//==========================
void CBossAttackState::ResetInfo()
{
	m_FlameCount = 0;
}

//==========================
//�U����ύX
//==========================
void CBossAttackState::ChangeAttack(CAttackBossStateBase* State)
{
	State->SetOwner(this);
	m_AttackStateMachine->ChangeState(State);
}

//==========================
//�U���t���[�������擾
//==========================
int CBossAttackState::GetFrame()
{
	return m_FlameCount;
}

//==========================
//�R���{������擾
//==========================
bool CBossAttackState::GetCombo()
{
	return m_Combo;
}