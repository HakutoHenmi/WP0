#pragma once
#include <d3d12.h>
#include <wrl/client.h>
#include <cstdint>
#include <vector>

namespace Engine {

class SrvManager {
public:
    static SrvManager* GetInstance();

    void Initialize(ID3D12Device* device);
    
    // SRVインデックスの割り当て（静的）
    uint32_t AllocateSrvIndex(uint32_t count = 1);
    
    // 動的SRVインデックスの割り当て（フレームごと）
    uint32_t AllocateDynamicSrvIndex(uint32_t count = 1);
    
    // 動的カーソルのリセット（フレーム開始時）
    void ResetDynamicCursor();

    // ハンドルの取得
    D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

    // テクスチャ用SRVの作成
    void CreateSRVForTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevels);
    
    // StructuredBuffer用SRVの作成
    void CreateSRVForStructuredBuffer(uint32_t srvIndex, ID3D12Resource* pResource, UINT numElements, UINT structureByteStride);

    ID3D12DescriptorHeap* GetDescriptorHeap() const { return descriptorHeap_.Get(); }
    uint32_t GetDescriptorSize() const { return descriptorSize_; }
    ID3D12Device* GetDevice() const { return device_; }

    static constexpr uint32_t kMaxSRVs = 2048;
    static constexpr uint32_t kStaticMax = 1000;

private:
    SrvManager() = default;
    ~SrvManager() = default;
    SrvManager(const SrvManager&) = delete;
    SrvManager& operator=(const SrvManager&) = delete;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
    uint32_t descriptorSize_ = 0;
    
    uint32_t srvCursor_ = 10; // 0-9は予約（メインレンダーターゲット用など）
    uint32_t srvDynamicCursor_ = kStaticMax;

    ID3D12Device* device_ = nullptr;
};

} // namespace Engine
