//==========================
// 
// カメラ処理[camera.h]
// Author Yuki Goto
//
//==========================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//カメラクラスの定義
class CCamera
{
public:
	//定数
	static const float Y_DISTANCE;//距離
	static const float Z_DISTANCE;//距離

	//メンバ関数
	CCamera();//コンストラクタ
	~CCamera();//デストラクタ
	HRESULT Init();//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
	void SetCamera();//カメラの設定
	void SetShape(int flame, int scale);//カメラ揺れ設定
	void Move(D3DXVECTOR3 pos);//カメラの移動
	void VerticalMove(D3DXVECTOR3 pos);//カメラの縦移動
	D3DXVECTOR3& GetPosR();//注視点の取得
	void OutGame(D3DXVECTOR3 pos);//インゲーム以外のカメラ
	D3DXVECTOR3& GetRot();//向きの取得
	void Overhead(D3DXVECTOR3 pos);//頭上から写す
private:
	//メンバ関数
	void Input();//入力処理

	//メンバ変数
	D3DXVECTOR3 m_posV;//視点
	D3DXVECTOR3 m_posR;//注視点
	D3DXVECTOR3 m_targetposV;//視点
	D3DXVECTOR3 m_targetposR;//注視点
	D3DXVECTOR3 m_vecU;//上方向
	D3DXVECTOR3 m_rot;//向き
	D3DXVECTOR3 move;//移動値
	D3DXMATRIX m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;//ビューマトリックス
	float m_PosVY;//視点のY座標
	float m_PosRY;//注視点のY座標
	int m_nFlame;//フレーム数
	int m_fShapeScale;//揺れの量
};

#endif