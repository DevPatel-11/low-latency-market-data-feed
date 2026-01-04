#pragma once
#include <cstdint>
#include <vector>

namespace mdf {

class NumaSupport {
public:
    static int get_numa_node(int cpu_id);
    static std::vector<int> get_cpus_for_node(int node);
    static void bind_to_cpu(int cpu_id);
    static int get_num_nodes();
    static void allocate_numa_aware(void** ptr, size_t size, int node);
};

} // namespace mdf
