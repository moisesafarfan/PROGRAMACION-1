# Sistema de Administración de Tienda en C++
## Entrega Final — Proyecto de Programación 1

---

# Información del Estudiante

| Campo | Detalle |
|---|---|
| **Estudiante** | Moisés Abinadí Farfan González |
| **Carné** | 9941-25-86 |
| **Curso** | Programación 1 |
| **Proyecto** | Sistema de Administración de Tienda |
| **Fase** | Entrega Final |
| **Lenguaje** | C++ — Programación Estructurada |

---

# Descripción del Proyecto

El Sistema de Administración de Tienda es un programa de consola desarrollado en C++ que permite gestionar de forma completa una tienda pequeña. El sistema administra productos, procesa ventas, genera reportes estadísticos y mantiene el control del inventario mediante archivos binarios.

El programa opera en un ciclo continuo: el usuario selecciona una opción del menú principal, el módulo correspondiente se ejecuta, los cambios se persisten en disco y el sistema regresa al menú. Este ciclo se repite hasta que el usuario decide salir.

Toda la información se guarda en archivos binarios (`productos.dat` y `ventas.dat`) para que los datos no se pierdan al cerrar el programa.

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
- Ordenar productos usando **Bubble Sort** y **Selection Sort** según distintos criterios.
- Implementar búsqueda secuencial por nombre y búsqueda directa por código.
- Utilizar una matriz `ventasPorMes[12][MAX_VENTAS]` para estadísticas mensuales.
- Exportar reportes a un archivo `.txt`.
- Aplicar `try/catch` en todas las entradas y operaciones de archivos.

---

# Tecnologías Utilizadas

- **Lenguaje:** C++
- **Paradigma:** Programación estructurada
- **Persistencia de datos:** Archivos binarios (`.dat`)
- **Entorno de desarrollo:** Visual Studio Code
- **Compilador:** g++ (MinGW en Windows / g++ en Linux)
- **Control de versiones:** Git / GitHub

---

# Estructura del Proyecto

El sistema está separado en **12 archivos `.cpp` y `.h`**, cada uno con una responsabilidad específica:

```
tienda/
├── main.cpp             → Menú principal, bienvenida y ciclo del programa
├── estructuras.h        → Structs, constantes y variables globales
├── archivos.h           → Prototipos de lectura/escritura de archivos
├── archivos.cpp         → Implementación de archivos binarios
├── productos.h          → Prototipos del Módulo 1
├── productos.cpp        → Módulo 1: Gestión de Productos
├── ventas.h             → Prototipos del Módulo 2
├── ventas.cpp           → Módulo 2: Proceso de Venta
├── reportes.h           → Prototipos del Módulo 3
├── reportes.cpp         → Módulo 3: Reportes y Ordenamientos
├── utilidades.h         → Prototipos del Módulo 4
└── utilidades.cpp       → Módulo 4: Utilidades del Sistema
```

---

# Cómo Compilar y Ejecutar

### Compilar

Abrir una terminal en la carpeta del proyecto y ejecutar:

```bash
g++ -o tienda main.cpp archivos.cpp productos.cpp ventas.cpp reportes.cpp utilidades.cpp -lm
```

### Ejecutar

```bash
# Windows:
./tienda.exe

# Linux / Mac:
./tienda
```

### Al iniciar el programa se mostrará:

```
========================================
   SISTEMA DE ADMINISTRACION DE TIENDA
========================================
  Estudiante : Moisés Abinadí Farfan González
  Carné      : 9941-25-86
  Curso      : Programación 1
========================================
```

---

# Módulos Implementados

## Módulo 1 — Gestión de Productos (`productos.cpp`)

Administra el catálogo de productos de la tienda:

- Registrar producto nuevo con validación de código único
- Listar todos los productos activos en tabla
- Buscar producto por código (búsqueda directa)
- Buscar producto por nombre (búsqueda secuencial, sin distinción de mayúsculas)
- Actualizar stock con validación de valor negativo
- Modificar precio con validación de valor positivo
- Eliminar / desactivar producto (eliminación lógica, el registro permanece en el archivo)

---

## Módulo 2 — Proceso de Venta (`ventas.cpp`)

Maneja el flujo completo de una transacción de venta:

