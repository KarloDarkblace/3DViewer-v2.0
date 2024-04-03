#include "s21_affine.h"
#include <cmath>

namespace s21 {

/**
 * @brief Выполняет перемещение вершин объекта по оси X.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Величина, на которую осуществляется перемещение по оси X.
 */
void MoveX::Calculate(std::vector<Vector3>& vertices, const double& value) {
  for (auto& vertex : vertices) {
    vertex.x += value;
  }
}

/**
 * @brief Выполняет перемещение вершин объекта по оси Y.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Величина, на которую осуществляется перемещение по оси Y.
 */
void MoveY::Calculate(std::vector<Vector3>& vertices, const double& value) {
  for (auto& vertex : vertices) {
    vertex.y += value;
  }
}

/**
 * @brief Выполняет перемещение вершин объекта по оси Z.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Величина, на которую осуществляется перемещение по оси Z.
 */
void MoveZ::Calculate(std::vector<Vector3>& vertices, const double& value) {
  for (auto& vertex : vertices) {
    vertex.z += value;
  }
}

/**
 * @brief Выполняет вращение вершин объекта вокруг оси X.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Угол вращения в градусах.
 */
void RotateX::Calculate(std::vector<Vector3>& vertices, const double& value) {
  double rad = value * M_PI / 180.0;
  for (auto& vertex : vertices) {
    double y = vertex.y * cos(rad) - vertex.z * sin(rad);
    double z = vertex.y * sin(rad) + vertex.z * cos(rad);
    vertex.y = y;
    vertex.z = z;
  }
}

/**
 * @brief Выполняет вращение вершин объекта вокруг оси Y.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Угол вращения в градусах.
 */
void RotateY::Calculate(std::vector<Vector3>& vertices, const double& value) {
  double rad = value * M_PI / 180.0;
  for (auto& vertex : vertices) {
    double x = vertex.x * cos(rad) + vertex.z * sin(rad);
    double z = -vertex.x * sin(rad) + vertex.z * cos(rad);
    vertex.x = x;
    vertex.z = z;
  }
}

/**
 * @brief Выполняет вращение вершин объекта вокруг оси Z.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Угол вращения в градусах.
 */
void RotateZ::Calculate(std::vector<Vector3>& vertices, const double& value) {
  double rad = value * M_PI / 180.0;
  for (auto& vertex : vertices) {
    double x = vertex.x * cos(rad) - vertex.y * sin(rad);
    double y = vertex.x * sin(rad) + vertex.y * cos(rad);
    vertex.x = x;
    vertex.y = y;
  }
}

/**
 * @brief Выполняет масштабирование вершин объекта.
 * 
 * @param vertices Список вершин объекта для трансформации.
 * @param value Коэффициент масштабирования.
 */
void Scale::Calculate(std::vector<Vector3>& vertices, const double& value) {
  for (auto& vertex : vertices) {
    vertex.x *= value;
    vertex.y *= value;
    vertex.z *= value;
  }
}

}  // namespace s21
