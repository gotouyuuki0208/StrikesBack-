//==========================
// 
// ����[weapon.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAPON_H_
#define _WEAPON_H_

//include
#include "objectX.h"
#include"modelparts.h"
#include "weaponpoint.h"
#include"collisionvisual.h"

//�N���X�̒�`
class CWeapon :public CObjectX
{
public:
	//�񋓌^�̒�`
	enum class WEAPONTYPE
	{
		NONE = 0,
		BIG,//����Ŏ���
		SMALL,//�Ў�Ŏ���
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CWeapon(int nPriority = PRIORITY);//�R���X�g���N�^
	~CWeapon() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CWeapon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void SetParent(CModelParts* Parent);//�e���f���̐ݒ�
	void CollisionEnemy();//�G�Ƃ̓����蔻��
	void SetAttackReset();//�U�������߂�
	WEAPONTYPE GetWeaponType();//����̎�ނ��擾
	void SetWeaponType(WEAPONTYPE weapontype);//����̎�ނ�ݒ�
	int GetModelIdx();//���f���̔ԍ����擾
	void SetModelIdx(int num);//���f���̔ԍ���ݒ�
	void Reaction();//����������o����Ƃ��̔���
	void Reset();//�X�P�[�������Z�b�g
	void CreateVisual();//�����蔻�����������
	void GrabCharacter();//�L�����N�^�[�ɒ͂܂ꂽ
	void ReleseCharacter(D3DXVECTOR3 pos);//�L�����N�^�[��������
	bool GetGrab();//�͂܂�Ă邩�擾
	void SetDurability(int Num);//�ϋv�l�̐ݒ�
	int GetDurability();//�ϋv�l�̎擾
	void SubDurability();//�ϋv�l�����炷

private:

	//�����o�֐�
	void ColisionPlayer();//�v���C���[�Ƃ̓����蔻��

	//�����o�ϐ�
	CModelParts* m_Parent;//�e���f��
	bool m_Attack;//�Փ˂���������
	WEAPONTYPE m_weapontype;//����̎��
	int m_ModelIdx;//���f���̔ԍ�
	CWeaponPoint* m_WeaponPoint;//����̈ʒu�\��
	bool m_Transparent;//�����x�̏㉺����
	CCollisionVisual* m_visual;//�����蔻��̉���
	bool m_Garb;//�L�����N�^�[�������Ă邩����
	int m_Durability;//�ϋv�l
};
#endif