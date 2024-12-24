//==========================
// 
// �A�E�g�Q�[���̃L�����N�^�[[outgamecharactar.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "outgamecharactar.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int COutGameChara::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
COutGameChara::COutGameChara(int nPriority) :CMotionModel(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
COutGameChara::~COutGameChara()
{

}

//==========================
//����������
//==========================
HRESULT COutGameChara::Init()
{
	//�����ݒ�
	CMotionModel::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  COutGameChara::Uninit()
{
	//�I������
	CMotionModel::Uninit();
}

//==========================
//�X�V����
//==========================
void COutGameChara::Update()
{
	//�X�V����
	CMotionModel::Update();
	Motion();

	if (CManager::GetInstance()->GetScene()->GetScene() == CScene::MODE::RESULT)
	{
		SetMotion(MOTION_TYPE::MOVE);
	}
}

//==========================
//�`�揈��
//==========================
void COutGameChara::Draw()
{
	//�`�揈��
	CMotionModel::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
COutGameChara* COutGameChara::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	COutGameChara* pOutGameChara = DBG_NEW COutGameChara;

	//�ʒu�̐ݒ�
	pOutGameChara->SetPos(pos);

	//����������
	pOutGameChara->Init();

	//�����̐ݒ�
	pOutGameChara->SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0));

	//���a�̐ݒ�
	pOutGameChara->SetRadius(15.0f);

	//�t�@�C����ǂݍ���
	pOutGameChara->LoadFile("data\\MOTION\\outgame_player.txt", scale);

	return pOutGameChara;
}