//==========================
// 
// �v���C���[�̏�ԊǗ�[playerstate.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playerstate.h"
#include "manager.h"
#include "player.h"
#include "attackstate.h"

//�ÓI�����o������
const int CDamageState::DAMEGE_FLAME = 54;//�_���[�W��Ԃ��I������܂ł̃t���[����
const int CAttackState::INPUT_START_FLAME = 24;//���͎�t�J�n�t���[����
const int CAttackState::INPUT_FINISH_FLAME = 60;//���͎�t�I���t���[����
const int CAttackState::RESET_FLAME = 54;//�R���{�̏�񃊃Z�b�g�t���[����
const int CAvoidanceState::AVOIDANCE_FLAME = 6;//����t���[����
const int CDamageBrrowState::BRROW_FLAME = 50;//�_���[�W��Ԃ��I������܂ł̃t���[����

//========================================================================================================
//�v���C���[�̏�ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CPlayerStateBase::CPlayerStateBase():
	m_pPlayer(nullptr)//�v���C���[�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CPlayerStateBase::~CPlayerStateBase()
{

}

//==========================
//�X�e�[�g�̏����҂�ݒ�
//==========================
void CPlayerStateBase::SetOwner(CPlayer* player)
{
	m_pPlayer = player;
}

//==========================
//�X�e�[�g�̏��L�҂��擾
//==========================
CPlayer* CPlayerStateBase::GetOwner()
{
	return m_pPlayer;
}

//========================================================================================================
//�ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CNeutralState::CNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CNeutralState::~CNeutralState()
{

}

//==========================
//�J�n
//==========================
void CNeutralState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);
}

//==========================
//�X�V
//==========================
void CNeutralState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick())
	{//���X�e�B�b�N����͂���Ă���

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CMoveState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick()
		&& pJoypad->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
	{//���X�e�B�b�N����͂���Ă��邩��LT��������Ă���

		//�_�b�V����ԂɕύX
		auto NewState = DBG_NEW CDushState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_X))
	{//X�{�^���������ꂽ

		//�K�[�h��ԂɕύX
		auto NewState = DBG_NEW CGuardState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{//Y�{�^�������

		//�U����ԂɕύX
		auto NewState = DBG_NEW CAttackState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
	{//���X�e�B�b�N����͂���Ă���

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CAvoidanceState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//���X�e�B�b�N����͂���Ă���

		//���������
		m_pPlayer->PickUpWeapon();

		if (!m_pPlayer->GetHaveWeapon())
		{//����������Ă��Ȃ�
			return;
		}

		if(!m_pPlayer->GetWeaponType())
		{//�傫������������Ă�Ƃ�

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CBigWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
		}
		else
		{//����������������Ă�Ƃ�

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
		}
		return;
	}
}

//==========================
//�I��
//==========================
void CNeutralState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//���蕐�폊���ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBigWeaponNeutralState::CBigWeaponNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBigWeaponNeutralState::~CBigWeaponNeutralState()
{

}

//==========================
//�J�n
//==========================
void CBigWeaponNeutralState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);
}

//==========================
//�X�V
//==========================
void CBigWeaponNeutralState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick())
	{//���X�e�B�b�N����͂���Ă���

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CBigWeaponMoveState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//���X�e�B�b�N����͂���Ă���

		//������̂Ă�
		m_pPlayer->ReleaseWeapon();

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{//���X�e�B�b�N����͂���Ă���

		//�U����ԂɕύX
		auto NewState = DBG_NEW CAttackState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBigWeaponNeutralState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�Ў蕐�폊���ҋ@��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CSmallWeaponNeutralState::CSmallWeaponNeutralState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSmallWeaponNeutralState::~CSmallWeaponNeutralState()
{

}

//==========================
//�J�n
//==========================
void CSmallWeaponNeutralState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);
}

