#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "engine/utils/uuid.h"
#include "engine/renderer/debug_camera.h"
#include "engine/renderer/renderer_structures.h"
#include "engine/renderer/graphics_device.h"
#include "engine/utils/matrix.h"

#include "engine/assets/asset_manager.h"

class WindowManager;

class Renderer {
public:
    Renderer(AssetManager& assetManager);
    ~Renderer();

    void ConfigureWindow();
    bool Init(WindowManager& window);
    void BeginFrame();
    void SubmitMesh(UUID meshId, const Matrix4& worldTransform);
    void Render();
    void EndFrame();

    /// SHADER STUFF
    /// --------------------

    /**
     * @brief Compiles a runtime shader program on the graphics device and caches it by UUID.
     * @return The program UUID.
     */
    UUID RegisterShaderProgram(const ShaderProgramData& shaderProgram);

private:
    AssetManager& assetManagerRef;
    std::unique_ptr<GraphicsDevice> device;
    WindowManager* window = nullptr;
    DebugCamera debugCamera;

    std::vector<RenderSubmission> frameSubmissions;
    RenderData frameData;
    std::unordered_map<UUID, MeshRenderData> meshCache;
    std::unordered_map<UUID, ShaderProgramData> shaderCache;
    std::unordered_map<UUID, TDEVICE_RID> textureCache;

    MeshRenderData* GetOrCreateMeshRenderData(UUID meshId);
    TDEVICE_RID GetOrCreateTexture(UUID textureId);
    bool ResolveMaterial(
        UUID materialId,
        SPDEVICE_RID& shaderProgramId,
        GraphicsDeviceMaterialData& resolvedMaterial
    );
    void BuildDrawCommands();
};
