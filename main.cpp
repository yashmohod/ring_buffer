#include "includes/ring_buffer.hpp"
#include <iostream>

int main() {
    // Basic push and access
    RingBuffer<double, 5> buf;
    buf.push(1.0);
    buf.push(2.0);
    buf.push(3.0);

    std::cout << "Size: " << buf.size() << "\n";       // 3
    std::cout << "Full: " << buf.full() << "\n";       // 0
    std::cout << "buf[0]: " << buf[0] << "\n";         // 1.0 (oldest)
    std::cout << "buf[2]: " << buf[2] << "\n";         // 3.0 (newest)

    // Fill to capacity
    buf.push(4.0);
    buf.push(5.0);
    std::cout << "Full: " << buf.full() << "\n";       // 1

    // Overwrite — oldest element drops off
    buf.push(6.0);
    std::cout << "buf[0]: " << buf[0] << "\n";         // 2.0 (1.0 was overwritten)
    std::cout << "buf[4]: " << buf[4] << "\n";         // 6.0

    // Range-for
    for (auto x : buf) {
        std::cout << x << " ";                         // 2.0 3.0 4.0 5.0 6.0
    }
    std::cout << "\n";

    // mean() — only works for arithmetic types
    std::cout << "Mean: " << buf.mean() << "\n";       // 4.0

    // Compile error if you try mean() on non-arithmetic type:
    // RingBuffer<std::string, 4> sbuf;
    // sbuf.mean(); // static_assert fires here

    return 0;
}
