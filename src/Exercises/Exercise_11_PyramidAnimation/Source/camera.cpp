#include "Exercises/Exercise_11_PyramidAnimation/Headers/camera.h"

void Camera::look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    z_ = glm::normalize(eye - center);
    x_ = glm::normalize(glm::cross(up, z_));
    y_ = glm::normalize(glm::cross(z_, x_));
    position_ = eye;
    center_ = center;
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
    glm::mat4 V(1.0f);

    for (auto i = 0; i < 3; ++i) {
        V[i][0] = x_[i];
        V[i][1] = y_[i];
        V[i][2] = z_[i];
    }

    auto t = -glm::vec3{
            glm::dot(x_, position_),
            glm::dot(y_, position_),
            glm::dot(z_, position_)
        };

    V[3] = glm::vec4(t, 1.0f);

    return V;
}

glm::mat4 Camera::projection() const {
    return glm::perspective(fov_, aspect_, near_, far_);
}

void Camera::zoom(float y_offset) {
    auto x = fov_ / PI_;
    auto y = inverse_logistic(x);

    y += y_offset;
    x = logistic(y);
    fov_ = x * PI_;
}

glm::vec3 Camera::x() const {
    return x_;
}

glm::vec3 Camera::y() const {
    return y_;
}

glm::vec3 Camera::z() const {
    return z_;
}

glm::vec3 Camera::position() const {
    return position_;
}

glm::vec3 Camera::center() const {
    return center_;
}

void Camera::rotate_around_point(float angle, const glm::vec3 &axis, const glm::vec3 &c) {
    auto R = rotation(angle, axis);

    x_ = R * x_;
    y_ = R * y_;
    z_ = R * z_;

    auto t = position_ - c;

    t = R * t;
    position_ = c + t;
}

void Camera::rotate_around_center(float angle, const glm::vec3 &axis) {
    rotate_around_point(angle, axis, center_);
}
