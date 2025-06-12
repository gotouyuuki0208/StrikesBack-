//==========================
// 
// �f�o�b�O�\��[drawdebug.h]
// Author Yuki Goto
//
//==========================
#include"drawdebug.h"
#include"manager.h"

//==========================
//�R���X�g���N�^
//==========================
CDrawDebug::CDrawDebug():
m_pFont(nullptr)
{

}

//==========================
//�f�X�g���N�^
//==========================
CDrawDebug::~CDrawDebug()
{

}

//==========================
//����������
//==========================
HRESULT CDrawDebug::Init()
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//�f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//==========================
//�I������
//==========================
void CDrawDebug::Uninit()
{
	if (m_pFont != nullptr)
	{
		m_pFont = nullptr;
	}
}

//==========================
//�`�揈��
//==========================
void CDrawDebug::DrawDebug()
{

}