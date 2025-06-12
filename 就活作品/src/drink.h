//==========================
// 
// ���ݕ�[drink.h]
// Author Yuki Goto
//
//==========================
#ifndef _DRINK_H_
#define _DRINK_H_

//include
#include "item.h"

//�N���X�̒�`
class CDrink :public CItem
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CDrink(int nPriority = PRIORITY);//�R���X�g���N�^
	~CDrink() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CDrink* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
};
#endif