//==========================
// 
// �}�l�[�W���[[manager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"

//==========================
// �R���X�g���N�^
//==========================
CManager::CManager(void):
m_pRenderer(nullptr),//�����_���[
m_pKeyboard(nullptr),//�L�[�{�[�h
m_pJoypad(nullptr),//�L�[�{�[�h
m_pSound(nullptr),//�T�E���h
m_Camera(nullptr),//�J�������擾
m_Light(nullptr),//���C�g���擾
m_Debug(nullptr),//�f�o�b�O���
m_Texture(nullptr),//�e�N�X�`��
m_Model(nullptr),//���f��
m_pFade(nullptr),//�t�F�[�h
m_pScene(nullptr),//���݂̉��
m_Stage(nullptr),//�X�e�[�W
m_Tutorial(nullptr),//�`���[�g���A��
m_GameManager(nullptr),//�Q�[���Ǘ�
m_Collision(nullptr),//�����蔻��
m_HudManager(nullptr)//HUD�̊Ǘ�
{
	
}

//==========================
// �f�X�g���N�^
//==========================
CManager::~CManager(void)
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	m_pRenderer = DBG_NEW CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h
	m_pKeyboard = DBG_NEW CInputKeyboard;
	m_pKeyboard->Init(hInstance, hWnd);

	//�p�b�h
	m_pJoypad = DBG_NEW CInputJoypad;
	m_pJoypad->Init(hInstance, hWnd);

	//�T�E���h
	m_pSound = DBG_NEW CSound;
	m_pSound->Init(hWnd);
	
	//�J����
	m_Camera = DBG_NEW CCamera;
	m_Camera->Init();

	//���C�g
	m_Light = DBG_NEW CLight;
	m_Light->Init();

	//�e�N�X�`��
	m_Texture = DBG_NEW CTexture;
	
	//���f��
	m_Model = DBG_NEW CModel;

	//�t�F�[�h
	m_pFade = CFade::Create();
	//m_pFade->SetFade(CScene::MODE::TITLE);//�ŏ��̃V�[���ݒ�
	m_pFade->SetFade(CScene::MODE::GAME);//�ŏ��̃V�[���ݒ�
	
	//�f�o�b�O
	m_Debug = DBG_NEW CDebug;

	//�X�e�[�W
	m_Stage = DBG_NEW CStageManager;

	//�`���[�g���A��
	m_Tutorial = DBG_NEW CTutorialManager;

	//�Q�[���Ǘ�
	m_GameManager = DBG_NEW CGameManager;

	//�����蔻��
	m_Collision = DBG_NEW CCollision;

	//HUD�̊Ǘ�
	m_HudManager = DBG_NEW CHudManager;

	return S_OK;
}

