#include "ParticleManager.h"
#include "Renderer.h"

namespace Engine {

ParticleManager* ParticleManager::GetInstance() {
    static ParticleManager instance;
    return &instance;
}

void ParticleManager::Initialize(Renderer* renderer) {
    renderer_ = renderer;
    systems_.clear();
}

void ParticleManager::Update(float dt) {
    for (auto& pair : systems_) {
        pair.second->Update(dt);
    }
}

void ParticleManager::Draw(const Camera& cam) {
    for (auto& pair : systems_) {
        // 全てのParticleSystemについてDrawを呼ぶ
        // ParticleSystem内部でインスタンス描画予約が行われる
        pair.second->Draw(cam);
    }
}

void ParticleManager::Emit(const std::string& texturePath, const Vector3& pos, const Vector3& vel, const Vector3& acceleration, 
                          const Vector3& startScale, const Vector3& endScale,
                          const Vector4& startColor, const Vector4& endColor, 
                          float life, const Vector3& angVel, float damping) {
    
    // システムがなければ作成
    if (systems_.find(texturePath) == systems_.end()) {
        auto newSys = std::make_unique<ParticleSystem>();
        newSys->Initialize(*renderer_, 1000, defaultMeshPath_, texturePath);
        systems_[texturePath] = std::move(newSys);
    }
    
    systems_[texturePath]->Emit(pos, vel, acceleration, startScale, endScale, startColor, endColor, life, angVel, damping);
}

void ParticleManager::ClearAll() {
    for (auto& pair : systems_) {
        pair.second->Clear();
    }
}

} // namespace Engine
