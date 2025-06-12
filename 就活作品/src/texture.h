//==========================
// 
// �e�N�X�`���Ǘ�[texture.h]
// Author Yuki Goto
//
//==========================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//�e�N�X�`���N���X�̒�`
class CTexture
{
public:
	//�萔
	static const int NUM_TEX = 100;//�e�N�X�`���̍ő吔

	//�����o�֐�
	CTexture();//�R���X�g���N�^
	~CTexture();//�f�X�g���N�^
	void UnLoad();//�e�N�X�`���̃A�����[�h
	int Regist(const char* pTextureName);//�e�N�X�`���o�^
	LPDIRECT3DTEXTURE9 GetAdress(int nIdx);//�e�N�X�`���擾
private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEX];//�e�N�X�`���ւ̃|�C���^
	string m_aTextureName[NUM_TEX];//�쐬�ς݂̃e�N�X�`�����ۊǃf�[�^�z��
	int m_numAll;//�e�N�X�`���̑���
};

#endif