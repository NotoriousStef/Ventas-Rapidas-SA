// analisis.cpp

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

struct VentasVendedor {
    int codigoVendedor;
    char nombreVendedor[30];
    int totalVentas;
};

VentasVendedor ventasVendedores[15];

struct VentasSucursal {
    char nombreSucursal[20];
    int totalVentas;
};

VentasSucursal ventasSucursales[3];

void establecerVendedores();
int vendedorConMayorIngreso();

int main()
{
    int cantidad;

    cout << "======================== Bienvenido a Ventas Rapidas SA ========================" << endl;

    establecerVendedores();
    int vendedorMaxIngreso = vendedorConMayorIngreso();
    cout << "El vendedor con mayor ingreso es el vendedor numero: " << ventasVendedores[vendedorMaxIngreso].codigoVendedor << endl;
    cout << "Nombre del vendedor: " << ventasVendedores[vendedorMaxIngreso].nombreVendedor << endl;
    cout << "Total de ventas del vendedor: " << ventasVendedores[vendedorMaxIngreso].totalVentas << endl;

    //TODO: Implementar la busqueda de sucursal con mayor ingreso y producto mas vendido

    cout << "Gracias por usar el sistema de Ventas Rapidas SA" << endl;
}

void establecerVendedores() {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir el archivo de registro." << endl;
        return 0; // No existe el archivo
    } else {
        Vendedor temp;
        int i = 0;
        while (fread(&temp, sizeof(Vendedor), 1, archivo) == 1) {
            ventasVendedores[i].codigoVendedor = temp.codigo;
            strcpy(ventasVendedores[i].nombreVendedor, temp.nombre);
            ventasVendedores[i].totalVentas = 0;
            i++;
        }

        fclose(archivo);
    };
}

int vendedorConMayorIngreso() {
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) return 0;

    Venta temp;
    int i = 0;
    while (fread(&temp, sizeof(Venta), 1, archivo) == 1) {
		for (int i = 0; i < 15; i++) { //debería haber un cantidad de vendedores no hardcodear el 15, se hace con el fseek y el ftell, lo puedo hacer yo
            if (temp.codigoVendedor == ventasVendedores[i].codigoVendedor) {
                ventasVendedores[i].totalVentas += temp.monto;
                break;
            }
        }
    }

    fclose(archivo);

    int vendedorMaxIngreso = 0;

    for (int j = 0; j < 15; j++) {
		if (j == 0 || ventasVendedores[j].totalVentas > ventasVendedores[vendedorMaxIngreso].totalVentas) { // no es necesario el j==0 porque ya se settea a 0 inicialmente
            vendedorMaxIngreso = j;
        }
    }

    return vendedorMaxIngreso;
}

void establecerSucursales() {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir el archivo de registro." << endl;
    } else {
        Vendedor temp;
        int i = 0;
        while (fread(&temp, sizeof(Vendedor), 1, archivo) == 1) {
            strcpy(ventasSucursales[i].nombreSucursal, temp.sucursal);
            ventasVendedores[i].totalVentas = 0;
            i++;
        }

        fclose(archivo);
    };
}

/* int sucursalConMayorIngreso() { //Falta de implementacion
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) return 0;

    Venta temp;
    int i = 0;
    while (fread(&temp, sizeof(Venta), 1, archivo) == 1) {
        for (int i = 0; i < 15; i++) {
            if (temp.codigoVendedor == ventasVendedores[i].codigoVendedor) {
                ventasVendedores[i].totalVentas += temp.monto;
                break;
            }
        }
    }

    fclose(archivo);

    int vendedorMaxIngreso = 0;

    for (int j = 0; j < 15; j++) {
        if (j == 0 || ventasVendedores[j].totalVentas > ventasVendedores[vendedorMaxIngreso].totalVentas) {
            vendedorMaxIngreso = j;
        }
    }

    return vendedorMaxIngreso;
} */
