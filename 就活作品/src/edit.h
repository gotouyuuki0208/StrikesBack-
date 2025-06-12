//==========================
// 
// オブジェクト配置[edit.h]
// Author Yuki Goto
//
//==========================
#ifndef _EDIT_H_
#define _EDIT_H_

//include
#include"objectgame.h"
#include <list>

//オブジェクト配置クラスの定義
class CEdit
{
public:
	
	//定数
	static const float MOVE;//移動量
	static const float SCALE;//スケール

	//メンバ関数
	CEdit();//コンストラクタ
	~CEdit();//デストラクタ
	HRESULT Init();//初期設定
	void Update();//更新処理
	void Uninit();//終了処理
	void Load();//配置情報を読み込む
	void Save();//配置情報を書き出す
	void DeleteAll();//リストの全てのオブジェクトを削除
private:

	//保存する情報
	struct Keep
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rot;
		int ObjectType;
	};

	//メンバ関数
	void Move();//移動
	void Scale();//スケール変更
	void Rotate();//向きを変える
	void Content();//オブジェクトを配置
	
	CObjectgame* SetType();//オブジェクトの種類を設定
	void ChangeType();//オブジェクトの種類を設定
	void KeepInfo();//情報を保存
	void SwitchEditMode();//編集モードの切り替え
	void StageChange();//ステージを変更

	void CameraFollow();//カメラが追従するか設定
	void CameraPos();//カメラの位置

	void CreateImGuiWindow();//ImGuiのウィンドウを生成
	void ObjectImGui();//オブジェクトに関する操作
	void CameraImGui();//カメラに関する操作

	void JsonFildSave();
	void JsonEnemySave();
	void JsonWeaponSave();
	void JsonItemSave();
	void JsonBuildingSave();

	void JsonEnemyLoad();
	void JsonFildLoad();
	void JsonWeaponLoad();
	void JsonItemLoad();
	void JsonBuildingLoad();

	//メンバ変数
	list<CObjectgame*> m_Object;//配置オブジェクトリスト
	list<CObjectgame*>::iterator m_Objectite;//配置オブジェクトリストイテレーター
	Keep m_EditObjectKeep;//編集中のオブジェクトを保存
	CObjectgame* m_EditObject;//現在編集しているオブジェクト
	D3DXVECTOR3 m_pos;//位置
	D3DXVECTOR3 m_camerapos;//位置
	D3DXVECTOR3 m_scale;//スケール
	D3DXVECTOR3 m_rot;//向き
	bool m_EditMode;//編集モード(false:新規オブジェクト true:配置済みオブジェクト)
	bool m_MoveDirection;//移動方向(false:Z移動 true:Y移動)
	bool m_SwitchInput;//入力方法(false:Press true:Trigger)
	bool m_move;//移動の編集(false:位置 true:向き)
	bool m_Camera;//カメラの位置
	bool m_ChangeScale;//スケール変更
	int m_ObjectType;//オブジェクトの種類
	float m_ChangePosNum;//移動する位置の数値
	float m_ChangeScaleNum;//変更するスケールの数値
	int m_wave;
};
#endif