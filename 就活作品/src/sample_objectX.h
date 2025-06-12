//==========================
// 
// 3D���f���`��T���v��[sample_objectX.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_OBJECTX_H_
#define _SAMPLE_OBJECTX_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CSampleObjectX :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSampleObjectX(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSampleObjectX() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSampleObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
	//�����o�ϐ�
	int m_nModelIdx;//���f���̔ԍ�
};
#endif