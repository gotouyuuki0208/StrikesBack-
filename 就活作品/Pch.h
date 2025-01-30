//==========================
// 
//プリコンパイル済みヘッダー[Pch.h]
// Author Yuki Goto
//
//==========================
#pragma once

//include
#include<windows.h>
#include"d3dx9.h"//描画処理に必要
#define DIRECTINPUT_VERSION (0X0800)//ビルド時の警告対処用マクロ
#include"dinput.h"//入力処理に必要
#include"xaudio2.h"//サウンド処理に必要
#include"Xinput.h"//ジョイパッド処理に必要
#include<assert.h>
#include<iostream>
#include<fstream>
#include<random>
#include<string>
#include<cmath>
#include<iterator>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//システム時刻取得に必要
#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要

//マクロ定義
#define SCREEN_WIDTH (1280)//ウインドウの幅
#define SCREEN_HEIGHT (720)//高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define CLASS_NAME "windowClass"//ウィンドウクラスの名前
#define WINDOW_NAME "Strikes Back"//ウインドウの名前

#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK , __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用係数(1.0fで固定)
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 nor;//法線ベクトル
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_3D;