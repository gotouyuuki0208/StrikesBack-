//==========================
// 
// �v���C���[����[player.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "player.h"
#include "manager.h"
#include "fild.h"
#include "block.h"
#include "bigweapon.h"
#include "smallweapon.h"
#include "boss.h"
#include "jihanki.h"
#include "deliveryperson.h"
#include "effect.h"
#include "particle.h"

//�ÓI�����o������
const int CPlayer::PRIORITY = 1;//�`�揇
const int CPlayer::MAX_LIFE = 25;//�����̍ő�l
const int CPlayer::INPUT_START_FLAME = 24;//���͎�t�J�n�t���[����
const int CPlayer::INPUT_FINISH_FLAME = 60;//���͎�t�I���t���[����
const int CPlayer::RESET_FLAME = 54;//�R���{�̏�񃊃Z�b�g�t���[������
const float CPlayer::MOVE_VALUE = 3.0f;//�ړ�
const float CPlayer::DASH_VALUE = 7.0f;//�_�b�V��
const float CPlayer::JUMP_VALUE = 10.0f;//�W�����v
const float CPlayer::GRAVITY_VALUE = 0.7f;//�d��
const float CPlayer::INERTIA_VALUE = 0.5f;//����
const float CPlayer::ROT_VALUE = 1.57f;//����
const float CPlayer::CHARA_WIDTH = 10.0f;//�L�����N�^�[��X�T�C�Y
const float CPlayer::CHARA_HEIGHT = 10.0f;//�L�����N�^�[��Y�T�C�Y

//==========================
//�R���X�g���N�^
//==========================
CPlayer::CPlayer(int nPriority) :
CCharacter(nPriority),//���N���X�̃R���X�g���N�^
m_grab(false),//�͂ݔ���
m_weapon(nullptr), //�������Ă镐��
//m_GrabEnemy(nullptr),//�͂�ł�G
m_boss(nullptr),//�{�X�̏����擾
m_FlameCount(0),//�t���[�����̃J�E���g�p
m_ComboStack{},//�U���R���{�̃X�^�b�N
m_StackIdx(0),//�X�^�b�N��TOP�̈ʒu
m_Attack(false),//�U������
m_CountAttack(0),//�R���{���ɍU���𓖂Ă���
m_testdeth(false),
m_DamageCount(0),
m_RecoveryItemStock(0),//�A�C�e���̃X�g�b�N��
m_WeaponType(false),//����̎��
m_VisualCor(false),//�����蔻��̐F�̐ݒ�
m_Avoidance(0),//����t���[��
LeftStickAngle(0.0f)//���X�e�B�b�N�̊p�x
{
	SetLife(MAX_LIFE);//�����̐ݒ�
	SetComboList();//�R���{���X�g�̐���
}

//==========================
//�f�X�g���N�^
//==========================
CPlayer::~CPlayer()
{

}

//==========================
//����������
//==========================
HRESULT CPlayer::Init()
{
	//�����ݒ�
	CCharacter::Init();
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	return S_OK;
}

//==========================
//�I������
//==========================
void  CPlayer::Uninit()
{
	if (m_weapon != nullptr)
	{
		m_weapon = nullptr;
	}

	/*if (m_GrabEnemy != nullptr)
	{
		m_GrabEnemy = nullptr;
	}*/
	
	if (m_boss != nullptr)
	{
		m_boss = nullptr;
	}

	//�I������
	CCharacter::Uninit();
}

//==========================
//�X�V����
//==========================
void CPlayer::Update()
{
	if (CManager::GetInstance()->GetStageManager()->GetChange())
	{//�X�e�[�W�J�ڒ�
		return;
	}

	if (!CManager::GetInstance()->GetDebug()->GetBossTest())
	{
		//���͏���
		Input();
	}

	//�������
	Avoidance();

	//�ړ�����
	Move();

	if (GetState() == STATE::ATTACK)
	{
		//�U������
		Attack();
	}

	//�n�ʂƂ̓����蔻��
	CollisionFild();

	//m_VisualCor = false;

	//�G�Ƃ̓����蔻��
	CollisionEnemy();

	ColisionDelevery();

	//���[�V�����̍X�V
	MotionUpdate();

	//�X�V����
	CCharacter::Update();

	if (GetDamage())
	{
		m_DamageCount++;
		if (m_DamageCount >= 54)
		{
			m_DamageCount = 0;
			SetDamage(false);
		}
	}

	//if (m_GrabEnemy != nullptr)
	//{//�G��͂�ł���Ƃ�
	//	GrabAttack();
	//}

	//�J�����Ǐ]
	CManager::GetInstance()->GetCamera()->Move(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z));

	//�������������蔻��̐ݒ�
	//m_Visual->SetPos(GetPos());
	//m_Visual->Update();

	if (!m_VisualCor)
	{
		//m_Visual->SetCorNomal();
	}
	else
	{
		//m_Visual->SetCorCollision();
	}
}

