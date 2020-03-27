/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<PlayerCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			auto ground = AddGameObject<FixedBox>(Vec3(30.0f, 1.0f, 30.0f), Vec3(0.0f), Vec3(0.0f, -1.0f, 0.0f));
			ground->AddTag(L"Ground");
			AddGameObject<Player>(Vec3(0.25f), Vec3(0.0f), Vec3(0.0f,1.0f,0.0f));
			AddGameObject<RescurNomalTarget>(Vec3(1, 0, 1), Vec3(1), Vec3(0));
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
