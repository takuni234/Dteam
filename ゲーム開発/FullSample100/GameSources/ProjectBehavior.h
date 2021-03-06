/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (keyState.m_bPressedKeyTbl['B']) {
				Obj->OnPushA();
				return;
			}
			if (keyState.m_bUpKeyTbl['B']) {
				Obj->OnUpA();
				return;
			}
			if (keyState.m_bPressedKeyTbl['M']) {
				Obj->OnPushB();
				return;
			}			
			if (keyState.m_bUpKeyTbl['M']) {
				Obj->OnUpB();
				return;
			}
			if (keyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushX();
				return;
			}
			if (keyState.m_bUpKeyTbl[VK_SPACE]) {
				Obj->OnUpX();
				return;
			}
			if (keyState.m_bPressedKeyTbl['C']) {
				Obj->OnPushY();
				return;
			}
			if (keyState.m_bUpKeyTbl['C']) {
				Obj->OnUpY();
				return;
			}
			if (keyState.m_bPressedKeyTbl['Z']) {
				Obj->OnPushStart();
				return;
			}
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				if (cntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A) {

				}
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				if (cntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnUpB();
				}
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				if (cntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnUpX();
				}
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
					Obj->OnPushY();
				}
				if (cntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_Y) {
					Obj->OnUpY();
				}
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START) {
					Obj->OnPushStart();
				}
			}
		}
	};
}

//end basecross

