//==========================
// 
// ���f���Ǘ�[model.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"model.h"
#include"manager.h"
#include"texture.h"

//==========================
// �R���X�g���N�^
//==========================
CModel::CModel(void)
{
	for (int i = 0; i < NUM_MODEL; i++)
	{
		m_pBuffMat[i] = nullptr;
		m_pMesh[i] = nullptr;
		m_dwNumMat[i] = 0;
		m_aModelName[i].clear();

		for (int n = 0; n < NUM_MODEL; n++)
		{
			m_Diffuse[i][n] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			m_apTexture[i][n] = nullptr;
		}
	}

	m_numAll = 0;
}

//==========================
// �f�X�g���N�^
//==========================
CModel::~CModel(void)
{

}

//==========================
//���f���̃A�����[�h
//==========================
void CModel::UnLoad(void)
{
	for (int i = 0; i < NUM_MODEL; i++)
	{
		if (m_pBuffMat[i] != nullptr)
		{
			m_pBuffMat[i]->Release();
			m_pBuffMat[i] = nullptr;
		}

		if (m_pMesh[i] != nullptr)
		{
			m_pMesh[i]->Release();
			m_pMesh[i] = nullptr;
		}

		for (int n = 0; n < NUM_MODEL; n++)
		{
			if (m_apTexture[i][n] != nullptr)
			{
				m_apTexture[i][n]->Release();
				m_apTexture[i][n] = nullptr;
			}
		}

		m_aModelName[i].clear();

	}
}

//==========================
//���f���o�^
//==========================
int CModel::Regist(const char* pModelName)
{
	int nIdx = 0;//���f��ID

	for (int i = 0; i < NUM_MODEL; i++)
	{
		if (m_dwNumMat[i] == 0)
		{//�o�^����ĂȂ�
			LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

			//���f���̓ǂݍ���
			D3DXLoadMeshFromX(pModelName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[i], NULL, &m_dwNumMat[i], &m_pMesh[i]);
			m_aModelName[i] = pModelName;//���f���̖��O��ۑ�
			nIdx = i;//ID�ݒ�
			m_numAll++;//���f����

			D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[i]->GetBufferPointer();//�}�e���A���f�[�^�ւ̃|�C���^���擾

			//���f���̃e�N�X�`���ǂݍ���
			for (int nCntMat = 0; nCntMat < (int)m_dwNumMat[i]; nCntMat++)
			{
				//�F��ۑ�
				m_Diffuse[i][nCntMat] = pMat[nCntMat].MatD3D.Diffuse;

				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					//CTexture* pTex = CManager::GetInstance()->GetTexture();
					//m_TexIdx[i] = pTex->Regist(pMat[nCntMat].pTextureFilename);
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&m_apTexture[i][nCntMat]);

				}
			}

			break;
		}
		else if (pModelName == m_aModelName[i])
		{//���ɐ����������f���ƈ�v����

			nIdx = i;//ID�ݒ�
			break;
		}
	}

	return nIdx;
}

//==========================
//���f���̃��b�V���擾
//==========================
LPD3DXMESH CModel::GetMeshAdress(int nIdx)
{
	return m_pMesh[nIdx];
}

//==========================
//���f���̃}�e���A���擾
//==========================
LPD3DXBUFFER CModel::GetBuffMatAdress(int nIdx)
{	
	return m_pBuffMat[nIdx];
}

//==========================
//���f���̃}�e���A���̐��擾
//==========================
DWORD CModel::GetNumMatAdress(int nIdx)
{
	 return m_dwNumMat[nIdx];
}

//==========================
//���f���̐F
//==========================
D3DCOLORVALUE CModel::GetDiffuse(int nIdx, int CorNum)
{
	return m_Diffuse[nIdx][CorNum];
}

//==========================
//�e�N�X�`��
//==========================
LPDIRECT3DTEXTURE9* CModel::GetTexIdx(int nIdx)
{
	return &m_apTexture[nIdx][0];
}
