// registro.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Vendedor {
    int codigo;
    char nombre[30];
    char sucursal[20];
};

void registroArchivo(Vendedor vendedores[], int cantidad);
bool codigoExiste(int codigoBuscado);
bool validarCodigo(int codigo, int index);
int medirVendedores();
bool sucursalExiste(char sucursales[][20], int cantidad, const char* nuevaSucursal);
int cargarSucursales(char sucursales[][20]);

Vendedor vendedores[14]; // Array para almacenar hasta 15 vendedores

int main()
{
    cout << "======================== Bienvenido a Ventas Rapidas SA ========================" << endl;
    int vendedoresRegistrados = medirVendedores();
    int disponibles = 15 - vendedoresRegistrados; // Calcular vendedores disponibles
    if (disponibles == 0) {
        cout << "No hay espacio disponible para registrar nuevos vendedores. El limite de 15 fue alcanzado." << endl;
        return 0; // Espacio lleno
    }
    cout << "Cuantos vendedores desea registrar? (Maximo actual " << disponibles << "):";
    int cantidad;
    cin >> cantidad;
    if (cantidad < 1 || disponibles < cantidad) {
        cout << "Cantidad invalida. Debe ser entre 1 y " << disponibles << "." << endl;
        return 1; // Cantidad invalida
    }

	char sucursalesExistentes[2][20]; // Array para almacenar hasta 3 sucursales diferentes
    int totalSucursales = cargarSucursales(sucursalesExistentes);

    int codigo;
    for (int i = 0; i < cantidad; i++) {
        cout << "#Registro " << (i + 1) << ":" << endl;
        cout << "Codigo de vendedor: ";
        cin >> codigo;

        if (validarCodigo(codigo, i)) {
            vendedores[i].codigo = codigo;
            cin.ignore();
            cout << "Nombre: ";
            cin.getline(vendedores[i].nombre, sizeof(vendedores[i].nombre));
            while (true) {
                cout << "Sucursal: ";
                cin.getline(vendedores[i].sucursal, sizeof(vendedores[i].sucursal));
                bool existe = sucursalExiste(sucursalesExistentes, totalSucursales, vendedores[i].sucursal);
                if (existe == true || totalSucursales < 3) {
                    if (!existe) {
                        strcpy(sucursalesExistentes[totalSucursales], vendedores[i].sucursal);
                        totalSucursales++;
                    }
                    break; // Salir del bucle while
                }
                else {
                    cout << "El limite de sucursales ya fue alcanzado. No se puede registrar una nueva sucursal." << endl;
                }
            }
        }
        else {
            i--;
        }
    }
    registroArchivo(vendedores, cantidad);
}

bool validarCodigo(int codigo, int index) {
    if (codigoExiste(codigo) == true) {
        cout << "El codigo unico de vendedor ingresado ya existe. Revise los numeros e intente nuevamente." << endl;
        // Repetir el registro
        return 0;
    }

    for (int j = 0; j < index; j++) {
        if (vendedores[j].codigo == codigo) {
            cout << "El codigo ya ha sido ingresado. Por favor, ingrese un codigo diferente." << endl;
            // Repetir el registro
            return 0;
        }
    }

    return 1;
}

void registroArchivo(Vendedor vendedores[], int cantidad) {
    FILE* archivo = fopen("vendedores.dat", "ab");
    if (archivo == NULL) {
        cout << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    fwrite(vendedores, sizeof(Vendedor), cantidad, archivo);

    fclose(archivo);
    cout << "Registro guardado exitosamente." << endl;
}

bool codigoExiste(int codigoBuscado) {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) return false;

    Vendedor temp;
    while (fread(&temp, sizeof(Vendedor), 1, archivo) == 1) {
        if (temp.codigo == codigoBuscado) {
            fclose(archivo);
            return true;
        }
    }

    fclose(archivo);
    return false;
}

int medirVendedores() {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) return 0;
    fseek(archivo, 0, SEEK_END);
    int cantidadVendedores = ftell(archivo) / sizeof(Vendedor);
    fclose(archivo);
    return cantidadVendedores;
}

bool sucursalExiste(char sucursales[][20], int cantidad, const char* nuevaSucursal) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(sucursales[i], nuevaSucursal) == 0) {
            return true;
        }
    }
    return false;
}

int cargarSucursales(char sucursales[][20]) {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) return 0;

    Vendedor temp;
    int cantidad = 0;

    while (fread(&temp, sizeof(Vendedor), 1, archivo) == 1) {
        if (!sucursalExiste(sucursales, cantidad, temp.sucursal)) {
            strcpy(sucursales[cantidad], temp.sucursal);
            cantidad++;
        }
    }

    fclose(archivo);
    return cantidad;
}
