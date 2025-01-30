//==========================
// 
// �Q�[����ʂ̏���[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game.h"
#include"manager.h"
#include"fild.h"
#include"player.h"
#include"enemy.h"
#include"block.h"
#include"weapon.h"
#include"bigweapon.h"
#include"hitenemy.h"
#include"weaponenemy.h"
#include"building.h"
#include"stagechangepoint.h"
#include"jihanki.h"
#include"deliveryperson.h"
#include"smallweapon.h"
#include"bosshpgauge.h"
#include"objectMesh.h"
#include"sky.h"
#include"bicycle.h"
#include"bat.h"
#include"enemymovepoint.h"
#include"UIbg.h"
#include"opeUI.h"

//==========================
// �R���X�g���N�^
//==========================
CGame::CGame() :
m_Edit(nullptr),//�z�u�c�[�����
m_player(nullptr),//�v���C���[�̏��
m_Boss(nullptr),//�{�X�̏��
m_PlalyerHPGauge(nullptr),//�v���C���[��HP�Q�[�W�̏��
m_BossHPGauge(nullptr),//�{�X��HP�Q�[�W�̏��
m_playerlife(0)
{
	m_Edit = DBG_NEW CEdit;
}

//==========================
// �f�X�g���N�^
//==========================
CGame::~CGame()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CGame::Init()
{
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_INGAME);
	CManager::GetInstance()->GetStageManager()->StageReset();
	CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::NONE);
	//CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 2000.0f));
	//CObjectMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), 3, 3);
	//CBlock::Create(D3DXVECTOR3(0.0f, 0.0f,0.0f), D3DXVECTOR3(3.0f, 1.0f, 3.0f));
	//CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CHitEnemy::Create(D3DXVECTOR3(-50.0f, 0.0f, 500.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CHitEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 2100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CHitEnemy::Create(D3DXVECTOR3(50.0f, 0.0f, 500.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CWeaponEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CWeapon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CStageChangePoint::Create(D3DXVECTOR3(-1900.0f, 0.0f, 1200.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	//CStageChangePoint::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	//CBuilding::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CJihanki::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CDeliveryPerson::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CBigWeapon::Create(D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), "data\\MODEL\\bicycle.x");
	//CSmallWeapon::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data\\MODEL\\iron_pipe.x");
	

	//�X�e�[�W�𐶐�
	m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_PlalyerHPGauge = CPlayerHPGauge::Create(D3DXVECTOR3(10.0f, 20.0f, 0.0f), 10, 300, m_player->GetLife());
	CManager::GetInstance()->GetStageManager()->Load();

	DisplayUI();

	return S_OK;
}

//==========================
// �I������
//==========================
void CGame::Uninit()
{
	if (m_Edit != nullptr)
	{
		m_Edit->Uninit();
		delete m_Edit;
		m_Edit = nullptr;
	}

	m_player = nullptr;
	m_Boss = nullptr;
	m_PlalyerHPGauge = nullptr;
	m_BossHPGauge = nullptr;
	
	CManager::GetInstance()->GetDebug()->Reset();
	CManager::GetInstance()->GetStageManager()->StageReset();

	CObject::ReleaseAll();

	CManager::GetInstance()->GetSound()->Stop();
}

//==========================
// �X�V����
//==========================
void CGame::Update()
{

	if (m_PlalyerHPGauge != nullptr)
	{
		m_PlalyerHPGauge->SetHP(m_player->GetLife());
	}

	UseEdit();

	//�X�e�[�W�̐؂�ւ�
	ChangeStage();

#ifdef _DEBUG
	if (m_Boss != nullptr)
	{
		m_BossHPGauge->SetHP(m_Boss->GetLife());
	}

	if (!CManager::GetInstance()->GetDebug()->GetEdit())
	{//�z�u�c�[�����g�p���Ă��Ȃ�
		DebugSelect();
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
#endif

	if (CManager::GetInstance()->GetGameManager()->GetGame() != CGameManager::GAME::NONE)
	{
		//�Q�[����ʂɑJ��
		CManager::GetInstance()->GetGameManager()->SetGame(CManager::GetInstance()->GetGameManager()->GetGame());
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
}

//==========================
// �`�揈��
//==========================
void CGame::Draw()
{

}

//==========================
//�X�e�[�W�̐؂�ւ�
//==========================
void CGame::ChangeStage()
{
	if (CManager::GetInstance()->GetStageManager()->GetChange()
		&& CManager::GetInstance()->GetStageManager()->ChangeObject())
	{//�X�e�[�W���؂�ւ���Ă�Ƃ�

		//���݂̃X�e�[�W���擾
		int StageNum = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

		//�v���C���[�̈ʒu��ύX
		if (StageNum == 2)
		{
			m_player->SetPos(D3DXVECTOR3 (-900.0f, 0.0f, 300.0f));
		}
		else
		{
			m_player->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		}
		m_player->DeleteWeapon();
		m_player->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));//�v���C���[�̌�����ύX

		//�X�e�[�W�𐶐�
		CManager::GetInstance()->GetStageManager()->DeleteAll();//�S�ẴI�u�W�F�N�g���폜
		CManager::GetInstance()->GetStageManager()->Load();//�I�u�W�F�N�g��ǂݍ���
		CManager::GetInstance()->GetCamera()->Init();

		CManager::GetInstance()->GetStageManager()->ChangeReset();
	}
}

