//==========================
// 
// �r���{�[�h����[billboard.h]
// Author Yuki Goto
//
//==========================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//include
#include"object3D.h"

//�r���{�[�h�N���X�̒�`
class CBillBoard :public CObjectgame
{
public:
	//�萔
	static const int PRIORITY;									//�`�揇
	static const int ANIM_FRAME;								//�A�j���[�V�����̃t���[����

	//�����o�֐�
	CBillBoard(int nPriority = PRIORITY);						//�R���X�g���N�^
	~CBillBoard() override;										//�f�X�g���N�^
	HRESULT Init() override;									//����������
	void Uninit() override;										//�I������
	void Update() override;										//�X�V����
	void Draw() override;										//�`�揈��
	static CBillBoard* Create(D3DXVECTOR3 pos);					//��������
	void SetSize(D3DXVECTOR3 size);								//�傫���ݒ�
	D3DXVECTOR3& GetSize();										//�傫�����擾
	void SetCol(D3DXCOLOR col);									//�F�̐ݒ�
	D3DXCOLOR& GetCol();										//�F�̎擾
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);					//�e�N�X�`�����蓖��
	void SetTexSize(float vertical, float width, float TexPos);	//�e�N�X�`���̃T�C�Y�ݒ�
	void Animetion(float vertical, int width);					//�A�j���[�V����
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();						//���_�o�b�t�@�̎擾
	LPDIRECT3DTEXTURE9& GetTex();								//�e�N�X�`���̎擾
	void TexMove();												//�e�N�X�`���𓮂���
private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_col;					//�F
	D3DXVECTOR3 m_size;					//�傫��
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	int m_nCntAnim;						//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;					//�e�N�X�`���A�j���[�V�����̕�����
	float m_PosTexV;					//�e�N�X�`���̏c�̈ʒu
};

#endif