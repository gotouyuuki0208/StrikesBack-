//==========================
// 
// �Q�[���S�̊Ǘ�[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"
#include"direction.h"
#include"hitenemy.h"
#include"enemy.h"

//==========================
//�R���X�g���N�^
//==========================
CGameManager::CGameManager():
m_GameClear(GAME::NONE),
m_player(nullptr),
m_Direction(false),
m_count(0),
m_PlayGame(false),
m_GameStartTutorial(false),
m_direction(nullptr),
m_CameraLookOn(false),
m_NowWave(0),
m_ActiveEnemy(0),
m_EnemyBeing(false)
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
	//BGM�̍Đ�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_INGAME);

	//�X�e�[�W����������
	CManager::GetInstance()->GetStageManager()->StageReset();

	//�X�e�[�W�𐶐�
	CManager::GetInstance()->GetStageManager()->Load();
	
	//�N���A����������
	SetGame(GAME::NONE);

	//�v���C���[�̏����擾
	GetPlayerInfo();

	//�E�F�[�u2�ōs��
	//Enemy = CHitEnemy::Create({ 0.0f,0.0f ,700.0f }, { 1.5f,1.5f ,1.5f }, 2);

	//�E�F�[�u1�ōs��
	//CHitEnemy::Create({ 0.0f,0.0f ,500.0f }, { 1.5f,1.5f ,1.5f }, 1);

	//���o�̃C���X�^���X����
	m_direction = DBG_NEW CDirection;
}

//==========================
//�I������
//==========================
void CGameManager::Uninit()
{
	if (m_player != nullptr)
	{//�v���C���[�̏�������
		m_player = nullptr;
	}

	if (m_direction != nullptr)
	{//���o�̏�������
		delete m_direction;
		m_direction = nullptr;
	}

	m_count = 0;
	m_PlayGame = false;
	m_GameStartTutorial = false;
	m_NowWave = 1;

	//�X�e�[�W�����폜
	CManager::GetInstance()->GetStageManager()->StageReset();

	//�I�u�W�F�N�g������
	CObject::ReleaseAll();

	//BGM���~
	CManager::GetInstance()->GetSound()->Stop();

	//HUD�Ǘ��N���X�̏���������
	CManager::GetInstance()->GetHudManager()->Reset();

	//�`���[�g���A���Ǘ��N���X�̏���������
	CManager::GetInstance()->GetTutorial()->Reset();
}

//==========================
//�X�V����
//==========================
void CGameManager::Update()
{
	//�E�F�[�u�̍X�V
	//WaveUpdate();

	//�`���[�g���A���̐ݒ�
	SetTutorial();

	//�J�����̐ݒ�
	SetCamera();

	//�X�e�[�W��ύX
	CManager::GetInstance()->GetStageManager()->ChangeStage();
}

//==========================
//�`���[�g���A���̐ݒ�
//==========================
void CGameManager::SetTutorial()
{
	//�Q�[���J�n���̃`���[�g���A����\��
	StartTutorial();

	//�`���[�g���A���\��������
	EndTutorial();
}

//==========================
//�J�����̐ݒ�
//==========================
void CGameManager::SetCamera()
{
	//�J�����̏����擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	CInputJoypad* pPad = CManager::GetInstance()->GetJoypad();

	if (pPad->GetTrigger(CInputJoypad::JOYKEY::JOYKEY_RIGHT_THUMB))
	{//�J������؂�ւ�
		m_CameraLookOn = !m_CameraLookOn;
	}

	if (!m_Direction)
	{//���o������Ȃ�

		if (!m_CameraLookOn)
		{//���b�N�I�����Ȃ�

			//�J�����Ǐ]
			pCamera->Move({ m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z });
		}
		else
		{//���b�N�I������

			//�G�����b�N�I��
			CmeraLookOn();
		}
	}
	else
	{//���o��

		//�{�X��̊J�n���o
		StartBossBattle();
	}
}

//==========================
//�Q�[���̃N���A����ݒ�
//==========================
void CGameManager::SetGame(GAME game)
{
	m_GameClear = game;
}

//==========================
//�Q�[���̃N���A�����擾
//==========================
CGameManager::GAME CGameManager::GetGame()
{
	return m_GameClear;
}

