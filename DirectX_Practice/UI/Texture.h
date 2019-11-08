#pragma once

#include "../System/DirectXIncLib.h"
#include "../Utility/Math.h"
#include <list>
#include <memory>
#include <string>

//頂点の構造体
struct TextureVertex {
    Vector3 mPos; //位置
    Vector2 mTex; //テクスチャ座標
};

struct TextureShaderConstantBuffer {
    Matrix4 mWP;
    Vector4 mColor;
    Vector4 mUV;
};

class Shader;
class Sprite;

class Texture {
public:
    Texture();
    ~Texture();
    void init(const std::string& fileName);
    static void end();
    static void drawAll(std::list<std::shared_ptr<Sprite>>* sprites);
    ID3D11ShaderResourceView* getTexture() const;

private:
    HRESULT createTexture(const std::string& fileName);

private:
    static ID3D11SamplerState* mSampleLinear;//サンプラー
    static std::shared_ptr<Shader> mShader;
    static ID3D11Buffer* mVertexBuffer;
    ID3D11ShaderResourceView* mTexture; //テクスチャ
};

