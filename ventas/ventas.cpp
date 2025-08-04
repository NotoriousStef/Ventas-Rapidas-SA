// ventas.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Venta {
    int fecha;
    int codigoVendedor;
    int codigoProducto;
    int monto;
};

struct Vendedor {
    int codigo;
    char nombre[30];
    char sucursal[20];
};

void registroArchivo(Venta ventas[], int cantidad);
bool codigoVendedorExiste(int codigoBuscado);
bool validarVenta(Venta venta);
int medirCantidadDeVentasPorFechas(int fechaBuscada);

Venta ventas[100000];

int main()
{
	int cantidad;

	cout << "======================== Bienvenido a Ventas Rapidas SA ========================" << endl;
	cout << "¿Cuantos ventas desea registrar?: ";
	cin >> cantidad;

    for (int i = 0; i < cantidad; i++) {
        int fecha;
        int codigoVendedor;
        int codigoProducto;
        int monto;

        cout << "#Registro " << (i + 1) << ":" << endl;
        cout << "Ingrese la fecha en formato AAAAMMDD (solo los números): ";
        cin >> fecha;
        ventas[i].fecha = fecha;
        cout << "Ingrese el codigo de vendedor: ";
        cin >> codigoVendedor;
        ventas[i].codigoVendedor = codigoVendedor;
        cout << "Ingrese el codigo de producto: ";
        cin >> codigoProducto;
        ventas[i].codigoProducto = codigoProducto;
        cout << "Ingrese el monto de la venta (solo los números): ";
        cin >> monto;
        ventas[i].monto = monto;

        if (!validarVenta(ventas[i])) {
            i--;
        }
    }
    registroArchivo(ventas, cantidad);
}

bool validarVenta(Venta venta) {
    if (medirCantidadDeVentasPorFechas(venta.fecha) >= 1000) {
        cout << "Se exedio el limite de ingreso de ventas por fecha." << endl;
        return 0;
    }

    if (codigoVendedorExiste(venta.codigoVendedor)) {
        cout << "El codigo unico de vendedor ingresado no existe. Revise los numeros e intente nuevamente." << endl;
        return 0;
    }

    return 1;
}

void registroArchivo(Venta ventas[], int cantidad) {
    FILE* archivo = fopen("ventas_diarias.dat", "ab"); 
    if (archivo == NULL) {
        cout << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    fwrite(ventas, sizeof(Venta), cantidad, archivo);

    fclose(archivo);
    cout << "Registro guardado exitosamente." << endl;
}

bool codigoVendedorExiste(int codigoBuscado) {
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

int medirCantidadDeVentasPorFechas(int fechaBuscada) {
    int cantFechaBuscada = 0;

    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) return 0;

    Venta temp; 
    while (fread(&temp, sizeof(Venta), 1, archivo) == 1) {
        if (temp.fecha == fechaBuscada) {
            cantFechaBuscada++;
        }
    }

    fclose(archivo);
    return cantFechaBuscada;
}