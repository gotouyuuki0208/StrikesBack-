//==========================
// 
// �|���S���̕`�揈��[object2D.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//include
#include "objectgame.h"

//�I�u�W�F�N�g2D�N���X�̒�`
class CObject2D:public CObjectgame
{
public:
	//�萔
	static const int PRIORITY;			//�`�揇

	//�����o�֐�
	CObject2D(int nPriority = PRIORITY);						//�R���X�g���N�^
	~CObject2D() override;										//�f�X�g���N�^
	HRESULT Init() override;									//����������
	void Uninit() override;										//�I������
	void Update() override;										//�X�V����
	void Draw() override;										//�`�揈��
	static CObject2D* Create();									//�I�u�W�F�N�g2D����
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);					//�e�N�X�`�����蓖��
	void Animetion(float vertical, int width);					//�A�j���[�V����
	float GetLength();											//�Ίp���̒����擾
	void SetCol(D3DCOLOR col);									//�F�̐ݒ�
	D3DCOLOR GetCol();											//�F�̎擾
	void SetSize(float vertical, float width);					//�傫���ݒ�
	void SetTexSize(float vertical, float width ,float TexPos);	//�e�N�X�`���̑傫���ݒ�
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff();						//���_�o�b�t�@�̃|�C���^���擾
	float GetWidth();											//���̃T�C�Y���擾
	float GetVertical();										//�c�̃T�C�Y���擾
private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DCOLOR m_col;						//�F
	float m_fLength;					//�Ίp���̒���
	float m_fAngle;						//�Ίp���̊p�x
	float m_fVertical;					//�c�̃T�C�Y
	float m_fWidth;						//���̃T�C�Y
	int m_nCntAnim;						//�e�N�X�`���A�j���[�V�����̐؂�ւ�
	int m_nPatternAnim;					//�e�N�X�`���A�j���[�V�����̕�����
};

#endif 
