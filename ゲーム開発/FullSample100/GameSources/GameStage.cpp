/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<PlayerCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<FixedBox>(
				Vec3(30.0f,1.0f,30.0f),	//const Vec3& Scale,
				Vec3(0.0f),				//const Vec3& Rotation,
				Vec3(0.0f,-1.0f,0.0f)	//const Vec3& Position
				);
			auto player = AddGameObject<Player>(Vec3(0.25f), Vec3(0.0f), Vec3(0.0f, 1.0f, 0.0f));
			SetSharedGameObject(L"Player", player);

			AddGameObject<RescurNomalTarget>(Vec3(1, 0, 1), Vec3(0.25f), Vec3(0));
			AddGameObject<RescurTarget_1>(Vec3(-2, 0, -2), Vec3(0.25f), Vec3(0));
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
