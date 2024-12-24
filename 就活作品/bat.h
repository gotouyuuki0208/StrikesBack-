//==========================
// 
// �o�b�g[bat.h]
// Author Yuki Goto
//
//==========================
#ifndef _BAT_H_
#define _BAT_H_

//include
#include "smallweapon.h"

//�N���X�̒�`
class CBat :public CSmallWeapon
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBat(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBat() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBat* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif