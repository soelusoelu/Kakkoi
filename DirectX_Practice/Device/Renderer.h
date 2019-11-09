#pragma once

#include "../Shader/Shader.h"
#include "../Utility/Math.h"
#include <memory>
#include <string>
#include <unordered_map>

class Texture;

class Renderer {
public:
    static std::shared_ptr<Shader> getShader(ShaderType type);
    static std::shared_ptr<Texture> getTexture(const std::string& fileName);

    static void clear();

private:
    static std::unordered_map<ShaderType, std::shared_ptr<Shader>> mShaders;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
};