//==========================
//�`�揈��
//==========================
void CPlayer::Draw()
{
	if (!m_testdeth)
	{
		//�`�揈��
		CCharacter::Draw();

		//m_Visual->Draw();
	}
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CPlayer* pPlayer = DBG_NEW CPlayer;

	//�ʒu�̐ݒ�
	pPlayer->SetPos(pos);

	//����������
	pPlayer->Init();

	//�t�@�C����ǂݍ���
	//pPlayer->LoadFile("data\\MOTION\\motion_enemy_hit.txt", scale);
	pPlayer->LoadFile("data\\MOTION\\motion_player_15.txt", scale);

	//���a�̐ݒ�
	pPlayer->SetRadius(15.0f);

	//�^�C�v�ݒ�
	pPlayer->SetType(TYPE::PLAYER);

	//�����蔻�����
	//pPlayer->m_Visual = CCollisionVisual::Create(pPlayer->GetPos(), pPlayer->GetRadius());
	
	return pPlayer;
}

//==========================
//���[�V�����̍X�V
//==========================
void CPlayer::MotionUpdate()
{
	//�p�[�c�̐��l�̌v�Z
	CalParts();
	if (m_weapon != nullptr)
	{//����������Ă�
		m_weapon->SetPos(CalMotionPos(15));
		m_weapon->SetRot(CalMotionRot(15));

	}

	//���[�V�����J�E���^�[��i�߂�
	MotionCountUpdate();

	if (ExceedMaxFlame())
	{//���[�V�����̃J�E���^�[���Đ��t���[���𒴂����Ƃ�

		if (m_weapon != nullptr)
		{//����������Ă�
			KeepFirstPos(m_weapon->GetPos(), 15);
			KeepFirstRot(m_weapon->GetRot(), 15);
		}
	}

	//���[�V�����̏����X�V
	UpdateMotionInfo();

}

//==========================
//���͏���
//==========================
void CPlayer::Input()
{
	if (GetDamage())
	{
		return;
	}

	//�U���̓��͏���
	InputAttack();

	if (GetState() == STATE::NEUTRAL
		|| GetState() == STATE::MOVE)
	{
		//�ړ��̓��͏���
		InputMove();
	}
}

//==========================
//�U���֌W�̓��͏���
//==========================
void CPlayer::InputAttack()
{
	if (GetState() != STATE::GUARD)
	{
		if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J)
			|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_Y))
		{//�U��
			SetState(STATE::ATTACK);
		}

		if (m_weapon == nullptr)
		{//����������Ă��Ȃ��Ƃ�
			if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_O)
				|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
			{//������E��
				PickUpWeapon();
			}
		}
		else if (m_weapon != nullptr)
		{
			if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_P)
				|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
			{//����������

				if (CManager::GetInstance()->GetJoypad()->Connection())
				{//�p�b�h���ڑ�����Ă���
					if (CManager::GetInstance()->GetJoypad()->GetLeftStick())
					{//���X�e�B�b�N�����͂���Ă���
						ThrowWeapon();
						return;
					}
				}
				ReleaseWeapon();
			}
		}
	}
	
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_B)
		|| CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_X))
	{
		if ((GetMotion() == MOTION_TYPE::MOVE
			|| GetMotion() == MOTION_TYPE::NEUTRAL
			|| GetMotion() == MOTION_TYPE::SMALLWEAPONNEUTRAL)
			&& GetState() != STATE::ATTACK)
		{
			Guard();
		}
	}
	if (CManager::GetInstance()->GetKeyboard()->GetRelease(DIK_B)
		|| CManager::GetInstance()->GetJoypad()->GetRelease(CInputJoypad::JOYKEY_X))
	{
		SetState(STATE::NEUTRAL);
	}

	if (CManager::GetInstance()->GetJoypad()->GetRelease(CInputJoypad::JOYKEY_A))
	{
		SetState(STATE::AVOIDANCE);
	}
}

