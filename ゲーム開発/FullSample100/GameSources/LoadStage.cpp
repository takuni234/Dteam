/*!
@file LoadStage.cpp
@brief ロードステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ロードステージクラス
	//--------------------------------------------------------------------------------------
	bool LoadStage::m_Loaded = false;
	std::mutex LoadStage::mtx;

	//リソースロード用のスレッド（スタティック関数）
	void LoadStage::LoadResourceFunc() {
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		wstring DataDir;
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = DataDir + L"Ground.png";
		App::GetApp()->RegisterTexture(L"GROUND_TX", strTexture);
		strTexture = DataDir + L"Ground2.png";
		App::GetApp()->RegisterTexture(L"GROUND2_TX", strTexture);
		strTexture = DataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = DataDir + L"fire.png";
		App::GetApp()->RegisterTexture(L"FIRE_TX", strTexture);
		strTexture = DataDir + L"PushBButton.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = DataDir + L"TitleLogo.png";
		App::GetApp()->RegisterTexture(L"TITLELOGO_TX", strTexture);
		strTexture = DataDir + L"HelpMe.png";
		App::GetApp()->RegisterTexture(L"HELPTEXT_TX", strTexture);
		strTexture = DataDir + L"Tx_survivor.png";
		App::GetApp()->RegisterTexture(L"SURVIVOR_TX", strTexture);
		strTexture = DataDir + L"Tx_rescuecharacter2.png";
		App::GetApp()->RegisterTexture(L"RESCUECHARACTER_TX", strTexture);
		strTexture = DataDir + L"Tx_rock2.png";
		App::GetApp()->RegisterTexture(L"HOTROCK_TX", strTexture);
		
		auto modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Survivor7.bmf");
		App::GetApp()->RegisterResource(L"SURVIVOR_1", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Survivor8.bmf");
		App::GetApp()->RegisterResource(L"SURVIVOR_2", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Rescuecharacter8.bmf");
		App::GetApp()->RegisterResource(L"RESCUECHARACTER_MESH", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"HotRock3.bmf");
		App::GetApp()->RegisterResource(L"HOTROCK_MESH", modelMesh);

		//サウンド
		wstring DataWav = DataDir + L"cursor.wav";
		App::GetApp()->RegisterWav(L"cursor", DataWav);
		DataWav = DataDir + L"air_shot.wav";
		App::GetApp()->RegisterWav(L"ICEAX_ATTACK_WAV", DataWav);
		DataWav = DataDir + L"ゴゴゴゴ.wav";
		App::GetApp()->RegisterWav(L"ERUPTION_WAV", DataWav);
		DataWav = DataDir + L"石が砕ける.wav";
		App::GetApp()->RegisterWav(L"ROCK_DESTORY_WAV", DataWav);
		DataWav = DataDir + L"left_foot.wav";
		App::GetApp()->RegisterWav(L"WALK_LEFT_WAV", DataWav);
		DataWav = DataDir + L"right_foot.wav";
		App::GetApp()->RegisterWav(L"WALK_RIGHT_WAV", DataWav);
		//BGM
		wstring strMusic = DataDir + L"nanika .wav";
		App::GetApp()->RegisterWav(L"Nanika", strMusic);

		mtx.lock();
		m_Loaded = true;
		mtx.unlock();

	}

	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	}

	//スプライトの作成
	void LoadStage::CreateTitleSprite() {
		AddGameObject<Sprite>(L"WAIT_TX", Vec2(300.0f, 150.0f), Vec3(450.0f,-400.0f,0.0f));
		AddGameObject<SerialAnimeSprite>(L"LOADTEST_TX", true,
			Vec2(256.0f, 256.0f), Vec2(400.0f, -200.0f), 4, 1, 0.1f);
	}

	//初期化
	void LoadStage::OnCreate() {
		wstring DataDir;
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);
		//お待ちくださいのテクスチャのみここで登録
		wstring strTexture = DataDir + L"wait.png";
		App::GetApp()->RegisterTexture(L"WAIT_TX", strTexture);
		strTexture = DataDir + L"movetest.png";
		App::GetApp()->RegisterTexture(L"MOVETEST_TX", strTexture);
		strTexture = DataDir + L"タンク.png";
		App::GetApp()->RegisterTexture(L"LOADTEST_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		//他のリソースを読み込むスレッドのスタート
		std::thread LoadThread(LoadResourceFunc);
		//終了までは待たない
		LoadThread.detach();

		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
	}

	//更新
	void LoadStage::OnUpdate() {
		if (m_Loaded) {
			//リソースのロードが終了したらタイトルステージに移行
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Title);
		}
	}


}
//end basecross
