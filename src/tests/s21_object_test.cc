#include <gtest/gtest.h>

#include "../controller/s21_controller.h"

TEST(Object3DTest, InitializeObject_ValidFile) {
  s21::ObjectController obj;
  ASSERT_EQ(obj.InitializeObject("objects/cube.obj"), s21::RETURN_NORMAL);
  ASSERT_EQ(obj.InitializeObject("objects/sword.obj"), s21::RETURN_NORMAL);
  ASSERT_EQ(obj.InitializeObject("objects/skull.obj"), s21::RETURN_NORMAL);
}

TEST(Object3DTest, InitializeObject_InvalidFile) {
  s21::ObjectController obj;
  ASSERT_EQ(obj.InitializeObject("objects/bebebebe.obj"), s21::RETURN_ERROR);
}

TEST(Object3DTest, CheckMaxVertex) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  ASSERT_DOUBLE_EQ(obj.GetMaxVertex(), 2.0);
}

TEST(Object3DTest, GetEdges) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  ASSERT_DOUBLE_EQ(obj.GetEdges().size(), 30.0);
}

TEST(Object3DTest, GetVertices) {
  s21::ObjectController obj;
  obj.InitializeObject("objects/cube.obj");
  ASSERT_DOUBLE_EQ(obj.GetVertices().size(), 8.0);
}