//==========================
//�K�[�h����
//==========================
void CPlayer::Guard()
{
	if (m_weapon != nullptr&&!m_WeaponType)
	{//���蕐��������Ă���Ƃ�
		return;
	}

	if (m_WeaponType)
	{//�Ў蕐��������Ă���Ƃ�
		SetWeaponMotion(MOTION_TYPE::SMALLWEAPONGUARD);
	}
	else
	{//�f��̂Ƃ�
		SetMotion(MOTION_TYPE::GUARD);
	}

	SetState(STATE::GUARD);
}

//==========================
//�ړ��̓��͏���
//==========================
void CPlayer::InputMove()
{
	float move = MOVE_VALUE;
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (m_weapon == nullptr
		|| (m_weapon != nullptr && m_WeaponType))
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT)
			|| CManager::GetInstance()->GetJoypad()->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
		{//�_�b�V��

			move = DASH_VALUE;
		}
	}

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{//���Ɉړ�

		//�ړ��l�̐ݒ�
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI)* move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI) * move));
		
		//�����̐ݒ�
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * D3DX_PI-3.14f, GetRotMove().z));

		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI - 3.14f, GetRot().z));

		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&&m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//�ړ����[�V����
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//�ړ����[�V����
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//�ړ����[�V����
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{//���Ɉړ�

		//�ړ��l�̐ݒ�
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI-(D3DX_PI/2)) * move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI - (D3DX_PI / 2)) * move));

		//�����̐ݒ�
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * D3DX_PI + D3DX_PI / 2, GetRotMove().z));
		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI + D3DX_PI / 2, GetRot().z));
		
		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&& m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//�ړ����[�V����
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//�ړ����[�V����
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//�ړ����[�V����
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{//��O�Ɉړ�
		SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI) * move,
			GetMove().y,
			GetMove().z - cosf(CameraRot * D3DX_PI) * move));

		//�����̐ݒ�
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * 0.0f, GetRotMove().z));
		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI, GetRot().z));

		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&& m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//�ړ����[�V����
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//�ړ����[�V����
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//�ړ����[�V����
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{//�E�Ɉړ�
		SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI - (D3DX_PI / 2)) * move,
			GetMove().y,
			GetMove().z - cosf(CameraRot * D3DX_PI - (D3DX_PI / 2)) * move));

		//�����̐ݒ�
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * D3DX_PI - D3DX_PI / 2, GetRotMove().z));
		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI - D3DX_PI / 2, GetRot().z));

		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&& m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//�ړ����[�V����
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//�ړ����[�V����
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//�ړ����[�V����
		}
	}
	else
	{//�ړ����Ă��Ȃ�
		//if (GetMotion() == MOTION_TYPE::MOVE
		//	|| GetMotion() == MOTION_TYPE::DUSH)
		//{
		//	if (m_weapon!=nullptr)
		//	{
		//		if (m_WeaponType)
		//		{
		//			SetMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//�ҋ@���[�V����
		//		}
		//		else
		//		{
		//			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//�ҋ@���[�V����
		//		}
		//	}
		//	else
		//	{
		//		SetMotion(MOTION_TYPE::NEUTRAL);//�ҋ@���[�V����
		//	}
		//}

		//SetState(STATE::NEUTRAL);
	}

	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		if (!CManager::GetInstance()->GetJoypad()->GetLeftStick())
		{//���X�e�B�b�N����͂��Ă��Ȃ�

			//��~���̃��[�V�����ɐݒ�
			if (m_weapon != nullptr)
			{
				if (m_WeaponType)
				{
					SetWeaponMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//�ҋ@���[�V����
				}
				else
				{
					SetWeaponMotion(MOTION_TYPE::WEAPONNEUTRAL);//�ҋ@���[�V����
				}
			}
			else
			{
				SetMotion(MOTION_TYPE::NEUTRAL);//�ҋ@���[�V����
			}
			return;
		}

		//���X�e�B�b�N�̊p�x���擾
		LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();
		
		//�ړ��l�̐ݒ�
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI+ LeftStickAngle) * move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * move));
		
		//�����̐ݒ�
		SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot* D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));

		//���[�V�����̐ݒ�
		if (move == MOVE_VALUE)
		{
			if (m_weapon!=nullptr)
			{
				if (!m_WeaponType
					&& m_weapon->GetGrab())
				{
					SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//�ړ����[�V����
				}
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//�ړ����[�V����
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//�ړ����[�V����
		}
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_N))
	{
		Recovery();
	}

	//���̃��[�V������ۑ�
	SetOldMotion(GetMotion());
}

