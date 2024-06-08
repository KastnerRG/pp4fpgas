#include <iostream>
#include <vector>

#include "complex_fir.h"

const int SIZE = 256;

int main() {
    // Define taps for the complex FIR filter. Separate real and imaginary parts.
    int Itaps[NUM_TAPS] = {1, 2, 0, -3, 0, 4, -5, 0, 1, -2, 0, -3, 0, 4, -5, 0};
    int Qtaps[NUM_TAPS] = {0, -1, 2, 0, -3, 0, 4, -5, 0, 1, -2, 0, 3, 0, -4, 5};

    int Iout = 0, Qout = 0;
    int expected_Iout = 6592, expected_Qout = -6558;

    for (int i = 0; i < SIZE; i++) {
        complexFIR(i, -i, &Iout, &Qout, Itaps, Qtaps);
        std::cout << "Result - Iout: " << Iout << ", Qout: " << Qout << std::endl;
    }

    if (Iout == expected_Iout && Qout == expected_Qout) {
        return 0; // Success
    } else {
        return 1; // Failure
    }
}