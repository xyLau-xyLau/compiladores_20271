#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COTA_SALIDA 4096

typedef struct {
    const char* nombre;
    const char* caso;
    const char* valor_esperado;
} Prueba;

int escanea(const char* caso, char* buffer, size_t bufsize) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "echo \"%s\" | ./lexer", caso);
    
    FILE* fp = popen(cmd, "r");
    if (!fp) {
        return -1;
    }

    size_t len = fread(buffer, 1, bufsize - 1, fp);
    buffer[len] = '\0';

    pclose(fp);
    return 0;
}

int ejecuta_prueba(const Prueba* prueba){
    char output[COTA_SALIDA];

    if (escanea (prueba -> caso, output, sizeof(output)) != 0){
        printf("[ERROR] %s: No se puede ejecutar el escaner", prueba -> nombre);
        return 0;
    }

    if (strcmp(output, prueba -> valor_esperado) == 0){
        printf("[APROBADA]: %s \n", prueba -> nombre);
        return 1;
    } else {
        printf("[FALLADA]: %s\n", prueba -> nombre);
        printf("Se esperaba: %s\n", prueba -> valor_esperado);
        printf("Se obtuvo: %s\n", output);
        return 0;
    }
}

int main(void){
    Prueba pruebas[] = {
        {"Entero", "1", "[INT_LITERAL:1]\n"},
        {"Comentario una línea", "// Hola", ""},
        {"Comentario multilínea", "/* Hola\n k ase*/", ""},
        {"Comentario multilínea anidado", "/*/*sd/*as\nd */s*/l\nll*/", ""},
        {"Comentario abierto en fin de archivo", "/*/*/**/*/", "Error, Fin de archivo y comentario abierto\n"},
        {"Literal True", "#t", "[KW_TRUE:#t]\n"},
        {"Literal False", "#f", "[KW_FALSE:#f]\n"},
        {"Right shift", ">>", "[RIGHT_SHIFT:>>]\n"},
        {"GE", ">=", "[GE:>=]\n"},
        {"GT", ">", "[GT:>]\n"},
        {"Variable: _algf","_algf", "[IDENTIFIER:_algf]\n"},
        {"Variable: l0_aS", "l0_aS", "[IDENTIFIER:l0_aS]\n"},
        {"Error en variable: 3a", "3a", "Variables deben empezar con _ o letras: 3a\n"},
        {"Float: Notación científica: 10.5e+2", "10.5e+2", "[FLOAT_LITERAL:10.5e+2]\n"}
    };
    int pruebas_totales = sizeof(pruebas) / sizeof(Prueba);
    int aprobadas = 0;

    for (int i = 0; i < pruebas_totales; i++){
        aprobadas += ejecuta_prueba(&pruebas[i]);
    }

    printf("\nResultados\n");
    printf("Aprobadas: %d/%d\n", aprobadas, pruebas_totales);
    return (aprobadas == pruebas_totales);
}