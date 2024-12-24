//==========================
// 
// 3D�|���S���̕`�揈��[object3D.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//include
#include "objectgame.h"

//�I�u�W�F�N�g3D�N���X�̒�`
class CObject3D :public CObjectgame
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CObject3D(int nPriority = PRIORITY);//�R���X�g���N�^
	~CObject3D() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CObject3D* Create();//�I�u�W�F�N�g3D����
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//�e�N�X�`�����蓖��
	void SetSize(D3DXVECTOR3 size);//�傫���ݒ�
	D3DXVECTOR3& GetSize();//�傫���擾
	void SetCor(D3DXCOLOR cor);//�F�̐ݒ�
private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_size;//�傫��
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	D3DXCOLOR m_cor;//�F
};

#endif 
