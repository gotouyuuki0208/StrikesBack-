//==========================
// 
// �����_���[[renderer.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"renderer.h"
#include"main.h"
#include"object2D.h"
#include"manager.h"

//�ÓI�����o������
const int CRenderer::NUM_EXPLANATION = 25;//�f�o�b�O�\���̍ő吔
///========================
//�R���X�g���N�^
//========================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	g_pFont = nullptr;
}

//========================
//�f�X�g���N�^
//========================
CRenderer::~CRenderer()
{

}

//========================
//�����ݒ�
//========================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�Q�[����ʃT�C�Y(��)

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʃT�C�Y(����)

	d3dpp.BackBufferFormat = d3ddm.Format;//�o�b�N�o�b�t�@�̌`��

	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)

	d3dpp.EnableAutoDepthStencil = TRUE;//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�v�X�o�b�t�@�Ƃ���16bit���g��

	d3dpp.Windowed = bWindow;//�E�C���h�E���[�h

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//========================
//�I������
//========================
void CRenderer::Uninit(void)
{

	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != nullptr)
	{
		g_pFont->Release();
		g_pFont = nullptr;
	}

}

//========================
//�X�V����
//========================
void CRenderer::Update()
{
	CObject::UpdateAll();
}

//========================
//�`�揈��
//========================
void CRenderer::Draw()
{
	//��ʃN���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 170, 255, 0), 1.0f, 0);
	//m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);
	
	//�`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�J�����̐ݒ�
		CManager::GetInstance()->GetCamera()->SetCamera();

		//�S�I�u�W�F�N�g�`��
		CObject::DrawAll();

#ifdef _DEBUG
		//�f�o�b�O�\��
		DrawDebug();
#endif 

		//�`��̏I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//========================
//3D�f�o�C�X�̎擾
//========================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//========================
//�f�o�b�O�\��
//========================
void CRenderer::DrawDebug(void)
{
	RECT rect[NUM_EXPLANATION];
	char aStr[NUM_EXPLANATION][256];

	for (int nCnt = 0; nCnt < NUM_EXPLANATION; nCnt++)
	{
		rect[nCnt] = { 0,20 * nCnt,SCREEN_WIDTH ,SCREEN_HEIGHT };
	}

	//������ɑ��
	wsprintf(&aStr[0][0], "FPS:%d\n", GetFps());
	wsprintf(&aStr[1][0], "���_��]:Z,C\n");
	wsprintf(&aStr[2][0], "����:J\n");
	wsprintf(&aStr[3][0], "������E��:O\n");
	wsprintf(&aStr[4][0], "������̂Ă�:P\n");
	wsprintf(&aStr[5][0], "�K�[�h:B\n");
	wsprintf(&aStr[6][0], "�v���C���[�̃f�o�b�O:F1\n");
	wsprintf(&aStr[7][0], "�{�X�̃f�o�b�O:F2\n");
	wsprintf(&aStr[8][0], "�X�e�[�W�ҏW:F4\n");
	wsprintf(&aStr[9][0], "�ړ�:W,A,S,D\n");
	wsprintf(&aStr[10][0], "�z�u:SPACE\n");
	wsprintf(&aStr[11][0], "���f���̃X�P�[���ύX:1,2\n");
	wsprintf(&aStr[12][0], "�O�̃I�u�W�F�N�g�Ɉړ�:3\n");
	wsprintf(&aStr[13][0], "���̃I�u�W�F�N�g�Ɉړ�:4\n");
	wsprintf(&aStr[14][0], "�ŏ��̃I�u�W�F�N�g�Ɉړ�:5\n");
	wsprintf(&aStr[15][0], "�Ō�̃I�u�W�F�N�g�Ɉړ�:6\n");
	wsprintf(&aStr[16][0], "�I�u�W�F�N�g���폜:7\n");
	wsprintf(&aStr[17][0], "WASD�̑����ύX(�ʒu�ƌ���):8\n");
	wsprintf(&aStr[18][0], "�J�����̈ʒu��ύX:9\n");
	wsprintf(&aStr[19][0], "WS�̑����ύX(Z����Y��):O\n");
	wsprintf(&aStr[20][0], "�ۑ�:M\n");
	wsprintf(&aStr[21][0], "Trigger��Press��؂�ւ�:��\n");
	wsprintf(&aStr[22][0], "�I�u�W�F�N�g�̎�ނ�؂�ւ�:��,��\n");
	wsprintf(&aStr[23][0], "�ҏW���[�h��؂�ւ�(�V�K�z�u�Ɣz�u�ς�):��\n");
	wsprintf(&aStr[24][0], "�X�e�[�W��؂�ւ�:V\n");

	//�e�L�X�g�̕`��
	for (int nCnt = 0; nCnt < NUM_EXPLANATION; nCnt++)
	{
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect[nCnt], DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
	}

}