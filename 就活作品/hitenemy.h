//==========================
// 
// ����G[hitenemy.h]
// Author Yuki Goto
//
//==========================
#ifndef _HITENEMY_H_
#define _HITENEMY_H_

//include
#include "weakenemy.h"
#include "hpgauge3D.h"

//�N���X�̒�`
class CHitEnemy :public CWeakEnemy
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CHitEnemy(int nPriority = PRIORITY);//�R���X�g���N�^
	~CHitEnemy() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CHitEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	
private:

	//�����o�ϐ�
	CHPGauge3D* m_HPGauge;//HP�Q�[�W�̏��
};
#endif