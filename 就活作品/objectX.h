//==========================
// 
// ���f���̕`�揈��[objectX.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//include
#include "objectgame.h"

//�I�u�W�F�N�gX�N���X�̒�`
class CObjectX :public CObjectgame
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CObjectX(int nPriority = PRIORITY);//�R���X�g���N�^
	~CObjectX() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CObjectX* Create();//���f������
	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPDIRECT3DTEXTURE9 * pTexture);//���f�����蓖��
	void SetSize();//���f���̃T�C�Y��ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//�e�N�X�`�����蓖��
	D3DXVECTOR3& GetVtxMin();//���_�̍ŏ��̏ꏊ���擾
	D3DXVECTOR3& GetVtxMax();//���_�̍ő�̏ꏊ���擾
	D3DXVECTOR3& GetSize();//�T�C�Y�擾
	LPD3DXMESH& GetMesh();//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER& GetBuffMat();//�}�e���A���ւ̃|�C���^
	DWORD& GetNumMat();//�}�e���A���̐�
	void SetTransparent(float cor);//�����x��ݒ�
	float GetTransparent();//�����x���擾

private:
	//�����o�ϐ�
	LPD3DXMESH m_pMesh;//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_Size;//���f���̑傫��
	D3DXVECTOR3 m_vtxMin;//���_�̍ŏ�
	D3DXVECTOR3 m_vtxMax;//���_�̍ő�
	LPDIRECT3DTEXTURE9* m_pTexture2;//���f���̃e�N�X�`���̃|�C���^
	float m_Transparent;//�����x
};
#endif 