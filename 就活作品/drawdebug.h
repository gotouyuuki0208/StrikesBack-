//==========================
// 
// �f�o�b�O�\��[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _DRAWDEBUG_H_
#define _DRAWDEBUG_H_

//�N���X�̒�`
class CDrawDebug
{
public:

	//�����o�֐�
	CDrawDebug();//�R���X�g���N�^
	~CDrawDebug();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	static void DrawDebug();//�`�揈��
private:

	//�����o�ϐ�
	LPD3DXFONT m_pFont;
};

#endif