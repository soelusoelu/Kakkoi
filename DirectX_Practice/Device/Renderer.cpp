#include "Renderer.h"
#include "../Device/Sound.h"
#include "../UI/Texture.h"
#include "../UI/Sprite.h"

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

void Renderer::drawNumber(int number, Vector2 position, bool isRightAlignment) {
    // マイナスの場合は0
    number = Math::Max<int>(number, 0);

    constexpr int widthChar = 32; // 画像横幅
    constexpr int widthOfTexture = 512;
    constexpr float widthRate = static_cast<float>(widthChar) / static_cast<float>(widthOfTexture);

    //桁数計算(本当は=1)
    int digit = 0;
    if (isRightAlignment) {
        for (int i = number; i >= 10; i /= 10) {
            digit++;
        }
    }

    Sprite* sprite = new Sprite("number.png", Vector2(widthOfTexture, 64.f), 0.01f);
    sprite->setPosition(Vector2(position.x - widthChar * digit, position.y));

    // 数字を文字列化し、1文字ずつ取り出す
    for (auto n : std::to_string(number)) {
        // 数字のテクスチャが数字1つにつき幅32高さ64
        // 文字と文字を引き算し、整数値を取得している
        float num = (n - '0') * widthChar;
        num /= sprite->getSize().x;
        auto a = num + widthRate;
        sprite->setUV(num, 0, a, 1);
        sprite->draw();

        // 1文字描画したら1桁分右にずらす
        sprite->setPosition(Vector2(sprite->getPosition().x + widthChar, sprite->getPosition().y));
    }
    Sprite::destroy(sprite);
}

void Renderer::clear() {
    mShaders.clear();
    mTextures.clear();
    mSounds.clear();
}

std::unordered_map<ShaderType, std::shared_ptr<Shader>> Renderer::mShaders;
std::unordered_map<std::string, std::shared_ptr<Texture>> Renderer::mTextures;
std::unordered_map<std::string, std::shared_ptr<SoundInfo>> Renderer::mSounds;
