#pragma once

#include "SceneBase.h"

class Title : public SceneBase {
public:
    Title();
    ~Title();
    virtual void updateScene() override;
    virtual void drawScene() const override;
};
