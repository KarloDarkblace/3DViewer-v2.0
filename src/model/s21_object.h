#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_S21_MODEL_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_S21_MODEL_H_

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace s21 {

constexpr int RETURN_NORMAL = 0;
constexpr int RETURN_ERROR = 1;

struct Vector3 {
  double x, y, z;
};

class Object3D final {
 public:
  int InitializeObject(const std::string& filename) noexcept;

 public:
  double GetMaxVertex() noexcept { return max_vertex_; };
  std::vector<Vector3>& GetVertices() noexcept { return vertices_; };
  std::vector<std::pair<unsigned, unsigned>> GetEdges() noexcept {
    return edges_;
  };

 private:
  std::vector<unsigned> ExtractVertexIndicesFromFace(
      std::istringstream& line_stream) noexcept;
  void AddEdgesFromFaceVertices(
      const std::vector<unsigned>& face_vertices) noexcept;
  void ParsingFile(std::ifstream& filestream) noexcept;
  void ParseVertexLine(std::istringstream& line) noexcept;
  void CleanObject() noexcept;
  void CheckMaxVertex(const Vector3& vertex) noexcept;

 private:
  std::vector<Vector3> vertices_;
  std::vector<std::pair<unsigned, unsigned>> edges_;
  double max_vertex_ = 0;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_S21_MODEL_H_