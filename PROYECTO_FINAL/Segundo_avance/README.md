# Sistema de Administración de Tienda en C++
## Avance 2 – Implementación del Sistema

---

# Descripción del Proyecto

El presente proyecto consiste en el desarrollo de un sistema de consola en C++ orientado a la administración de una tienda. El sistema permite gestionar productos, controlar stock, registrar ventas y generar reportes estadísticos mediante el uso de archivos binarios y programación estructurada.

El programa funciona en un ciclo continuo: el usuario elige una opción del menú principal → el módulo correspondiente se ejecuta → los cambios se guardan en disco → el sistema regresa al menú. Este ciclo se repite hasta que el usuario decide salir.

Toda la información se persiste en archivos binarios (`productos.dat` y `ventas.dat`) para que los datos no se pierdan al cerrar el programa.

---

# Objetivo General

Desarrollar un sistema de consola en C++ que permita administrar productos, ventas e inventario mediante archivos binarios, aplicando programación estructurada, modularización, búsqueda, ordenamiento, validación de datos y manejo de excepciones.

---

# Objetivos Específicos

- Registrar, listar, buscar, modificar y desactivar productos de la tienda.
- Registrar ventas con múltiples productos usando la estructura `DetalleVenta`.
- Validar el stock disponible antes de confirmar cada venta.
- Calcular subtotales, aplicar IVA (12%) y descuentos automáticos por monto o cantidad.
- Generar reportes de productos con menor stock, más vendidos y ventas por mes.
- Ordenar productos usando Bubble Sort y Selection Sort según distintos criterios.
- Implementar búsqueda secuencial por nombre y búsqueda directa por código.
- Utilizar una matriz `ventasPorMes[12][MAX_VENTAS]` para estadísticas mensuales.
- Exportar reportes a un archivo `.txt`.
- Aplicar manejo de excepciones con `try/catch` en entradas y operaciones de archivos.


---

# Estructura del Proyecto

El sistema está separado en múltiples archivos `.cpp` y `.h`, cada uno con una responsabilidad específica:

```
sistema/
├── main.cpp            → Menú principal y ciclo del programa
├── estructuras.h       → Structs, constantes y variables globales
├── archivos.h          → Prototipos de lectura/escritura de archivos
├── archivos.cpp        → Implementación de archivos binarios
├── productos.h         → Prototipos del Módulo 1
├── productos.cpp       → Módulo 1: Gestión de Productos
├── ventas.h            → Prototipos del Módulo 2
├── ventas.cpp          → Módulo 2: Proceso de Venta
├── reportes.h          → Prototipos del Módulo 3
├── reportes.cpp        → Módulo 3: Reportes y Ordenamientos
├── utilidades.h        → Prototipos del Módulo 4
└── utilidades.cpp      → Módulo 4: Utilidades del Sistema
```

---

# Módulos Implementados

## Módulo 1 – Gestión de Productos (`productos.cpp`)

Administra el catálogo de productos de la tienda:

- Registrar producto nuevo con validación de código único
- Listar todos los productos activos
- Buscar producto por código (búsqueda directa)
- Buscar producto por nombre (búsqueda secuencial, sin distinción de mayúsculas)
- Actualizar stock
- Modificar precio
- Eliminar / desactivar producto (eliminación lógica, el registro permanece en el archivo)

---

## Módulo 2 – Proceso de Venta (`ventas.cpp`)

Maneja el flujo completo de una transacción de venta:

- Crear venta con ID único y fecha del sistema
- Seleccionar múltiples productos usando `struct DetalleVenta`
- Validar stock disponible antes de agregar cada producto
- Calcular subtotal acumulado
- Aplicar IVA del 12%
- Aplicar descuento automático:
  - Si subtotal > Q500 → 5% de descuento
  - Si cantidad total de artículos % 5 == 0 → 3% de bono adicional
- Mostrar ticket con total redondeado a 2 decimales
- Confirmar venta antes de guardar
- Descontar stock automáticamente en `productos.dat`
- Guardar venta en `ventas.dat`

---

## Módulo 3 – Reportes (`reportes.cpp`)

Genera estadísticas y listados ordenados del sistema:

- Productos con menor stock (por umbral configurable)
- Top 10 productos más vendidos
- Ventas totales de un día específico
- Ventas por mes usando la matriz `ventasPorMes[12][MAX_VENTAS]`
- Ordenar productos con **Bubble Sort** (5 criterios)
- Ordenar productos con **Selection Sort** (5 criterios)

---

## Módulo 4 – Utilidades del Sistema (`utilidades.cpp`)

Funciones de mantenimiento y administración general:

- Exportar reporte completo a `reporte.txt` con fecha, inventario y ventas por mes
- Reiniciar inventario (requiere escribir `CONFIRMAR`)
- Mostrar estadísticas generales: productos activos, valor del inventario, total recaudado, promedio por venta

---

# Estructuras de Datos

## Struct Producto

```cpp
struct Producto {
    int    codigo;          // identificador único
    char   nombre[60];      // nombre del producto
    char   categoria[30];   // ej: "Electrónica", "Ropa"
    double precio;          // precio unitario en quetzales
    int    stock;           // unidades disponibles
    int    totalVendido;    // acumulado de unidades vendidas
    bool   activo;          // false = eliminado lógicamente
};
```

## Struct DetalleVenta

```cpp
struct DetalleVenta {
    int    idProducto;      // código del producto vendido
    char   nombre[60];      // nombre al momento de la venta
    int    cantidad;        // unidades compradas
    double precioUnit;      // precio al momento de la venta
    double subtotalDet;     // cantidad × precioUnit
};
```

## Struct Venta

```cpp
struct Venta {
    int          id;                    // número de venta
    char         fecha[11];             // formato "YYYY-MM-DD"
    int          mes;                   // 0=enero ... 11=diciembre
    DetalleVenta detalles[20];          // productos de la venta
    int          numDetalles;           // cuántos productos tiene
    int          totalArticulos;        // suma de cantidades
    double       subtotal;
    double       descuento;
    double       iva;
    double       total;                 // total final redondeado
};
```

---

# Archivos Binarios

```
productos.dat   →  almacena el arreglo de struct Producto
ventas.dat      →  almacena el arreglo de struct Venta
reporte.txt     →  archivo de exportación generado por el Módulo 4
```

Se leen al iniciar el programa y se actualizan cada vez que se realiza una operación de escritura.

---

# Modularización

El sistema cuenta con más de 25 funciones independientes distribuidas en los módulos:

```cpp
// Archivos
void cargarProductos();         void guardarProductos();
void cargarVentas();            void guardarVentas();

// Módulo 1 – Productos
void menuGestionProductos();    void registrarProducto();
void listarProductos();         int  buscarPorCodigo(int cod);
int  buscarPorNombre(const char* nombre);
void actualizarStock(int, int); void modificarPrecio(int, double);
void eliminarProducto(int);

// Módulo 2 – Ventas
void   menuProcesarVenta();     void   procesarVenta();
double calcularDescuento(double, int);
double calcularIVA(double);     double redondear(double, int);
void   actualizarMatrizMes(int);

// Módulo 3 – Reportes
void menuReportes();            void ordenarBubble(int);
void ordenarSelection(int);     void reporteMenorStock();
void reporteMasVendidos();      void reporteVentasDia();
void reporteVentasMes();

// Módulo 4 – Utilidades
void menuUtilidades();          void exportarReporte();
void reiniciarInventario();     void mostrarEstadisticas();
```

---

# Búsquedas Implementadas

| Tipo | Función | Descripción |
|---|---|---|
| Por código | `buscarPorCodigo(int cod)` | Recorre el arreglo comparando el código numérico. Retorna el índice o -1. |
| Por nombre | `buscarPorNombre(const char*)` | Búsqueda secuencial que compara sin distinción de mayúsculas usando `strstr()`. |

---

# Algoritmos de Ordenamiento

Ambos algoritmos están en `reportes.cpp` y aceptan 5 criterios:

| # | Criterio |
|---|---|
| 1 | Precio ascendente |
| 2 | Precio descendente |
| 3 | Stock ascendente |
| 4 | Stock descendente |
| 5 | Más vendidos |

### Bubble Sort

Compara elementos adyacentes y los intercambia si están en el orden incorrecto. Repite el proceso hasta que no hay más intercambios.

```cpp
void ordenarBubble(int criterio) {
    for (int i = 0; i < totalProductos - 1; i++)
        for (int j = 0; j < totalProductos - i - 1; j++)
            if (debeCambiar(productos[j], productos[j+1], criterio)) {
                Producto temp  = productos[j];
                productos[j]   = productos[j+1];
                productos[j+1] = temp;
            }
}
```

### Selection Sort

Busca el elemento mínimo en la parte no ordenada y lo coloca en su posición correcta.

```cpp
void ordenarSelection(int criterio) {
    for (int i = 0; i < totalProductos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < totalProductos; j++)
            if (debeCambiar(productos[minIdx], productos[j], criterio))
                minIdx = j;
        if (minIdx != i) {
            Producto temp     = productos[i];
            productos[i]      = productos[minIdx];
            productos[minIdx] = temp;
        }
    }
}
```

---

# Uso de Matrices

Se utiliza una matriz para almacenar estadísticas de ventas mensuales:

```cpp
int ventasPorMes[12][MAX_VENTAS];   // índices de ventas por mes
int conteoVentasMes[12] = {0};      // cuántas ventas hay en cada mes
```

Cada fila representa un mes (0 = enero, 11 = diciembre). Al registrar una venta se guarda su índice en la fila del mes correspondiente. El reporte mensual suma los totales de todas las ventas de cada fila.

---

# Manejo de Excepciones

Se implementa `try/catch` en los siguientes casos:

| Situación | Excepción capturada |
|---|---|
| El usuario escribe letras donde va un número | `invalid_argument` |
| Opción de menú fuera del rango válido | `out_of_range` |
| Stock negativo o precio igual a cero | Excepción lanzada manualmente |
| Error al abrir o crear archivos `.dat` | `runtime_error` |
| Código de producto duplicado al registrar | `runtime_error` |
| Venta sin productos confirmada | `runtime_error` |

---

# Cobertura de Requerimientos Técnicos

| Requerimiento | Estado | Archivo |
|---|---|---|
| `struct Producto` | ✅ Implementado | `estructuras.h` |
| `struct Venta` | ✅ Implementado | `estructuras.h` |
| `struct DetalleVenta` | ✅ Implementado | `estructuras.h` |
| `productos.dat` | ✅ Implementado | `archivos.cpp` |
| `ventas.dat` | ✅ Implementado | `archivos.cpp` |
| Mínimo 10 funciones | ✅ 25+ funciones | Todos los módulos |
| Búsqueda secuencial por nombre | ✅ Implementado | `productos.cpp` |
| Búsqueda por código | ✅ Implementado | `productos.cpp` |
| Bubble Sort | ✅ Implementado | `reportes.cpp` |
| Selection Sort | ✅ Implementado | `reportes.cpp` |
| Matriz `ventasPorMes[12][N]` | ✅ Implementado | `main.cpp` / `ventas.cpp` |
| `try/catch` | ✅ En todos los módulos | Todos los archivos |
| IVA 12% | ✅ `calcularIVA()` | `ventas.cpp` |
| Descuentos automáticos | ✅ `calcularDescuento()` | `ventas.cpp` |
| `round()` / redondeo | ✅ `redondear()` | `ventas.cpp` |
| Operador `%` en lógica comercial | ✅ `totalArticulos % 5 == 0` | `ventas.cpp` |
| Separación en múltiples archivos | ✅ 12 archivos `.cpp` y `.h` | Todo el proyecto |
| Exportar reporte `.txt` | ✅ Implementado | `utilidades.cpp` |

---

# Estado Actual del Proyecto

El proyecto se encuentra en la fase de:

- ✅ Análisis y diseño del sistema (Avance 1)
- ✅ Implementación del Módulo 1 — Gestión de Productos
- ✅ Implementación del Módulo 2 — Proceso de Venta
- ✅ Implementación del Módulo 3 — Reportes y Ordenamientos
- ✅ Implementación del Módulo 4 — Utilidades del Sistema
- ✅ Persistencia en archivos binarios
- ✅ Separación en múltiples archivos `.cpp` y `.h`
- ✅ Manejo de excepciones con `try/catch`

---

# Próximo Avance Final

En la entrega final se completará:

- Pruebas completas de todos los módulos con datos reales
- Revisión y ajuste de validaciones
- Aplicación de ajustes o recomendaciones. 
- Documentación final del código

---

*Avance 2 — Implementación del Sistema*
*Programación 1*
