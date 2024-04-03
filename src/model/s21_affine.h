#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_S21_AFFINE_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_S21_AFFINE_H_

#include "s21_object.h"

namespace s21 {

class ITransform {
 public:
  virtual void Calculate(std::vector<Vector3>& vertices,
                         const double& value) = 0;
  virtual ~ITransform() = default;
};

class Move : public ITransform {};

class Rotate : public ITransform {};

class Scale : public ITransform {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

class MoveX : public Move {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

class MoveY : public Move {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

class MoveZ : public Move {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

class RotateX : public Rotate {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

class RotateY : public Rotate {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

class RotateZ : public Rotate {
 public:
  void Calculate(std::vector<Vector3>& vertices, const double& value) override;
};

template <class Transformation>
class AffineTransformation {
  static_assert(std::is_base_of<ITransform, Transformation>::value,
                "Transformation must be inherited from ITransform");

 public:
  void Transform(std::vector<Vector3>& vertices, const double& value) {
    Transformation transform;
    transform.Calculate(vertices, value);
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_S21_AFFINE_H_