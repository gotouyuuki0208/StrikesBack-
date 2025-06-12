//==========================
// 
// ���̋@[jihanki.h]
// Author Yuki Goto
//
//==========================
#ifndef _JIHANKI_H_
#define _JIHANKI_H_

//include
#include "objectX.h"
#include "collisionvisual.h"

//�N���X�̒�`
class CJihanki :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇
	static const int MAX_LIFE;//�����̍ő�l

	//�����o�֐�
	CJihanki(int nPriority = PRIORITY);//�R���X�g���N�^
	~CJihanki() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CJihanki* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
	void Damage(int Damage);//�_���[�W����
	void DamageVisual(D3DXVECTOR3 pos,float radius);//�U���̓����蔻��
	void DamageParticle();//��e���Ƀp�[�e�B�N�����o������
private:
	//�����o�֐�
	void ColisionPlayer();//�v���C���[�Ƃ̓����蔻��

	//�����o�ϐ�
	int m_nModelIdx;//�e�N�X�`���̔ԍ�
	int m_Life;//����
	CCollisionVisual* m_visual[2];//�����蔻��̉���
};
#endif