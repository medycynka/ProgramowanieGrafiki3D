#ifndef INC_3DGRAPHICSEXAMPLES_CAMERA_CONTROLER_HPP
#define INC_3DGRAPHICSEXAMPLES_CAMERA_CONTROLER_HPP

#pragma once

#include <memory>
#include "camera.h"

class CameraControler {
public:
    explicit CameraControler(Camera* camera) : camera_(camera) {}
    CameraControler(int w_, int h_) : camera_(nullptr), scale_{(float)w_ / (float)h_ * scale_coefficient} {}
    CameraControler(int w_, int h_, Camera* camera) : camera_(camera), scale_{(float)w_ / (float)h_ * scale_coefficient} {}

    Camera* create_camera(){
        auto* new_camera = al_.allocate(1);
        al_.construct(new_camera);

        return new_camera;
    }

    void set_camera(Camera *camera);

    void update_scale(int w_, int h_);

    void rotate_camera(float dx, float dy);

    void mouse_moved(float x, float y);

    void LMB_pressed(float x, float y);

    void LMB_released(float x, float y);

private:
    constexpr static const float scale_coefficient{0.01f};

    std::allocator<Camera> al_;
    Camera *camera_;
    float scale_ = 1.0f;
    bool LMB_pressed_ = false;
    float x_ = 0.0;
    float y_ = 0.0;
};

#endif //INC_3DGRAPHICSEXAMPLES_CAMERA_CONTROLER_HPP
