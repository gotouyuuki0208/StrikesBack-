//==========================
// 
// �Ў蕐��[smallweapon.h]
// Author Yuki Goto
//
//==========================
#ifndef _SMALLWEAPON_H_
#define _SMALLWEAPON_H_

//include
#include "weapon.h"
#include"trajectory.h"

//�N���X�̒�`
class CSmallWeapon :public CWeapon
{
public:

	enum class SMALLWEAPON
	{
		NONE = 0,
		BAT,//�o�b�g
		PIPE,//�p�C�v
		SYOKAKI,//���Ί�
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSmallWeapon(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSmallWeapon() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSmallWeapon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, const char ModelName[256]);//�I�u�W�F�N�g����
	void SetSmallWeapon(SMALLWEAPON type);//�Ў蕐��̎�ނ�ݒ�
	SMALLWEAPON GetSmallWeapon();//�Ў蕐��̎�ނ��擾
private:

	SMALLWEAPON m_SmallWeapontype;//�Ў蕐��̎�ނ�ݒ�
};
#endif