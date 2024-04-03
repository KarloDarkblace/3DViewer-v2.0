#include <gtest/gtest.h>
#include <cmath>

#include "../controller/s21_controller.h"

bool CompareVectors(const s21::Vector3& v1, const s21::Vector3& v2,
                    double tolerance = 1e-6) {
  return std::abs(v1.x - v2.x) < tolerance &&
         std::abs(v1.y - v2.y) < tolerance && std::abs(v1.z - v2.z) < tolerance;
}

TEST(AffineTransformationTest, MoveX) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  const double moveValue = 124.12f;
  auto initialVertices = obj.GetVertices();
  obj.MoveByX(moveValue);

  auto vertices = obj.GetVertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_TRUE(CompareVectors(
        vertices[i], s21::Vector3{initialVertices[i].x + moveValue,
                                  initialVertices[i].y, initialVertices[i].z}));
  }
}

TEST(AffineTransformationTest, MoveY) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  const double moveValue = 3.48f;
  auto initialVertices = obj.GetVertices();
  obj.MoveByY(moveValue);

  auto vertices = obj.GetVertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_TRUE(CompareVectors(
        vertices[i],
        s21::Vector3{initialVertices[i].x, initialVertices[i].y + moveValue,
                     initialVertices[i].z}));
  }
}

TEST(AffineTransformationTest, MoveZ) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  const double moveValue = 5.192f;
  auto initialVertices = obj.GetVertices();
  obj.MoveByZ(moveValue);

  auto vertices = obj.GetVertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    EXPECT_TRUE(CompareVectors(
        vertices[i], s21::Vector3{initialVertices[i].x, initialVertices[i].y,
                                  initialVertices[i].z + moveValue}));
  }
}

TEST(AffineTransformationTest, RotateX) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  double angle = 90.0f;
  obj.RotateByX(angle);

  auto vertices = obj.GetVertices();
  EXPECT_TRUE(CompareVectors(
      vertices[0], s21::Vector3{vertices[0].x, -vertices[0].z, vertices[0].y}));
}

TEST(AffineTransformationTest, RotateY) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  double angle = 90.0f;
  obj.RotateByY(angle);

  auto vertices = obj.GetVertices();
  EXPECT_TRUE(CompareVectors(
      vertices[0], s21::Vector3{vertices[0].z, vertices[0].y, -vertices[0].x}));
}

TEST(AffineTransformationTest, RotateZ) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  double angle = 90.0f;
  obj.RotateByZ(angle);

  auto vertices = obj.GetVertices();
  EXPECT_TRUE(CompareVectors(
      vertices[0], s21::Vector3{-vertices[0].y, vertices[0].x, vertices[0].z}));
}

TEST(AffineTransformationTest, Scale) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  double scaleFactor = 3.455121f;
  obj.Scale(scaleFactor);

  auto vertices = obj.GetVertices();
  EXPECT_TRUE(CompareVectors(
      vertices[0],
      s21::Vector3{vertices[0].x * scaleFactor, vertices[0].y * scaleFactor,
                   vertices[0].z * scaleFactor}));
}