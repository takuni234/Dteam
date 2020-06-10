/*!
@file GameOverStage.cpp
@brief ゲームオーバーステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームオーバーステージ実体
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//点滅するスプライト作成
	void GameOverStage::CreatePushSprite() {
		//ステージの背景
		auto ptrSprite = AddGameObject<Sprite>(L"GAMEOVER_BACKGROUND_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-3);
		//UI フレーム
		ptrSprite = AddGameObject<Sprite>(L"RESULT_FRAME1_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-2);
		//「ゲームオーバー」
		ptrSprite = AddGameObject<Sprite>(L"GAMEOVER_TX", Vec2(900.0f, 300.0f), Vec3(0.0f, 220.0f,0.0f));
		ptrSprite->SetDrawLayer(-1);
	}

	void GameOverStage::CreateSprite() {
		CreateSharedObjectGroup(L"GameOverSprite");
		//配置する位置（全体）
		Vec3 DefultPos(0.0f, 50.0f, 0.0f);
		Vec3 alignVec(0.0f);
		for (int i = 0; i < static_cast<int>(GameOverStageMenuKey::Max); i++) {
			Vec2 createScale(450.0f, 150.0f);
			Vec3 createPos(Vec3(0.0f, -i * 150.0f, 0.0f) + DefultPos);
			wstring txKey;
			switch (static_cast<GameOverStageMenuKey>(i))
			{
				// 「ステージセレクトへ」の画像
			case GameOverStageMenuKey::Select:
				txKey = L"TOSTAGESELECT_TX";
				break;
				// 「リトライ」の画像
			case GameOverStageMenuKey::Retry:
				txKey = L"TORETRY_TX";
				break;
				// 「タイトルへ」の画像
			case GameOverStageMenuKey::Title:
				txKey = L"TOTITLE_TX";
				break;
			default:
				//エラー
				txKey = L"SKY_TX";
				break;
			}
			if (m_SpriteAlign) {
				//左揃え
				alignVec = Vec3(createScale.x, 0.0f, 0.0f) * 0.5f;
			}
			auto ptrSprite = AddGameObject<Sprite>(txKey, createScale, createPos + alignVec);
			m_GameOverSpriteDefultScale.push_back(ptrSprite->GetComponent<Transform>()->GetScale());
			m_GameOverSpritePos.push_back(createPos);
			GetSharedObjectGroup(L"GameOverSprite")->IntoGroup(ptrSprite);
		}

		auto ptrCursol = AddGameObject<Sprite>(L"LEFTARROWCURSOL_TX", Vec2(50.0f));
		ptrCursol->SetPosition(DefultPos + Vec3((m_GameOverSpriteDefultScale[static_cast<int>(GameOverStageMenuKey::Select)].x + ptrCursol->GetScale().x) * 0.5f, 0.0f, 0.0f) + alignVec);
		SetSharedGameObject(L"GameOverCursor", ptrCursol);
	}

	void GameOverStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePushSprite();
			CreateSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void GameOverStage::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		StageSelectKeyInput();
		bool start =
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START ||
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
			KeyState.m_bPressedKeyTbl[VK_SPACE];

		UpdateCursor();

		if (start) {
			ChangeStageSceneSelected();
		}
	}

	void GameOverStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameOverStage::StageSelectKeyInput() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		int currentNum = m_SelectNum;

		if (CntlVec[0].bConnected) {
			if (!m_InputOnce) {
				if (CntlVec[0].fThumbLY >= 0.9f) {
					m_SelectNum--;
					m_InputOnce = true;
				}
				else if (CntlVec[0].fThumbLY <= -0.9f) {
					m_SelectNum++;
					m_InputOnce = true;
				}
			}
			else {
				m_Time += elapsedTime;
				if (m_Time > 0.3f) {
					m_InputOnce = false;
					m_Time = 0.0f;
				}
			}
			if (CntlVec[0].fThumbLY <= 0.05f && CntlVec[0].fThumbLY >= -0.05f) {
				m_InputOnce = false;
				m_Time = 0.0f;
			}
		}
		else if (!(KeyState.m_bPushKeyTbl['S'] && KeyState.m_bPushKeyTbl['D'])) {
			if (!m_InputOnce) {
				if (KeyState.m_bPushKeyTbl['S']) {
					m_SelectNum++;
					m_InputOnce = true;
				}
				if (KeyState.m_bPushKeyTbl['W']) {
					m_SelectNum--;
					m_InputOnce = true;
				}
			}
			else {
				m_Time += elapsedTime;
				if (m_Time > 0.3f) {
					m_InputOnce = false;
					m_Time = 0.0f;
				}
			}
			if (KeyState.m_bUpKeyTbl['S'] && KeyState.m_bUpKeyTbl['W']) {
				m_InputOnce = false;
				m_Time = 0.0f;
			}
		}

		if (currentNum != m_SelectNum) {
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"CURSOR_WAV", 0, 0.1f);
		}
		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(GameOverStageMenuKey::Max);
		}
		m_MenuKey = GameOverStageMenuKey(m_SelectNum % static_cast<int>(GameOverStageMenuKey::Max));
	}

	void GameOverStage::UpdateCursor() {
		auto ptrCursor = GetSharedGameObject<Sprite>(L"GameOverCursor");
		auto ptrTrans = ptrCursor->GetComponent<Transform>();
		Vec3 alignVec(0.0f);
		if (m_SpriteAlign) {
			//左揃え
			alignVec = Vec3(m_GameOverSpriteDefultScale[static_cast<int>(m_MenuKey)].x, 0.0f, 0.0f) * 0.5f;
		}
		ptrTrans->SetPosition(m_GameOverSpritePos[static_cast<int>(m_MenuKey)] + Vec3((m_GameOverSpriteDefultScale[static_cast<int>(m_MenuKey)].x + ptrTrans->GetScale().x) * 0.5f, 0.0f, 0.0f) + alignVec);
	}

	void GameOverStage::ChangeStageSceneSelected() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		switch (m_MenuKey)
		{
		case GameOverStageMenuKey::Select:
			ptrScene->ChangeScene(SceneKey::Select);
			break;
		case GameOverStageMenuKey::Retry:
			ptrScene->ChangeScene(SceneKey::Game);
			break;
		case GameOverStageMenuKey::Title:
			ptrScene->ChangeScene(SceneKey::Title);
			break;
		default:
			break;
		}
	}
}
//end basecross
