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
#include "bigweapon.h"
#include "smallweapon.h"
#include "boss.h"
#include "jihanki.h"
#include "effect.h"
#include "particle.h"
#include "guardeffect.h"
#include "weapon.h"
#include "enemy.h"
#include "weakenemy.h"
#include"collision.h"
//�ÓI�����o������
const int CPlayer::PRIORITY = 1;//�`�揇
const int CPlayer::MAX_LIFE = 25;//�����̍ő�l
const float CPlayer::MOVE_VALUE = 3.0f;//�ړ�
const float CPlayer::DASH_VALUE = 7.0f;//�_�b�V��
const float CPlayer::JUMP_VALUE = 10.0f;//�W�����v
const float CPlayer::GRAVITY_VALUE = 0.7f;//�d��
const float CPlayer::INERTIA_VALUE = 0.5f;//����
const float CPlayer::ROT_VALUE = 1.57f;//����
const float CPlayer::CHARA_WIDTH = 10.0f;//�L�����N�^�[��X�T�C�Y
const float CPlayer::CHARA_HEIGHT = 10.0f;//�L�����N�^�[��Y�T�C�Y
const float CPlayer::AVOIDANCE_VALUE = 10.0f;//����̈ړ��l
//==========================
//�R���X�g���N�^
//==========================
CPlayer::CPlayer(int nPriority) :
CCharacter(nPriority),//���N���X�̃R���X�g���N�^
m_grab(false),//�͂ݔ���
m_weapon(nullptr), //�������Ă镐��
m_boss(nullptr),//�{�X�̏����擾
m_RecoveryItemStock(0),//�A�C�e���̃X�g�b�N��
m_WeaponType(false),//����̎��
m_VisualCor(false),//�����蔻��̐F�̐ݒ�
LeftStickAngle(0.0f),//���X�e�B�b�N�̊p�x
m_StateMachine(nullptr),//��ԊǗ�
m_DamageNum(0),//�_���[�W�񐔃J�E���g
m_Attack(false),//�U�����q�b�g����������
m_breakweapon(false)//���킪��ꂽ������
{
	SetLife(MAX_LIFE);//�����̐ݒ�
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
	
	//HP�Q�[�W�̐���
	CManager::GetInstance()->GetHudManager()->CreatePlayerHPGauge();

	//�����̕ύX
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//��ԊǗ��N���X�̍쐬
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CNeutralState;
	ChangeState(NewState);

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
	
	if (m_boss != nullptr)
	{
		m_boss = nullptr;
	}

	if (m_StateMachine != nullptr)
	{
		delete m_StateMachine;
		m_StateMachine = nullptr;
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
	{//�Q�[�����V�ׂȂ����
		return;
	}

	if (!CManager::GetInstance()->GetGameManager()->GetPlayGame())
	{//�Q�[�����V�ׂȂ����
		return;
	}

	//�X�e�[�g�̍X�V
	m_StateMachine->Update();

	//�n�ʂƂ̓����蔻��
	CollisionFild();

	//�G�Ƃ̓����蔻��
	CollisionEnemy();

	//���[�V�����̍X�V
	MotionUpdate();

	//�X�V����
	CCharacter::Update();

	//HP�Q�[�W�̍X�V
	CManager::GetInstance()->GetHudManager()->ChangePlayerHP(GetLife());
}

//==========================
//�`�揈��
//==========================
void CPlayer::Draw()
{
	//�`�揈��
	CCharacter::Draw();
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
	pPlayer->LoadFile("data\\MOTION\\motion_player_15.txt", scale);

	//���a�̐ݒ�
	pPlayer->SetRadius(15.0f);

	//�^�C�v�ݒ�
	pPlayer->SetType(TYPE::PLAYER);
	
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
//��Ԃ�ύX
//==========================
void CPlayer::ChangeState(CPlayerStateBase* NewState)
{
	NewState->SetOwner(this);
	m_StateMachine->ChangeState(NewState);
}

//==========================
//�ړ��̓��͏���
//==========================
void CPlayer::InputMove()
{
	float move = MOVE_VALUE;
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (CManager::GetInstance()->GetJoypad()->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
	{//�_�b�V��

		//���݂̏�Ԃ��擾
		auto State = m_StateMachine->GetState();

		if (typeid(*State) != typeid(CBigWeaponMoveState))
		{//���蕐��������ĂȂ�

			move = DASH_VALUE;
		}
	}

	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		//���X�e�B�b�N�̊p�x���擾
		LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();

		//�ړ��l�̐ݒ�
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * move));

		//�����̐ݒ�
		D3DXVECTOR3 rot = GetRot();

		SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
	}

}