//==========================
//�ړ�����
//==========================
void CPlayer::Move()
{
	//�O��̈ʒu��ۑ�
	SetPosOld(GetPos());
	
	//�����Əd��
	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * INERTIA_VALUE,
		GetMove().y,
		GetMove().z += (0 - GetMove().z) * INERTIA_VALUE));

	
	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x += (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y,
		GetDamegeBlow().z += (0 - GetDamegeBlow().z) * 0.25f));
	
	//������ю��̈ړ�
	SetMove(D3DXVECTOR3(GetMove().x + GetDamegeBlow().x,
		GetMove().y+ GetDamegeBlow().y,
		GetMove().z + GetDamegeBlow().z));

	//�ʒu�̐ݒ�
	SetPos(GetPos() + GetMove());
}

//==========================
//���
//==========================
void CPlayer::Avoidance()
{
	if (GetState() != STATE::AVOIDANCE)
	{
		return;
	}

	m_Avoidance++;

	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		//�J�����̌������擾
		float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

		//�ړ��l�̐ݒ�
		SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI + LeftStickAngle) * 7.0f,
			GetMove().y,
			GetMove().z - cosf(CameraRot * D3DX_PI + LeftStickAngle) * 7.0f));

		//�����̐ݒ�
		SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
	}

	SetMotion(MOTION_TYPE::AVOIDANCE_BACK);

	if (m_Avoidance == 10)
	{
		m_Avoidance = 0;
		SetState(STATE::NEUTRAL);
	}
}

//==========================
//�U������
//==========================
void CPlayer::Attack()
{
	
	if (GetDamage())
	{//�_���[�W���󂯂Ă���
		return;
	}

	if (GetOldMotion() == GetMotion())
	{//�O��̃��[�V�����ƍ��̃��[�V����������

		//���̃��[�V������ۑ�
		SetOldMotion(GetMotion());

		if (m_weapon != nullptr)
		{
			SetWeaponMotion(Pop());
		}
		else
		{
			//�U�����[�V�����ɕύX
			SetMotion(Pop());
		}
	}

	if (m_FlameCount > 10 && m_FlameCount < 24)
	{
		//���̋@�ւ̓����蔻��
		CollisionJihankiAttack();

		//�z�B���ւ̓����蔻��
		ColisionDeleveryAttack();
		
		//�G�ւ̍U������
		if (m_weapon==nullptr)
		{//����������Ă��Ȃ�
			CollisionHitEnemy();
		}
		else
		{
			CollisionWeaponEnemy();
		}

		CorrectionAngle();
	}
	else
	{
		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (GetPartsExistence(i))
			{
				//GetParts(i)->VisualDelete();
			}
		}
	}

	m_FlameCount++;

	if (m_FlameCount > INPUT_START_FLAME && m_FlameCount <= INPUT_FINISH_FLAME && m_StackIdx>0)
	{
		if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J)
			|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_Y))
		{
			//���[�V�������Đ�
			if (m_weapon != nullptr)
			{
				SetWeaponMotion(Pop());
			}
			else
			{
				//�U�����[�V�����ɕύX
				SetMotion(Pop());
			}

			CorrectionAngle();

			m_FlameCount = 0;
			m_Attack = false;
			
		}
	}
	else if (m_FlameCount > INPUT_FINISH_FLAME || (m_FlameCount > RESET_FLAME && m_StackIdx <= 0))
	{
		//���̃��[�V������ۑ�
		SetOldMotion(GetMotion());

		//�ʏ��ԂɕύX
		SetState(STATE::NEUTRAL);

		if (m_weapon!=nullptr)
		{//����������Ă�Ƃ�

			if (m_WeaponType)
			{//�Ў蕐��̂Ƃ�
				SetWeaponMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//�ҋ@���[�V����
			}
			else
			{//���蕐��̂Ƃ�
				SetWeaponMotion(MOTION_TYPE::WEAPONNEUTRAL);//�ҋ@���[�V����
			}
		}

		//�R���{�̃X�^�b�N�����Z�b�g
		ResetStak();

		m_FlameCount = 0;

		m_Attack = false;

		m_CountAttack = 0;

		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (GetPartsExistence(i))
			{
				//GetParts(i)->VisualDelete();
			}
		}
		
	}
}

//==========================
//�{�X���擾
//==========================
void CPlayer::GetBoss(CEnemy* boss)
{
	if (m_boss != nullptr
		&&boss!=nullptr)
	{
		return;
	}

	m_boss = boss;
}

//==========================
//���폊������
//==========================
bool CPlayer::GetHaveWeapon()
{
	if (m_weapon == nullptr)
	{
		return false;
	}

	return true;
}

