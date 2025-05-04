//==========================
// 
// ���b�V���|���S���̕`�揈��[objectmesh.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECTEMSH_H_
#define _OBJECTEMSH_H_

//include
#include "objectgame.h"

//�N���X�̒�`
class CObjectMesh :public CObjectgame
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CObjectMesh(int nPriority = PRIORITY);//�R���X�g���N�^
	~CObjectMesh() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CObjectMesh* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical);//���f������
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//�e�N�X�`�����蓖��
	void SetVerticalDiv(int vertical);//�c�̕�������ݒ�
	int GetVerticalDiv();//�c�̕��������擾
	void SetWidthDiv(int width);//���̕�������ݒ�
	int GetWidthDiv();//���̕��������擾
	void SetSize(D3DXVECTOR3 size);//�T�C�Y��ݒ�
	D3DXVECTOR3& GetSize();//�T�C�Y���擾
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();//���_�o�b�t�@���擾
	int GetNumVtx();//���_���̎擾
private:

	//�����o�֐�
	void SetInit();//���_�o�b�t�@�̏����ݒ�
	void SeIdx();//�C���f�b�N�X�o�b�t�@�̐ݒ�

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_size;//�|���S���̃T�C�Y
	int m_WidthDiv;//���̕�����
	int m_VerticalDiv;//�c�̕�����
	int m_NumVtx;//���_��
	int m_NumIdx;//�C���f�b�N�X��
	int m_nTexIdx;
};
#endif 