#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
namespace basecross {
	class GrabArea : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		GrabArea(const shared_ptr<Stage>& Stage, const Vec3& scale, const Vec3& rotation, const Vec3& position);
		virtual ~GrabArea() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

	};
}