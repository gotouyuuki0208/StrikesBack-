//==========================
// 
// �傫������[bigweapon.h]
// Author Yuki Goto
//
//==========================
#ifndef _BIGWEAPON_H_
#define _BIGWEAPON_H_

//include
#include "weapon.h"

//�N���X�̒�`
class CBigWeapon :public CWeapon
{
public:
	enum class BIGWEAPON
	{
		NONE=0,
		BICYCLE,//���]��
		CONE,
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBigWeapon(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBigWeapon() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBigWeapon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,const char ModelName[256]);//�I�u�W�F�N�g����
	void SetBigWeapon(BIGWEAPON type);//���蕐��̎�ނ�ݒ�
	BIGWEAPON GetBigWeapon();//��tr����̎�ނ��擾
private:
	BIGWEAPON m_BigWeapontype;//���蕐��̎��
};
#endif