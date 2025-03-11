#pragma once
#include <IRender.h>
namespace nsK2EngineLow {
	class RenderingEngine
	{
		void AddRenderObject(IRender* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}
		std::vector< IRender* > m_renderObjects;                      // 描画オブジェクトのリスト。

	};
}

