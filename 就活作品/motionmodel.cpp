//==========================
// 
// ���[�V�������郂�f���̕`�揈��[motionmodel.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "motionmodel.h"
#include "manager.h"

//�ÓI�����o������
const int CMotionModel::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CMotionModel::CMotionModel(int nPriority) :CObjectgame(nPriority)
{
	m_Shadow = nullptr;
	m_PartsNum = 0;//���f���p�[�c��ǂݍ��񂾉�

	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_PartsList[i] = nullptr;
		m_FirstMotion[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_FirstMotion[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < MAX_MOTION; i++)
	{
		m_MotionInfo[i].Loop = 0;
		m_MotionInfo[i].nKeyNum = 0;
		for (int n = 0; n < MAX_PARTS; n++)
		{
			m_MotionInfo[i].aKeySet[n].nFrame = 0;
			for (int j = 0; j < MAX_PARTS; j++)
			{
				m_MotionInfo[i].aKeySet[n].aKey[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_MotionInfo[i].aKeySet[n].aKey[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	m_nCurKey = 0;//���݂̃L�[�ԍ�
	m_nCntMotion = 0;//���[�V�����J�E���^�[
	m_MotionType = MOTION_TYPE::NEUTRAL;
	m_oldMotion = MOTION_TYPE::NEUTRAL;
}

//==========================
//�f�X�g���N�^
//==========================
CMotionModel::~CMotionModel()
{

}

//==========================
//����������
//==========================
HRESULT CMotionModel::Init()
{
	SetMotion(MOTION_TYPE::NEUTRAL);

	m_Shadow = CShadow::Create(GetPos(), D3DXVECTOR3(15.0f, 0.0f, 15.0f));

	return S_OK;
}

//==========================
//�I������
//==========================
void CMotionModel::Uninit()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Uninit();
			m_PartsList[i] = nullptr;
		}
	}

	if (m_Shadow != nullptr)
	{
		m_Shadow->Uninit();
		m_Shadow = nullptr;
	}

	Release();
}

//==========================
//�X�V����
//==========================
void CMotionModel::Update()
{

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Update();
		}
	}

	if (m_Shadow != nullptr)
	{
		m_Shadow->Move(GetPos());
	}
}

//==========================
//�`�揈��
//==========================
void CMotionModel::Draw()
{
	//�s��̐���
	CreateMtx();

	//���f���p�[�c�̕`��
	PartsDraw();
}

//==========================
//�s��̐���
//==========================
void CMotionModel::CreateMtx()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&GetMtxWorld());

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());
}

//==========================
//�p�[�c�̕`��
//==========================
void CMotionModel::PartsDraw()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Draw();
		}
	}
}

//==========================
//���f������
//==========================
CMotionModel* CMotionModel::Create()
{
	CMotionModel* pMotionModel = DBG_NEW CMotionModel;

	return pMotionModel;
}

//==========================
//�p�[�c�̏����擾
//==========================
CModelParts* CMotionModel::GetParts(int PartsNum)
{
	return m_PartsList[PartsNum];
}

//==========================
//�p�[�c�̐���
//==========================
void CMotionModel::SetParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* parents, int ModelPartsNum, D3DXVECTOR3 scale)
{
	m_PartsList[m_PartsNum] = CModelParts::Create(pos, rot, parents, ModelPartsNum, scale);
	m_PartsNum++;
}

//==========================
//���f���p�[�c�̃}�g���b�N�X���擾
//==========================
D3DXMATRIX& CMotionModel::GetPartsMtx(int PartsNum)
{
	return m_PartsList[PartsNum]->GetMtxWorld();
}

//==========================
//�p�[�c�̍폜
//==========================
void CMotionModel::DeleteParts(int num)
{
	if (m_PartsList[num] != nullptr)
	{
		m_PartsList[num]->Uninit();
		m_PartsList[num] = nullptr;
		m_PartsNum--;
	}
}

//==========================
//�p�[�c�����݂��邩����
//==========================
bool CMotionModel::GetPartsExistence(int PartsNum)
{
	if (m_PartsList[PartsNum] == nullptr)
	{
		return false;
	}

	return true;
}

