/*
Created by Sari I. Younan
29/04/2024 19:05:20
Heat.cpp
*/

#include "Heat.h"

const double alpha = 0.14558;  // thermal diffusivity
const double dr = 0.1;      // radial distance step
const double dt = 0.001;     // time step
const int num_r = 20;      // number of radial points
const double initial_temp = 24.0;  // initial temperature at r = 0
const double ambient_temp = 15;  // ambient temperature within the brain

void update_temperature(vector<double>& temp) {
    vector<double> new_temp(num_r, ambient_temp);

    // Apply Neumann boundary condition at the last radial point
    new_temp[num_r - 1] = temp[num_r - 1]; // assuming insulated boundary

    for (int i = 1; i < num_r - 1; ++i) {
        double r = i * dr;
        new_temp[i] = temp[i] + dt * alpha * (
            (temp[i+1] - 2 * temp[i] + temp[i-1]) / (dr * dr) +
            (1 / r) * (temp[i+1] - temp[i-1]) / (2 * dr)
        );
    }

    new_temp[0] = initial_temp;
    // Update r=0 assuming symmetry, derivative is zero
    new_temp[0] = temp[0] + dt * alpha * (
        (temp[1] - 2 * temp[0] + temp[1]) / (dr * dr)  // Symmetric condition
    );
    temp = new_temp;
}

int main() {
    // Initialize temperature array
    vector<double> temperature(num_r, ambient_temp);

    temperature[0] = initial_temp;

    auto start = chrono::steady_clock::now();

    while (true) {

        auto now = chrono::steady_clock::now();
        chrono::duration<double> elapsed = now - start;

        update_temperature(temperature);

        // Print temperature profile for visualization (every second)
        if (static_cast<int>(elapsed.count()) % 1 == 0) {
            cout << "Time: " << elapsed.count() << "s\n";
            for (int i = 0; i < num_r; ++i) {
                cout << "r=" << i * dr << " Temp=" << temperature[i] << "\n";
            }
            cout << "\n";
        }

        if (elapsed.count() > 10) break; // Stop after 10 seconds for example

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