//==========================
//���폊������
//==========================
void CPlayer::DeleteWeapon()
{
	m_weapon = nullptr;
	SetComboList();
}

//==========================
//�R���{���X�g�̐���
//==========================
void CPlayer::SetComboList()
{
	if (m_weapon == nullptr)
	{//����������Ă��Ȃ�
		m_ComboList[0] = MOTION_TYPE::ATTACK;
		m_ComboList[1] = MOTION_TYPE::ATTACK2;
		m_ComboList[2] = MOTION_TYPE::ATTACK3;
	}
	else
	{//����������Ă���
		if (m_WeaponType)
		{//�Ў蕐��
			m_ComboList[0] = MOTION_TYPE::SMALLWEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::SMALLWEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::SMALLWEAPONATTACK3;

		}
		else
		{//���蕐��
			m_ComboList[0] = MOTION_TYPE::WEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::WEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::WEAPONATTACK3;
		}
	}

	ResetStak();//�X�^�b�N�̃��Z�b�g
}

//==========================
//�_���[�W����
//==========================
void CPlayer::Damage(int damage)
{
	if (GetState() != STATE::GUARD)
	{
		SetLife(GetLife()- damage);
		SetMotion(MOTION_TYPE::DAMAGE);
		m_DamageCount = 0;
		SetDamage(true);
		
		//�R���{�̃X�^�b�N�����Z�b�g
		ResetStak();
		m_FlameCount = 0;
		m_Attack = false;
		m_CountAttack = 0;
	}
	
	if (GetState() == STATE::GUARD)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_GUARD);

	}

	if (GetLife() <= 0)
	{
		m_testdeth = true;
		if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::NONE)
		{
			CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::OVER);
		}
	}
}

//==========================
//�A�C�e���̐��𑝂₷
//==========================
void CPlayer::AddItem()
{
	m_RecoveryItemStock++;
}

//==========================
//���͎�t���Ԃ��擾
//==========================
int CPlayer::GetInputFrame()
{
	return m_FlameCount;
}

//==========================
//�͂ݍU���̏���
//==========================
void CPlayer::GrabAttack()
{
	/*m_FlameCount++;

	if (m_FlameCount > 3 && m_FlameCount <=31)
	{
		m_GrabEnemy->BeGrabbed(GetParts(5)->GetMtxWorld());
	}
	else if(m_FlameCount>31)
	{
		ReleaseEnemy();
		m_FlameCount = 0;
	}*/
}

//==========================
//�n�ʂƂ̓����蔻��
//==========================
void CPlayer::CollisionFild()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CFild::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::FILD)
		{//�I�u�W�F�N�g���t�B�[���h�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		CFild* pFild = (CFild*)pObj;

		if (GetPosOld().y >= pFild->GetPos().y - pFild->GetSize().y
			&& GetPos().y < pFild->GetPos().y + pFild->GetSize().y
			&& GetPos().x <= pFild->GetPos().x + pFild->GetSize().x
			&& GetPos().x >= pFild->GetPos().x - pFild->GetSize().x
			&& GetPos().z <= pFild->GetPos().z + pFild->GetSize().z
			&& GetPos().z >= pFild->GetPos().z - pFild->GetSize().z)
		{//�Փ˂��Ă���
			SetMove(D3DXVECTOR3(GetMove().x, 0.0f, GetMove().z));
			SetPos(D3DXVECTOR3(GetPos().x, pFild->GetPos().y+0.1f, GetPos().z));
		}

		pObj = CObject::GetObj(pObj, CFild::PRIORITY);
	}
}

//==========================
//�G�Ƃ̓����蔻��
//==========================
void CPlayer::CollisionEnemy()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CBoss::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CBoss* pBoss = (CBoss*)pObj;

		bool Colision = ColisionSphere(GetPos(),
			pBoss->GetPos(),
			GetRadius(),
			pBoss->GetRadius());

		if (Colision)
		{
			//m_VisualCor = true;

			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����x�N�g��
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���K�������x�N�g��

			//�����x�N�g�����Z�o
			Vector.x = VectorCalculation(pBoss->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pBoss->GetPos().z, GetPos().z);

			//�x�N�g���𐳋K��
			D3DXVec3Normalize(&NormalizeVec, &Vector);
			
			//�ʒu��ύX
			pBoss->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pBoss->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * floor((GetRadius() + pBoss->GetRadius())),
				GetPos().y,
				GetPos().z + NormalizeVec.z * floor((GetRadius() + pBoss->GetRadius()))));
		}

		pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
	}
}

//==========================
//�G������Ƃ��̓����蔻��
//==========================
void CPlayer::CollisionHitEnemy()
{
	if (m_StackIdx != 1)
	{
		//GetParts(8)->CreateVisual(D3DXVECTOR3(GetPartsMtx(8)._41, GetPartsMtx(8)._42, GetPartsMtx(8)._43), 20.0f);
	}
	else
	{
		//GetParts(5)->CreateVisual(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43), 15.0f);
	}

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision;

		if (m_StackIdx != 1)
		{
			Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(8)._41 + 5.0f, GetPartsMtx(8)._42, GetPartsMtx(8)._43),
				D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
				20.0f,
				15.0f);
		}
		else
		{
			Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41 + 5.0f, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
				D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
				15.0f,
				15.0f);
		}

		//pEnemy->DamageVisual(1, 15.0f);

		if (Colision && !m_Attack)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			if (m_StackIdx != 1)
			{
				//GetParts(8)->GetVisual()->SetCorCollision();

				for (int i = 0; i < 3; i++)
				{
					CEffect::Create(D3DXVECTOR3(GetPartsMtx(8)._41, GetPartsMtx(8)._42, GetPartsMtx(8)._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f),15.0f,15.0f);
				}
			}
			else
			{
				//GetParts(5)->GetVisual()->SetCorCollision();

				for (int i = 0; i < 3; i++)
				{
					CEffect::Create(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 15.0f, 15.0f);
				}
			}
			

			//�_���[�W����
			pEnemy->Damage(1);
			m_Attack = true;
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
			m_CountAttack++;
			if (m_StackIdx <= 0 && m_CountAttack >= 3)
			{
				if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
				{
					//�������
					pEnemy->DamegeBlow(GetPos());

				}
			}
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//�G�𕐊�ŉ���Ƃ��̓����蔻��
//==========================
void CPlayer::CollisionWeaponEnemy()
{
	//GetParts(15)->CreateVisual(D3DXVECTOR3(GetPartsMtx(8)._41, GetPartsMtx(8)._42, GetPartsMtx(8)._43), 30.0f);

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
			30.0f,
			30.0f);

		//pEnemy->DamageVisual(1, 30.0f);

		if (Colision && !m_Attack)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);

			for (int i = 0; i < 20; i++)
			{
				CParticle::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
					D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
					10,
					1.0f,
					1.0f,
					10.0f);

			}

			for (int i = 0; i < 3; i++)
			{
				CEffect::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 15.0f, 15.0f);
			}

			//GetParts(15)->GetVisual()->SetCorCollision();
			if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::SMALL)
			{
				pEnemy->Damage(2);
			}
			else
			{
				pEnemy->Damage(3);
			}
			m_Attack = true;
			m_weapon->SubDurability();//����̑ϋv�l�����炷
			if (m_StackIdx <= 0)
			{
				if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
				{
					//�������
					pEnemy->DamegeBlow(GetPos());
				}
			}

			if (m_weapon->GetDurability() <= 0)
			{//�ϋv�l���Ȃ��Ȃ����Ƃ�
				DeleteParts(15);
				SetMotion(MOTION_TYPE::NEUTRAL);//�ҋ@���[�V����

				//������폜����
				CManager::GetInstance()->GetStageManager()->DeleteObj(*m_weapon);
				m_weapon->Uninit();
				m_weapon = nullptr;
				m_WeaponType = false;

				SetComboList();//�R���{���X�g�̐���
				break;
			}
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//���̋@�ɍU�����̓����蔻��
//==========================
void CPlayer::CollisionJihankiAttack()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CJihanki::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::JIHANKI)
		{//�I�u�W�F�N�g�����̋@�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
			continue;
		}

		CJihanki* pJihan = (CJihanki*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
			D3DXVECTOR3(pJihan->GetPos().x, pJihan->GetPos().y+20.0f, pJihan->GetPos().z),
			10.0f,
			30.0f);

		//pJihan->DamageVisual(D3DXVECTOR3(pJihan->GetPos().x, pJihan->GetPos().y + 30.0f, pJihan->GetPos().z),
			//30.0f);

		if (Colision && !m_Attack)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			//�_���[�W����
			pJihan->Damage(1);
			m_Attack = true;
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
			m_CountAttack++;
		}

		pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
	}
}

