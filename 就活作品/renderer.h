//==========================
// 
// �����_���[[renderer.h]
// Author Yuki Goto
//
//==========================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//�����_���[�N���X�̒�`
class CRenderer
{
public:
	//�萔
	static const int NUM_EXPLANATION;//�f�o�b�O�\���̐�

	//�����o�֐�
	CRenderer();//�R���X�g���N�^
	~CRenderer();//�f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindow);//�����ݒ�
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice();//3D�f�o�C�X�̎擾
private:

	//�����o�֐�
	void DrawDebug();//�f�o�b�O�\��

	//�����o�ϐ�
	LPDIRECT3D9 m_pD3D;//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;//Direct3D�f�o�C�X
	LPD3DXFONT g_pFont;
};

#endif 