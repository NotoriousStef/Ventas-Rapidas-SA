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
int medirCantidadDeVentasPorFechas(int fechaBuscada);
Venta ingresarVenta(int cantidadActual);

Venta ventas[100000];

int main()
{
    int cantidad;

    cout << "======================== Bienvenido a Ventas Rapidas SA ========================" << endl;
    cout << "¿Cuantas ventas desea registrar?: ";
    cin >> cantidad;

    for (int i = 0; i < cantidad; i++) {
        ventas[i] = ingresarVenta(i);
    }

    registroArchivo(ventas, cantidad);
    cout << "Registro de ventas finalizado. Gracias por usar el sistema de Ventas Rapidas SA" << endl;
}

Venta ingresarVenta(int cantidadActual) {
    Venta nuevaVenta;
    bool fechaValida = false;
    bool codigoVendedorValido = false;

    while (!fechaValida) {
        cout << "Ingrese la fecha en formato AAAAMMDD (solo los números): ";
        cin >> nuevaVenta.fecha;

        int ventasEnArchivo = medirCantidadDeVentasPorFechas(nuevaVenta.fecha);
        int ventasEnMemoria = 0;
        for (int i = 0; i < cantidadActual; i++) {
            if (ventas[i].fecha == nuevaVenta.fecha) ventasEnMemoria++;
        }

        if ((ventasEnArchivo + ventasEnMemoria) >= 1000) {
            cout << "Se excedió el límite de ingreso de ventas por fecha." << endl;
        } else {
            fechaValida = true;
        }
    }

    while (!codigoVendedorValido) {
        cout << "Ingrese el codigo de vendedor: ";
        cin >> nuevaVenta.codigoVendedor;

        if (codigoVendedorExiste(nuevaVenta.codigoVendedor)) {
            codigoVendedorValido = true;
        } else {
            cout << "El codigo unico de vendedor ingresado no existe. Revise los numeros e intente nuevamente." << endl;
        }
    }
    
    cout << "Ingrese el codigo de producto: ";
    cin >> nuevaVenta.codigoProducto;
    cout << "Ingrese el monto de la venta (solo los números): ";
    cin >> nuevaVenta.monto;

    return nuevaVenta;
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