//==========================
//�Q�[���J�n���̑�������\��
//==========================
void CGameManager::StartTutorial()
{
	if (m_GameStartTutorial)
	{//���łɐ�������
		return;
	}

	//�F�̓����x���擾
	float Transparency = CManager::GetInstance()->GetFade()->GetTransparency();

	if (Transparency > 0.0f)
	{//�V�[���؂�ւ��̃t�F�[�h���I����ĂȂ�

		return;
	}

	//�t���[�����𐔂���
	m_count++;

	if (m_count <= 30)
	{//1�b�o�߂��Ă��Ȃ�
		return;
	}

	//�t���O��ύX
	m_GameStartTutorial = true;

	//�`���[�g���A���\��
	CManager::GetInstance()->GetTutorial()->ActionTutorialDisplay();
}

//==========================
//��������\���̏I��
//==========================
void CGameManager::EndTutorial()
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
	{//�{�^���������ꂽ

		//�`���[�g���A���\��������
		CManager::GetInstance()->GetTutorial()->TutorialDelete();
	}
}

//==========================
//�V�ׂ��Ԃ��擾
//==========================
bool CGameManager::GetPlayGame()
{
	return m_PlayGame;
}

//==========================
//�L�����N�^�[����̔����ύX
//==========================
void CGameManager::ChangePlayGame(bool play)
{
	m_PlayGame = play;
}

//==========================
//���o���ɕύX
//==========================
void CGameManager::SetDirection()
{
	//���o���ɕύX
	m_Direction = true;

	//�{�X�̏����擾����
	m_direction->GetBossInfo();
}
//==========================
//���o�����擾
//==========================
bool CGameManager::GetDirection()
{
	return m_Direction;
}

//==========================
//�{�X��J�n���̉��o
//==========================
void CGameManager::StartBossBattle()
{
	//�J�����̏����擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//�v���C���[�̈ʒu
	D3DXVECTOR3 pos = m_player->GetPos();

	//�J�������ŏI�I�Ɉړ�����ʒu��ݒ�
	pCamera->SetTargetPos(m_player->GetPos(),3000);

	//����s�ɕύX
	m_PlayGame = false;

	//���o�̍X�V
	m_direction->Update();

	if (m_direction->GetEnd())
	{//�I������

		//���o������Ȃ��ݒ�ɕύX
		m_Direction = false;

		//����\�ɕύX
		m_PlayGame = true;
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
//�J�����̃��b�N�I��
//==========================
void CGameManager::CmeraLookOn()
{
	if (Enemy == nullptr)
	{
		return;
	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//�J�����Ǐ]
	pCamera->LockOn({ m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z }
	, { Enemy->GetPos().x, Enemy->GetPos().y, Enemy->GetPos().z });

}

//==========================
//���݂̃E�F�[�u���擾
//==========================
int CGameManager::GetWave()
{
	return m_NowWave;
}

//==========================
//�E�F�[�u�𑝂₷
//==========================
void CGameManager::AddWave()
{
	m_NowWave++;
}

//==========================
//�s�����Ă�G�̐��𑝂₷
//==========================
void CGameManager::AddActiveEnemy()
{
	m_ActiveEnemy++;
}

//==========================
//�s�����Ă�G�̐������炷
//==========================
void CGameManager::SubActiveEnemy()
{
	m_ActiveEnemy--;
}

//==========================
//�s�����̓G�̐����擾
//==========================
int CGameManager::GetActiveEnemy()
{
	return m_ActiveEnemy;
}

//==========================
//�E�F�[�u�̍X�V
//==========================
void CGameManager::WaveUpdate()
{
	//�X�e�[�W�}�l�[�W���[�̏��
	CStageManager* pStageManager = CManager::GetInstance()->GetStageManager();

	//�G�����邩����
	JudgeEnemyBeing();

	if (!m_PlayGame|| !m_EnemyBeing|| pStageManager->GetChange())
	{//�s���ł��Ȃ����G�����Ȃ����X�e�[�W�؂�ւ�蒆

		return;
	}

	if (m_ActiveEnemy <= 0)
	{//�s�����Ă�G�����Ȃ�

		m_NowWave++;
	}
}

//==========================
//�G�����݂��Ă邩����
//==========================
void CGameManager::JudgeEnemyBeing()
{
	m_EnemyBeing = false;

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
		{//�I�u�W�F�N�g���G�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		m_EnemyBeing = true;

		break;
	}
}
