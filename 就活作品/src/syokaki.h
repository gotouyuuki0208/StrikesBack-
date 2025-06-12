//==========================
// 
// �o�b�g[bat.h]
// Author Yuki Goto
//
//==========================
#ifndef _syokaki_H_
#define _syokaki_H_

//include
#include "smallweapon.h"

//�N���X�̒�`
class CSyokaki :public CSmallWeapon
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSyokaki(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSyokaki() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSyokaki* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif