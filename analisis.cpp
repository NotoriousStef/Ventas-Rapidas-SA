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
void establecerSucursales();
int sucursalConMayorIngreso(); 

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
	establecerSucursales();
    cout << "Gracias por usar el sistema de Ventas Rapidas SA" << endl;
}

void establecerVendedores() {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir el archivo de registro." << endl;
    } else {
        Vendedor temp;
        int i = 0;
        while (fread(&temp, sizeof(Vendedor), 1, archivo) == 1) {
            ventasVendedores[i].codigoVendedor = temp.codigo;
            strcpy(ventasVendedores[i].nombreVendedor, temp.nombre);
            ventasVendedores[i].totalVentas = 0;
            i++;
        }
    }
    fclose(archivo);
}

int vendedorConMayorIngreso() {
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
		if (ventasVendedores[j].totalVentas > ventasVendedores[vendedorMaxIngreso].totalVentas) {
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
			if (i == 0) {
				strcpy(ventasSucursales[i].nombreSucursal, temp.sucursal);
				ventasSucursales[i].totalVentas = 0;
			}
			else {
				bool existe = false;
				for (int j = 0; j <= i; j++) {
					if (strcmp(ventasSucursales[j].nombreSucursal, temp.sucursal) == 0) {
						existe = true;
					}
				}
				if (!existe) {
					strcpy(ventasSucursales[i].nombreSucursal, temp.sucursal);
					ventasSucursales[i].totalVentas = 0;
				}
			}
			i++;
        }

        fclose(archivo);
    }
}

void rankingProductos() {
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir el archivo de ventas." << endl;
        return;
    }
    Venta temp;
    Venta productosVendidos[1000]; // Suponiendo un máximo de 1000 productos diferentes
    int cantidadProductos = 0;
    int i = 0;
    while (fread(&temp, sizeof(Venta), 1, archivo) == 1) {
        if (i == 0) {
            productosVendidos[i].codigoProducto = temp.codigoProducto;
            productosVendidos[i].monto = temp.monto;
            cantidadProductos++;
        } else {
            bool existe = false;
            for (int j = 0; j < cantidadProductos; j++) {
                if (productosVendidos[j].codigoProducto == temp.codigoProducto) {
                    productosVendidos[j].monto += temp.monto;
                    existe = true;
                    break;
                }
            }
            if (!existe) {
                productosVendidos[cantidadProductos].codigoProducto = temp.codigoProducto;
                productosVendidos[cantidadProductos].monto = temp.monto;
                cantidadProductos++;
            }
        }
        i++;
    }
    fclose(archivo);

    // Ordenar productos por monto vendido
    for (int j = 0; j < cantidadProductos - 1; j++) {
        for (int k = j + 1; k < cantidadProductos; k++) {
            if (productosVendidos[j].monto < productosVendidos[k].monto) {
                Venta tempProducto = productosVendidos[j];
                productosVendidos[j] = productosVendidos[k];
                productosVendidos[k] = tempProducto;
            }
        }
    }

    cout << "Ranking de productos vendidos:" << endl;
    for (int j = 0; j < cantidadProductos; j++) {
        cout << "Producto: " << productosVendidos[j].codigoProducto << ", Monto vendido: " << productosVendidos[j].monto << endl;
    }


}

