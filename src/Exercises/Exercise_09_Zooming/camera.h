#ifndef INC_3DGRAPHICSEXAMPLES_CAMERA_H
#define INC_3DGRAPHICSEXAMPLES_CAMERA_H

#pragma once

#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:

    void look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

    void perspective(float fov, float aspect, float near, float far);

    void set_aspect(float aspect);

    glm::mat4 view() const;

    glm::mat4 projection() const;

    void zoom(float y_offset);

private:
    float fov_;
    float aspect_;
    float near_;
    float far_;

    glm::mat4 V_;
};

static float logistic(float y) {
    return 1.0f / (1.0f + std::exp(-y));
}

static float inverse_logistic(float x) {
    return std::log(x / (1.0f - x));
}

#endif //INC_3DGRAPHICSEXAMPLES_CAMERA_H
