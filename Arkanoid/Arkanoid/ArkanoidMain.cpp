#include "pch.h"
#include "ArkanoidMain.h"
#include "Common\DirectXHelper.h"
#include "Engine\GameEngine.h"

using namespace Arkanoid;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;
using namespace Engine;

// The DirectX 12 Application template is documented at https://go.microsoft.com/fwlink/?LinkID=613670&clcid=0x409

// Loads and initializes application assets when the application is loaded.
ArkanoidMain::ArkanoidMain()
{
	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

// Creates and initializes the renderers.
void ArkanoidMain::CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	// initialize my Engine
	//EngineRes::Initialize(deviceResources);
	GameEngine::Instance()->Initialize(deviceResources);

	m_sceneRenderer = std::unique_ptr<LevelOne>(new LevelOne());

	m_sceneRenderer->Start();

	OnWindowSizeChanged();
}

// Updates the application state once per frame.
void ArkanoidMain::Update()
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		m_sceneRenderer->Update(m_timer);
	});
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool ArkanoidMain::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	// Render the scene objects.
	GameEngine::Instance()->BeginScene();
	m_sceneRenderer->Render();
	GameEngine::Instance()->EndScene();

	return true;
}

// Updates application state when the window's size changes (e.g. device orientation change)
void ArkanoidMain::OnWindowSizeChanged()
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->OnWindowResizeEvent();
}

// Notifies the app that it is being suspended.
void ArkanoidMain::OnSuspending()
{
	// TODO: Replace this with your app's suspending logic.

	// Process lifetime management may terminate suspended apps at any time, so it is
	// good practice to save any state that will allow the app to restart where it left off.

	//m_sceneRenderer->SaveState();

	// If your application uses video memory allocations that are easy to re-create,
	// consider releasing that memory to make it available to other applications.
}

// Notifes the app that it is no longer suspended.
void ArkanoidMain::OnResuming()
{
	// TODO: Replace this with your app's resuming logic.
}

// Notifies renderers that device resources need to be released.
void ArkanoidMain::OnDeviceRemoved()
{
	// TODO: Save any necessary application or renderer state and release the renderer
	// and its resources which are no longer valid.
	//m_sceneRenderer->SaveState();
	m_sceneRenderer = nullptr;
}
