//==========================
// 
// ���C�g����[light.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "light.h"
#include"manager.h"

//========================
//�R���X�g���N�^
//========================
CLight::CLight()
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		//���C�g�̏�������������
		ZeroMemory(&m_aLight[i], sizeof(D3DLIGHT9));
	}
}

//========================
//�f�X�g���N�^
//========================
CLight::~CLight()
{

}

//========================
//�����ݒ�
//========================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DXVECTOR3 vecDir;//�ݒ�p�����x�N�g��

	float x = 0.0f, y = 0.0f, z = 0.0f;

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (nCnt)
		{
		case 0:
			x = 0.0f;
			y = -1.0f;
			z = 0.0f;
			break;

		case 1:
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;
			break;

		case 2:
			x = 1.5f;
			y = -1.0f;
			z = 1.0f;
			break;

		case 3:
			x = -1.5f;
			y = -1.0f;
			z = -1.0f;
			break;

		default:
			break;
		}

		//���C�g�̕�����ݒ�
		vecDir = D3DXVECTOR3(x, y, z);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[nCnt].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);

	}

	return S_OK;
}

//========================
//�I������
//========================
void CLight::Uninit(void)
{

}

//========================
//�X�V����
//========================
void CLight::Update()
{

}