//==========================
//�z�B���̍U�������蔻��
//==========================
void CPlayer::ColisionDeleveryAttack()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CDeliveryPerson::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::DELIVERY)
		{//�I�u�W�F�N�g���z�B���ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		CDeliveryPerson* pDelivery = (CDeliveryPerson*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
			D3DXVECTOR3(pDelivery->GetPartsMtx(1)._41, pDelivery->GetPartsMtx(1)._42, pDelivery->GetPartsMtx(1)._43),
			10.0f,
			30.0f);

		if (Colision && !m_Attack)
		{
			//�_���[�W����
			pDelivery->Damage(1);
			m_Attack = true;
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
			m_CountAttack++;
		}

		pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
	}
}

//==========================
//�z�B���̓����蔻��
//==========================
void CPlayer::ColisionDelevery()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CDeliveryPerson::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::DELIVERY)
		{//�I�u�W�F�N�g���z�B���ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		CDeliveryPerson* pDelivery = (CDeliveryPerson*)pObj;

		bool Colision = ColisionSphere(GetPos(),
			pDelivery->GetPos(),
			GetRadius(),
			pDelivery->GetRadius());

		pDelivery->Movable();//�ړ��\�ɂ���

		if (Colision)
		{
			//m_VisualCor = true;

			pDelivery->Immovable();//�ړ��s�\�ɂ���
		}

		pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
	}
}

//==========================
//�G��͂ޏ���
//==========================
void CPlayer::GrabEnemy()
{
	/*if (m_GrabEnemy != nullptr)
	{
		return;
	}*/

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool colision = ColisionSphere(GetPos(), pEnemy->GetPos(), 10.0f, 30.0f);

		if (colision)
		{
			//SetMotion(MOTION_TYPE::GRABATTACK);
			//pEnemy->SetMotion(MOTION_TYPE::GRAB);
			//pEnemy->SetMotion(MOTION_TYPE::GRAB);
			//pEnemy->BeGrabbed(GetParts(5)->GetMtxWorld());
			//m_GrabEnemy = pEnemy;
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//������E��
//==========================
void CPlayer::PickUpWeapon()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CWeapon::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::WEAPON)
		{//�I�u�W�F�N�g������ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		CWeapon* pWeapon = (CWeapon*)pObj;

		if (pWeapon->GetGrab())
		{//���킪�߂܂�Ă���
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		bool colision = ColisionSphere(GetPos(), pWeapon->GetPos(), GetRadius(), pWeapon->GetRadius());

		if (colision)
		{
			

			if (pWeapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
			{
				pWeapon->SetParent(GetParts(5));
				pWeapon->SetPos(D3DXVECTOR3(10.0f, -2.0f, -5.0f));
				pWeapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetWeaponMotion(MOTION_TYPE::WEAPONNEUTRAL);//�ҋ@���[�V����(���펝��)
				m_WeaponType = false;
			}
			else
			{
				pWeapon->SetParent(GetParts(8));
				pWeapon->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
				pWeapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetWeaponMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//�ҋ@���[�V����(���펝��)
				m_WeaponType = true;
			}
			
			pWeapon->GrabCharacter();//�͂܂ꂽ��Ԃɂ���
			m_weapon = pWeapon;//�͂񂾕���̏���ۑ�
			if (m_boss != nullptr)
			{//�{�X������Ƃ�
				CBoss* pBoss = dynamic_cast<CBoss*>(m_boss);
				pBoss->GrabChangeWeapon(pWeapon);
			}
			
			SetComboList();//�R���{���X�g�̐���
			break;
		}

		pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
	}
}

//==========================
//����������
//==========================
void CPlayer::ReleaseWeapon()
{
	if (m_weapon == nullptr)
	{//����������Ă��Ȃ�
		return;
	}

	//�v���C���[��������̈ʒu���擾
	D3DXVECTOR3 pos = D3DXVECTOR3(m_weapon->GetMtxWorld()._41, 0.0f, m_weapon->GetMtxWorld()._43);
	m_weapon->SetParent(nullptr);
	m_weapon->ReleseCharacter(pos);//��������
	m_weapon->CorrectInfo();
	m_weapon = nullptr;//����̏����폜

	SetMotion(MOTION_TYPE::NEUTRAL);//�ҋ@���[�V����
	SetComboList();//�R���{���X�g�̐���
}

//==========================
//�G�����
//==========================
void CPlayer::ReleaseEnemy()
{
	/*if (m_GrabEnemy != nullptr)
	{
		m_GrabEnemy->ReleaseGrab(D3DXVECTOR3(GetParts(5)->GetRot().x, GetRot().y+D3DX_PI, 0.0f));
		m_GrabEnemy->Damage(10);
		m_GrabEnemy = nullptr;
	}*/
}

//==========================
//�f�[�^�̒ǉ�
//==========================
void CPlayer::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//�f�[�^�̎��o��
//==========================
CMotionModel::MOTION_TYPE CPlayer::Pop()
{
	if (m_StackIdx <= 0)
	{
		if (m_weapon != nullptr)
		{//����������Ă�Ƃ�
			if (m_WeaponType)
			{//�Ў蕐��
				return MOTION_TYPE::SMALLWEAPONNEUTRAL;//�ҋ@���[�V����
			}
			else
			{
				return MOTION_TYPE::WEAPONNEUTRAL;//�ҋ@���[�V����
			}
		}
		else
		{//����������Ă��Ȃ�
			return MOTION_TYPE::NEUTRAL;
		}
	}

	return m_ComboStack[--m_StackIdx];

}

//==========================
//�X�^�b�N�̏���߂�
//==========================
void CPlayer::ResetStak()
{
	m_StackIdx = 0;
	for (int i = 2; i >= 0; i--)
	{
		Push(m_ComboList[i]);
	}
}

//==========================
//�񕜃A�C�e�����g�p
//==========================
void CPlayer::Recovery()
{
	if (m_RecoveryItemStock <= 0)
	{
		return;
	}

	m_RecoveryItemStock--;//�A�C�e���������炷

	SetLife(GetLife() + 2);//��
}

//==========================
//�p�x�̕␳
//==========================
void CPlayer::CorrectionAngle()
{
	float distance = 0.0f;
	CEnemy* pNearEnemy = nullptr;

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		float newdistance = (pEnemy->GetPos().x - GetPos().x) * (pEnemy->GetPos().x - GetPos().x) +
			(pEnemy->GetPos().z - GetPos().z) * (pEnemy->GetPos().z - GetPos().z);

		if (distance == 0.0f || newdistance <= distance)
		{
			distance = newdistance;//������ۑ�
			pNearEnemy = pEnemy;//�߂��G�̏���ۑ�
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}

	if (pNearEnemy == nullptr)
	{
		if (CManager::GetInstance()->GetJoypad()->Connection())
		{//�p�b�h���ڑ�����Ă���Ƃ�

			//�J�����̌������擾
			float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

			//�ړ��l�̐ݒ�
			SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f,
				GetMove().y,
				GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f));

			//�����̐ݒ�
			SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
		}

		return;
	}

	bool colision = ColisionSphere(GetPos(), pNearEnemy->GetPos(), GetRadius() * 3, pNearEnemy->GetRadius());

	if (colision)
	{
		//�i�ފp�x���v�Z
		float Angle = atan2f(pNearEnemy->GetPos().x - GetPos().x, pNearEnemy->GetPos().z - GetPos().z);

		//������ݒ�
		SetRot(D3DXVECTOR3(GetRot().x, Angle + D3DX_PI, GetRot().z));
	}
	else
	{
		if (CManager::GetInstance()->GetJoypad()->Connection())
		{//�p�b�h���ڑ�����Ă���Ƃ�

			//�J�����̌������擾
			float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

			//�ړ��l�̐ݒ�
			SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f,
				GetMove().y,
				GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f));

			//�����̐ݒ�
			SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
		}
	}
}

