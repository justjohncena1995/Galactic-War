//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Gamestate.h"
#include "Planets.h"
#include "Player.h"
#include "Menu.h"
#include "Bullets.h"
#include "Asteroid.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



using Microsoft::WRL::ComPtr;

// smart pointers
std::unique_ptr<gameState> theGame(new gameState);
std::unique_ptr<planets> thePlanets(new planets);
std::unique_ptr<Player> thePlayer(new Player);
std::unique_ptr<Menu> theMenu(new Menu);
std::unique_ptr<Bullets> theBullets(new Bullets);
std::unique_ptr<Asteroid> theAsteroids(new Asteroid);


Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1),
	m_pitch(0),
	m_yaw(0)
{
 
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_window = window;
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateDevice();

	CreateResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
	
	// Setting the menu up first
	theGame->setMenu(true);

	// Initialize the mouse and keyboard 
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);


	// Player's Model properties
	thePlayer->playerlProperties();
	


	std::random_device rd;
	m_random = std::make_unique<std::mt19937>(rd());


	
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	auto mouse = m_mouse->GetState();

	// TODO: Add your game logic here.

	// Initializing the mouse controls for the menu
	if (theGame->getMenu() == true)
	{
		// Mouse input for the start button
		if ((mouse.x > startRect.left && mouse.x < startRect.right) && (mouse.y > startRect.top && mouse.y < startRect.bottom))
		{

			if (mouse.leftButton)
			{
				theGame->setMenu(false);
				theGame->setGame(true);
			}
		}
	}


	float elapsedTime = float(timer.GetElapsedSeconds());
	float time = float(timer.GetTotalSeconds());



	// rotation for the game background
	background = Matrix::CreateRotationX(time / 5);

	// rotaion for the menu background
	background1 = Matrix::CreateRotationY(time / 7);

	
	

	

	// Keyboard controls
	auto kb = m_keyboard->GetState();
	if (kb.Escape)
	PostQuitMessage(0);
	
	if (theGame->getgameP() == true)
	{
		for (int i = 0; i < 20; i++)
		{
			model1[i] = Matrix::CreateRotationY(1.0f);
			model1[i] = Matrix::CreateScale(0.009);
			std::uniform_real_distribution<float> distX(-5.f, 10.f);
			std::uniform_real_distribution<float> distY(-5.f, 10.f);
		    std::uniform_real_distribution<float> rotation(0.f, 360.f);

			theAsteroids->setXpos(distX(*m_random));
			theAsteroids->setYpos(distY(*m_random));


			model1[i] *= Matrix::CreateRotationY(rotation(*m_random));
			model1[i] *= Matrix::CreateTranslation(Vector3(theAsteroids->getXpos(), theAsteroids->getYpos(), 0.0f));
		}
		
	

		// Movement for player 1
		if (kb.A)
		{
			thePlayer->model = Matrix::CreateTranslation(-Vector3::Right) * Matrix::CreateRotationY(-0.1f) * thePlayer->model;
		}

		if (kb.S)
		{
			thePlayer->model = Matrix::CreateTranslation(-Vector3::Backward * 8) * Matrix::CreateRotationY(.0f) * thePlayer->model;
		}
		
		if (kb.D)
		{
			thePlayer->model = Matrix::CreateTranslation(-Vector3::Left) * Matrix::CreateRotationY(0.1f) * thePlayer->model;;
		}
		
	}


	
	

    elapsedTime;
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.


	float y = sinf(m_pitch);
	float r = cosf(m_pitch);
	float z = r*cosf(m_yaw);
	float x = r*sinf(m_yaw);

	

	if (theGame->getMenu() == true)
	{
		// Draw the background for the menu
		m_background1->Draw(background1, m_view, m_proj, Colors::White, menuB.Get());

		// Begin spriteBatch
		m_spriteBatch->Begin();
		// Draw start button
		m_spriteBatch->Draw(startB.Get(), startRect);
		// Draw title 
		m_spriteBatch->Draw(titleT.Get(), m_screenPos1, nullptr, Colors::White, 0.f, m_origin1);
		// Draw Exit button
		m_spriteBatch->Draw(exitB.Get(), exitRect);
		// End spriteBatch
		m_spriteBatch->End();

	}

	

	if (theGame->getgameP() == true)
	{
			
		// Draw player model
		thePlayer->m_model->Draw(m_d3dContext.Get(), *m_states, thePlayer->model, m_view, m_proj);

		
		for (int j = 0; j < 20; j++)
		{
			asteroid->Draw(m_d3dContext.Get(), *m_states, model1[j], m_view, m_proj);
		}

		
		
	   // Draw background
		m_background->Draw(background, m_view, m_proj, Colors::White, t_background.Get());	

		
	}

	

    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter;
            memset(&filter, 0, sizeof(filter));
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).

	// Initializing the spritebatch
	m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());
	// Creating the resource for the spritbatch
	ComPtr<ID3D11Resource> resource;
	// Setting the texture for the start button
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"start.jpg",resource.GetAddressOf(),
	startB.ReleaseAndGetAddressOf()));
	// Creating the texture resource
	ComPtr<ID3D11Texture2D> button;
	DX::ThrowIfFailed(resource.As(&button));
	// Creating the button description
	CD3D11_TEXTURE2D_DESC butDesc;
	button->GetDesc(&butDesc);

	// Creating the exit button
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"Exit.jpg", resource.GetAddressOf(), exitB.ReleaseAndGetAddressOf()));

	// Drawing the title 
	m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get()); 
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"galacticwar.png", resource.GetAddressOf(),
	titleT.ReleaseAndGetAddressOf()));
	// Title origin 
	m_origin1.x = float(butDesc.Width / 2);
	m_origin1.y = float(butDesc.Height / 2);

	// Creating the common states for the model
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	// Creating the factory for the sharing and texture resources
	m_fxFactory = std::make_unique<EffectFactory>(m_d3dDevice.Get());

	// Creating the background 
	m_background = GeometricPrimitive::CreateSphere(m_d3dContext.Get(), 9.f, 10, false, true);
	m_background->CreateInputLayout(m_effect.get(), m_inputLayout.ReleaseAndGetAddressOf());

	// Creating the memu background
	m_background1 = GeometricPrimitive::CreateSphere(m_d3dContext.Get(), 9.f, 10, false, false);
	m_background1->CreateInputLayout(m_effect.get(), m_inputLayout.ReleaseAndGetAddressOf());

	// Moon Planet
	world[0] = GeometricPrimitive::CreateSphere(m_d3dContext.Get(), 0.1f);
	

	// Menu Background
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"menubackground.jpg", nullptr,
	menuB.ReleaseAndGetAddressOf()));

	// Create player model
	thePlayer->m_model = Model::CreateFromSDKMESH(m_d3dDevice.Get(), L"myship1.sdkmesh", *m_fxFactory);
	
	// Creating second player
	asteroid = Model::CreateFromSDKMESH(m_d3dDevice.Get(), L"rock1.sdkmesh", *m_fxFactory);

	// Texture for background
	DX::ThrowIfFailed(CreateWICTextureFromFile(m_d3dDevice.Get(), L"background.jpg", nullptr, t_background.ReleaseAndGetAddressOf()));

	// Setting the background
	m_effect->SetTexture(t_background.Get());

	m_world = Matrix::Identity;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.

	// Camera Settings
	m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),Vector3(thePlayer->model._41,thePlayer->model._42 -3,thePlayer->model._43 -3), Vector3::UnitY);
	// Projection settings
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, float(backBufferWidth) / float(backBufferHeight), 0.1f, 10.f);

	
	// Start Button properties 
	startRect.left = backBufferHeight / 9.f;
	startRect.right = backBufferHeight / 2.f;
	startRect.bottom = backBufferWidth / 3.f;
	startRect.top = backBufferWidth / 4.5f;

	exitRect.left = backBufferHeight / 2.f;
	exitRect.right = backBufferHeight / 2.f;
	exitRect.bottom = backBufferWidth / 4.f;
	exitRect.top = backBufferWidth / 3.f;

	// Title screen screen position
	m_screenPos1.x = backBufferWidth / 5.f;
	m_screenPos1.y = backBufferHeight / 9.1f;

	// Setting the lighting 
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);

	
}


void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	// Releasing the memory
	moonT.Reset();
	world[0].reset();
	menuB.Reset();
	m_spriteBatch.reset();
	startB.Reset();
	m_effect.reset();
	m_inputLayout.Reset();
	t_background.Reset();
	m_background.reset();
	m_states.reset();
	m_fxFactory.reset();
	asteroid.reset();
	m_model.reset();
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}