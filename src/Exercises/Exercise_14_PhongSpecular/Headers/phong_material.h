#ifndef INC_3DGRAPHICSEXAMPLES_PHONG_MATERIAL_H
#define INC_3DGRAPHICSEXAMPLES_PHONG_MATERIAL_H

#pragma once

#include <iostream>
#include <glm/glm.hpp>

struct PhongMaterial {
    alignas(16) glm::vec3 Kd;
    alignas(4) uint32_t Kd_map;
    alignas(16) glm::vec3 Ks;
    alignas(4) uint32_t Ks_map;
    alignas(4) float Ns;
    alignas(4) uint32_t Ns_map;
};

#endif //INC_3DGRAPHICSEXAMPLES_PHONG_MATERIAL_H
