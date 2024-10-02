#include <iostream>
#include <array>
#include <random>
#include <cstdint>
#include <limits>
#include <ctime>
//#include <gmpxx.h>

using namespace std;

// Declaración de funciones
int BitLength(uint64_t x);
int64_t GenRand(int64_t x);
int64_t SqrtInt(uint64_t x);
array<int64_t, 3> GenKey(uint32_t var1, uint32_t var2);
array<int64_t, 4> EncryptVars(int32_t var1, int32_t var2);
double FinalCalculation(int64_t EV1, int64_t EV2, int64_t EV3, int64_t EV4);

int main(){
    int32_t x = 32;
    int64_t rand = GenRand(x);

    // Imprimir la longitud binaria de x y el número aleatorio generado
    cout << "\nLa longitud binaria de " << x << " es: " << BitLength(x) << "\n";
    cout << "El numero random generado con el mismo tamano es: " << rand << " Y su longitud es: " << BitLength(rand) << "\n";

    uint32_t var1 = 2;
    uint32_t var2 = 2;
    array<int64_t, 4> encryptedVars = EncryptVars(var1, var2);

    // Imprimir los valores encriptados (eliminar la impresión de los valores en GenKey y EncryptVars)
    //cout << "EV1: " << encryptedVars[0] << "\n";
    //cout << "EV2: " << encryptedVars[1] << "\n";
    //cout << "EV3: " << encryptedVars[2] << "\n";
    //cout << "EV4: " << encryptedVars[3] << "\n";

    // Calcular y imprimir el resultado final
    double R = FinalCalculation(encryptedVars[0], encryptedVars[1], encryptedVars[2], encryptedVars[3]);
    cout << "R: " << R << "\n";

    return 0; 
}

// Función para calcular la longitud binaria de un número
int BitLength(uint64_t x){
    int length = 0;
    while(x > 0){
        x >>= 1;
        length++;
    }
    return length;
}

// Función para generar un número aleatorio con una longitud de bits específica
int64_t GenRand(int64_t x){
    if(x < 1 || x > 64){
        throw invalid_argument("x debe estar en el intervalo [1, 64]");
    }

    mt19937 gen(random_device{}());
    if (x == 64) {
        uniform_int_distribution<uint64_t> random(0, numeric_limits<uint64_t>::max());
        return static_cast<int64_t>(random(gen) & numeric_limits<int64_t>::max());
    } else {
        uniform_int_distribution<uint64_t> random(1LL<<(x-1), (1LL<<x)-1);
        return random(gen);
    }
}

// Función para calcular la raíz cuadrada de un número y redondearla al entero más cercano
int64_t SqrtInt(uint64_t x){
    return static_cast<int64_t>(round(sqrt(x)));
}

// Función para generar una clave de tres números aleatorios basados en dos variables de entrada
array<int64_t, 3> GenKey(uint32_t var1, uint32_t var2) {
    int64_t k1 = GenRand(64 - BitLength(var1));
    int64_t k2 = GenRand(64);
    int64_t k3 = GenRand(64 - BitLength(SqrtInt(static_cast<uint64_t>(var1) * var1 + static_cast<uint64_t>(var2) * var2)));

    // Imprimir los valores de k para depuración
    cout << "k1: " << k1 << "\n";
    cout << "k2: " << k2 << "\n";
    cout << "k3: " << k3 << "\n";

    array<int64_t, 3> K = {k1, k2, k3};

    return K;
}

// Función para encriptar dos variables de entrada y devolver un array de cuatro valores encriptados
array<int64_t, 4> EncryptVars(int32_t var1, int32_t var2) {
    array<int64_t, 3> K = GenKey(var1, var2);

    int64_t ev1 = K[0] * var1 + K[1];
    int64_t ev2 = K[2] * SqrtInt(static_cast<uint64_t>(var1) * var1 + static_cast<uint64_t>(var2) * var2);
    double ev3 = static_cast<double>(K[1]) / ev2;
    double ev4 = static_cast<double>(K[2]) / K[0];

    // Imprimir los valores de EV para depuración
    cout << "ev1: " << ev1 << "\n";
    cout << "ev2: " << ev2 << "\n";
    cout << "ev3: " << ev3 << "\n";
    cout << "ev4: " << ev4 << "\n";

    array<int64_t, 4> EV = {ev1, ev2, static_cast<int64_t>(ev3), static_cast<int64_t>(ev4)};

    return EV; 
}


// Función para realizar el cálculo final basado en los valores encriptados
double FinalCalculation(int64_t EV1, int64_t EV2, int64_t EV3, int64_t EV4){
    return EV4 * (static_cast<double>(EV1) / EV2 - EV3);
}

