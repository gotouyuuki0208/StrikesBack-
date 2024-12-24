//==========================
// 
// �}�l�[�W���[[manager.h]
// Author Yuki Goto
//
//==========================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//include
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"camera.h"
#include"light.h"
#include"texture.h"
#include"model.h"
#include"scene.h"
#include"fade.h"
#include"debug.h"
#include"stagemanager.h"
#include"TutorialManager.h"
#include"GameManager.h"

//�}�l�[�W���N���X�̒�`
class CManager
{
public:

	//�����o�֐�
	~CManager();//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//�����ݒ�
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��

	static CManager* GetInstance();//�C���X�^���X�擾
	CRenderer* GetRenderer();//�����_���[�擾
	CInputKeyboard*GetKeyboard();//�L�[�{�[�h���͎擾
	CInputJoypad* GetJoypad();//�p�b�h���擾
	CSound* GetSound();//�T�E���h���擾
	//CBlockManager* GetBlockManager();//�u���b�N���擾
	CCamera* GetCamera();//�J�������擾
	CLight* GetLight();//���C�g���擾
	CTexture* GetTexture();//�e�N�X�`�����擾
	CModel* GetModel();//���f�����擾
	CFade* GetFade();//�t�F�[�h�̎擾
	CDebug* GetDebug();//�f�o�b�O�̎擾
	CStageManager* GetStageManager();//�X�e�[�W�̎擾
	CTutorial* GetTutorial();//�`���[�g���A���̎擾
	CScene* GetScene();//�V�[���̎擾
	CGameManager* GetGameManager();
	void SetMode(CScene::MODE mode);//��ʂ̐ݒ�
private:

	//�����o�֐�
	CManager();//�R���X�g���N�^

	//�����o�ϐ�
	CRenderer* m_pRenderer;//�����_���[
	CInputKeyboard* m_pKeyboard;//�L�[�{�[�h
	CInputJoypad* m_pJoypad;//�L�[�{�[�h
	CSound* m_pSound;//�T�E���h
	CCamera* m_Camera;//�J�������
	CLight* m_Light;//���C�g���
	CTexture* m_Texture;//�e�N�X�`��
	CModel* m_Model;//���f��
	CScene* m_pScene;//���݂̉��
	CFade* m_pFade;//�t�F�[�h
	CDebug* m_Debug;//�f�o�b�O
	CStageManager* m_Stage;//�X�e�[�W�Ǘ�
	CTutorial* m_Tutorial;//�`���[�g���A���Ǘ�
	CGameManager* m_GameManager;//�Q�[���Ǘ�
};

#endif 
