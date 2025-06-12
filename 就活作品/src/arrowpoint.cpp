//==========================
// 
// ���\�����w�������ʒu[arrowpoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "arrowpoint.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CArrowPoint::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CArrowPoint::CArrowPoint(int nPriority) :
	CFild(nPriority),
	m_player(nullptr)
{

}

//==========================
//�f�X�g���N�^
//==========================
CArrowPoint::~CArrowPoint()
{

}

//==========================
//����������
//==========================
HRESULT CArrowPoint::Init()
{
	//�����ݒ�
	CObject3D::Init();

	//�v���C���[�̏����擾
	GetPlayerinfo();

	return S_OK;
}

//==========================
//�I������
//==========================
void CArrowPoint::Uninit()
{
	if (m_player != nullptr)
	{
		m_player = nullptr;
	}

	//�I������
	CObject3D::Uninit();
}

//==========================
//�X�V����
//==========================
void CArrowPoint::Update()
{
	//�X�V����
	CObject3D::Update();

	//�v���C���[�����邩����
	//CollisionPlayer();
}

//==========================
//�`�揈��
//==========================
void CArrowPoint::Draw()
{
	//�`�揈��
	CObject3D::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CArrowPoint* CArrowPoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CArrowPoint* pArrowPoint = DBG_NEW CArrowPoint;

	//�ʒu�̐ݒ�
	pArrowPoint->SetPos(pos);

	//�傫���̐ݒ�
	pArrowPoint->SetSize(size);

	//�F�̐ݒ�
	pArrowPoint->SetCol({ 1.0f,1.0f,1.0f,1.0f });

	//����������
	pArrowPoint->Init();

	//�^�C�v�ݒ�
	pArrowPoint->SetType(TYPE::FILD);
	pArrowPoint->SetFild(FILDTYPE::ARROWPOINT);

	return pArrowPoint;
}

//==========================
//�v���C���[�̏����擾
//==========================
void CArrowPoint::GetPlayerinfo()
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
//�v���C���[���������Ă邩����
//==========================
void CArrowPoint::CollisionPlayer()
{
	if (m_player->GetPos().x <= GetPos().x + GetSize().x
		&& m_player->GetPos().x >= GetPos().x - GetSize().x
		&& m_player->GetPos().z <= GetPos().z + GetSize().z
		&& m_player->GetPos().z >= GetPos().z - GetSize().z)
	{//���Ƀv���C���[������

		//�E�F�[�u��i�߂�
		CManager::GetInstance()->GetGameManager()->AddWave();

		//�I������
		Uninit();
	}
}