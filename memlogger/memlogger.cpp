#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sstream>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdint>

uintptr_t get_module_base(pid_t pid, const std::string& module_name) {
    std::ifstream maps("/proc/" + std::to_string(pid) + "/maps");
    std::string line;
    while (std::getline(maps, line)) {
        if (line.find(module_name) != std::string::npos) {
            std::stringstream ss(line);
            std::string address;
            std::getline(ss, address, '-');
            return std::stoul(address, nullptr, 16);
        }
    }
    return 0;
}

void dump_memory(int mem_fd, uintptr_t address, size_t size) {
    std::vector<uint8_t> buffer(size);

    // Use pread for safer reading
    ssize_t bytes = pread(mem_fd, buffer.data(), size, address);
    if (bytes <= 0) {
        std::cerr << "Failed to read memory at " << std::hex << address << std::endl;
        return;
    }

    // Hex + ASCII dump (Cheat Engine style)
    for (size_t i = 0; i < size; i += 16) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << (address + i) << ":  ";

        for (size_t j = 0; j < 16; ++j) {
            if (i + j < size)
                std::cout << std::setw(2) << static_cast<int>(buffer[i + j]) << " ";
            else
                std::cout << "   ";
        }

        std::cout << "  ";
        for (size_t j = 0; j < 16 && i + j < size; ++j) {
            char c = buffer[i + j];
            std::cout << (isprint(c) ? c : '.');
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <pid> <module_name> <offset_in_hex> [size]" << std::endl;
        return 1;
    }

    pid_t pid = std::stoi(argv[1]);
    std::string module = argv[2];
    uintptr_t offset = std::stoul(argv[3], nullptr, 16);
    size_t size = (argc >= 5) ? std::stoul(argv[4]) : 64;

    uintptr_t base = get_module_base(pid, module);
    if (!base) {
        std::cerr << "Failed to find module: " << module << std::endl;
        return 1;
    }

    uintptr_t address = base + offset;
    std::string mem_path = "/proc/" + std::to_string(pid) + "/mem";

    int mem_fd = open(mem_path.c_str(), O_RDONLY);
    if (mem_fd == -1) {
        std::cerr << "Failed to open mem file for PID " << pid << std::endl;
        return 1;
    }

    std::cout << "Logging memory at: 0x" << std::hex << address << " (" << module << " + 0x" << offset << ")" << std::endl;

    while (true) {
        system("clear");
        dump_memory(mem_fd, address, size);
        usleep(100000); // 100ms refresh
    }

    close(mem_fd);
    return 0;
}