//==========================
// �I������
//==========================
void CManager::Uninit(void)
{

	//�S�I�u�W�F�N�g���
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{//�����_���[
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pScene != nullptr)
	{//�V�[��
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{//�L�[�{�[�h
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	
	if (m_pJoypad != nullptr)
	{//�p�b�h
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	if (m_pSound != nullptr)
	{//�T�E���h
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_Camera != nullptr)
	{//�J����
		m_Camera->Uninit();
		delete m_Camera;
		m_Camera = nullptr;
	}

	if (m_Light != nullptr)
	{//���C�g
		m_Light->Uninit();
		delete m_Light;
		m_Light = nullptr;
	}

	if (m_Texture != nullptr)
	{//�e�N�X�`��
		m_Texture->UnLoad();
		delete m_Texture;
		m_Texture = nullptr;
	}

	if (m_Model != nullptr)
	{//���f��
		m_Model->UnLoad();
		delete m_Model;
		m_Model = nullptr;
	}

	if (m_pFade != nullptr)
	{//�t�F�[�h
		m_pFade->CObject2D::Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_Debug != nullptr)
	{//�f�o�b�O
		delete m_Debug;
		m_Debug = nullptr;
	}

	if (m_Stage != nullptr)
	{//�X�e�[�W
		m_Stage->Uninit();
		delete m_Stage;
		m_Stage = nullptr;
	}

	if (m_Tutorial != nullptr)
	{//�`���[�g���A��
		delete m_Tutorial;
		m_Tutorial = nullptr;
	}

	if (m_GameManager != nullptr)
	{//�Q�[���Ǘ�
		delete m_GameManager;
		m_GameManager = nullptr;
	}

	if (m_Collision != nullptr)
	{//�����蔻��
		delete m_Collision;
		m_Collision = nullptr;
	}

	if (m_HudManager != nullptr)
	{//HUD�̊Ǘ�
		delete m_HudManager;
		m_HudManager = nullptr;
	}
}

//==========================
// �X�V����
//==========================
void CManager::Update(void)
{
	m_pRenderer->Update();//�����_���[�̍X�V

	m_pKeyboard->Update();//�L�[�{�[�h�̍X�V

	m_pJoypad->Update();//�p�b�h�̍X�V

	//if (m_pFade->GetFade() == CFade::FADE::FADE_NONE)
	if (m_pScene != nullptr)
	{//�t�F�[�h���ĂȂ��Ƃ�
		m_pScene->Update();//�V�[���̍X�V
	}
	
	m_Camera->Update();//�J�����̍X�V
}

//==========================
// �`�揈��
//==========================
void CManager::Draw(void)
{
	m_pRenderer->Draw();//�����_���[�̕`��

	//if (m_pFade->GetFade() == CFade::FADE::FADE_NONE)
	if (m_pScene != nullptr)
	{//�t�F�[�h���ĂȂ��Ƃ�
		m_pScene->Draw();//�V�[���̕`��
	}
}

//=====================
//�����_���[�擾
//=====================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=====================
//�L�[�{�[�h�擾
//=====================
CInputKeyboard* CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=====================
//�p�b�h�擾
//=====================
CInputJoypad* CManager::GetJoypad(void)
{
	return m_pJoypad;
}

//=====================
//�T�E���h�擾
//=====================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}

//=====================
//�C���X�^���X�擾
//=====================
CManager* CManager::GetInstance()
{
	static CManager instance;
	return &instance;
}

//=====================
//�J�������擾
//=====================
CCamera* CManager::GetCamera(void)
{
	return m_Camera;
}

//=====================
//���C�g���擾
//=====================
CLight* CManager::GetLight(void)
{
	return m_Light;
}

//=====================
//�e�N�X�`�����擾
//=====================
CTexture* CManager::GetTexture(void)
{
	return m_Texture;
}

//=====================
//���f�����擾
//=====================
CModel* CManager::GetModel()
{
	return m_Model;
}

//=====================
//�t�F�[�h�̎擾
//=====================
CFade* CManager::GetFade()
{
	return m_pFade;
}

//=====================
//�f�o�b�O�̎擾
//=====================
CDebug* CManager::GetDebug()
{
	return m_Debug;
}

//=====================
//�X�e�[�W�̎擾
//=====================
CStageManager* CManager::GetStageManager()
{
	return m_Stage;
}

//=====================
//�`���[�g���A���̎擾
//=====================
CTutorialManager* CManager::GetTutorial()
{
	return m_Tutorial;
}

//=====================
//�V�[���̎擾
//=====================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//=====================
//�Q�[���Ǘ��̎擾
//=====================
CGameManager* CManager::GetGameManager()
{
	return m_GameManager;
}

//=====================
//�����蔻��̎擾
//=====================
CCollision* CManager::GetCollision()
{
	return m_Collision;
}

//=====================
//HUD�̊Ǘ�
//=====================
CHudManager* CManager::GetHudManager()
{
	return m_HudManager;
}

//=====================
//�V�[���̐ݒ�
//=====================
void CManager::SetMode(CScene::MODE mode)
{
	//�I������
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//����
	m_pScene = CScene::Create(mode);
	m_pScene->Init();
	m_Camera->Init();
}