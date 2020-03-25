#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RescurNomalTarget::RescurNomalTarget(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale, Vec3 rotate)
		:GameObject(stage), m_Position(pos), m_Scale(scale), m_Rotation(rotate) {

	}

	void RescurNomalTarget::OnCreate() {
		auto Drow = AddComponent<PNTStaticDraw>();
		Drow->SetMeshResource(L"DEFAULT_CUBE");
		Drow->SetDiffuse(Col4(1, 0, 0, 1));


	}

	void RescurNomalTarget::OnUpdate() {

	}

}