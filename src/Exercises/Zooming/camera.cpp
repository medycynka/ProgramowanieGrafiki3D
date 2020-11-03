#include "camera.h"

void Camera::look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    V_ = glm::lookAt(eye, center, up);
}

void Camera::perspective(float fov, float aspect, float near, float far) {
    fov_ = fov;
    aspect_ = aspect;
    near_ = near;
    far_ = far;
}

void Camera::set_aspect(float aspect) {
    aspect_ = aspect;
}

glm::mat4 Camera::view() const {
    return V_;
}

glm::mat4 Camera::projection() const {
    return glm::perspective(fov_, aspect_, near_, far_);
}

void Camera::zoom(float y_offset) {
    auto x = fov_ / glm::pi<float>();
    auto y = inverse_logistic(x);

    y += y_offset;
    x = logistic(y);
    fov_ = x * glm::pi<float>();
}
