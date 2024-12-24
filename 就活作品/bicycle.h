//==========================
// 
// ���]��[bicycle.h]
// Author Yuki Goto
//
//==========================
#ifndef _BICYCLE_H_
#define _BICYCLE_H_

//include
#include "bigweapon.h"

//�N���X�̒�`
class CBicycle :public CBigWeapon
{
public:
	
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBicycle(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBicycle() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBicycle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif