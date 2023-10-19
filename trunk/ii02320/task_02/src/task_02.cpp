﻿#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class func {
private:
    double K = 0.0001, T = 100, T_D = 100, T_0 = 1;
    double q_0 = K * (1 + T_D / T_0);
    double q_1 = -K * (1 + 2 * T_D / T_0 - T_0 / T);
    double q_2 = K * T_D / T_0;
    double q[3] = { q_0, q_1, q_2 };
    double e[3] = { 0, 0, 0 };
    vector<double> y = { 0, 0, 0 };
    double u[2] = { 1, 1 };
public:
    double sum() {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += q[i] * e[i];
        }
        return sum;
    }

    void nonlin(int time, double setpoint, double a = 0.5, double b = 0.3, double c = 0.9, double d = 0.7) {
        for (int i = 0; i < time; i++) {
            e[0] = setpoint - y[y.size() - 1];
            e[1] = setpoint - y[y.size() - 2];
            e[2] = setpoint - y[y.size() - 3];
            u[0] = u[1] + sum();
            y.push_back(a * y[y.size() - 1] - b * y[y.size() - 2] * y[y.size() - 2] + c * u[0] + d * sin(u[1]));
            u[1] = u[0];
        }
    }

    vector<double> getY() {
        return y;
    }
};

int main() {
    double setpoint;
    ofstream out("output.txt");
    func f;

    if (out.is_open()) {
        cout << "Enter the setpoint: ";
        cin >> setpoint;
        f.nonlin(100, setpoint);
        vector<double> y_values = f.getY();

        for (int i = 0; i < y_values.size(); i++) {
            double scaledValue = y_values[i] * setpoint / y_values[y_values.size() - 1];
            cout << i << " " << scaledValue << endl;
            out << i << " " << scaledValue << endl;
        }

        out.close();
    }
    else {
        cerr << "Error: Cannot open the output file." << endl;
    }

    return 0;
}
