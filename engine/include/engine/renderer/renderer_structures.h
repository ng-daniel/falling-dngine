#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "engine/utils/uuid.h"
#include "engine/utils/matrix.h"
#include "engine/utils/vector.h"

enum GraphicsAPI {
    OpenGL,
    Vulkan
};

/**
 * @brief Interface for graphics devices to define their own API specific data structures
 */
struct IGraphicsDeviceData {
    virtual ~IGraphicsDeviceData() = default;
};

/**
 * @brief Interface for graphics device shaders to define their own API specific shader structures
 */
struct IGraphicsDeviceShader {
    virtual ~IGraphicsDeviceShader() = default;
};

/**
 * @brief ID type for graphics device specific shader programs
 * 
 */
using SPDEVICE_RID = std::uint32_t;
constexpr SPDEVICE_RID INVALID_SPDEVICE_RID = 0;

/**
 * @brief ID type for graphics device specific textures.
 */
using TDEVICE_RID = std::uint32_t;
constexpr TDEVICE_RID INVALID_TDEVICE_RID = 0;

enum class MaterialTextureSlot : std::size_t {
    BaseColor = 0,
    MetallicRoughness,
    Normal,
    Occlusion,
    Emissive,
    Count
};

constexpr std::size_t MATERIAL_TEXTURE_SLOT_COUNT =
    static_cast<std::size_t>(MaterialTextureSlot::Count);

constexpr std::uint32_t MaterialTextureBit(MaterialTextureSlot slot) {
    return 1u << static_cast<std::uint32_t>(slot);
}

struct ShaderProgramData {
    UUID id = INVALID_UUID;
    SPDEVICE_RID deviceProgramId = INVALID_SPDEVICE_RID;
    
    UUID vertexShaderId = INVALID_UUID;
    UUID fragmentShaderId = INVALID_UUID;
};

struct PrimitiveRenderData {
    UUID meshId;
    int pIdx; // primitive index in the mesh data array
    UUID materialId = INVALID_UUID;
    std::unique_ptr<IGraphicsDeviceData> graphicsDeviceData;
};

/**
 * @brief Stores render data for a single mesh
 */
struct MeshRenderData {
    UUID meshId;
    bool initialized = false;
    std::vector<PrimitiveRenderData> primitives;
};

/**
 * @brief A single render submission from the main loop to the renderer
 */
struct RenderSubmission {
    MeshRenderData * mesh = nullptr;
    Matrix4 worldTransform;
};

/**
 * @brief Values shared by every draw command in a frame.
 *
 * Camera input will populate these in a later stage. They are identity matrices
 * until then.
 */
struct FrameUniformData {
    Matrix4 view;
    Matrix4 projection;
};

struct GraphicsDeviceMaterialData {
    UUID materialId = INVALID_UUID;

    Vector4 baseColorFactor = Vector4(1.0f);
    float metallicFactor = 1.0f;
    float roughnessFactor = 1.0f;
    float occlusionFactor = 1.0f;
    float normalFactor = 1.0f;
    Vector3 emissiveFactor = Vector3(0.0f);

    std::array<TDEVICE_RID, MATERIAL_TEXTURE_SLOT_COUNT> textures{};
    std::uint32_t textureMask = 0;

    bool HasTexture(MaterialTextureSlot slot) const {
        return (textureMask & MaterialTextureBit(slot)) != 0;
    }
};

/**
 * @brief A fully resolved primitive draw for the graphics device.
 */
struct DrawCommand {
    PrimitiveRenderData* primitive = nullptr;
    SPDEVICE_RID shaderProgram = INVALID_SPDEVICE_RID;
    Matrix4 model;
    GraphicsDeviceMaterialData material;
};

/**
 * @brief Device-ready data for a single frame.
 */
struct RenderData {
    FrameUniformData frame;
    std::vector<DrawCommand> commands;
};
