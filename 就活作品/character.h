//==========================
// 
// �L�����N�^�[[character.h]
// Author Yuki Goto
//
//==========================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//include
#include "motionmodel.h"
#include "collisionvisual.h"

//�N���X�̒�`
class CCharacter :public CMotionModel
{
public:
	
	enum class STATE
	{
		NEUTRAL = 0,//�ʏ�
		ATTACK,//�U��
		MOVE,//�ړ�
		GUARD,//�K�[�h
		AVOIDANCE,//���
		GRAB,//�͂܂��
		MAX,
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CCharacter(int nPriority = PRIORITY);//�R���X�g���N�^
	~CCharacter() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	void DamegeBlow(D3DXVECTOR3 pos);//��e���̐�����я���
	void SetLife(int life);//�����̐ݒ�
	int GetLife();//�����̎擾
	bool GetDamage();//�_���[�W����̎擾
	void SetDamage(bool damege);//�_���[�W����̕ύX
	void SetState(STATE state);//��Ԃ̐ݒ�
	STATE GetState();//��Ԃ̎擾
	void DamageVisual(int PartsNum, float Radius);//��e���̓����蔻��̉���
	void SetVisual();//�����蔻��̉�������
	void SetDamegeBlow(D3DXVECTOR3 move);//������їp�̈ړ��l�ݒ�
	D3DXVECTOR3& GetDamegeBlow();//������їp�̈ړ��l�擾
private:

	//�����o�ϐ�
	STATE m_state;//���݂̏��
	int m_nLife;//����
	bool m_Damage;//�_���[�W��Ԕ���
	D3DXVECTOR3 m_DamageMove;//������їp�̈ړ��l
	CCollisionVisual* m_visual;//�����蔻��̉���
};
#endif