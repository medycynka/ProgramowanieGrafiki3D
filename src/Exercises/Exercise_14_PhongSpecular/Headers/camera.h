#ifndef INC_3DGRAPHICSEXAMPLES_CAMERA_H
#define INC_3DGRAPHICSEXAMPLES_CAMERA_H

#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "rotation.h"

class Camera {
public:

    void look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

    void perspective(float fov, float aspect, float near, float far);

    void set_aspect(float aspect);

    glm::mat4 view() const;

    glm::mat4 projection() const;

    glm::vec3 x() const;

    glm::vec3 y() const;

    glm::vec3 z() const;

    glm::vec3 position() const;

    glm::vec3 center() const;

    void zoom(float y_offset);

    void rotate_around_point(float angle, const glm::vec3 &axis, const glm::vec3 &c);

    void rotate_around_center(float angle, const glm::vec3 &axis);

private:
    float fov_;
    float aspect_;
    float near_;
    float far_;
    glm::vec3 position_;
    glm::vec3 center_;
    glm::vec3 x_;
    glm::vec3 y_;
    glm::vec3 z_;

    constexpr static const float PI_ = glm::pi<float>();
};

static float logistic(float y) {
    return 1.0f / (1.0f + std::exp(-y));
}

static float inverse_logistic(float x) {
    return std::log(x / (1.0f - x));
}

#endif //INC_3DGRAPHICSEXAMPLES_CAMERA_H
