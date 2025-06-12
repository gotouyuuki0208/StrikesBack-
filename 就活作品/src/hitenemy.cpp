//==========================
// 
// ����G[hitenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "hitenemy.h"
#include "manager.h"
#include "model.h"
#include "hpgauge3D.h"

//�ÓI�����o������
const int CHitEnemy::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CHitEnemy::CHitEnemy(int nPriority):
CWeakEnemy(nPriority),//���R���X�g���N�^
m_HPGauge(nullptr)//HP�Q�[�W�̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CHitEnemy::~CHitEnemy()
{

}

//==========================
//����������
//==========================
HRESULT CHitEnemy::Init()
{
	//�����ݒ�
	CWeakEnemy::Init();

	//����U���ɐݒ�
	//SetAttackState(ATTACK_STATE::ATTACK);

	//HP�Q�[�W�𐶐�
	m_HPGauge = CHPGauge3D::Create(D3DXVECTOR3(GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42, GetParts(2)->GetMtxWorld()._43),
		D3DXVECTOR3(20.0f, 3.0f, 0.0f),
		GetLife());
	
	return S_OK;
}

//==========================
//�I������
//==========================
void  CHitEnemy::Uninit()
{
	//�I������
	CWeakEnemy::Uninit();

	if (m_HPGauge != nullptr)
	{
		m_HPGauge->Uninit();
		m_HPGauge = nullptr;
	}
}

//==========================
//�X�V����
//==========================
void CHitEnemy::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	//�X�V����
	CWeakEnemy::Update();

	if (m_HPGauge != nullptr)
	{
		m_HPGauge->SetHP(GetLife());
		m_HPGauge->SetPos({ GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42 + 20.0f, GetParts(2)->GetMtxWorld()._43 });
	}
}

//==========================
//�`�揈��
//==========================
void CHitEnemy::Draw()
{
	//�`�揈��
	CWeakEnemy::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CHitEnemy* CHitEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int wave)
{
	//�C���X�^���X����
	CHitEnemy* pHitEnemy = DBG_NEW CHitEnemy;

	//�ʒu�̐ݒ�
	pHitEnemy->SetPos(pos);

	//�����̐ݒ�
	pHitEnemy->SetLife(5);

	//�t�@�C����ǂݍ���
	pHitEnemy->LoadFile("data\\MOTION\\enemy.txt", scale);

	//�s������E�F�[�u��ݒ�
	pHitEnemy->SetActionWave(wave);

	//����������
	pHitEnemy->Init();

	//pHitEnemy->SetDamageCor();

	//���a�̐ݒ�
	pHitEnemy->SetRadius(15.0f);

	//��ނ̐ݒ�
	pHitEnemy->SetType(TYPE::ENEMY);

	//�G�̎�ނ�ݒ�
	pHitEnemy->SetEnemyType(ENEMY_TYPE::HitEnemy);

	//�����蔻�������
	//pHitEnemy->SetVisual();

	return pHitEnemy;
}