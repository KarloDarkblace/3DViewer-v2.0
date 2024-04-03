#include "s21_object.h"

namespace s21 {

int Object3D::InitializeObject(const std::string& filename) noexcept {
  CleanObject();

  std::ifstream file(filename);
  if (!file.is_open()) {
    return RETURN_ERROR;
  }

  ParsingFile(file);

  file.close();
  return RETURN_NORMAL;
}

void Object3D::CleanObject() noexcept {
  edges_.clear();
  vertices_.clear();
  max_vertex_ = 0;
}

void Object3D::CheckMaxVertex(const Vector3& vertex) noexcept {
  max_vertex_ = std::max(max_vertex_, std::abs(vertex.x));
  max_vertex_ = std::max(max_vertex_, std::abs(vertex.y));
  max_vertex_ = std::max(max_vertex_, std::abs(vertex.z));
}

void Object3D::ParseVertexLine(std::istringstream& line_stream) noexcept {
  Vector3 vertex;
  line_stream >> vertex.x >> vertex.y >> vertex.z;
  vertices_.push_back(vertex);
  CheckMaxVertex(vertex);
}

std::vector<unsigned> Object3D::ExtractVertexIndicesFromFace(
    std::istringstream& line_stream) noexcept {
  std::vector<unsigned> face_vertices;
  std::string vertex_data;
  while (line_stream >> vertex_data) {
    std::istringstream vertex_data_stream(vertex_data);
    std::string vertex_index;
    getline(vertex_data_stream, vertex_index, '/');
    int index = std::stoi(vertex_index);
    index = index < 0 ? vertices_.size() + index : index - 1;
    face_vertices.push_back(index);
  }
  return face_vertices;
}

void Object3D::AddEdgesFromFaceVertices(
    const std::vector<unsigned>& face_vertices) noexcept {
  for (size_t i = 0; i < face_vertices.size(); ++i) {
    unsigned startIndex = face_vertices[i];
    unsigned endIndex = face_vertices[(i + 1) % face_vertices.size()];
    if (startIndex != endIndex) {
      edges_.emplace_back(startIndex, endIndex);
    }
  }
}

void Object3D::ParsingFile(std::ifstream& filestream) noexcept {
  std::string line;
  while (getline(filestream, line)) {
    std::istringstream line_stream(line);
    std::string lineType;
    line_stream >> lineType;
    if (lineType == "v") {
      ParseVertexLine(line_stream);
    } else if (lineType == "f") {
      auto face_vertices = ExtractVertexIndicesFromFace(line_stream);
      AddEdgesFromFaceVertices(face_vertices);
    }
  }
}

}  // namespace s21
