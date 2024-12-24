//==========================
// 
// ���͏���[input.h]
// Author Yuki Goto
//
//==========================

//include
#include"input.h"

//�ÓI�����o
LPDIRECTINPUT8 CInput::m_pInput;

//==========���N���X==========

//==============================
// �R���X�g���N�^
//==============================
CInput::CInput(void)
{

}

//==============================
// �f�X�g���N�^
//==============================
CInput::~CInput(void)
{

}

//==============================
// �����ݒ�
//==============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	return S_OK;
}

//==============================
// �I������
//==============================
void CInput::Uninit(void)
{

}

//===========�L�[�{�[�h���̓N���X==========

//==============================
// �R���X�g���N�^
//==============================
CInputKeyboard::CInputKeyboard(void) : m_aKeyState(), m_aKeyStateTrigger(), m_aKeyStateRelease()
{

}

//==============================
// �f�X�g���N�^
//==============================
CInputKeyboard::~CInputKeyboard(void)
{

}

//==============================
//�L�[�{�[�h�̏���������
//==============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&m_pInput), nullptr)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�𐶐�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//==============================
//�L�[�{�[�h�̏I������
//==============================
void CInputKeyboard::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//==============================
//�L�[�{�[�h�̍X�V����
//==============================
void CInputKeyboard::Update(void)
{

	BYTE aKeyState[MAX_KEY];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateRelease[nCntKey]= (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];//�L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//==============================
//�L�[�{�[�h�̃v���X�����擾
//==============================
bool CInputKeyboard::GetPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//==============================
//�L�[�{�[�h�̃g���K�[�����擾
//==============================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//==============================
//�����[�X�����擾
//==============================
bool CInputKeyboard::GetRelease(int nKey)
{
	return ((m_aKeyStateRelease[nKey] & 0x80) != 0) ? true : false;
}

//===========�p�b�h���̓N���X==========

//==============================
// �R���X�g���N�^
//==============================
CInputJoypad::CInputJoypad(void):m_state(), m_stateTrigger(), m_StateRelease()
{
	
}

//==============================
// �f�X�g���N�^
//==============================
CInputJoypad::~CInputJoypad(void)
{

}

//==============================
//�W���C�p�b�h�̏���������
//==============================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�������̃N���A
	memset(&m_state, 0, sizeof(XINPUT_STATE));
	memset(&m_stateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//==============================
//�W���C�p�b�h�̏I������
//==============================
void CInputJoypad::Uninit(void)
{
	//Xinput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//==============================
//�W���C�p�b�h�̍X�V����
//==============================
void CInputJoypad::Update(void)
{
	XINPUT_STATE JoyKeyState;//�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = JoyKeyState.Gamepad.wButtons;
		WORD OldButton = m_state.Gamepad.wButtons;
		m_stateTrigger.Gamepad.wButtons = ~OldButton & Button;//�g���K�[����
		m_StateRelease.Gamepad.wButtons = ~Button & OldButton;

		m_state = JoyKeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}

	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}

	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}

	// ���X�e�B�b�N����̓��͂�����p�b�h�ɕϊ�
	m_state.Gamepad.wButtons |= ThumbToDPad(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

}

//==============================
//�W���C�p�b�h�̃v���X�����擾
//==============================
bool CInputJoypad::GetPress(JOYKEY Key)
{
	return (m_state.Gamepad.wButtons & (0x01 << Key));
}

//==============================
//�g���K�[�����擾
//==============================
bool CInputJoypad::GetTrigger(JOYKEY Key)
{
	return (m_stateTrigger.Gamepad.wButtons & (0x01 << Key));
}

//==============================
//�g���K�[�����擾
//==============================
bool CInputJoypad::GetRelease(JOYKEY Key)
{
	return (m_StateRelease.Gamepad.wButtons & (0x01 << Key));
}

//==============================
//�g���K�[�y�_�������擾
//==============================
bool CInputJoypad::GetTriggerPedal(JOYKEY Key)
{
	int nControllerTriggerPedal = 0;

	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nControllerTriggerPedal = m_state.Gamepad.bLeftTrigger;
		break;

	case JOYKEY_RIGHT_TRIGGER:
		nControllerTriggerPedal = m_state.Gamepad.bRightTrigger;
		break;
	}

	return nControllerTriggerPedal > 0;
}

//=========================================
// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
//=========================================
WORD CInputJoypad::ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//=========================================
//�E�X�e�B�b�N�̊p�x�擾
//=========================================
float CInputJoypad::GetRightAngle()
{
	float angle = atan2f(m_state.Gamepad.sThumbRX, m_state.Gamepad.sThumbRY);
	return angle;
}

//=========================================
//���X�e�B�b�N�̊p�x�擾
//=========================================
float CInputJoypad::GetLeftAngle()
{
	float angle = atan2f(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY);
	return angle;
}

//=========================================
//�p�b�h���ڑ�������
//=========================================
bool CInputJoypad::Connection()
{
	XINPUT_STATE JoyKeyState;//�W���C�p�b�h�̓��͏��
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		return true;
	}
	
	return false;
}

//=========================================
//�X�e�B�b�N�����͂���Ă邩����
//=========================================
bool CInputJoypad::GetRightStick()
{
	if (m_state.Gamepad.sThumbRX == 0 
		&& m_state.Gamepad.sThumbRY == 0
		&&m_state.Gamepad.sThumbRX == 0
		&& m_state.Gamepad.sThumbRY == 0)
	{
		return false;
	}
	return true;
}

//=========================================
//���X�e�B�b�N�����͂���Ă邩����
//=========================================
bool CInputJoypad::GetLeftStick()
{
	if (m_state.Gamepad.sThumbLX == 0
		&& m_state.Gamepad.sThumbLY == 0
		&& m_state.Gamepad.sThumbLX == 0
		&& m_state.Gamepad.sThumbLY == 0)
	{
		return false;
	}
	return true;
}
