#pragma once
#include "Util.hpp"

namespace util {
	template<typename vertex_type, typename indice_type, int N, int M>
	unsigned int set_vertex_array_object(const std::array<vertex_type, N>& vertices, const std::array<indice_type, M>& indices);
}