#include "Renderer.h"
#include "../Device/Sound.h"
#include "../UI/Texture.h"

std::shared_ptr<Shader> Renderer::getShader(ShaderType type) {
    std::shared_ptr<Shader> shader;
    auto itr = mShaders.find(type);
    if (itr != mShaders.end()) { //既に読み込まれている
        shader = itr->second;
    } else { //初読み込み
        shader = std::make_shared<Shader>();
        shader->init(type);
        mShaders.emplace(type, shader);
    }
    return shader;
}

std::shared_ptr<Texture> Renderer::getTexture(const std::string& fileName) {
    std::shared_ptr<Texture> texture;
    auto itr = mTextures.find(fileName);
    if (itr != mTextures.end()) { //既に読み込まれている
        texture = itr->second;
    } else { //初読み込み
        texture = std::make_shared<Texture>();
        texture->init(fileName);
        mTextures.emplace(fileName, texture);
    }
    return texture;
}

std::shared_ptr<SoundInfo> Renderer::getSound(const std::string& fileName) {
    std::shared_ptr<SoundInfo> soundInfo;
    auto itr = mSounds.find(fileName);
    if (itr != mSounds.end()) { //既に読み込まれている
        soundInfo = itr->second;
    } else { //初読み込み
        soundInfo = std::make_shared<SoundInfo>();
        Sound::load(fileName, soundInfo);
        mSounds.emplace(fileName, soundInfo);
    }
    return soundInfo;
}

void Renderer::clear() {
    mShaders.clear();
    mTextures.clear();
    mSounds.clear();
}

std::unordered_map<ShaderType, std::shared_ptr<Shader>> Renderer::mShaders;
std::unordered_map<std::string, std::shared_ptr<Texture>> Renderer::mTextures;
std::unordered_map<std::string, std::shared_ptr<SoundInfo>> Renderer::mSounds;
