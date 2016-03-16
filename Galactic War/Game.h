//
// Game.h
//

#pragma once

#include "StepTimer.h"



// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();
    void Present();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> t_background;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> startB;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> menuB;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> titleT;


	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	DirectX::SimpleMath::Matrix background;
	DirectX::SimpleMath::Matrix background1;
	DirectX::SimpleMath::Matrix model;
	DirectX::SimpleMath::Matrix rotate[2];
	DirectX::SimpleMath::Matrix trans[2];
	DirectX::SimpleMath::Matrix scale[2];
	DirectX::SimpleMath::Vector3 m_cameraPos;
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;
	DirectX::SimpleMath::Vector2 m_screenPos1;
	DirectX::SimpleMath::Vector2 m_origin1;
	DirectX::SimpleMath::Vector2 m_screenPos2;
	DirectX::SimpleMath::Vector2 m_origin2;

	RECT m_fullscreenRect;

	float m_pitch;
	float m_yaw;


	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::GeometricPrimitive > m_background;
	std::unique_ptr<DirectX::GeometricPrimitive > m_background1;
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	
	
	

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};