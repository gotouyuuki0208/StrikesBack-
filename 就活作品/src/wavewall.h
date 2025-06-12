//==========================
// 
// �E�F�[�u�ŏ������[wavewall.h]
// Author Yuki Goto
//
//==========================
#ifndef _WAVEWALL_H_
#define _WAVEWALL_H_

//include
#include "building.h"

//�N���X�̒�`
class CWaveWall :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CWaveWall(int nPriority = PRIORITY);//�R���X�g���N�^
	~CWaveWall() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CWaveWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot,int wave);//�I�u�W�F�N�g����
	int GetMyWave();//�����̃E�F�[�u���擾
private:

	//�����o�ϐ�
	int m_MyWave;//�����̃E�F�[�u
};
#endif