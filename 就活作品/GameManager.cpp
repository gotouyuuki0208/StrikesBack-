//==========================
// 
// �Q�[���S�̊Ǘ�[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"

//==========================
//�R���X�g���N�^
//==========================
CGameManager::CGameManager():
GameClear(GAME::NONE),
m_player(nullptr),//�v���C���[�̏��
m_Direction(false),//���o�̔���
m_boss(nullptr),
m_count(0),
m_StageChamge(false)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGameManager::~CGameManager()
{

}

//==========================
//����������
//==========================
void CGameManager::Init()
{
	SetGame(GAME::NONE);//�N���A����������
	GetPlayerInfo();//�v���C���[�̏����擾
}

//==========================
//�I������
//==========================
void CGameManager::Uninit()
{
	if (m_player != nullptr)
	{
		m_player = nullptr;
	}
}

//==========================
//�Q�[���̃N���A����ݒ�
//==========================
void CGameManager::SetGame(GAME game)
{
	GameClear = game;
}

//==========================
//�Q�[���̃N���A�����擾
//==========================
CGameManager::GAME CGameManager::GetGame()
{
	return GameClear;
}

//==========================
//�J�������Ǐ]����Ώۂ�ݒ�
//==========================
void CGameManager::SetCamera()
{
	if (!m_Direction)
	{
		
		//�J�����Ǐ]
		CManager::GetInstance()->GetCamera()->Move(m_player->GetPos());
	}
	else
	{
		if (!CManager::GetInstance()->GetStageManager()->GetChange())
		{
			m_count++;
			if (m_count > 60)
			{
				StartBossBattle();
			}
			else
			{
				CManager::GetInstance()->GetCamera()->Move(m_boss->GetPos());
			}
		}
	}
}

//==========================

//==========================
void CGameManager::a()
{
	//�v���C���[��HP�Q�[�W�̍X�V
	CManager::GetInstance()->GetStageManager()->HPGaugeUpdate();

	//�J�����Ǐ]����Ώۂ�ݒ�
	SetCamera();
	
	//�X�e�[�W�̐؂�ւ�
	CManager::GetInstance()->GetStageManager()->ChangeStage();
}

//==========================
//���o�̐ݒ�
//==========================
void CGameManager::SetDirection()
{
	m_Direction = !m_Direction;
}

//==========================
//���o�����擾
//==========================
bool CGameManager::GetDirection()
{
	return m_Direction;
}

//==========================
//�؂�ւ�蔻����擾
//==========================
bool CGameManager::GetChange()
{
	return m_StageChamge;
}

//==========================
//�؂�ւ�蔻������Z�b�g
//==========================
void CGameManager::SetChange()
{
	m_StageChamge = !m_StageChamge;
}

//==========================
//�{�X��J�n���̉��o
//==========================
void CGameManager::StartBossBattle()
{
	if (m_boss == nullptr)
	{
		return;
	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	D3DXVECTOR3 pos = m_player->GetPos();

	pCamera->SetTargetPos(m_player->GetPos());
	pCamera->TarGetMove();

	if (pCamera->GetPosV().z <= m_player->GetPos().z + (pCamera->Z_DISTANCE+1.0f))
	{
		SetDirection();
		D3DXVECTOR3 pos = m_player->GetPos();
		int a = 0;
	}
}

//==========================
//�v���C���[�̏����擾
//==========================
void CGameManager::GetPlayerInfo()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CPlayer::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::PLAYER)
		{//�I�u�W�F�N�g���v���C���[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		CPlayer* pPlayer = (CPlayer*)pObj;

		//�v���C���[�̏����擾
		m_player = pPlayer;

		break;
	}
}

//==========================
//�{�X�̏����擾
//==========================
void CGameManager::GetBossInfo()
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
		{//�I�u�W�F�N�g���G�l�~�[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE::BOSS)
		{//�I�u�W�F�N�g���{�X�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CBoss* pBoss = (CBoss*)pObj;

		//�{�X�̏����擾
		m_boss = pBoss;

		break;
	}
}