- Crear venta con ID único y fecha del sistema
- Seleccionar múltiples productos usando `struct DetalleVenta`
- Validar stock disponible antes de agregar cada producto
- Calcular subtotal acumulado
- Aplicar IVA del 12%: `iva = base × 0.12`
- Descuento automático: **5%** si subtotal > Q500
- Bono adicional: **3%** si `totalArticulos % 5 == 0`
- Mostrar ticket con total redondeado a 2 decimales
- Confirmar venta antes de guardar
- Descontar stock automáticamente al confirmar
- Guardar venta en `ventas.dat` y actualizar `productos.dat`

---

## Módulo 3 — Reportes (`reportes.cpp`)

Genera estadísticas y listados ordenados:

- Productos con menor stock (umbral configurable)
- Top 10 productos más vendidos
- Ventas del día (filtrado por fecha `YYYY-MM-DD`)
- Ventas por mes usando la matriz `ventasPorMes[12][MAX_VENTAS]`
- Ordenar productos con **Bubble Sort** (5 criterios)
- Ordenar productos con **Selection Sort** (5 criterios)

---

## Módulo 4 — Utilidades del Sistema (`utilidades.cpp`)

- Exportar reporte completo a `reporte.txt` con fecha, inventario y ventas por mes
- Reiniciar inventario (requiere escribir `CONFIRMAR`)
- Mostrar estadísticas generales: productos activos, valor del inventario, total recaudado, promedio por venta

---

# Estructuras de Datos

## struct Producto

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

## struct DetalleVenta

```cpp
struct DetalleVenta {
    int    idProducto;      // código del producto vendido
    char   nombre[60];      // nombre al momento de la venta
    int    cantidad;        // unidades compradas
    double precioUnit;      // precio al momento de la venta
    double subtotalDet;     // cantidad × precioUnit
};
```

## struct Venta

```cpp
struct Venta {
    int          id;                    // número de venta
    char         fecha[11];             // formato "YYYY-MM-DD"
    int          mes;                   // 0=enero ... 11=diciembre
    DetalleVenta detalles[20];          // productos de la venta
    int          numDetalles;
    int          totalArticulos;
    double       subtotal;
    double       descuento;
    double       iva;
    double       total;                 // total redondeado a 2 decimales
};
```

---

# Archivos Binarios

| Archivo | Contenido |
|---|---|
| `productos.dat` | Arreglo completo de `Producto[]`. Se lee al iniciar y se reescribe en cada modificación. |
| `ventas.dat` | Arreglo completo de `Venta[]`. Se lee al iniciar y se actualiza al registrar cada venta. |
| `reporte.txt` | Archivo de texto generado por el Módulo 4 con inventario y resumen de ventas. |

---

# Modularización

El sistema cuenta con más de **25 funciones independientes**:

```cpp
// Archivos
void cargarProductos();       void guardarProductos();
void cargarVentas();          void guardarVentas();

// Módulo 1 – Productos
void menuGestionProductos();  void registrarProducto();
void listarProductos();       int  buscarPorCodigo(int cod);
int  buscarPorNombre(const char* nombre);
void actualizarStock(int, int);
void modificarPrecio(int, double);
void eliminarProducto(int);

// Módulo 2 – Ventas
void   menuProcesarVenta();   void   procesarVenta();
double calcularDescuento(double, int);
double calcularIVA(double);   double redondear(double, int);
void   actualizarMatrizMes(int);

// Módulo 3 – Reportes
void menuReportes();          void ordenarBubble(int);
void ordenarSelection(int);   void reporteMenorStock();
void reporteMasVendidos();    void reporteVentasDia();
void reporteVentasMes();

// Módulo 4 – Utilidades
void menuUtilidades();        void exportarReporte();
void reiniciarInventario();   void mostrarEstadisticas();
```

---

# Búsquedas Implementadas

| Tipo | Función | Descripción |
|---|---|---|
| Por código | `buscarPorCodigo(int cod)` | Recorre el arreglo comparando el código numérico. Retorna el índice o -1. |
| Por nombre | `buscarPorNombre(const char*)` | Búsqueda secuencial sin distinción de mayúsculas usando `strstr()`. |

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

### Bubble Sort (con optimización)

Compara elementos adyacentes e intercambia si están en el orden incorrecto. Si en una pasada completa no hubo intercambios, el arreglo ya está ordenado y el algoritmo termina anticipadamente.

```cpp
bool huboCambio;
for (int i = 0; i < totalProductos - 1; i++) {
    huboCambio = false;
    for (int j = 0; j < totalProductos - i - 1; j++) {
        if (debeCambiar(productos[j], productos[j+1], criterio)) {
            Producto temp  = productos[j];
            productos[j]   = productos[j+1];
            productos[j+1] = temp;
            huboCambio = true;
        }
    }
    if (!huboCambio) break;
}
```

