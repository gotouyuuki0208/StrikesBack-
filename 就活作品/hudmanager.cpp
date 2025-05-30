//==========================
// 
// HUD�Ǘ�[hudmanager.h]
// Author Yuki Goto
//
//==========================
#include"hudmanager.h"
#include"manager.h"
#include"playerhpgauge.h"
#include"bosshpgauge.h"
#include"UIbg.h"
#include"opeUI.h"

//==========================
//�R���X�g���N�^
//==========================
CHudManager::CHudManager():
	m_pPlayerHPGauge(nullptr),//�v���C���[��HP�Q�[�W
	m_pBossHPGauge(nullptr)//�{�X��HP�Q�[�W
{

}

//==========================
//�f�X�g���N�^
//==========================
CHudManager::~CHudManager()
{

}

//==========================
//�v���C���[HP���ύX���ꂽ
//==========================
void CHudManager::ChangePlayerHP(int hp)
{
	if (m_pPlayerHPGauge == nullptr)
	{
		return;
	}

	//HP�Q�[�W��HP�̐��l��n��
	m_pPlayerHPGauge->SetHP(hp);
}

//==========================
//�{�X��HP���ύX���ꂽ
//==========================
void CHudManager::ChangeBossHP(int hp)
{
	if (m_pBossHPGauge == nullptr)
	{
		return;
	}

	//HP�Q�[�W��HP�̐��l��n��
	m_pBossHPGauge->SetHP(hp);
}

//==========================
//�v���C���[�̃Q�[�W�𐶐�
//==========================
void CHudManager::CreatePlayerHPGauge()
{
	if (m_pPlayerHPGauge != nullptr)
	{
		return;
	}

	//�v���C���[��HP�Q�[�W�𐶐�
	m_pPlayerHPGauge = CPlayerHPGauge::Create({ 10.0f, 20.0f, 0.0f },//�ʒu
		10,//�c��
		300);//����

}

//==========================
//�{�X�̃Q�[�W�𐶐�
//==========================
void CHudManager::CreateBossHPGauge()
{
	if (m_pBossHPGauge != nullptr)
	{
		return;
	}

	//�{�X��HP�Q�[�W�𐶐�
	m_pBossHPGauge = CBossHPGauge::Create({ 1200.0f, 680.0f, 0.0f },//�ʒu
		10,//�c��
		300);//����
}

//==========================
//���Z�b�g
//==========================
void CHudManager::Reset()
{
	if (m_pBossHPGauge != nullptr)
	{
		m_pBossHPGauge = nullptr;
	}

	if (m_pPlayerHPGauge != nullptr)
	{
		m_pPlayerHPGauge = nullptr;
	}
}

//==========================
//UI�\��
//==========================
void CHudManager::DisplayUI()
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