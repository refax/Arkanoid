#pragma once
#include "Engine/SceneController.h"

namespace Engine
{
	class Square;
}

class LevelOne : public Engine::SceneController
{
public:
	explicit LevelOne();
	virtual ~LevelOne();




private:
	void doOnWindowsResizeEvent() override;
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;


private:
	class Engine::Square* m_square;
};