//==========================
//��e���̐F�ɐݒ�
//==========================
void CMotionModel::SetDamageCor()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->SetCor();
		}
	}
}

//==========================
//�����x�����炷
//==========================
void CMotionModel::SubTransparency(float col)
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->SetCor();
			m_PartsList[i]->SubCol(col);
		}
	}
}

//==========================
//���݂̃��[�V�������擾
//==========================
CMotionModel::MOTION_TYPE CMotionModel::GetMotion()
{
	return m_MotionType;
}

//==========================
//�O�̃��[�V�������擾
//==========================
CMotionModel::MOTION_TYPE CMotionModel::GetOldMotion()
{
	return m_oldMotion;
}

//==========================
//�O�̃��[�V������ۑ�
//==========================
void CMotionModel::SetOldMotion(MOTION_TYPE motion)
{
	m_oldMotion = motion;
}

//==========================
//���݂̃L�[�ԍ��擾
//==========================
int CMotionModel::GetKeyNum()
{
	return m_nCurKey;
}

//==========================
//���[�V������ݒ�
//==========================
void CMotionModel::SetMotion(MOTION_TYPE MotionType)
{
	if (m_MotionType == MotionType)
	{
		return;
	}

	m_MotionType = MotionType;

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			KeepFirstPos(m_PartsList[i]->GetMotionPos(), i);
			KeepFirstRot(m_PartsList[i]->GetRot(), i);
			//m_FirstMotion[i].pos = m_PartsList[i]->GetMotionPos();
			//m_FirstMotion[i].rot = m_PartsList[i]->GetRot();
		}
	}

	m_nCurKey = 0;//���݂̃L�[�ԍ�
	m_nCntMotion = 0;//���[�V�����J�E���^�[
}

//==========================
//���[�V��������
//==========================
void CMotionModel::Motion()
{
	//�p�[�c�̐��l�̌v�Z
	CalParts();

	//���[�V�����J�E���^�[��i�߂�
	MotionCountUpdate();

	//���[�V�����̏����X�V
	UpdateMotionInfo();
}

//==========================
//���[�V�����̏����X�V
//==========================
void CMotionModel::UpdateMotionInfo()
{
	if (ExceedMaxFlame())
	{//���[�V�����J�E���^�[���Đ��t���[�����ɒB����

		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (m_PartsList[i] != nullptr)
			{
				KeepFirstPos(m_PartsList[i]->GetMotionPos(), i);
				KeepFirstRot(m_PartsList[i]->GetRot(), i);
				//m_FirstMotion[i].pos = m_PartsList[i]->GetMotionPos();
				//m_FirstMotion[i].rot = m_PartsList[i]->GetRot();
			}
		}

		m_nCurKey++;//���݂̃L�[�ԍ���i�߂�
		m_nCntMotion = 0;//�J�E���^�[��������

		if (m_nCurKey == m_MotionInfo[(int)m_MotionType].nKeyNum)
		{//���݂̃L�[�ԍ����L�[�̑����ɂȂ���
			m_nCurKey = 0;//���݂̃L�[�ԍ���0�ɖ߂�

			if (m_MotionInfo[(int)m_MotionType].Loop == 0)
			{//���݂̃��[�V���������[�v���Ȃ��Ƃ�

				//���̃��[�V������ۑ�
				SetOldMotion(GetMotion());

				//�ҋ@���[�V�����ɕύX
				SetMotion(MOTION_TYPE::NEUTRAL);
			}
		}
	}
}

//==========================
//�J�E���^�[�̍X�V
//==========================
void CMotionModel::MotionCountUpdate()
{
	m_nCntMotion++;
}

