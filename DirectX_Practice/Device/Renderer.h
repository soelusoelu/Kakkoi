#pragma once

#include "../Device/Sound.h"
#include "../Shader/Shader.h"
#include "../Utility/Math.h"
#include <memory>
#include <string>
#include <unordered_map>

class Sprite;
class Texture;

class Renderer {
public:
    static std::shared_ptr<Shader> getShader(ShaderType type);
    static std::shared_ptr<Texture> getTexture(const std::string& fileName);
    static std::shared_ptr<SoundInfo> getSound(const std::string& fileName);
    static void drawNumber(int number, Vector2 position, bool isRightAlignment = false);

    static void clear();

private:
    static std::unordered_map<ShaderType, std::shared_ptr<Shader>> mShaders;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
    static std::unordered_map<std::string, std::shared_ptr<SoundInfo>> mSounds;
};

