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

Vendedor vendedores[14]; // Array para almacenar hasta 15 vendedores

int main()
{
	cout << "======================== Bienvenido a Ventas Rapidas SA ========================" << endl;
	cout << "Cuantos vendedores desea registrar? (Maximo 15): ";
	int cantidad;
	cin >> cantidad;
	if (cantidad < 1 || 15 < cantidad) {
		cout << "Cantidad invalida. Debe ser entre 1 y 15." << endl;
		return 1; // Salir del programa si la cantidad es invalida
	}
    int codigo;
    for (int i = 0; i < cantidad; i++) {
        cout << "#Registro " << (i + 1) << ":" << endl;
        cout << "Codigo de vendedor: ";
        cin >> codigo;
        if (codigoExiste(codigo) == true) {
            cout << "El codigo unico de vendedor ingresado ya existe. Revise los numeros e intente nuevamente." << endl;
            i--; // Repetir el registro
            break;
        }
        else {
            for (int j = 0; j < i; j++) {
                if (vendedores[j].codigo == codigo) {
                    cout << "El codigo ya ha sido ingresado. Por favor, ingrese un codigo diferente." << endl;
                    i--; // Repetir el registro
                    break;
                }
			}
            vendedores[i].codigo = codigo;
        }

        cin.ignore();
        cout << "Nombre: ";
        cin.getline(vendedores[i].nombre, sizeof(vendedores[i].nombre));
		cout << "Sucursal: ";
		cin.getline(vendedores[i].sucursal, sizeof(vendedores[i].sucursal));
    }
    registroArchivo(vendedores, cantidad);
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