//==========================
//�p�[�c�̍X�V�ɕK�v�Ȑ��l���v�Z
//==========================
void CMotionModel::CalParts()
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		if (m_PartsList[nCntModel] != nullptr)
		{
			//���ݒl�����߂�
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�p�[�c�̌��������߂�
			rot = CalMotionRot(nCntModel);

			//�����̐ݒ�
			m_PartsList[nCntModel]->SetRot(rot);

			if (!m_PartsList[nCntModel]->GetExistParent())
			{//�e�̃p�[�c���Ȃ��Ƃ�

				//�p�[�c�̈ʒu�����߂�
				pos = CalMotionPos(nCntModel);

				//�ʒu�̐ݒ�
				m_PartsList[nCntModel]->SetMotionPos(pos);
			}
		}
	}
}

//==========================
//���[�V�����̃J�E���^�[���Đ��t���[���𒴂���������
//==========================
bool CMotionModel::ExceedMaxFlame()
{
	if (m_nCntMotion == m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame)
	{
		return true;
	}

	return false;
}

//==========================
//���[�V�������̃p�[�c�̈ʒu�����߂�
//==========================
D3DXVECTOR3& CMotionModel::CalMotionPos(int PartsNum)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���Βl�����߂�
	float Cur = (float)m_nCntMotion / m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame;

	//�ʒu�̍��������߂�
	D3DXVECTOR3 diffpos = m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].pos - m_FirstMotion[PartsNum].pos;

	//���ݒl�����߂�
	pos.x = m_FirstMotion[PartsNum].pos.x + (diffpos.x * Cur);
	pos.y = m_FirstMotion[PartsNum].pos.y + (diffpos.y * Cur);
	pos.z = m_FirstMotion[PartsNum].pos.z + (diffpos.z * Cur);

	return pos;
}

//==========================
//���[�V�������̃p�[�c�̌��������߂�
//==========================
D3DXVECTOR3& CMotionModel::CalMotionRot(int PartsNum)
{
	D3DXVECTOR3 addrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���Βl�����߂�
	float Cur = (float)m_nCntMotion / m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame;

	//�����̍��������߂�
	addrot.x = RevisionRot(m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].rot.x, m_FirstMotion[PartsNum].rot.x, Cur);
	addrot.y = RevisionRot(m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].rot.y, m_FirstMotion[PartsNum].rot.y, Cur);
	addrot.z = RevisionRot(m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].rot.z, m_FirstMotion[PartsNum].rot.z, Cur);

	rot.x = m_FirstMotion[PartsNum].rot.x + addrot.x;
	rot.y = m_FirstMotion[PartsNum].rot.y + addrot.y;
	rot.z = m_FirstMotion[PartsNum].rot.z + addrot.z;

	return rot;
}

//==========================
//�ŏ��̈ʒu��ۑ�
//==========================
void CMotionModel::KeepFirstPos(D3DXVECTOR3 pos, int PartsNum)
{
	m_FirstMotion[PartsNum].pos = pos;
}

//==========================
//�ŏ��̌�����ۑ�
//==========================
void CMotionModel::KeepFirstRot(D3DXVECTOR3 rot, int PartsNum)
{
	m_FirstMotion[PartsNum].rot = rot;
}

