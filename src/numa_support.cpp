#include "numa_support.h"
#include <sched.h>
#include <cstring>

namespace mdf {

int NumaSupport::get_numa_node(int cpu_id) {
    return cpu_id / 4;  // Assume 4 CPUs per NUMA node
}

std::vector<int> NumaSupport::get_cpus_for_node(int node) {
    std::vector<int> cpus;
    for (int i = 0; i < 4; ++i) {
        cpus.push_back(node * 4 + i);
    }
    return cpus;
}

void NumaSupport::bind_to_cpu(int cpu_id) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu_id, &set);
    sched_setaffinity(0, sizeof(set), &set);
}

int NumaSupport::get_num_nodes() {
    return 2;  // Default to 2 NUMA nodes
}

void NumaSupport::allocate_numa_aware(void** ptr, size_t size, int node) {
    // Placeholder: real implementation would use numactl API
    *ptr = new char[size];
}

} // namespace mdf
