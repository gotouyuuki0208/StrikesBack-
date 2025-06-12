//==========================
// 
// ���]��[bicycle.h]
// Author Yuki Goto
//
//==========================
#ifndef _CONE_H_
#define _CONE_H_

//include
#include "bigweapon.h"

//�N���X�̒�`
class CCone :public CBigWeapon
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CCone(int nPriority = PRIORITY);//�R���X�g���N�^
	~CCone() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CCone* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif