/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include <random>

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5.0f);
		const Vec3 at(0.0f);
		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera用のビュー
		m_PlayerCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<PlayerCamera>();
		ptrMyCamera->SetEye(eye);
		ptrMyCamera->SetAt(at);
		m_PlayerCameraView->SetCamera(ptrMyCamera);
		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetMyLighting();
	}

	//スコアスプライト作成
	void GameStage::CreateScoreSprite() {
		auto ptrScore = AddGameObject<ScoreSprite>(3,
			L"NUMBER_TX",
			true,
			Vec2(250.0f, 100.0f),
			Vec3(0.0f, 300.0f, 0.0f));
		ptrScore->SetScore(m_TotalTime);
		SetSharedGameObject(L"ScoreSprite", ptrScore);
	}

	//木の作成
	void GameStage::CreateTreeObjects(const Vec2& mapSize, const Vec3& stageSize) {
		srand((unsigned int)time(NULL));
		for (int i = -int(stageSize.z * 0.5f); i < int(stageSize.z * 0.5f); i++) {
			for (int j = -int(stageSize.x * 0.5f); j < int(stageSize.x * 0.5f); j++) {
				if (-mapSize.x * 0.5f <= j && mapSize.x * 0.5f >= j && mapSize.y * 0.5f >= i) {
				}
				else {
					//40%の確立で生成
					if (float(rand() % 10 + 1) < 5) {
						AddGameObject<Tree>(Vec3(0.3f), Vec3(0.0f), Vec3(float(j) + 0.5f, 0.0f, float(i) + 0.5f));
					}
				}
			}
		}
	}

	void GameStage::CreateHPSprite() {
		Vec2 HPUIScale(200.0f,100.0f);
		Vec3 HPUIPos(-450.0f, 300.0f, 0.0f);
		auto ptrHP = AddGameObject<HPSprite>(L"HPGAUGE1_TX", 10.0f, HPUIScale, HPUIPos);
		ptrHP->SetDrawLayer(2);
		ptrHP = AddGameObject<HPSprite>(L"HPGAUGE2_TX", 10.0f, HPUIScale, HPUIPos + Vec3(6.5f,0.0f,0.0f));
		ptrHP->SetDrawLayer(3);
		SetSharedGameObject(L"PlayerHPSprite", ptrHP);
	}

	void GameStage::CreateObjectB_CSV() {
		auto group = CreateSharedObjectGroup(L"RescurTargetGroup");
		//CSVの行単位の配列
		vector<wstring> LineVec;
		//0番目のカラムがL"TilingFixedBox"である行を抜き出す
		ObjCsvfile.GetSelect(LineVec, 0, L"Tx_Box(Clone)");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (torkns[7] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[7].c_str());
			Rot.y = (torkns[8] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[8].c_str());
			Rot.z = (torkns[9] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[9].c_str());

			Vec3 Rot2(Rot.x - 45 / 3.1415f, Rot.y / 3.1415f, Rot.z - 90 / 3.1415f);
			AddGameObject<Rock>(Vec3(Pos.x, Pos.y - 0.5f, Pos.z), Scale, Rot);
		}

		ObjCsvfile.GetSelect(LineVec, 0, L"Cube");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 col_Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 col_Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			Vec3 col_Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			col_Rot.x = (torkns[7] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[7].c_str());
			col_Rot.y = (torkns[8] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[8].c_str());
			col_Rot.z = (torkns[9] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[9].c_str());

			//Vec3 Rot2(Rot.x - 45 / 3.1415f, Rot.y / 3.1415f, Rot.z - 90 / 3.1415f);
			AddGameObject<CollisionBox>(Vec3(col_Pos.x, col_Pos.y - 0.5f, col_Pos.z), col_Scale, col_Rot); //-1 * (* 13.74f )
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"stage");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 col_Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 col_Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			StagePos = col_Pos;
			StageScale = col_Scale;
			auto ground = AddGameObject<FixedBox>(col_Scale, Vec3(0.0f), col_Pos);
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Wall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 col_Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 col_Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			AddGameObject<CollisionBox>(Vec3(col_Pos.x, col_Pos.y - 0.5f, col_Pos.z), col_Scale,Vec3(0)); //-1 * (* 13.74f )

			if (col_Scale.x > StageWallScale.x) {
				StageWallScale.x = col_Scale.x;
			}
			if (col_Scale.z > StageWallScale.y) {
				StageWallScale.y = col_Scale.z;
			}
			AddGameObject<TransparentBox>(
				Vec3(col_Scale), 
				Vec3(0.0f),
				Vec3(col_Pos));
		}

		ObjCsvfile.GetSelect(LineVec, 0, L"Player");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			PlayerPos.x = (float)_wtof(torkns[1].c_str());
			PlayerPos.y = (float)_wtof(torkns[2].c_str());
			PlayerPos.z = (float)_wtof(torkns[3].c_str());

		}

		ObjCsvfile.GetSelect(LineVec, 0, L"RescurTarget_1");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			GoalCount++;
			group->IntoGroup(AddGameObject<RescurTarget_1>(Vec3(Pos), Vec3(0.25f), Vec3(0)));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"RescurTarget_2");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			GoalCount++;
			group->IntoGroup(AddGameObject<RescurTarget_2>(Vec3(Pos), Vec3(0.25f), Vec3(0)));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"maguma");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			magumaPos = Pos;
			AddGameObject<IncreaseObject2>(Pos);
			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Obj_Rock");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			AddGameObject<ObjRock>(Pos, Vec3(1), Vec3(0), L"HOTROCK_TX", false);

			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Obj_Cinder");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			AddGameObject<Obj_Cinder>(Pos,Pos.x);

			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		ObjCsvfile.GetSelect(LineVec, 0, L"Goal");
		for (auto& v : LineVec) {
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()-1),
				(float)_wtof(torkns[3].c_str())
			);
			GoalPos = Pos;
			//AddGameObject<Enemy>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
		App::GetApp()->GetScene<Scene>()->SetAllMember(GoalCount);
	}

	void GameStage::SetBackGroundColor(Col4 color) {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		ptrScene->SetClearColor(color);
	}

	void GameStage::SetBackGroundPlayerPosColor(Col4 posZeroCol, Col4 posMaxCol, float posSizeMax) {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrTrans = ptrPlayer->GetComponent<Transform>();
		auto playerPosCol = ptrTrans->GetPosition().y / posSizeMax;
		Col4 ZeroCol = posZeroCol - posZeroCol * playerPosCol;
		Col4 MaxCol = posMaxCol * playerPosCol;
		SetBackGroundColor(ZeroCol + MaxCol);
		//煙の濃度(alpha)
		auto ptrSmoke = GetSharedGameObject<Sprite>(L"SmokeSprite");
		ptrSmoke->SetAlpha(playerPosCol);
	}

	//カメラマンの作成
	void GameStage::CreateCameraman() {
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	void GameStage::CreateSmoke() {
		auto ptrHP = AddGameObject<Sprite>(L"SMOKE_TX", 10.0f, Vec2(1280.0f, 800.0f), Vec3(0.0));
		ptrHP->SetDrawLayer(1);
		SetSharedGameObject(L"SmokeSprite", ptrHP);
	}

	void GameStage::OnCreate() {
		try {
			auto ptrScene = App::GetApp()->GetScene<Scene>();
			wstring detadir;
			App::GetApp()->GetDataDirectory(detadir);
			ObjCsvfile.SetFileName(detadir + ptrScene->GetStageCSVKey()); // シーンクラスに保存されているステージを読み込む
			//ObjCsvfile.SetFileName(detadir + /*L"TestStage.csv");*/ L"SaveData25.csv");// SaveData.csv");// GameStageA.csv");
			ObjCsvfile.ReadCsv();

			CreateObjectB_CSV();

			//SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//マップのサイズに合わせて木を生成する
			CreateTreeObjects(StageWallScale, StageScale);
			auto ground = AddGameObject<FixedBox>(StageScale, Vec3(0.0f),StagePos);
			//ground->AddTag(L"Ground");
			//SetSharedGameObject(L"Stage", ground);

			auto goalObj = AddGameObject<GoalObject>(Vec3(1.0f), Vec3(0.0f, XM_PIDIV2, 0.0f), Vec3(GoalPos),GoalCount);
			SetSharedGameObject(L"Goal", goalObj);

			auto player = AddGameObject<Player>(Vec3(0.25f), Vec3(0.0f), PlayerPos);// Vec3(0.0f, 1.0f, 0.0f));
			SetSharedGameObject(L"Player", player);
			CreateHPSprite();
			CreateSmoke();
			//カメラマンの作成
			CreateCameraman();

			//AddGameObject<Enemy>(Vec3(4, 2, -7), Vec3(0.25f), Vec3(0));
			//AddGameObject<RescurNomalTarget>(Vec3(3.7f, 5, 4.4f), Vec3(0.25f), Vec3(0));
			//AddGameObject<RescurTarget_1>(Vec3(-2,5 , -2), Vec3(0.25f), Vec3(0));
			//AddGameObject<IncreaseObject>(magumaPos);

			//AddGameObject<TransparentBox>(Vec3(10.0f, 80.0f, 10.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 0.0f));
			CreateScoreSprite();
			//BGM
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"ERUPTION_WAV", XAUDIO2_LOOP_INFINITE, 0.0f);
			m_RescueBGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.07f);
			CreateSharedObjectGroup(L"PlayerBullet");
		}
		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {		
		auto goal = GetSharedGameObject<GoalObject>(L"Goal");

		SetBackGroundPlayerPosColor(m_Color, m_Color1, 2.24f);

		if (GetThis<GameStage>()->GetCameraSelect() == CameraSelect::openingCamera) {
			return;
		}
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime;
		if (m_TotalTime <= 0&&TimeUpFlg==false) {
			//App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::GameOver);
			AddGameObject<GameEndSplite>(Vec3(-740, 0, 0), Vec2(900.0f, 300.0f), Vec3(0), L"GAMEOVER_TX");
			TimeUpFlg = true;
		}
		//スコアを更新する
		if (goal->GetGoalflg() == false&&goal->GetEndflg() == false) {
			auto ptrScor = GetSharedGameObject<ScoreSprite>(L"ScoreSprite");
			ptrScor->SetScore(m_TotalTime);
			m_BGM->m_SourceVoice->SetVolume(0.0f + (1-(m_TotalTime / m_MAXTIME)) * 0.2f);
			GameEndFlg = true;
		}
		//クリア
		if (goal->GetGoalflg() && GameEndFlg) {
			AddGameObject<GameEndSplite>(Vec3(-740, 0, 0), Vec2(900.0f, 300.0f), Vec3(0), L"GAMECREAR_TX");
			GameEndFlg = false;
		}
		//ゲームオーバー
		if (goal->GetEndflg() && GameEndFlg&&TimeUpFlg==false) {
			AddGameObject<GameEndSplite>(Vec3(-740, 0, 0), Vec2(900.0f,300.0f), Vec3(0), L"GAMEOVER_TX");
			GameEndFlg = false;
			TimeUpFlg = false;
		}
	}
	void GameStage::StageChange() {
		auto goal = GetSharedGameObject<GoalObject>(L"Goal");
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&goal->GetGoalflg()) {
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Title);
		}
	}

	void GameStage::UpdateStage() {
		auto goal = GetSharedGameObject<GoalObject>(L"Goal");
		m_InputHandler.PushHandle(GetThis<GameStage>());
		if (m_IsUpdate) {
			Stage::UpdateStage();
		}
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage::ToPlayerCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<PlayerCamera>(m_PlayerCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_PlayerCameraView);
			m_CameraSelect = CameraSelect::playerCamera;
		}
	}

	void GameStage::OnPushStart() {
		if (m_IsUpdate) {
			m_IsUpdate = false;
		}
		else {
			m_IsUpdate = true;
		}
	}

}
//end basecross
