//==========================
// 
// �S�p�C�v[pipe.h]
// Author Yuki Goto
//
//==========================
#ifndef _PIPE_H_
#define _PIPE_H_

//include
#include "smallweapon.h"

//�N���X�̒�`
class CPipe :public CSmallWeapon
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CPipe(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPipe() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CPipe* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif