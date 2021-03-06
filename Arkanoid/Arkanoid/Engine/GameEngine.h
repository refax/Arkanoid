#pragma once
/************************************************************************/
/* This class give access to global resources                           */
/************************************************************************/

#include "Common\GeometryGenerator.h"

using MeshData = GeometryGenerator::MeshData;
using Vertex = GeometryGenerator::Vertex;

namespace DX
{
	class DeviceResources;
}

namespace Engine
{
	class Camera;
	struct DirectionalLight;
	struct AmbientLight;


	class GameEngine
	{

	public:
		static GameEngine* Instance();

		void Initialize(const std::shared_ptr<DX::DeviceResources>& deviceResources );

		inline std::shared_ptr<DX::DeviceResources> DeviceResources() const { return m_deviceResources; }
		inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList() const { return m_commandList;  }
		inline Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignature() const { return m_rootSignature;  }
		inline std::shared_ptr<Camera> GetActiveCamera() const{ return m_activeCamera; }
		inline std::shared_ptr<DirectionalLight> GetDirectionalLight() const { return m_directionalLight; }
		inline std::shared_ptr<AmbientLight> GetAmbientLight() const { return m_ambientLight; }
		inline void SetActiveCamera(std::shared_ptr<Camera>& camera) { m_activeCamera.reset(); m_activeCamera = camera; }

		inline const MeshData& GetSphereMeshData() const { return m_Sphere; }
		inline const MeshData& GetSquareMeshData() const { return m_Square; }
		inline const MeshData& GetCilinderMeshData() const { return m_Cilinder; }

		void BeginScene();
		void EndScene();


	private:
		GameEngine();
		~GameEngine();

		GameEngine(const GameEngine&);
		GameEngine& operator=(const GameEngine&) = default;



	private:
		static GameEngine* s_Instance;

		std::shared_ptr<DX::DeviceResources>				m_deviceResources;
		std::shared_ptr<Camera>								m_activeCamera;
		std::shared_ptr<DirectionalLight>					m_directionalLight;
		std::shared_ptr<AmbientLight>						m_ambientLight;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;

		MeshData											m_Square;
		MeshData											m_Sphere;
		MeshData											m_Cilinder;
		
	};
}

