#include "../Headers/camera_controler.h"

void CameraControler::update_scale(int w, int h) {
    scale_ = (float)w / (float)h * scale_coefficient;
}

void CameraControler::set_camera(Camera *camera)  {
    camera_ = camera;
}

void CameraControler::rotate_camera(float dx, float dy) {
    camera_->rotate_around_center(-scale_ * dy, camera_->x());
    camera_->rotate_around_center(-scale_ * dx, glm::vec3{0.0f, 0.0f, 1.0f});
}

void CameraControler::mouse_moved(float x, float y) {
    if (LMB_pressed_) {
        auto dx = x - x_;
        auto dy = y - y_;

        x_ = x;
        y_ = y;
        rotate_camera(dx, dy);
    }
}

void CameraControler::LMB_pressed(float x, float y) {
    LMB_pressed_ = true;
    x_ = x;
    y_ = y;
}

void CameraControler::LMB_released(float x, float y) {
    LMB_pressed_ = false;
    auto dx = x - x_;
    auto dy = y - y_;

    rotate_camera(dx, dy);
}
