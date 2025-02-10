#include <gtest/gtest.h>
#include "../src/Integradora.cpp"  // Incluir el código a probar

// Ejemplo de función en Integradora.cpp
int suma(int a, int b) {
    return a + b;
}

// 🔹 PRUEBA UNITARIA: Verificar que suma funciona correctamente
TEST(IntegradoraTest, SumaTest) {
    EXPECT_EQ(suma(2, 3), 5);   // 2 + 3 debe ser 5
    EXPECT_EQ(suma(-1, 1), 0);  // -1 + 1 debe ser 0
    EXPECT_EQ(suma(0, 0), 0);   // 0 + 0 debe ser 0
}

// 🔹 Agregar más pruebas aquí...

// 🔹 Función principal para ejecutar las pruebas
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
