#pragma once

#include "../System/DirectXIncLib.h"

enum class ShaderType {
    Mesh,
    Texture
};

class Shader {
public:
    Shader();
    ~Shader();
    void init(ShaderType type);

    ID3D11VertexShader* getVertexShader() const {
        return mVertexShader;
    }
    ID3D11InputLayout* getVertexLayout() const {
        return mVertexLayout;
    }
    ID3D11PixelShader* getPixelShader() const {
        return mPixelShader;
    }
    ID3D11Buffer* mConstantBuffer0;
    ID3D11Buffer* mConstantBuffer1;

private:
    HRESULT initTextureShader();

    ID3D11VertexShader* mVertexShader;
    ID3D11InputLayout* mVertexLayout;
    ID3D11PixelShader* mPixelShader;
    ID3D11BlendState* mBlendState; //アルファブレンディング
};

