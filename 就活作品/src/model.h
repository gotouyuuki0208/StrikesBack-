//==========================
// 
// ���f���Ǘ�[model.h]
// Author Yuki Goto
//
//==========================
#ifndef _MODEL_H_
#define _MODEL_H_

//���f���N���X�̒�`
class CModel
{
public:
	//�����o�֐�
	CModel();//�R���X�g���N�^
	~CModel();//�f�X�g���N�^
	void UnLoad();//�e�N�X�`���̃A�����[�h
	int Regist(const char* pModelName);//���f���o�^
	LPD3DXMESH GetMeshAdress(int nIdx);//���f���̃��b�V���擾
	LPD3DXBUFFER GetBuffMatAdress(int nIdx);//���f���̃}�e���A���擾
	DWORD GetNumMatAdress(int nIdx);//���f���̃}�e���A���̐��擾
	D3DCOLORVALUE GetDiffuse(int nIdx, int CorNum);//���f���̐F
	LPDIRECT3DTEXTURE9 * GetTexIdx(int nIdx);//���f���̃e�N�X�`���ԍ��擾
private:

	//�萔
	static const int NUM_MODEL = 150;//���f���̎�ސ�

	//�����o�ϐ�
	LPD3DXMESH m_pMesh[NUM_MODEL];//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat[NUM_MODEL];//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat[NUM_MODEL];//�}�e���A���̐�
	D3DCOLORVALUE m_Diffuse[NUM_MODEL][NUM_MODEL];//�F�̕ۑ��p
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_MODEL][NUM_MODEL];
	int m_TexIdx[NUM_MODEL];//���f���̃e�N�X�`���ԍ�
	string m_aModelName[NUM_MODEL];//�쐬�ς݂̃e�N�X�`�����ۊǃf�[�^�z��
	int m_numAll;//�e�N�X�`���̑���
};
#endif