//==========================
//�X�V
//==========================
void CSmallWeaponNeutralState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick())
	{//���X�e�B�b�N����͂���Ă���

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CMoveState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_X))
	{//X�{�^���������ꂽ

		//�K�[�h��ԂɕύX
		auto NewState = DBG_NEW CSmallWeaponGuardState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//���X�e�B�b�N����͂���Ă���

		//������̂Ă�
		m_pPlayer->ReleaseWeapon();

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{//���X�e�B�b�N����͂���Ă���

		//�ҋ@��ԂɕύX
		auto NewState = DBG_NEW CAttackState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CSmallWeaponNeutralState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�ړ���ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CMoveState::CMoveState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CMoveState::~CMoveState()
{

}

//==========================
//�J�n
//==========================
void CMoveState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//�X�V
//==========================
void CMoveState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::MOVE);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (!pJoypad->Connection())
	{//�p�b�h���ڑ�����Ă��Ȃ�
		return;
	}

	if (!pJoypad->GetLeftStick())
	{//���X�e�B�b�N����͂���Ă��Ȃ�

		if (m_pPlayer->GetHaveWeapon())
		{
			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		else
		{
			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		
	}

	if (pJoypad->GetLeftStick()
		&& pJoypad->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
	{//���X�e�B�b�N����͂���Ă��邩��LT��������Ă���

		//�_�b�V����ԂɕύX
		auto NewState = DBG_NEW CDushState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//���X�e�B�b�N����͂���Ă���

		//������̂Ă�
		auto NewState = DBG_NEW CWeaponThrowState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	//�ړ�����
	m_pPlayer->InputMove();
	m_pPlayer->Move();
}

//==========================
//�I��
//==========================
void CMoveState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//���펝���ړ���ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CBigWeaponMoveState::CBigWeaponMoveState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CBigWeaponMoveState::~CBigWeaponMoveState()
{

}

//==========================
//�J�n
//==========================
void CBigWeaponMoveState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//�X�V
//==========================
void CBigWeaponMoveState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::WEAPONMOVE);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	//�ړ�����
	m_pPlayer->InputMove();
	m_pPlayer->Move();

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		if (!pJoypad->GetLeftStick())
		{//���X�e�B�b�N����͂���Ă���

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CBigWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//���X�e�B�b�N����͂���Ă���

		//������̂Ă�
		auto NewState = DBG_NEW CWeaponThrowState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CBigWeaponMoveState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�_�b�V����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CDushState::CDushState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CDushState::~CDushState()
{

}

//==========================
//�J�n
//==========================
void CDushState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DUSH);
}

//==========================
//�X�V
//==========================
void CDushState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DUSH);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		if (pJoypad->GetLeftStick()
			&& !pJoypad->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
		{//���X�e�B�b�N����͂���Ă���

			//�ړ���ԂɕύX
			auto NewState = DBG_NEW CMoveState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (pJoypad->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		if (!pJoypad->GetLeftStick())
		{//���X�e�B�b�N����͂���Ă���

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//���X�e�B�b�N����͂���Ă���

		//������̂Ă�
		m_pPlayer->ThrowWeapon();
	}

	//�ړ�����
	m_pPlayer->InputMove();
	m_pPlayer->Move();
}

//==========================
//�I��
//==========================
void CDushState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�K�[�h��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CGuardState::CGuardState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CGuardState::~CGuardState()
{

}

//==========================
//�J�n
//==========================
void CGuardState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::GUARD);
}

//==========================
//�X�V
//==========================
void CGuardState::Update()
{

	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::GUARD);

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamageNum() >= 3)
	{//�A����3���e����
		m_pPlayer->ResetDamageNum();//��e�񐔂�������
	}

	if (pJoypad->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		if (pJoypad->GetRelease(CInputJoypad::JOYKEY_X))
		{//X�{�^���������ꂽ

			//�ړ���ԂɕύX
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}
}

//==========================
//�I��
//==========================
void CGuardState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�Ў蕐�펝���K�[�h��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CSmallWeaponGuardState::CSmallWeaponGuardState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CSmallWeaponGuardState::~CSmallWeaponGuardState()
{

}

//==========================
//�J�n
//==========================
void CSmallWeaponGuardState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);
}

