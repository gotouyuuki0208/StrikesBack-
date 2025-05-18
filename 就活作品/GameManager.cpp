//==========================
// 
// �Q�[���S�̊Ǘ�[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"
#include"direction.h"

//==========================
//�R���X�g���N�^
//==========================
CGameManager::CGameManager():
m_GameClear(GAME::NONE),
m_player(nullptr),//�v���C���[�̏��
m_Direction(false),//���o�̔���
m_count(0),//�t���[�����J�E���g�p
m_PlayGame(false),//�Q�[����V�ׂ邩����(false:�V�ׂȂ� true:�V�ׂ�)
m_GameStartTutorial(false),//�Q�[���̊J�n���̑��������\������������
m_direction(nullptr)//���o�̏��
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

	//�X�e�[�W�����폜
	CManager::GetInstance()->GetStageManager()->StageReset();

	//�I�u�W�F�N�g������
	CObject::ReleaseAll();

	//BGM���~
	CManager::GetInstance()->GetSound()->Stop();
}

//==========================
//�X�V����
//==========================
void CGameManager::Update()
{
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
	CManager::GetInstance()->GetGameManager()->StartTutorial();

	//�`���[�g���A���\��������
	CManager::GetInstance()->GetGameManager()->EndTutorial();
}

//==========================
//�J�����̐ݒ�
//==========================
void CGameManager::SetCamera()
{
	if (!m_Direction)
	{
		//�J�����Ǐ]
		CManager::GetInstance()->GetCamera()->Move({ m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z });
	}
	else
	{
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