//==========================
//���폊�����̃��[�V������ݒ�
//==========================
void CPlayer::SetWeaponMotion(CMotionModel::MOTION_TYPE motion)
{
	if (GetMotion() == motion)
	{
		return;
	}

	SetMotion(motion);

	if (m_weapon != nullptr)
	{
		KeepFirstPos(m_weapon->GetPos(),15);
		KeepFirstRot(m_weapon->GetRot(),15);
	}
}

//==========================
//����𓊂���
//==========================
void CPlayer::ThrowWeapon()
{
	if (m_weapon == nullptr)
	{//����������Ă��Ȃ�
		return;
	}
	
	m_weapon->ThrowAngle(this);
	m_weapon->SetParent(nullptr);
	//m_weapon->CorrectInfo();
	m_weapon->SetPos(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43));
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	//���X�e�B�b�N�̊p�x���擾
	LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();

	//�ړ��l�̐ݒ�
	m_weapon->SetMove(D3DXVECTOR3(m_weapon->GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * 30.0f,
		m_weapon->GetMove().y,
		m_weapon->GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * 30.0f));

	m_weapon = nullptr;//����̏����폜

	SetMotion(MOTION_TYPE::NEUTRAL);//�ҋ@���[�V����
	SetComboList();//�R���{���X�g�̐���
}