### Selection Sort

Busca el elemento mínimo en la parte no ordenada y lo coloca en su posición correcta.

```cpp
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

Se implementa `try/catch` en todos los módulos con tres tipos de excepción:

| Excepción | Cuándo se usa |
|---|---|
| `invalid_argument` | Letras donde va un número, stock negativo, precio cero |
| `out_of_range` | Opción de menú fuera del rango válido |
| `runtime_error` | Error al abrir archivo, código duplicado, stock insuficiente |

---

# Cobertura de Requerimientos Técnicos

| Requerimiento | Estado | Archivo |
|---|---|---|
| `struct Producto` | ✅ | `estructuras.h` |
| `struct Venta` | ✅ | `estructuras.h` |
| `struct DetalleVenta` | ✅ | `estructuras.h` |
| `productos.dat` | ✅ | `archivos.cpp` |
| `ventas.dat` | ✅ | `archivos.cpp` |
| Mínimo 10 funciones (25+ implementadas) | ✅ | Todos los módulos |
| Búsqueda secuencial por nombre | ✅ | `productos.cpp` |
| Búsqueda por código | ✅ | `productos.cpp` |
| Bubble Sort con optimización | ✅ | `reportes.cpp` |
| Selection Sort | ✅ | `reportes.cpp` |
| Matriz `ventasPorMes[12][N]` | ✅ | `main.cpp` / `ventas.cpp` / `reportes.cpp` |
| `try/catch` en todos los módulos | ✅ | Todos los archivos |
| IVA 12% | ✅ | `ventas.cpp` |
| Descuentos automáticos (5% y 3%) | ✅ | `ventas.cpp` |
| `round()` / redondeo a 2 decimales | ✅ | `ventas.cpp` |
| Operador `%` en lógica comercial | ✅ | `ventas.cpp` |
| Separación en múltiples `.cpp` y `.h` | ✅ | 12 archivos independientes |
| Exportar reporte `.txt` | ✅ | `utilidades.cpp` |
| Nombre del estudiante visible en consola | ✅ | `main.cpp` |

---

# Cambios Realizados por Avance

## Avance 1 — Diseño y Análisis
- Algoritmo general del sistema
- Pseudocódigo de los 4 módulos
- Diagrama de flujo
- Definición de estructuras y variables

## Avance 2 — Implementación Base
- Implementación de los 4 módulos en C++
- Separación en 12 archivos `.cpp` y `.h`
- Archivos binarios `productos.dat` y `ventas.dat`
- Búsquedas, ordenamientos y matriz implementados

## Entrega Final — Sistema Completo
- Pantalla de bienvenida con nombre del estudiante y carné visible en consola
- `try/catch` mejorado con tres tipos de excepción separados (`invalid_argument`, `out_of_range`, `runtime_error`)
- Bubble Sort con optimización de parada anticipada
- Reporte de ventas por mes muestra explícitamente el uso de la matriz `ventasPorMes[12][N]`
- Reporte del día mejorado mostrando descuento, IVA y total por venta
- Función auxiliar `mostrarTablaOrdenada()` para eliminar repetición de código
- Validación de índices en la matriz de ventas por mes
- Mensaje de despedida con nombre del estudiante

---

# Estado del Proyecto

- ✅ Análisis y diseño del sistema
- ✅ Módulo 1 — Gestión de Productos
- ✅ Módulo 2 — Proceso de Venta
- ✅ Módulo 3 — Reportes y Ordenamientos
- ✅ Módulo 4 — Utilidades del Sistema
- ✅ Persistencia en archivos binarios
- ✅ Separación en múltiples archivos `.cpp` y `.h`
- ✅ Manejo de excepciones con `try/catch`
- ✅ Nombre del estudiante visible en consola
- ✅ Exportación de reportes a `.txt`
- ✅ Documentación completa

---

# Archivos del Repositorio

```
/
├── main.cpp
├── estructuras.h
├── archivos.h
├── archivos.cpp
├── productos.h
├── productos.cpp
├── ventas.h
├── ventas.cpp
├── reportes.h
├── reportes.cpp
├── utilidades.h
├── utilidades.cpp
├── productos.dat         ← archivo de prueba con productos cargados
├── ventas.dat            ← archivo de prueba con ventas registradas
├── README.md
├── documentacion.docx
└── evidencias.pdf
```

---

*Entrega Final — Sistema de Administración de Tienda en C++*
*Moisés Abinadí Farfan González  |  Carné: 9941-25-86  |  Programación 1*
