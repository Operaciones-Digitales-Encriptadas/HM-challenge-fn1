#include <iostream>
#include <random>
#include <stdexcept>
#include <cstdint>
#include <cmath>

using namespace std;

void showInterface() {
    cout << "Welcome to my program, please choose an option: " << endl;
    cout << "1. BitLength" << endl;
    cout << "2. GenRan " << endl;
    cout << "3. EncryptVars" << endl;
    cout << "4. FinalCalculation" << endl;
    cout << "5. Exit" << endl;
}

int BitLength(int x) {
    int contador = 0;
    while (x > 0) {
        contador++;
        x = x / 2;
    }
    return contador;
}

int IntSqrt(int x) {
    return static_cast<int>(sqrt(x));
}

int64_t GenRan(int x) {
    if (x < 1 || x > 512) {
        cout<<"x debe estar en el intervalo 1, 512";
    }

    int64_t lower_bound = (1LL << (x - 1));
    int64_t upper_bound = (1LL << x) - 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int64_t> dist(lower_bound, upper_bound);

    return dist(gen);
}

void GenKey(int Var1, int Var2, int64_t& K1, int64_t& K2, int64_t& K3) {
    K1 = GenRan(64 - BitLength(Var1));
    K2 = GenRan(64);
    K3 = GenRan(64 - BitLength(IntSqrt(Var1 * Var1 + Var2 * Var2)));
}

void EncryptVars(int Var1, int Var2, double& EV1, double& EV2, double& EV3, double& EV4) {
    int64_t K1, K2, K3;

    GenKey(Var1, Var2, K1, K2, K3);

    EV1 = K1 * Var1 + K2;
    EV2 = K3 * IntSqrt(Var1 * Var1 + Var2 * Var2);
    EV3 = static_cast<double>(K2) / EV2;
    EV4 = static_cast<double>(K3) / K1;
}

double FinalCalculation(double EV1, double EV2, double EV3, double EV4) {
    return EV4 * ((EV1 / EV2) - EV3);
}

int main() {
    bool programFinish = false;
    int opcion;
    int leave;

    do {
        showInterface();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int decimalNumber;
                cout << "Give me a number to determine its bit length: " << endl;
                cin >> decimalNumber;
                cout << "Bit length: " << BitLength(decimalNumber) << endl;
                break;
            }

            case 2: {
                int randomBits;
                cout << "Give me a number between 1 and 512: " << endl;
                cin >> randomBits;
                try {
                    cout << "Random number with " << randomBits << " bits: " << GenRan(randomBits) << endl;
                } catch (const out_of_range &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }

            case 3: {
                int Var1, Var2;
                double EV1, EV2, EV3, EV4;
                cout << "Ingrese Var1: ";
                cin >> Var1;
                cout << "Ingrese Var2: ";
                cin >> Var2;

                EncryptVars(Var1, Var2, EV1, EV2, EV3, EV4);

                cout << "EV1 = " << EV1 << endl;
                cout << "EV2 = " << EV2 << endl;
                cout << "EV3 = " << EV3 << endl;
                cout << "EV4 = " << EV4 << endl;
                break;
            }

            case 4: {
                double EV1, EV2, EV3, EV4;
                cout << "Ingrese EV1: ";
                cin >> EV1;
                cout << "Ingrese EV2: ";
                cin >> EV2;
                cout << "Ingrese EV3: ";
                cin >> EV3;
                cout << "Ingrese EV4: ";
                cin >> EV4;

                double R = FinalCalculation(EV1, EV2, EV3, EV4);

                cout << "Resultado R = " << R << endl;
                break;
            }

            case 5: {
                programFinish = true;
                break;
            }

            default:
                cout << "there's a bad answer" << endl;
                break;
        }

        if (!programFinish) {
            cout << "do you want to continue 1.si 2.no";
            cin >> leave;

            if (leave == 2) {
                programFinish = true;
            }
        }


    } while (!programFinish);

    cout << "tenkiuuuuu :)" << endl;
    return 0;
}