//==========================
//�f�o�b�O�̎�ނ�I��
//==========================
void CGame::DebugSelect()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F1))
	{//�v���C���[�̃f�o�b�O
		CObject::ReleaseAll();

		if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
		{
			CManager::GetInstance()->GetDebug()->Reset();
			CManager::GetInstance()->GetDebug()->StartPlayerTest();//�v���C���[�̃f�o�b�O���X�^�[�g
			CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			//CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			CBigWeapon::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), "data\\MODEL\\cone.x");
			CSmallWeapon::Create(D3DXVECTOR3(-100.0f,0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data\\MODEL\\iron_pipe.x");
			CSmallWeapon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data\\MODEL\\syokaki.x");
			CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishPlayerTest();//�v���C���[�̃f�o�b�O���I��
			Init();
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F2))
	{//�{�X�̃f�o�b�O
		CObject::ReleaseAll();

		if (!CManager::GetInstance()->GetDebug()->GetBossTest())
		{
			CManager::GetInstance()->GetDebug()->Reset();
			CManager::GetInstance()->GetDebug()->StartBossTest();//�{�X�̃f�o�b�O���X�^�[�g
			CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_Boss = CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_BossHPGauge = CBossHPGauge::Create(D3DXVECTOR3(1000.0f, 680.0f, 0.0f), 10, 100, m_Boss->GetLife());
			CBigWeapon::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), "data\\MODEL\\.x");
			CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CBuilding::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishBossTest();//�{�X�̃f�o�b�O���I��
			Init();
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F3))
	{//�퓬�̃f�o�b�O
		CObject::ReleaseAll();

		if (!CManager::GetInstance()->GetDebug()->GetBattleTest())
		{
			CManager::GetInstance()->GetDebug()->Reset();
			CManager::GetInstance()->GetDebug()->StartBattleTest();//�{�X�̃f�o�b�O���X�^�[�g
			m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_PlalyerHPGauge = CPlayerHPGauge::Create(D3DXVECTOR3(10.0f, 20.0f, 0.0f), 10, 300, m_player->GetLife());
			CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			CBicycle::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f,0.0f,0.0f));
			CBat::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishBattleTest();//�{�X�̃f�o�b�O���I��
			Init();
		}
	}
}

//==========================
//�z�u�c�[���̎g�p
//==========================
void CGame::UseEdit()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F4))
	{
		if (!CManager::GetInstance()->GetDebug()->GetEdit())
		{
			CManager::GetInstance()->GetDebug()->StartEdit();
			CObject::ReleaseAll();
			m_PlalyerHPGauge = nullptr;
			m_Edit->Uninit();

			//���݂̃X�e�[�W���擾
			int StageNum = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
			//�X�e�[�W�𐶐�
			m_Edit->Load(StageNum);

			m_Edit->Init();
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishEdit();
			CObject::ReleaseAll();
			m_Edit->Uninit();
			Init();
			
		}
		CManager::GetInstance()->GetKeyboard()->Update();

	}
	
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		m_Edit->Update();
	}
}

//==========================
//UI�\��
//==========================
void CGame::DisplayUI()
{
	for (int i = 0; i < 5; i++)
	{
		CUIBg::Create(D3DXVECTOR3(1100.0f, 30.0f + (i * 40.0f), 0.0f));
	}
	COpeUI::Create(D3DXVECTOR3(1150.0f, 30.0f, 0.0f), D3DXVECTOR3(100.0f, 20.0f, 0.0f), "data\\TEXTURE\\dush.png");
	COpeUI::Create(D3DXVECTOR3(1130.0f, 70.0f, 0.0f), D3DXVECTOR3(70.0f, 20.0f, 0.0f), "data\\TEXTURE\\camera.png");
	COpeUI::Create(D3DXVECTOR3(1140.0f, 110.0f, 0.0f), D3DXVECTOR3(60.0f, 20.0f, 0.0f), "data\\TEXTURE\\attack.png");
	COpeUI::Create(D3DXVECTOR3(1100.0f, 150.0f, 0.0f), D3DXVECTOR3(100.0f, 20.0f, 0.0f), "data\\TEXTURE\\grab.png");
	COpeUI::Create(D3DXVECTOR3(1130.0f, 190.0f, 0.0f), D3DXVECTOR3(70.0f, 20.0f, 0.0f), "data\\TEXTURE\\guard.png");
}