//==========================
//�t�@�C����ǂݍ���
//==========================
void CMotionModel::LoadFile(const char name[256], D3DXVECTOR3 scale)
{
	ifstream inputfile(name);//�e�L�X�g�t�@�C�����J��

	string Data;
	char FileName[256];//���f���̃t�@�C���p�X
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	int Index = 0;//���f���̔ԍ�
	int Parent = 0;//�e�̔ԍ�
	int ModelNum = 0;//���f���̐�
	int ModelPartsNum[20];//���f���p�[�c�̔ԍ�
	int motionCount = 0;//���[�V�����̐�
	int KeySetCount = 0;//�L�[�Z�b�g�̐�
	int KeyCount = 0;//�L�[�̐�
	float Radius = 0.0f;//�����蔻��̔��a

	if (!inputfile)
	{
		return;
	}

	while (1)
	{
		getline(inputfile, Data);

		//���f����
		if (Data.find("���f����") != string::npos)
		{
			getline(inputfile, Data);
			inputfile >> Data;
			inputfile >> Data;
			inputfile >> ModelNum;
		}

		//���f���t�@�C��
		if (Data.find("���f���t�@�C����") != string::npos)
		{
			CModel* pModel = CManager::GetInstance()->GetModel();
			for (int i = 0; i < ModelNum; i++)
			{
				getline(inputfile, Data, '=');
				inputfile >> FileName;
				ModelPartsNum[i] = pModel->Regist(FileName);
			}
		}

		//�L�����N�^�[���
		if (Data.find("PARTSSET") != string::npos)
		{
			while (getline(inputfile, Data, '='))//����ǂݍ���
			{
				if (Data.find("INDEX") != string::npos)
				{
					inputfile >> Index;
				}
				if (Data.find("PARENT") != string::npos)
				{
					inputfile >> Parent;
				}
				if (Data.find("POS") != string::npos)
				{
					inputfile >> pos.x;
					inputfile >> pos.y;
					inputfile >> pos.z;
				}
				if (Data.find("ROT") != string::npos)
				{
					inputfile >> rot.x;
					inputfile >> rot.y;
					inputfile >> rot.z;
					inputfile >> Data;

					if (Data.find("END_PARTSSET") != string::npos)
					{
						if (Parent == -1)
						{
							m_PartsList[m_PartsNum] = CModelParts::Create(pos, rot, nullptr, ModelPartsNum[m_PartsNum], scale);
						}
						else
						{
							m_PartsList[m_PartsNum] = CModelParts::Create(pos, rot, m_PartsList[Parent], ModelPartsNum[m_PartsNum], scale);
						}

						m_PartsNum++;
						Data.clear();
						break;
					}
				}
			}
		}

		////�����蔻��̏��
		//if (Data.find("COLLISIONSET") != string::npos)
		//{
		//	while (getline(inputfile, Data, '='))//����ǂݍ���
		//	{
		//		if (Data.find("INDEX") != string::npos)
		//		{
		//			inputfile >> Index;
		//		}
		//		if (Data.find("PARENT") != string::npos)
		//		{
		//			inputfile >> Parent;
		//		}
		//		if (Data.find("POS") != string::npos)
		//		{
		//			inputfile >> pos.x;
		//			inputfile >> pos.y;
		//			inputfile >> pos.z;
		//		}
		//		if (Data.find("RADIUS") != string::npos)
		//		{
		//			inputfile >> Radius;
		//			break;
		//		}
		//	}
		//	getline(inputfile, Data);
		//	if (Data.find("END_COLLISIONSET") != string::npos)
		//	{
		//		m_PartsList[Index]->CreateVisual(pos, Radius);
		//	}
		//}

		//���[�V�������
		if (Data.find("MOTIONSET") != string::npos)
		{
			while (getline(inputfile, Data, '='))//����ǂݍ���
			{
				if (Data.find("LOOP") != string::npos)
				{
					inputfile >> m_MotionInfo[motionCount].Loop;
				}
				if (Data.find("NUM_KEY") != string::npos)
				{
					inputfile >> m_MotionInfo[motionCount].nKeyNum;
					break;
				}
			}
			while (getline(inputfile, Data))//����ǂݍ���
			{
				if (Data.find("KEYSET") != string::npos)
				{
					while (getline(inputfile, Data, '='))//����ǂݍ���
					{
						if (Data.find("FRAME") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].nFrame;
							break;
						}
					}
				}

				if (Data.find("KEY") != string::npos)
				{
					while (getline(inputfile, Data, '='))//����ǂݍ���
					{
						if (Data.find("POS") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.x;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.y;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.z;
						}
						if (Data.find("ROT") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.x;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.y;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.z;
							KeyCount++;
							getline(inputfile, Data);
							getline(inputfile, Data);
							getline(inputfile, Data);
							if (Data.find("END_KEYSET") != string::npos)
							{
								KeySetCount++;
								KeyCount = 0;
							}
							break;
						}
					}
				}
				if (Data.find("END_MOTIONSET") != string::npos)
				{
					KeySetCount = 0;
					motionCount++;
					break;
				}
			}
		}

		if (Data.find("END_SCRIPT") != string::npos)
		{
			break;
		}
	}

	inputfile.close();//�t�@�C�������

}