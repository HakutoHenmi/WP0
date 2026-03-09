#pragma once
#include "Particle.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace Engine {

class ParticleManager {
public:
    static ParticleManager* GetInstance();

    void Initialize(Renderer* renderer);
    
    // パーティクルの更新
    void Update(float dt);
    
    // パーティクルの描画（テクスチャごとにまとめて描画）
    void Draw(const Camera& cam);

    // パーティクルの放出
    void Emit(const std::string& texturePath, const Vector3& pos, const Vector3& vel, const Vector3& acceleration, 
              const Vector3& startScale, const Vector3& endScale,
              const Vector4& startColor, const Vector4& endColor, 
              float life, const Vector3& angVel = {0,0,0}, float damping = 0.0f);

    // 全クリア
    void ClearAll();

private:
    ParticleManager() = default;
    ~ParticleManager() = default;
    ParticleManager(const ParticleManager&) = delete;
    ParticleManager& operator=(const ParticleManager&) = delete;

    Renderer* renderer_ = nullptr;
    
    // テクスチャパスをキーとしたParticleSystemのマップ
    std::unordered_map<std::string, std::unique_ptr<ParticleSystem>> systems_;
    
    // デフォルトのメッシュパス（必要に応じて変更可能にすべきだが、一旦固定あるいは引数で）
    std::string defaultMeshPath_ = "Resources/plane.obj";
};

} // namespace Engine
