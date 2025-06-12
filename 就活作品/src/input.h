//==========================
// 
// ���͏���[input.h]
// Author Yuki Goto
//
//==========================
#ifndef _INPUT_H_
#define _INPUT_H_

//�}�N����`
#define MAX_KEY (256)//�L�[�̍ő吔
#define MAX_JOYKEY (16)//�{�^���̍ő吔

//���͋K��N���X(DirectInput�̊Ǘ�)
class CInput
{
public:

	//�����o�֐�
	CInput();//�R���X�g���N�^
	~CInput();//�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);//����������
	virtual void Uninit();//�I������
	virtual void Update() = 0;//�X�V����

protected:

	//�����o�ϐ�
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h���̓N���X
class CInputKeyboard :public CInput
{
public:

	//�����o�֐�
	CInputKeyboard();//�R���X�g���N�^
	~CInputKeyboard();//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	bool GetPress(int nKey);//�v���X�����擾
	bool GetTrigger(int nKey);//�g���K�[�����擾
	bool GetRelease(int nKey);//�����[�X�����擾
private:

	//�����o�ϐ�
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
	BYTE m_aKeyStateRelease[MAX_KEY];
};

//�p�b�h���̓N���X
class CInputJoypad :public CInput
{
public:

	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,//�\���L�[(��)
		JOYKEY_DOWN,//�\���L�[(��)
		JOYKEY_LEFT,//�\���L�[(��)
		JOYKEY_RIGHT,//�\���L�[(�E)
		JOYKEY_START,//STRAT�L�[
		JOYKEY_BACK,//BACK�L�[
		JOYKEY_LEFT_THUMB,//���X�e�B�b�N
		JOYKEY_RIGHT_THUMB,//�E�X�e�B�b�N
		JOYKEY_LB,//LB�L�[
		JOYKEY_RB,//RB�L�[
		JOYKEY_LEFT_TRIGGER,//LT�L�[
		JOYKEY_RIGHT_TRIGGER,//RT�L�[
		JOYKEY_A,//A�L�[
		JOYKEY_B,//B�L�[
		JOYKEY_X,//X�L�[
		JOYKEY_Y,//Y�L�[
		JOYKEY_MAX
	}JOYKEY;

	//�����o�֐�
	CInputJoypad();//�R���X�g���N�^
	~CInputJoypad();//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	bool GetPress(JOYKEY Key);//�v���X�����擾
	bool GetTrigger(JOYKEY Key);//�g���K�[�����擾
	bool GetRelease(JOYKEY Key);//
	bool GetTriggerPedal(JOYKEY Key);//�g���K�[�y�_���̏����擾
	WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
	float GetRightAngle();//�E�X�e�B�b�N�̊p�x�擾
	float GetLeftAngle();//���X�e�B�b�N�̊p�x�擾
	bool Connection();//�p�b�h���ڑ�����Ă��邩����
	bool GetRightStick();//�X�e�B�b�N�����͂���Ă邩����
	bool GetLeftStick();//���X�e�B�b�N�����͂���Ă邩����
private:

	//�����o�ϐ�
	XINPUT_STATE m_state;//�W���C�p�b�h�̃v���X���
	XINPUT_STATE m_stateTrigger;//�W���C�p�b�h�̃g���K�[���;
	XINPUT_STATE m_StateRelease;
};
#endif