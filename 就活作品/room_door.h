//==========================
// 
// �����̃h�A[room_door.h]
// Author Yuki Goto
//
//==========================
#ifndef _ROOM_DOOR_H_
#define _ROOM_DOOR_H_

//include
#include "building.h"

//�N���X�̒�`
class CRoomDoor :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CRoomDoor(int nPriority = PRIORITY);//�R���X�g���N�^
	~CRoomDoor() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CRoomDoor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif