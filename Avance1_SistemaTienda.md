# Avance 1 — Sistema de Administración de Tienda en C++
## Algoritmo General, Pseudocódigo y Declaración de Variables

---

# Descripción del Proyecto

El presente proyecto consiste en el desarrollo de un sistema en C++ orientado a la administración de ventas e inventario para una tienda.

El sistema permitirá gestionar productos, controlar stock, registrar ventas y generar reportes estadísticos mediante el uso de archivos binarios, programación estructurada y modularización.

Además, se implementarán validaciones, búsquedas, ordenamientos y manejo de excepciones para mejorar la integridad y organización del sistema.

---

## 1. ALGORITMO GENERAL

### Idea central
El sistema es un programa de consola que se ejecuta en un ciclo continuo. Al iniciarse carga los datos desde archivos binarios (`productos.dat` y `ventas.dat`), luego presenta un menú con cuatro módulos. El usuario navega el menú, realiza operaciones y el programa persiste los cambios en disco antes de volver al menú. El ciclo se repite hasta que el usuario elige salir.

### Pasos del algoritmo principal

1. **Inicialización**: Intentar abrir `productos.dat` y `ventas.dat`. Si no existen, crearlos vacíos.
2. **Ciclo principal** (se repite hasta salir):
   - Mostrar menú principal con las 4 opciones de módulo + salir.
   - Leer opción del usuario con validación (try/catch para entradas inválidas).
   - Derivar al módulo correspondiente.
3. **Módulo 1 – Gestión de productos**: CRUD sobre `struct Producto` persistido en `productos.dat`.
4. **Módulo 2 – Proceso de venta**: Crear `struct Venta` con sus `struct DetalleVenta[]`, validar stock, calcular totales con IVA y descuentos, guardar en `ventas.dat`, descontar stock.
5. **Módulo 3 – Reportes**: Leer ambos archivos, aplicar ordenamiento (Bubble Sort / Selection Sort), búsqueda secuencial/por código y llenar la matriz `ventasPorMes[12][N]`.
6. **Módulo 4 – Utilidades**: Exportar a `.txt`, reiniciar inventario con confirmación, mostrar estadísticas.
7. **Finalización**: Guardar estado final en archivos y cerrar el programa.

---

## 2. PSEUDOCÓDIGO COMPLETO

```
PROGRAMA SistemaTienda
  CONSTANTES:
    MAX_PRODUCTOS = 500
    MAX_VENTAS    = 1000
    MAX_DETALLE   = 20
    IVA           = 0.12
    DESC_MONTO    = 0.05
    LIMITE_MONTO  = 500.0

  ESTRUCTURAS: (ver Sección 3)

  VARIABLES GLOBALES:
    productos[MAX_PRODUCTOS] : arreglo de Producto
    totalProductos : entero = 0
    ventas[MAX_VENTAS] : arreglo de Venta
    totalVentas : entero = 0
    ventasPorMes[12][MAX_VENTAS] : entero (matriz de conteo)

  ═══════════════════════════════════════════════
  FUNCIÓN principal()
  ═══════════════════════════════════════════════
    INICIO
      cargarProductos()        // lee productos.dat
      cargarVentas()           // lee ventas.dat
      opcion ← 0
      MIENTRAS opcion ≠ 5 HACER
        mostrarMenuPrincipal()
        INTENTAR
          leer opcion
          SI opcion < 1 O opcion > 5 ENTONCES
            LANZAR excepción "Opción inválida"
          FIN SI
        ATRAPAR excepción
          mostrar "Error: ingrese un número entre 1 y 5"
          CONTINUAR
        FIN INTENTAR
        SEGÚN opcion HACER
          CASO 1: menuGestionProductos()
          CASO 2: menuProcesarVenta()
          CASO 3: menuReportes()
          CASO 4: menuUtilidades()
          CASO 5: mostrar "Hasta luego"
        FIN SEGÚN
      FIN MIENTRAS
    FIN

  ═══════════════════════════════════════════════
  MÓDULO 1 — Gestión de Productos Pseudocódigo
  ═══════════════════════════════════════════════

  FUNCIÓN registrarProducto()
    INICIO
      INTENTAR
        leer codigo, nombre, precio, stock, categoria
        SI precio ≤ 0 O stock < 0 ENTONCES
          LANZAR excepción "Datos inválidos"
        FIN SI
        SI buscarPorCodigo(codigo) ≠ -1 ENTONCES
          mostrar "Código ya existe"
          RETORNAR
        FIN SI
        nuevo ← crear Producto con datos leídos
        nuevo.activo ← VERDADERO
        nuevo.totalVendido ← 0
        productos[totalProductos] ← nuevo
        totalProductos++
        guardarProductos()     // escribe en productos.dat
        mostrar "Producto registrado con éxito"
      ATRAPAR excepción
        mostrar "Error al registrar: " + mensaje
      FIN INTENTAR
    FIN

  FUNCIÓN listarProductos()
    INICIO
      SI totalProductos = 0 ENTONCES
        mostrar "No hay productos registrados"
        RETORNAR
      FIN SI
      PARA i ← 0 HASTA totalProductos-1 HACER
        SI productos[i].activo ENTONCES
          mostrar codigo, nombre, precio, stock
        FIN SI
      FIN PARA
    FIN

  FUNCIÓN buscarPorCodigo(cod : entero) → entero
    INICIO
      PARA i ← 0 HASTA totalProductos-1 HACER
        SI productos[i].codigo = cod Y productos[i].activo ENTONCES
          RETORNAR i
        FIN SI
      FIN PARA
      RETORNAR -1  // no encontrado
    FIN

  FUNCIÓN buscarPorNombre(nombre : cadena) → entero
    // Búsqueda secuencial por nombre (insensible a mayúsculas)
    INICIO
      PARA i ← 0 HASTA totalProductos-1 HACER
        SI toLower(productos[i].nombre) CONTIENE toLower(nombre)
          Y productos[i].activo ENTONCES
          RETORNAR i
        FIN SI
      FIN PARA
      RETORNAR -1
    FIN

  FUNCIÓN actualizarStock(cod : entero, nuevoStock : entero)
    INICIO
      idx ← buscarPorCodigo(cod)
      SI idx = -1 ENTONCES mostrar "No encontrado" RETORNAR FIN SI
      SI nuevoStock < 0 ENTONCES
        LANZAR excepción "Stock no puede ser negativo"
      FIN SI
      productos[idx].stock ← nuevoStock
      guardarProductos()
    FIN

  FUNCIÓN modificarPrecio(cod : entero, nuevoPrecio : real)
    INICIO
      idx ← buscarPorCodigo(cod)
      SI idx = -1 ENTONCES mostrar "No encontrado" RETORNAR FIN SI
      SI nuevoPrecio ≤ 0 ENTONCES
        LANZAR excepción "Precio debe ser positivo"
      FIN SI
      productos[idx].precio ← nuevoPrecio
      guardarProductos()
    FIN

  FUNCIÓN eliminarProducto(cod : entero)
    // Desactivación lógica (no borra el registro)
    INICIO
      idx ← buscarPorCodigo(cod)
      SI idx = -1 ENTONCES mostrar "No encontrado" RETORNAR FIN SI
      productos[idx].activo ← FALSO
      guardarProductos()
      mostrar "Producto desactivado"
    FIN

  ═══════════════════════════════════════════════
  MÓDULO 2 — Proceso de Venta Pseudocódigo
  ═══════════════════════════════════════════════

  FUNCIÓN procesarVenta()
    INICIO
      nuevaVenta ← nueva Venta vacía
      nuevaVenta.id ← totalVentas + 1
      nuevaVenta.fecha ← obtenerFechaActual()
      subtotal ← 0.0
      totalArticulos ← 0
      seguirAgregando ← VERDADERO

      MIENTRAS seguirAgregando HACER
        INTENTAR
          leer codigoProducto, cantidad
          idx ← buscarPorCodigo(codigoProducto)
          SI idx = -1 ENTONCES
            mostrar "Producto no encontrado"
            CONTINUAR
          FIN SI
          SI productos[idx].stock < cantidad ENTONCES
            mostrar "Stock insuficiente (disponible: " + productos[idx].stock + ")"
            CONTINUAR
          FIN SI
          // Agregar detalle
          det.idProducto  ← codigoProducto
          det.nombre      ← productos[idx].nombre
          det.cantidad    ← cantidad
          det.precioUnit  ← productos[idx].precio
          det.subtotalDet ← cantidad * productos[idx].precio
          nuevaVenta.detalles[nuevaVenta.numDetalles] ← det
          nuevaVenta.numDetalles++
          subtotal        ← subtotal + det.subtotalDet
          totalArticulos  ← totalArticulos + cantidad
          leer confirmacion "¿Agregar otro producto? (s/n)"
          SI confirmacion = 'n' ENTONCES seguirAgregando ← FALSO FIN SI
        ATRAPAR excepción
          mostrar "Error en entrada: " + mensaje
        FIN INTENTAR
      FIN MIENTRAS

      // ── Calcular descuentos ──
      descuento ← 0.0
      SI subtotal > LIMITE_MONTO ENTONCES
        descuento ← subtotal * DESC_MONTO    // 5%
      FIN SI
      SI totalArticulos % 5 = 0 ENTONCES
        descuento ← descuento + subtotal * 0.03  // bono adicional 3%
      FIN SI
      baseIVA ← subtotal - descuento
      iva     ← baseIVA * IVA
      total   ← redondear(baseIVA + iva, 2)

      nuevaVenta.subtotal   ← subtotal
      nuevaVenta.descuento  ← descuento
      nuevaVenta.iva        ← iva
      nuevaVenta.total      ← total
      nuevaVenta.mes        ← obtenerMesActual()  // 0-11

      mostrar ticket con subtotal, descuento, IVA, total

      // ── Descontar stock y guardar ──
      PARA i ← 0 HASTA nuevaVenta.numDetalles-1 HACER
        idx ← buscarPorCodigo(nuevaVenta.detalles[i].idProducto)
        productos[idx].stock       ← productos[idx].stock - nuevaVenta.detalles[i].cantidad
        productos[idx].totalVendido ← productos[idx].totalVendido + nuevaVenta.detalles[i].cantidad
      FIN PARA

      ventas[totalVentas] ← nuevaVenta
      totalVentas++
      guardarProductos()
      guardarVentas()
      actualizarMatrizMes(nuevaVenta)
    FIN

  ═══════════════════════════════════════════════
  MÓDULO 3 — Reportes Pseudocódigo
  ═══════════════════════════════════════════════

  FUNCIÓN ordenarBubble(criterio : entero)
    // criterio: 1=precio asc, 2=precio desc, 3=stock asc, 4=stock desc, 5=ventas
    INICIO
      PARA i ← 0 HASTA totalProductos-2 HACER
        PARA j ← 0 HASTA totalProductos-i-2 HACER
          intercambiar ← FALSO
          SEGÚN criterio HACER
            CASO 1: SI productos[j].precio  > productos[j+1].precio  ENTONCES intercambiar FIN
            CASO 2: SI productos[j].precio  < productos[j+1].precio  ENTONCES intercambiar FIN
            CASO 3: SI productos[j].stock   > productos[j+1].stock   ENTONCES intercambiar FIN
            CASO 4: SI productos[j].stock   < productos[j+1].stock   ENTONCES intercambiar FIN
            CASO 5: SI productos[j].totalVendido < productos[j+1].totalVendido ENTONCES intercambiar FIN
          FIN SEGÚN
          SI intercambiar ENTONCES
            temp ← productos[j]
            productos[j] ← productos[j+1]
            productos[j+1] ← temp
          FIN SI
        FIN PARA
      FIN PARA
    FIN

  FUNCIÓN ordenarSelection(criterio : entero)
    INICIO
      PARA i ← 0 HASTA totalProductos-2 HACER
        minIdx ← i
        PARA j ← i+1 HASTA totalProductos-1 HACER
          SI cumpleCriterio(productos[j], productos[minIdx], criterio) ENTONCES
            minIdx ← j
          FIN SI
        FIN PARA
        SI minIdx ≠ i ENTONCES
          temp ← productos[i]; productos[i] ← productos[minIdx]; productos[minIdx] ← temp
        FIN SI
      FIN PARA
    FIN

  FUNCIÓN reporteMenorStock(umbral : entero)
    INICIO
      PARA i ← 0 HASTA totalProductos-1 HACER
        SI productos[i].stock ≤ umbral Y productos[i].activo ENTONCES
          mostrar productos[i]
        FIN SI
      FIN PARA
    FIN

  FUNCIÓN reporteMasVendidos()
    INICIO
      copia ← copiar arreglo productos
      ordenarBubble(5)   // por totalVendido desc
      mostrar top 10
    FIN

  FUNCIÓN reporteVentasDia(fecha : cadena)
    INICIO
      totalDia ← 0.0
      PARA i ← 0 HASTA totalVentas-1 HACER
        SI ventas[i].fecha = fecha ENTONCES
          totalDia ← totalDia + ventas[i].total
        FIN SI
      FIN PARA
      mostrar "Ventas del día " + fecha + ": Q" + totalDia
    FIN

  FUNCIÓN reporteVentasMes()
    // Usa la matriz ventasPorMes[12][MAX_VENTAS]
    INICIO
      PARA mes ← 0 HASTA 11 HACER
        totalMes ← 0.0
        PARA i ← 0 HASTA ventasPorMes[mes][0]-1 HACER  // [mes][0] = cantidad de ventas
          totalMes ← totalMes + ventasPorMes[mes][i+1]
        FIN PARA
        mostrar nombreMes(mes) + ": Q" + totalMes
      FIN PARA
    FIN

  ═══════════════════════════════════════════════
  MÓDULO 4 — Utilidades del Sistema Pseudocódigo
  ═══════════════════════════════════════════════

  FUNCIÓN exportarReporte()
    INICIO
      INTENTAR
        abrir archivo "reporte.txt" para escritura
        SI error ENTONCES LANZAR excepción "No se pudo crear reporte.txt" FIN SI
        escribir encabezado con fecha y hora
        escribir listado de productos
        escribir resumen de ventas
        cerrar archivo
        mostrar "Reporte exportado exitosamente"
      ATRAPAR excepción
        mostrar "Error de archivo: " + mensaje
      FIN INTENTAR
    FIN

  FUNCIÓN reiniciarInventario()
    INICIO
      mostrar "¿Está seguro de reiniciar el inventario? (escriba CONFIRMAR)"
      leer confirmacion
      SI confirmacion = "CONFIRMAR" ENTONCES
        PARA i ← 0 HASTA totalProductos-1 HACER
          productos[i].stock ← 0
        FIN PARA
        guardarProductos()
        mostrar "Inventario reiniciado"
      SINO
        mostrar "Operación cancelada"
      FIN SI
    FIN

  FUNCIÓN mostrarEstadisticas()
    INICIO
      totalRecaudado ← 0.0
      PARA i ← 0 HASTA totalVentas-1 HACER
        totalRecaudado ← totalRecaudado + ventas[i].total
      FIN PARA
      mostrar "Total productos activos: " + contarActivos()
      mostrar "Total ventas realizadas: " + totalVentas
      mostrar "Total recaudado: Q"        + totalRecaudado
      mostrar "Promedio por venta: Q"     + (totalRecaudado / totalVentas)
    FIN

FIN PROGRAMA
```

---

## 3. DECLARACIÓN DE ESTRUCTURAS Y VARIABLES PROPUESTAS

```cpp
// ═══════════════════════════════════════════════════════
//  Sistema de Administración de Tienda - Avance 1
//  Declaración de structs, constantes y variables globales
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <stdexcept>

using namespace std;

// ───────────────────────────────────────────────────────
//  CONSTANTES DEL SISTEMA
// ───────────────────────────────────────────────────────
const int    MAX_PRODUCTOS  = 500;
const int    MAX_VENTAS     = 1000;
const int    MAX_DETALLE    = 20;      // máx. productos por venta
const int    MAX_MESES      = 12;
const double IVA_RATE       = 0.12;   // 12 % IVA
const double DESC_MONTO_POR = 0.05;   // 5 % si subtotal > Q500
const double DESC_BONO_POR  = 0.03;   // 3 % bono artículos % 5 == 0
const double LIMITE_DESC    = 500.0;  // Q500 umbral descuento
const char   FILE_PRODUCTOS[] = "productos.dat";
const char   FILE_VENTAS[]    = "ventas.dat";
const char   FILE_REPORTE[]   = "reporte.txt";

// ───────────────────────────────────────────────────────
//  STRUCT: Producto
// ───────────────────────────────────────────────────────
struct Producto {
    int    codigo;           // identificador único
    char   nombre[60];       // nombre del producto
    char   categoria[30];    // categoría (ej. "Electrónica")
    double precio;           // precio unitario en quetzales
    int    stock;            // unidades disponibles
    int    totalVendido;     // acumulado de unidades vendidas (para reportes)
    bool   activo;           // false = eliminado lógicamente
};

// ───────────────────────────────────────────────────────
//  STRUCT: DetalleVenta  (línea de producto dentro de una venta)
// ───────────────────────────────────────────────────────
struct DetalleVenta {
    int    idProducto;       // código del producto vendido
    char   nombre[60];       // copia del nombre (por si se modifica después)
    int    cantidad;         // unidades compradas en esta línea
    double precioUnit;       // precio al momento de la venta
    double subtotalDet;      // cantidad * precioUnit
};

// ───────────────────────────────────────────────────────
//  STRUCT: Venta
// ───────────────────────────────────────────────────────
struct Venta {
    int          id;                          // número de venta
    char         fecha[11];                   // "YYYY-MM-DD"
    int          mes;                         // 0-11 (para matriz)
    DetalleVenta detalles[MAX_DETALLE];       // líneas de la venta
    int          numDetalles;                 // cuántos detalles tiene
    int          totalArticulos;              // suma de cantidades
    double       subtotal;                    // antes de descuentos
    double       descuento;                   // monto de descuento aplicado
    double       iva;                         // monto de IVA
    double       total;                       // total final redondeado
};

// ───────────────────────────────────────────────────────
//  VARIABLES GLOBALES
// ───────────────────────────────────────────────────────

// Arreglo principal de productos (cargado desde productos.dat)
Producto productos[MAX_PRODUCTOS];
int      totalProductos = 0;

// Arreglo principal de ventas (cargado desde ventas.dat)
Venta    ventas[MAX_VENTAS];
int      totalVentas = 0;

// Matriz de ventas por mes: ventasPorMes[mes][índice de venta en ese mes]
// Almacena IDs de ventas por mes para reportes estadísticos
int ventasPorMes[MAX_MESES][MAX_VENTAS];
int conteoVentasMes[MAX_MESES] = {0};  // cuántas ventas hay por mes

// ───────────────────────────────────────────────────────
//  PROTOTIPOS DE FUNCIONES 
// ───────────────────────────────────────────────────────

// Archivos
void cargarProductos();
void guardarProductos();
void cargarVentas();
void guardarVentas();

// Módulo 1 – Productos
void   menuGestionProductos();
void   registrarProducto();
void   listarProductos();
int    buscarPorCodigo(int cod);
int    buscarPorNombre(const char* nombre);
void   actualizarStock(int cod, int nuevoStock);
void   modificarPrecio(int cod, double nuevoPrecio);
void   eliminarProducto(int cod);

// Módulo 2 – Ventas
void   menuProcesarVenta();
void   procesarVenta();
double calcularDescuento(double subtotal, int totalArticulos);
double calcularIVA(double base);
double redondear(double valor, int decimales);
void   actualizarMatrizMes(const Venta& v);

// Módulo 3 – Reportes
void   menuReportes();
void   ordenarBubble(int criterio);
void   ordenarSelection(int criterio);
void   reporteMenorStock(int umbral);
void   reporteMasVendidos();
void   reporteVentasDia(const char* fecha);
void   reporteVentasMes();

// Módulo 4 – Utilidades
void   menuUtilidades();
void   exportarReporte();
void   reiniciarInventario();
void   mostrarEstadisticas();

// Auxiliares
void   mostrarMenuPrincipal();
void   limpiarPantalla();
char*  obtenerFechaActual();
int    obtenerMesActual();
int    contarActivos();

// ───────────────────────────────────────────────────────
//  FUNCIÓN MAIN 
// ───────────────────────────────────────────────────────
int main() {
    // Inicializar matriz de ventas por mes a cero
    for (int m = 0; m < MAX_MESES; m++)
        for (int v = 0; v < MAX_VENTAS; v++)
            ventasPorMes[m][v] = 0;

    // Cargar datos desde archivos binarios
    try {
        cargarProductos();
        cargarVentas();
    } catch (const exception& e) {
        cout << "Advertencia al cargar datos: " << e.what() << endl;
        cout << "Se iniciara con datos vacios." << endl;
    }

    int opcion = 0;

    do {
        mostrarMenuPrincipal();
        try {
            cin >> opcion;
            if (cin.fail()) throw invalid_argument("Entrada no numerica");
            if (opcion < 1 || opcion > 5) throw out_of_range("Opcion fuera de rango");
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Ingrese 1-5.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1: menuGestionProductos(); break;
            case 2: menuProcesarVenta();    break;
            case 3: menuReportes();         break;
            case 4: menuUtilidades();       break;
            case 5: cout << "Hasta luego.\n"; break;
        }
    } while (opcion != 5);

    return 0;
}
```