//==========================
//�X�V
//==========================
void CSmallWeaponGuardState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);

	if (m_pPlayer->GetDamageNum() >= 3)
	{//�A����3���e����
		m_pPlayer->ResetDamageNum();//��e�񐔂�������
	}

	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (pJoypad->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		if (pJoypad->GetRelease(CInputJoypad::JOYKEY_X))
		{//X�{�^���������ꂽ

			//�ړ���ԂɕύX
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}
}

//==========================
//�I��
//==========================
void CSmallWeaponGuardState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�U����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAttackState::CAttackState():
	m_FlameCount(0),//�t���[����
	m_AttackStateMachine(nullptr),//�U���̏�ԊǗ�
	m_Combo(false)//�R���{����
{

}

//==========================
//�f�X�g���N�^
//==========================
CAttackState::~CAttackState()
{

}

//==========================
//�J�n
//==========================
void CAttackState::Start()
{
	m_AttackStateMachine = DBG_NEW CAttackStateMachine;

	if (!m_pPlayer->GetHaveWeapon())
	{//�v���C���[��������������Ă��Ȃ�

		auto NewState = DBG_NEW CFirstAttackState;
		ChangeAttack(NewState);
	}
	else if (!m_pPlayer->GetWeaponType())
	{//���蕐�폊��

		auto NewState = DBG_NEW CFirstBigWeaponAttack;
		ChangeAttack(NewState);
	}
	else if (m_pPlayer->GetWeaponType())
	{//�Ў蕐��
		auto NewState = DBG_NEW CFirstSmallWeaponAttack;
		ChangeAttack(NewState);
	}
}

//==========================
//�X�V
//==========================
void CAttackState::Update()
{
	//�p�b�h�̏����擾
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	m_FlameCount++;

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{
		if (m_FlameCount > INPUT_START_FLAME)
		{//���͎�t���Ԓ��ɓ���
			m_Combo = true;
			
			//�p�x��␳
			m_pPlayer->CorrectionAngle();
			return;
		}
	}

	if (m_FlameCount > INPUT_FINISH_FLAME)
	{//���͎�t���Ԃ𒴂���

		if (!m_pPlayer->GetHaveWeapon())
		{//�v���C���[��������������Ă��Ȃ�
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		else if (!m_pPlayer->GetWeaponType())
		{//���蕐�폊��
			auto NewState = DBG_NEW CBigWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		else if (m_pPlayer->GetWeaponType())
		{//�Ў蕐�폊��
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (m_AttackStateMachine != nullptr)
	{
		m_AttackStateMachine->Update();
	}

	if (m_pPlayer->GetWeaponBreak())
	{//���킪��ꂽ

		//����j�󔻒�����Z�b�g
		m_pPlayer->BreakReset();

		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CAttackState::Uninit()
{
	if (m_AttackStateMachine != nullptr)
	{
		delete m_AttackStateMachine;
		m_AttackStateMachine = nullptr;
	}

	CPlayerStateBase::Uninit();
}

//==========================
//�R���{������擾
//==========================
bool CAttackState::GetCombo()
{
	return m_Combo;
}

//==========================
//����������
//==========================
void CAttackState::ResetInfo()
{
	m_FlameCount = 0;
	m_Combo = false;
}

//==========================
//�U����ύX
//==========================
void CAttackState::ChangeAttack(CAttackPlayerStateBase* State)
{
	State->SetOwner(this);
	m_AttackStateMachine->ChangeState(State);
}

//==========================
//�U���t���[�������擾
//==========================
int CAttackState::GetFrame()
{
	return m_FlameCount;
}

//========================================================================================================
//�_���[�W��ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CDamageState::CDamageState():
	m_DmageCount(0)//�_���[�W���󂯂Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CDamageState::~CDamageState()
{

}

//==========================
//�J�n
//==========================
void CDamageState::Start()
{
	
}

//==========================
//�X�V
//==========================
void CDamageState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);

	m_DmageCount++;
	if (m_DmageCount >= DAMEGE_FLAME)
	{
		m_DmageCount = 0;
		m_pPlayer->ResetDamageNum();//��e�񐔂�������
		
		//�ҋ@��ԂɕύX
		if (m_pPlayer->GetHaveWeapon())
		{//����������Ă�

			if (m_pPlayer->GetWeaponType())
			{//�Ў�
				auto NewState = DBG_NEW CSmallWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
			else
			{//����
				auto NewState = DBG_NEW CBigWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
		}
		else
		{//����������Ȃ�
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
		}
		
		return;
	}

	if (m_pPlayer->GetDamageNum() >= 3)
	{//�A����3���e����

		m_pPlayer->SetDamage(false);

		//������я�ԂɕύX
		auto NewState = DBG_NEW CDamageBrrowState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (m_pPlayer->GetDamage())
	{//�_���[�W���󂯂�

		m_pPlayer->SetDamage(false);

		//�_���[�W��ԂɕύX
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//�I��
//==========================
void CDamageState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//�����ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CAvoidanceState::CAvoidanceState():
	m_AvoidanceCount(0)//������Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CAvoidanceState::~CAvoidanceState()
{

}

//==========================
//�J�n
//==========================
void CAvoidanceState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::AVOIDANCE_BACK);
}

//==========================
//�X�V
//==========================
void CAvoidanceState::Update()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::AVOIDANCE_BACK);

	//�_���[�W���󂯂Ă��ȏ�ԂɕύX
	m_pPlayer->SetDamage(false);

	//�ړ�����
	m_pPlayer->Avoidance();

	m_AvoidanceCount++;

	if (m_AvoidanceCount > AVOIDANCE_FLAME)
	{
		m_AvoidanceCount = 0;
		m_pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//�ړ���ԂɕύX
		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);

		return;
	}

}

//==========================
//�I��
//==========================
void CAvoidanceState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//������я�ԃN���X
//========================================================================================================

//==========================
//�R���X�g���N�^
//==========================
CDamageBrrowState::CDamageBrrowState() :
	m_DmageCount(0)//�_���[�W���󂯂Ă���̃t���[����
{

}

//==========================
//�f�X�g���N�^
//==========================
CDamageBrrowState::~CDamageBrrowState()
{

}

//==========================
//�J�n
//==========================
void CDamageBrrowState::Start()
{
	//���[�V������ݒ�
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DAMAGEBLOW);

}

//==========================
//�X�V
//==========================
void CDamageBrrowState::Update()
{
	//�ړ�����
	m_pPlayer->Move();

	m_DmageCount++;
	if (m_DmageCount >= BRROW_FLAME)
	{
		m_DmageCount = 0;
		m_pPlayer->ResetDamageNum();//��e�񐔂�������

		//�ҋ@��ԂɕύX
		if (m_pPlayer->GetHaveWeapon())
		{//����������Ă�

			if (m_pPlayer->GetWeaponType())
			{//�Ў�
				auto NewState = DBG_NEW CSmallWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
			else
			{//����
				auto NewState = DBG_NEW CBigWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
		}
		else
		{//����������Ȃ�
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
		}

		return;
	}
}

//==========================
//�I��
//==========================
void CDamageBrrowState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//==============================================================================
//���퓊����ԃN���X
//==============================================================================

//==========================
//�R���X�g���N�^
//==========================
CWeaponThrowState::CWeaponThrowState()
{

}

//==========================
//�f�X�g���N�^
//==========================
CWeaponThrowState::~CWeaponThrowState()
{

}

//==========================
//�J�n
//==========================
void CWeaponThrowState::Start()
{
	m_pPlayer->ThrowWeapon();
}

//==========================
//�X�V
//==========================
void CWeaponThrowState::Update()
{
	//�ړ���ԂɕύX
	auto NewState = DBG_NEW CMoveState;
	m_pPlayer->ChangeState(NewState);
	return;
}

//==========================
//�I��
//==========================
void CWeaponThrowState::Uninit()
{
	CPlayerStateBase::Uninit();
}