﻿#include "Shader.h"
#include "../System/Game.h"
#include "../System/Direct3D11.h"
#include "../UI/Texture.h"

Shader::Shader() {
    ZeroMemory(this, sizeof(Shader));
}

Shader::~Shader() {
    SAFE_RELEASE(mVertexShader);
    SAFE_RELEASE(mVertexLayout);
    SAFE_RELEASE(mPixelShader);
    SAFE_RELEASE(mConstantBuffer0);
    SAFE_RELEASE(mConstantBuffer1);
    SAFE_RELEASE(mBlendState);
}

void Shader::init(ShaderType type) {
    if (type == ShaderType::Texture) {
        if (FAILED(initTextureShader())) {
            MessageBox(0, L"テクスチャ用シェーダー作成失敗", NULL, MB_OK);
        }
    }
}

HRESULT Shader::initTextureShader() {
    //hlslファイル読み込み ブロブ作成 ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
    ID3D10Blob* pCompiledShader = NULL;
    ID3D10Blob* pErrors = NULL;
    //ブロブからバーテックスシェーダー作成
    setShaderDirectory();
    if (FAILED(D3DX11CompileFromFile(L"Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL))) {
        MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
        return E_FAIL;
    }
    SAFE_RELEASE(pErrors);

    if (FAILED(Direct3D11::mDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mVertexShader))) {
        SAFE_RELEASE(pCompiledShader);
        MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
        return E_FAIL;
    }
    //頂点インプットレイアウトを定義
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = sizeof(layout) / sizeof(layout[0]);
    //頂点インプットレイアウトを作成
    if (FAILED(Direct3D11::mDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &mVertexLayout))) {
        return FALSE;
    }
    //ブロブからピクセルシェーダー作成
    if (FAILED(D3DX11CompileFromFile(L"Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL))) {
        MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
        return E_FAIL;
    }
    SAFE_RELEASE(pErrors);
    if (FAILED(Direct3D11::mDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &mPixelShader))) {
        SAFE_RELEASE(pCompiledShader);
        MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
        return E_FAIL;
    }
    SAFE_RELEASE(pCompiledShader);

    //コンスタントバッファー作成 ここでは変換行列渡し用
    D3D11_BUFFER_DESC cb;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.ByteWidth = sizeof(TextureShaderConstantBuffer);
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    cb.Usage = D3D11_USAGE_DYNAMIC;

    if (FAILED(Direct3D11::mDevice->CreateBuffer(&cb, NULL, &mConstantBuffer0))) {
        return E_FAIL;
    }

    //アルファブレンド用ブレンドステート作成
    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
    bd.IndependentBlendEnable = false;
    bd.AlphaToCoverageEnable = false;
    bd.RenderTarget[0].BlendEnable = true;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    if (FAILED(Direct3D11::mDevice->CreateBlendState(&bd, &mBlendState))) {
        return E_FAIL;
    }

    UINT mask = 0xffffffff;
    Direct3D11::mDeviceContext->OMSetBlendState(mBlendState, NULL, mask);

    return S_OK;
}