//==========================
//�U�����̈ړ�����
//==========================
void CPlayer::AttackMove()
{
	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//�p�b�h���ڑ�����Ă���Ƃ�

		//���X�e�B�b�N�̊p�x���擾
		LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();

		//�ړ��l�̐ݒ�
		SetMove(D3DXVECTOR3(GetMove().x + sinf(GetRot().y + D3DX_PI) * MOVE_VALUE,
			GetMove().y,
			GetMove().z + cosf(GetRot().y + D3DX_PI) * MOVE_VALUE));
	}
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

	
	//������ю��̈ړ�
	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x += (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y,
		GetDamegeBlow().z += (0 - GetDamegeBlow().z) * 0.25f));
	
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
	if (!CManager::GetInstance()->GetJoypad()->Connection())
	{//�p�b�h���ڑ�����Ă��Ȃ��Ƃ�
		return;
	}

	//�J�����̌������擾
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	//�ړ��l�̐ݒ�
	SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI + LeftStickAngle) * AVOIDANCE_VALUE,
		GetMove().y,
		GetMove().z - cosf(CameraRot * D3DX_PI + LeftStickAngle) * AVOIDANCE_VALUE));

	//�����̐ݒ�
	SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));

	//�ʒu�̐ݒ�
	SetPos(GetPos() + GetMove());
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
//����������Ă��Ȃ���ԂɕύX
//==========================
void CPlayer::DeleteWeapon()
{
	m_weapon = nullptr;
}

//==========================
//�_���[�W����
//==========================
void CPlayer::Damage()
{
	SetDamage(true);

	if (GetLife() <= 0)
	{
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

		bool Colision = Collision::Sphere(GetPos(),
			pBoss->GetPos(),
			GetRadius(),
			pBoss->GetRadius());

		if (Colision)
		{

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
void CPlayer::HitEnemy(int PartsNum)
{

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

		//�G�l�~�[�N���X�ɃL���X�g
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		//����̒��S�ʒu��ݒ�
		D3DXVECTOR3 mypos = { GetParts(PartsNum)->GetMtxWorld()._41,GetParts(PartsNum)->GetMtxWorld()._42,GetParts(PartsNum)->GetMtxWorld()._43 };
		D3DXVECTOR3 pos = { pEnemy->GetParts(1)->GetMtxWorld()._41,pEnemy->GetParts(1)->GetMtxWorld()._42,pEnemy->GetParts(1)->GetMtxWorld()._43 };

		bool Colision = Collision::Sphere(mypos, pos,10.0f, 10.0f);

		if (Colision)
		{//�U�����������Ă���

			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			//�_���[�W����
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::BOSS)
			{//�G���{�X

				CBoss* pBoss = dynamic_cast<CBoss*>(pObj);

				pBoss->hit(GetPos(), 1,GetMotion());
			}
			else
			{//�G���G

				CWeakEnemy* pWeakEnemy = dynamic_cast<CWeakEnemy*>(pObj);

				//�_���[�W����
				pWeakEnemy->Hit(GetPos(), 1, GetMotion());
			}
			
			//�J�����h��
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//�G�𕐊�ŉ���Ƃ��̓����蔻��
//==========================
void CPlayer::WeaponHitEnemy()
{
	if (m_weapon == nullptr)
	{//���킪�Ȃ��Ƃ�
		return;
	}

	//�U�����q�b�g�����������
	m_Attack = false;

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

		bool Colision = Collision::Sphere(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
			30.0f,
			30.0f);

		if (!Colision)
		{//�������Ă��Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::SMALL)
		{//�Ў蕐��̂Ƃ�

			//�_���[�W����
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::BOSS)
			{//�G���{�X

				CBoss* pBoss = dynamic_cast<CBoss*>(pObj);

				//�_���[�W����
				m_Attack = pBoss->hit(GetPos(), 2, GetMotion());
			}
			else
			{//�G���G

				CWeakEnemy* pWeakEnemy = dynamic_cast<CWeakEnemy*>(pObj);

				//�_���[�W����
				pWeakEnemy->Hit(GetPos(), 1, GetMotion());
			}
		}
		else
		{//���蕐��̂Ƃ�

			//�_���[�W����
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::BOSS)
			{//�G���{�X

				CBoss* pBoss = dynamic_cast<CBoss*>(pObj);

				//�_���[�W����
				m_Attack = pBoss->hit(GetPos(), 2, GetMotion());
			}
			else
			{//�G���G

				CWeakEnemy* pWeakEnemy = dynamic_cast<CWeakEnemy*>(pObj);

				//�_���[�W����
				m_Attack = pWeakEnemy->Hit(GetPos(), 2, GetMotion());
			}
		}

		if (m_Attack)
		{//�G�Ƀ_���[�W��������

			//SE���Đ�
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);

			for (int i = 0; i < 20; i++)
			{//�p�[�e�B�N���̐���
				CParticle::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
					D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
					10,
					1.0f,
					1.0f,
					10.0f);

			}

			for (int i = 0; i < 3; i++)
			{//�G�t�F�N�g�̕\��
				CEffect::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 15.0f, 15.0f);
			}

			//����̑ϋv�����炷
			WeaponDamage();

			if (m_breakweapon)
			{
				break;
			}

			m_Attack = false;
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

		bool Colision = Collision::Sphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
			D3DXVECTOR3(pJihan->GetPos().x, pJihan->GetPos().y+20.0f, pJihan->GetPos().z),
			10.0f,
			30.0f);

		if (Colision )
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			//�_���[�W����
			pJihan->Damage(1);
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
		}

		pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
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

		bool colision = Collision::Sphere(GetPos(), pWeapon->GetPos(), GetRadius(), pWeapon->GetRadius());

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

			m_breakweapon = false;

			break;
		}

		pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
	}
}

