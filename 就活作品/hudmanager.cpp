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