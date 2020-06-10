/*!
@file CopyrightInfoStage.cpp
@brief 著作権情報ステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	著作権情報ステージクラス実体
	//--------------------------------------------------------------------------------------
	void CopyrightInfoStage::CreateViewLight() {
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

	void CopyrightInfoStage::CreateSprite() {
		AddGameObject<Sprite>(L"COPYRIGHT_TX", Vec2(1280.0f,800.0f), Vec3(0.0f));
		auto ptrSprite = AddGameObject<Sprite>(L"FADE_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(10);
		SetSharedGameObject(L"FadeSprite", ptrSprite);
	}

	void CopyrightInfoStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateSprite();
		}
		catch (...) {
			throw;
		}
	}

	void CopyrightInfoStage::OnUpdate() {
		auto ptrSprite = GetSharedGameObject<Sprite>(L"FadeSprite");
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		if (m_Fade) {
			//リソースのロードが終了したらタイトルステージに移行
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Title);
		}
		if(ptrSprite->GetAlpha() > 0.0f && !m_FadeIn) {
			ptrSprite->SetAlpha(ptrSprite->GetAlpha() - elapsedTime * m_FadeSpeed);
			if (ptrSprite->GetAlpha() <= 0.0f) {
				m_FadeIn = true;
			}
		}
		if (m_FadeIn) {
			if (m_Time >= 3.0f) {
				if (ptrSprite->GetAlpha() < 1.0f) {
					ptrSprite->SetAlpha(ptrSprite->GetAlpha() + elapsedTime * m_FadeSpeed);
					if (ptrSprite->GetAlpha() >= 1.0f) {
						m_Fade = true;
					}
				}
			}
			else {
				m_Time += elapsedTime;
			}
		}
	}

	void CopyrightInfoStage::OnDestroy() {

	}

}
//end basecross