//==========================
//����̎�ނ��擾
//==========================
bool CPlayer::GetWeaponType()
{
	return m_WeaponType;
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

	bool colision = Collision::Sphere(GetPos(), pNearEnemy->GetPos(), GetRadius() * 3, pNearEnemy->GetRadius());

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
}

//==========================
//��e�񐔏�����
//==========================
void CPlayer::ResetDamageNum()
{
	m_DamageNum = 0;
}

//==========================
//��e�񐔎擾
//==========================
int CPlayer::GetDamageNum()
{
	return m_DamageNum;
}

//==========================
//�f��U����e����
//==========================
void CPlayer::hit(D3DXVECTOR3 pos, int damage)
{
	if (m_DamageNum >= 3)
	{
		return;
	}

	//��e�񐔂𑝂₷
	m_DamageNum++;

	//�_���[�W�̐��l���擾
	int DamageNum = damage;

	//���݂̏�Ԃ��擾
	auto State = m_StateMachine->GetState();

	if (typeid(*State) == typeid(CGuardState))
	{//�K�[�h��Ԃ̎�

		//�_���[�W�����炷
		DamageNum /= 2;
	}
	else if (typeid(*State) == typeid(CSmallWeaponGuardState))
	{//����K�[�h��Ԃ̎�

		//�_���[�W�����炷
		DamageNum /= 2;
		
		//����̑ϋv�����炷
		WeaponDamage();

		if (m_breakweapon)
		{//���킪��ꂽ

			//�ҋ@��ԂɕύX
			auto NewState = DBG_NEW CNeutralState;
			ChangeState(NewState);
		}
	}

	//���킪���ĂȂ�������
	State = m_StateMachine->GetState();

	//���C�t�����炷
	int Life = GetLife();
	SetLife(Life -= DamageNum);

	if (typeid(*State) != typeid(CGuardState)
		&& typeid(*State) != typeid(CSmallWeaponGuardState))
	{//�K�[�h��Ԃł͂Ȃ�
		Damage();

		if (m_DamageNum >= 3)
		{//3���e���Ă���
			DamegeBlow(pos);
		}
	}
	else
	{
		//�G�t�F�N�g��\������ʒu
		D3DXVECTOR3 Effectpos = { GetParts(5)->GetMtxWorld()._41,GetParts(5)->GetMtxWorld()._42,GetParts(5)->GetMtxWorld()._43 };

		//�K�[�h�G�t�F�N�g
		CGuardEffect::Create(Effectpos, GetRot());
	}
}

//==========================
//����̑ϋv�����炷
//==========================
void CPlayer::WeaponDamage()
{
	//����̑ϋv�l�����炷
	m_weapon->SubDurability();

	if (m_weapon->GetDurability() <= 0)
	{//�ϋv�l���Ȃ��Ȃ����Ƃ�
		DeleteParts(15);

		//������폜����
		CManager::GetInstance()->GetStageManager()->DeleteObj(*m_weapon);
		m_weapon->Uninit();
		m_weapon = nullptr;
		m_WeaponType = false;

		//���킪��ꂽ����ɕύX
		m_breakweapon = true;
	}
}

//==========================
//���C�t�̉�
//==========================
void CPlayer::RecoveryLife()
{
	//���C�t����
	SetLife(GetLife() + 5);

	if (GetLife() >= MAX_LIFE)
	{
		SetLife(MAX_LIFE);
	}
}

//==========================
//���킪��ꂽ���擾
//==========================
bool CPlayer::GetWeaponBreak()
{
	return m_breakweapon;
}

//==========================
//����j�󔻒�����Z�b�g
//==========================
void CPlayer::BreakReset()
{
	m_breakweapon = false;
}

//==========================
//�X�e�[�W�ύX���̃X�e�[�g�̕ύX
//==========================
void CPlayer::StageChangeState()
{
	auto NewState = DBG_NEW CNeutralState;
	ChangeState(NewState);
}