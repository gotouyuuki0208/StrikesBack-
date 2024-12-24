//==========================
// 
// �e�N�X�`���Ǘ�[texture.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"texture.h"
#include"manager.h"

//==========================
// �R���X�g���N�^
//==========================
CTexture::CTexture(void)
{
	for (int i = 0; i < NUM_TEX; i++)
	{
		m_apTexture[i] = nullptr;
		m_aTextureName[i].clear();
	}
	
	m_numAll = 0;
}

//==========================
// �f�X�g���N�^
//==========================
CTexture::~CTexture(void)
{

}

//==========================
//�e�N�X�`���̃A�����[�h
//==========================
void CTexture::UnLoad(void)
{
	for (int i = 0; i < NUM_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}

		m_aTextureName[i].clear();
	}
}

//==========================
//�e�N�X�`���o�^
//==========================
int CTexture::Regist(const char* pTextureName)
{
	int nIdx = 0;//�e�N�X�`��ID

	for (int i = 0; i < NUM_TEX; i++)
	{
		if (m_apTexture[i] == nullptr)
		{//�o�^����ĂȂ�
			LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pTextureName, &m_apTexture[i]);
			m_aTextureName[i] = pTextureName;//�e�N�X�`���̖��O��ۑ�
			nIdx = i;//ID�ݒ�
			m_numAll++;//�e�N�X�`����
			break;
		}
		else if (pTextureName == m_aTextureName[i])
		{//���ɐ��������e�N�X�`���ƈ�v����

			nIdx = i;//ID�ݒ�
			break;
		}
	}

	return nIdx;
}

//==========================
//�e�N�X�`���擾
//==========================
LPDIRECT3DTEXTURE9 CTexture::GetAdress(int nIdx)
{
	return m_apTexture[nIdx];
}