//==========================
// 
// ���[�V�������郂�f���̕`��T���v��[sample_MotionModel.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_MotionModel.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CSampleMotionModel::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSampleMotionModel::CSampleMotionModel(int nPriority) :CMotionModel(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSampleMotionModel::~CSampleMotionModel()
{

}

//==========================
//����������
//==========================
HRESULT CSampleMotionModel::Init()
{
	//�����ݒ�
	CMotionModel::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CSampleMotionModel::Uninit()
{
	//�I������
	CMotionModel::Uninit();
}

//==========================
//�X�V����
//==========================
void CSampleMotionModel::Update()
{
	//�X�V����
	CMotionModel::Update();
}

//==========================
//�`�揈��
//==========================
void CSampleMotionModel::Draw()
{
	//�`�揈��
	CMotionModel::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSampleMotionModel* CSampleMotionModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CSampleMotionModel* pSampleMotionModel = DBG_NEW CSampleMotionModel;

	//�ʒu�̐ݒ�
	pSampleMotionModel->SetPos(pos);

	//����������
	pSampleMotionModel->Init();

	//���a�̐ݒ�
	pSampleMotionModel->SetRadius(15.0f);

	//�t�@�C����ǂݍ���
	pSampleMotionModel->LoadFile("data\\MOTION\\motion_player.txt", scale);

	return pSampleMotionModel;
}