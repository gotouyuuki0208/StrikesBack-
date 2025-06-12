//==========================
// 
// �E�F�[�u�ŏ������[wavewall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"wavewall.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CWaveWall::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CWaveWall::CWaveWall(int nPriority) :
	CBuilding(nPriority),
	m_MyWave(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CWaveWall::~CWaveWall()
{

}

//==========================
//����������
//==========================
HRESULT CWaveWall::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CWaveWall::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CWaveWall::Update()
{
	//�X�V����
	CObjectX::Update();

	int rot = static_cast<int>(GetRot().y);

	if (rot == 1 || rot == -1)
	{
		//�v���C���[�Ƃ̓����蔻��
		ColisionPlayerWide();
	}
	else
	{
		//�v���C���[�Ƃ̓����蔻��
		ColisionPlayer();
	}

	//���݂̃E�F�[�u���擾
	int NowWave = CManager::GetInstance()->GetGameManager()->GetWave();

	if (m_MyWave < NowWave)
	{//�����̃E�F�[�u����

		//�������폜����
		CManager::GetInstance()->GetStageManager()->DeleteObj(*this);

		//�폜
		Uninit();
	}
	
}

//==========================
//�`�揈��
//==========================
void CWaveWall::Draw()
{
	//if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		//�`�揈��
		CBuilding::Draw();
	}
}

//==========================
//�I�u�W�F�N�g����
//==========================
CWaveWall* CWaveWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int wave)
{
	//�C���X�^���X����
	CWaveWall* pConveni = DBG_NEW CWaveWall;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\wall.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::WAVEWALL);

	//�����̃E�F�[�u��ۑ�
	pConveni->m_MyWave = wave;

	return pConveni;
}

//==========================
//�����̃E�F�[�u���擾
//==========================
int CWaveWall::GetMyWave()
{
	return m_MyWave;
}