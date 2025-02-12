#pragma once
#include "DxLib.h"

namespace
{
	constexpr int kTransparency = 160;	//ìßñæìx		ìßñæ{0} Å` é¿ë‘{255}   
}

// îºìßñæÇÃê›íË
#define DEBUG_TRANSPARENCY	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kTransparency);
// å≥Ç…ñﬂÇ∑
#define DEBUG_RESET	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);