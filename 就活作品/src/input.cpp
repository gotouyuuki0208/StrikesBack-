//==========================
// 
// 入力処理[input.h]
// Author Yuki Goto
//
//==========================

//include
#include"input.h"

//静的メンバ
LPDIRECTINPUT8 CInput::m_pInput;

//==========基底クラス==========

//==============================
// コンストラクタ
//==============================
CInput::CInput(void)
{

}

//==============================
// デストラクタ
//==============================
CInput::~CInput(void)
{

}

//==============================
// 初期設定
//==============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	return S_OK;
}

//==============================
// 終了処理
//==============================
void CInput::Uninit(void)
{

}

//===========キーボード入力クラス==========

//==============================
// コンストラクタ
//==============================
CInputKeyboard::CInputKeyboard(void) : m_aKeyState(), m_aKeyStateTrigger(), m_aKeyStateRelease()
{

}

//==============================
// デストラクタ
//==============================
CInputKeyboard::~CInputKeyboard(void)
{

}

//==============================
//キーボードの初期化処理
//==============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&m_pInput), nullptr)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	//データフォーマットを生成
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//==============================
//キーボードの終了処理
//==============================
void CInputKeyboard::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//==============================
//キーボードの更新処理
//==============================
void CInputKeyboard::Update(void)
{

	BYTE aKeyState[MAX_KEY];//キーボードの入力情報
	int nCntKey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//キーボードのトリガー情報を保存
			m_aKeyStateRelease[nCntKey]= (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];//キーボードのリリース情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//==============================
//キーボードのプレス情報を取得
//==============================
bool CInputKeyboard::GetPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//==============================
//キーボードのトリガー情報を取得
//==============================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//==============================
//リリース情報を取得
//==============================
bool CInputKeyboard::GetRelease(int nKey)
{
	return ((m_aKeyStateRelease[nKey] & 0x80) != 0) ? true : false;
}

//===========パッド入力クラス==========

//==============================
// コンストラクタ
//==============================
CInputJoypad::CInputJoypad(void):m_state(), m_stateTrigger(), m_StateRelease()
{
	
}

//==============================
// デストラクタ
//==============================
CInputJoypad::~CInputJoypad(void)
{

}

//==============================
//ジョイパッドの初期化処理
//==============================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//メモリのクリア
	memset(&m_state, 0, sizeof(XINPUT_STATE));
	memset(&m_stateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//==============================
//ジョイパッドの終了処理
//==============================
void CInputJoypad::Uninit(void)
{
	//Xinputのステートを設定(無効にする)
	XInputEnable(false);
}

//==============================
//ジョイパッドの更新処理
//==============================
void CInputJoypad::Update(void)
{
	XINPUT_STATE JoyKeyState;//ジョイパッドの入力情報

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = JoyKeyState.Gamepad.wButtons;
		WORD OldButton = m_state.Gamepad.wButtons;
		m_stateTrigger.Gamepad.wButtons = ~OldButton & Button;//トリガー処理
		m_StateRelease.Gamepad.wButtons = ~Button & OldButton;

		m_state = JoyKeyState;//ジョイパッドのプレス情報を保存
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

	// 左スティックからの入力を方向パッドに変換
	m_state.Gamepad.wButtons |= ThumbToDPad(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

}

//==============================
//ジョイパッドのプレス情報を取得
//==============================
bool CInputJoypad::GetPress(JOYKEY Key)
{
	return (m_state.Gamepad.wButtons & (0x01 << Key));
}

//==============================
//トリガー情報を取得
//==============================
bool CInputJoypad::GetTrigger(JOYKEY Key)
{
	return (m_stateTrigger.Gamepad.wButtons & (0x01 << Key));
}

//==============================
//トリガー情報を取得
//==============================
bool CInputJoypad::GetRelease(JOYKEY Key)
{
	return (m_StateRelease.Gamepad.wButtons & (0x01 << Key));
}

//==============================
//トリガーペダル情報を取得
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
// スティックの入力を方向パッドフラグに変換
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
//右スティックの角度取得
//=========================================
float CInputJoypad::GetRightAngle()
{
	float angle = atan2f(m_state.Gamepad.sThumbRX, m_state.Gamepad.sThumbRY);
	return angle;
}

//=========================================
//左スティックの角度取得
//=========================================
float CInputJoypad::GetLeftAngle()
{
	float angle = atan2f(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY);
	return angle;
}

//=========================================
//パッドが接続か判定
//=========================================
bool CInputJoypad::Connection()
{
	XINPUT_STATE JoyKeyState;//ジョイパッドの入力情報
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		return true;
	}
	
	return false;
}

//=========================================
//スティックが入力されてるか判定
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
//左スティックが入力されてるか判定
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