---

## 4. RESUMEN DE REQUERIMIENTOS TÉCNICOS CUBIERTOS

| Requerimiento | Cómo se cubre |
|---|---|
| `struct Producto` | Declarado con 7 campos incluyendo `activo` y `totalVendido` |
| `struct Venta` | Declarado con referencia a `DetalleVenta[]` |
| `struct DetalleVenta` | Declarado como sub-estructura de Venta |
| `productos.dat` / `ventas.dat` | Constantes de nombre declaradas; funciones de I/O prototipadas |
| Mínimo 10 funciones | 25+ prototipos declarados en sección 3 |
| Búsqueda secuencial por nombre | `buscarPorNombre()` en pseudocódigo Módulo 1 |
| Búsqueda por código | `buscarPorCodigo()` en pseudocódigo Módulo 1 |
| Bubble Sort | `ordenarBubble()` en pseudocódigo Módulo 3 |
| Selection Sort | `ordenarSelection()` en pseudocódigo Módulo 3 |
| Matriz `ventasPorMes[12][N]` | `ventasPorMes[MAX_MESES][MAX_VENTAS]` declarada globalmente |
| try/catch | En `main()`, `registrarProducto()`, `procesarVenta()`, `exportarReporte()` |
| IVA, descuentos, redondeo, `%` | Constantes + funciones `calcularDescuento()`, `calcularIVA()`, `redondear()` |

---
*Avance 1 — Planeación base. El Avance 2 contendrá la implementación completa de todas las funciones.*
