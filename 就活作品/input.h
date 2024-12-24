//==========================
// 
// 入力処理[input.h]
// Author Yuki Goto
//
//==========================
#ifndef _INPUT_H_
#define _INPUT_H_

//マクロ定義
#define MAX_KEY (256)//キーの最大数
#define MAX_JOYKEY (16)//ボタンの最大数

//入力規定クラス(DirectInputの管理)
class CInput
{
public:

	//メンバ関数
	CInput();//コンストラクタ
	~CInput();//デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);//初期化処理
	virtual void Uninit();//終了処理
	virtual void Update() = 0;//更新処理

protected:

	//メンバ変数
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボード入力クラス
class CInputKeyboard :public CInput
{
public:

	//メンバ関数
	CInputKeyboard();//コンストラクタ
	~CInputKeyboard();//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	bool GetPress(int nKey);//プレス情報を取得
	bool GetTrigger(int nKey);//トリガー情報を取得
	bool GetRelease(int nKey);//リリース情報を取得
private:

	//メンバ変数
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
	BYTE m_aKeyStateRelease[MAX_KEY];
};

//パッド入力クラス
class CInputJoypad :public CInput
{
public:

	//キーの種類
	typedef enum
	{
		JOYKEY_UP = 0,//十字キー(上)
		JOYKEY_DOWN,//十字キー(下)
		JOYKEY_LEFT,//十字キー(左)
		JOYKEY_RIGHT,//十字キー(右)
		JOYKEY_START,//STRATキー
		JOYKEY_BACK,//BACKキー
		JOYKEY_LEFT_THUMB,//左スティック
		JOYKEY_RIGHT_THUMB,//右スティック
		JOYKEY_LB,//LBキー
		JOYKEY_RB,//RBキー
		JOYKEY_LEFT_TRIGGER,//LTキー
		JOYKEY_RIGHT_TRIGGER,//RTキー
		JOYKEY_A,//Aキー
		JOYKEY_B,//Bキー
		JOYKEY_X,//Xキー
		JOYKEY_Y,//Yキー
		JOYKEY_MAX
	}JOYKEY;

	//メンバ関数
	CInputJoypad();//コンストラクタ
	~CInputJoypad();//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	bool GetPress(JOYKEY Key);//プレス情報を取得
	bool GetTrigger(JOYKEY Key);//トリガー情報を取得
	bool GetRelease(JOYKEY Key);//
	bool GetTriggerPedal(JOYKEY Key);//トリガーペダルの情報を取得
	WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);// スティックの入力を方向パッドフラグに変換
	float GetRightAngle();//右スティックの角度取得
	float GetLeftAngle();//左スティックの角度取得
	bool Connection();//パッドが接続されているか判定
	bool GetRightStick();//スティックが入力されてるか判定
	bool GetLeftStick();//左スティックが入力されてるか判定
private:

	//メンバ変数
	XINPUT_STATE m_state;//ジョイパッドのプレス情報
	XINPUT_STATE m_stateTrigger;//ジョイパッドのトリガー情報;
	XINPUT_STATE m_StateRelease;
};
#endif