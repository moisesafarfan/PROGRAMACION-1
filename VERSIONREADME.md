# Sistema de Administración de Tienda en C++
## Avance 1 – Diseño y Análisis del Sistema

---

# Descripción del Proyecto

El presente proyecto consiste en el desarrollo de un sistema de consola en C++ orientado a la administración de una tienda. El sistema permitirá gestionar productos, controlar stock, registrar ventas y generar reportes estadísticos mediante el uso de archivos binarios y programación estructurada.

El programa funciona en un ciclo continuo: el usuario elige una opción del menú principal → el módulo correspondiente se ejecuta → los cambios se guardan en disco → el sistema regresa al menú. Este ciclo se repite hasta que el usuario decide salir.

Toda la información se persiste en archivos binarios (`productos.dat` y `ventas.dat`) para que los datos no se pierdan al cerrar el programa.

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



## Diagrama de Flujo del Sistema

![Diagrama de Flujo](assets/diagrama_flujo_sistema_tienda.svg)

---


# Objetivo General

Desarrollar un sistema de consola en C++ que permita administrar productos, ventas e inventario mediante archivos binarios, aplicando programación estructurada, modularización, búsqueda, ordenamiento, validación de datos y manejo de excepciones.

---

# Objetivos Específicos

- Registrar, listar, buscar, modificar y desactivar productos de la tienda.
- Registrar ventas con múltiples productos seleccionados por el usuario.
- Validar el stock disponible antes de confirmar cada venta.
- Calcular subtotales, aplicar IVA (12%) y descuentos automáticos por monto o cantidad.
- Generar reportes de productos con menor stock, más vendidos y ventas por mes.
- Ordenar productos usando Bubble Sort y Selection Sort según distintos criterios.
- Implementar búsqueda secuencial por nombre y búsqueda directa por código.
- Utilizar una matriz `ventasPorMes[12][N]` para estadísticas mensuales.
- Exportar reportes a un archivo `.txt`.
- Aplicar manejo de excepciones con `try/catch` en entradas y operaciones de archivos.


---

# Estructura General del Sistema

El sistema está dividido en cuatro módulos principales, cada uno con funciones independientes:

## Módulo 1 – Gestión de Productos

Permite administrar el catálogo de productos de la tienda:

- Registrar productos nuevos
- Listar todos los productos activos
- Buscar producto por código (numérico)
- Buscar producto por nombre (búsqueda secuencial)
- Actualizar stock
- Modificar precio
- Eliminar / desactivar producto (eliminación lógica)

---

## Módulo 2 – Proceso de Venta

Maneja el flujo completo de una transacción de venta:

- Crear una venta nueva con ID único y fecha del sistema
- Seleccionar múltiples productos por venta
- Validar stock disponible antes de agregar cada producto
- Calcular subtotal acumulado
- Aplicar IVA del 12%
- Aplicar descuento automático:
  - Si subtotal > Q500 → 5% de descuento
  - Si cantidad total de artículos % 5 == 0 → 3% de bono adicional
- Mostrar ticket con total redondeado a 2 decimales
- Guardar la venta en `ventas.dat`
- Descontar stock automáticamente en `productos.dat`

---

## Módulo 3 – Reportes

Genera estadísticas y listados ordenados del sistema:

- Productos con menor stock (por debajo de un umbral)
- Productos más vendidos (por `totalVendido` acumulado)
- Ventas totales del día (filtrado por fecha)
- Ventas por mes usando la matriz `ventasPorMes[12][MAX_VENTAS]`
- Ordenar productos por precio ascendente / descendente
- Ordenar productos por stock ascendente / descendente
- Ordenar productos por ventas acumuladas

---

## Módulo 4 – Utilidades del Sistema

Funciones de mantenimiento y administración general:

- Exportar reporte completo a archivo `.txt`
- Reiniciar inventario (requiere confirmación escribiendo "CONFIRMAR")
- Mostrar estadísticas generales del sistema

---

# Estructuras Principales

## Struct Producto

Representa cada artículo registrado en la tienda.

```cpp
struct Producto {
    int    codigo;           // identificador único
    char   nombre[60];       // nombre del producto
    char   categoria[30];    // ej: "Electrónica", "Ropa"
    double precio;           // precio unitario en quetzales
    int    stock;            // unidades disponibles
    int    totalVendido;     // acumulado de unidades vendidas (para reportes)
    bool   activo;           // false = eliminado lógicamente
};
```

---

## Struct DetalleVenta

Representa una línea dentro de una venta (un producto comprado).

```cpp
struct DetalleVenta {
    int    idProducto;       // código del producto vendido
    char   nombre[60];       // copia del nombre al momento de la venta
    int    cantidad;         // unidades compradas en esta línea
    double precioUnit;       // precio al momento de la venta
    double subtotalDet;      // cantidad × precioUnit
};
```

---

## Struct Venta

Representa una transacción de venta completa.

```cpp
struct Venta {
    int          id;                    // número de venta
    char         fecha[11];             // formato "YYYY-MM-DD"
    int          mes;                   // 0 = enero ... 11 = diciembre
    DetalleVenta detalles[20];          // productos incluidos en la venta
    int          numDetalles;           // cuántos productos tiene la venta
    int          totalArticulos;        // suma total de unidades compradas
    double       subtotal;              // suma antes de descuentos
    double       descuento;             // monto de descuento aplicado
    double       iva;                   // monto de IVA (12%)
    double       total;                 // total final redondeado a 2 decimales
};
```

---

# Archivos Binarios

El sistema utilizará los siguientes archivos para persistir los datos:

```
productos.dat   →  almacena el arreglo de struct Producto
ventas.dat      →  almacena el arreglo de struct Venta
reporte.txt     →  archivo de exportación generado por el Módulo 4
```

Estos archivos se leen al iniciar el programa y se actualizan cada vez que se realiza una operación de escritura.

---

# Modularización

El sistema se divide en un mínimo de 10 funciones independientes. Cada función tiene una responsabilidad única y clara.

## Funciones propuestas

```cpp
// Archivos
void cargarProductos();
void guardarProductos();
void cargarVentas();
void guardarVentas();

// Módulo 1 – Productos
void menuGestionProductos();
void registrarProducto();
void listarProductos();
int  buscarPorCodigo(int cod);
int  buscarPorNombre(const char* nombre);
void actualizarStock(int cod, int nuevoStock);
void modificarPrecio(int cod, double nuevoPrecio);
void eliminarProducto(int cod);

// Módulo 2 – Ventas
void   menuProcesarVenta();
void   procesarVenta();
double calcularDescuento(double subtotal, int totalArticulos);
double calcularIVA(double base);
double redondear(double valor, int decimales);
void   actualizarMatrizMes(const Venta& v);

// Módulo 3 – Reportes
void menuReportes();
void ordenarBubble(int criterio);
void ordenarSelection(int criterio);
void reporteMenorStock(int umbral);
void reporteMasVendidos();
void reporteVentasDia(const char* fecha);
void reporteVentasMes();

// Módulo 4 – Utilidades
void menuUtilidades();
void exportarReporte();
void reiniciarInventario();
void mostrarEstadisticas();
```

---

# Pseudocódigo

## Programa Principal

```
INICIO del programa
  cargarProductos()          ← leer productos.dat
  cargarVentas()             ← leer ventas.dat
  opcion ← 0

  MIENTRAS opcion != 5 HACER
    MOSTRAR menú principal
    INTENTAR
      LEER opcion
      SI opcion < 1 O opcion > 5 ENTONCES
        LANZAR error "Opción inválida"
      FIN SI
    ATRAPAR error
      MOSTRAR "Error: ingrese un número del 1 al 5"
      CONTINUAR al siguiente ciclo
    FIN INTENTAR

    SEGÚN opcion HACER
      1: menuGestionProductos()
      2: menuProcesarVenta()
      3: menuReportes()
      4: menuUtilidades()
      5: MOSTRAR "Hasta luego"
    FIN SEGÚN
  FIN MIENTRAS
FIN del programa
```

---

## Pseudocódigo – Módulo 1: Gestión de Productos

### Registrar producto

```
INICIO registrarProducto
  INTENTAR
    LEER codigo, nombre, categoria, precio, stock
    SI precio <= 0 O stock < 0 ENTONCES
      LANZAR error "Datos inválidos"
    FIN SI
    SI buscarPorCodigo(codigo) != -1 ENTONCES
      MOSTRAR "Código ya existe"
      RETORNAR
    FIN SI
    Crear producto con los datos leídos
    producto.activo       ← VERDADERO
    producto.totalVendido ← 0
    Agregar al arreglo productos[]
    guardarProductos()
    MOSTRAR "Producto registrado con éxito"
  ATRAPAR error
    MOSTRAR "Error al registrar: " + mensaje
  FIN INTENTAR
FIN registrarProducto
```

### Buscar por nombre (búsqueda secuencial)

```
INICIO buscarPorNombre(nombre)
  PARA i ← 0 HASTA totalProductos - 1 HACER
    SI productos[i].nombre CONTIENE nombre
       Y productos[i].activo ENTONCES
      RETORNAR i         ← posición encontrada
    FIN SI
  FIN PARA
  RETORNAR -1            ← no encontrado
FIN buscarPorNombre
```

### Buscar por código

```
INICIO buscarPorCodigo(cod)
  PARA i ← 0 HASTA totalProductos - 1 HACER
    SI productos[i].codigo == cod
       Y productos[i].activo ENTONCES
      RETORNAR i
    FIN SI
  FIN PARA
  RETORNAR -1
FIN buscarPorCodigo
```

### Eliminar / desactivar producto

```
INICIO eliminarProducto(cod)
  idx ← buscarPorCodigo(cod)
  SI idx == -1 ENTONCES
    MOSTRAR "Producto no encontrado"
    RETORNAR
  FIN SI
  productos[idx].activo ← FALSO    ← no se borra, solo se oculta
  guardarProductos()
  MOSTRAR "Producto desactivado correctamente"
FIN eliminarProducto
```

---

## Pseudocódigo – Módulo 2: Proceso de Venta

```
INICIO procesarVenta
  Crear nuevaVenta con id único y fecha de hoy
  subtotal       ← 0.0
  totalArticulos ← 0

  MIENTRAS usuario quiera agregar productos HACER
    INTENTAR
      LEER codigoProducto, cantidad
      idx ← buscarPorCodigo(codigoProducto)
      SI idx == -1 ENTONCES
        MOSTRAR "Producto no encontrado"
        CONTINUAR
      FIN SI
      SI productos[idx].stock < cantidad ENTONCES
        MOSTRAR "Stock insuficiente (disponible: X)"
        CONTINUAR
      FIN SI
      Agregar detalle a nuevaVenta.detalles[]
      subtotal       ← subtotal + cantidad × precio
      totalArticulos ← totalArticulos + cantidad
      LEER "¿Agregar otro producto? (s/n)"
    ATRAPAR error
      MOSTRAR "Error en entrada"
    FIN INTENTAR
  FIN MIENTRAS

  // Calcular descuentos
  descuento ← 0.0
  SI subtotal > 500 ENTONCES
    descuento ← subtotal × 0.05        ← 5%
  FIN SI
  SI totalArticulos % 5 == 0 ENTONCES
    descuento ← descuento + subtotal × 0.03   ← bono 3%
  FIN SI

  baseIVA ← subtotal - descuento
  iva     ← baseIVA × 0.12
  total   ← redondear(baseIVA + iva, 2)

  MOSTRAR ticket con subtotal, descuento, IVA, total

  // Descontar stock y actualizar contadores
  PARA cada detalle en nuevaVenta HACER
    idx ← buscarPorCodigo(detalle.idProducto)
    productos[idx].stock        ← productos[idx].stock - detalle.cantidad
    productos[idx].totalVendido ← productos[idx].totalVendido + detalle.cantidad
  FIN PARA

  guardarVentas()
  guardarProductos()
  actualizarMatrizMes(nuevaVenta)
FIN procesarVenta
```

---

## Pseudocódigo – Módulo 3: Reportes

### Ordenamiento Bubble Sort

```
INICIO ordenarBubble(criterio)
  PARA i ← 0 HASTA totalProductos - 2 HACER
    PARA j ← 0 HASTA totalProductos - i - 2 HACER
      SI productos[j] y productos[j+1] están en orden incorrecto ENTONCES
        temp           ← productos[j]
        productos[j]   ← productos[j+1]
        productos[j+1] ← temp
      FIN SI
    FIN PARA
  FIN PARA
FIN ordenarBubble
```

### Ordenamiento Selection Sort

```
INICIO ordenarSelection(criterio)
  PARA i ← 0 HASTA totalProductos - 2 HACER
    minIdx ← i
    PARA j ← i+1 HASTA totalProductos - 1 HACER
      SI productos[j] es menor que productos[minIdx] ENTONCES
        minIdx ← j
      FIN SI
    FIN PARA
    SI minIdx != i ENTONCES
      Intercambiar productos[i] con productos[minIdx]
    FIN SI
  FIN PARA
FIN ordenarSelection
```

### Reporte de ventas por mes (usando la matriz)

```
INICIO reporteVentasMes
  PARA mes ← 0 HASTA 11 HACER
    totalMes ← 0.0
    PARA i ← 0 HASTA conteoVentasMes[mes] - 1 HACER
      totalMes ← totalMes + ventas[ ventasPorMes[mes][i] ].total
    FIN PARA
    MOSTRAR nombreMes(mes) + ": Q" + totalMes
  FIN PARA
FIN reporteVentasMes
```

---

## Pseudocódigo – Módulo 4: Utilidades

### Exportar reporte

```
INICIO exportarReporte
  INTENTAR
    Abrir reporte.txt para escritura
    SI error al abrir ENTONCES
      LANZAR error "No se pudo crear reporte.txt"
    FIN SI
    Escribir encabezado con fecha y hora
    Escribir listado de productos activos
    Escribir resumen de ventas totales
    Cerrar archivo
    MOSTRAR "Reporte exportado correctamente"
  ATRAPAR error
    MOSTRAR "Error de archivo: " + mensaje
  FIN INTENTAR
FIN exportarReporte
```

### Reiniciar inventario

```
INICIO reiniciarInventario
  MOSTRAR "Esta acción pondrá todos los stocks en 0. Escriba CONFIRMAR para continuar"
  LEER confirmacion
  SI confirmacion == "CONFIRMAR" ENTONCES
    PARA i ← 0 HASTA totalProductos - 1 HACER
      productos[i].stock ← 0
    FIN PARA
    guardarProductos()
    MOSTRAR "Inventario reiniciado"
  SINO
    MOSTRAR "Operación cancelada"
  FIN SI
FIN reiniciarInventario
```

---

# Búsquedas y Ordenamientos

## Búsquedas

| Tipo | Descripción | Módulo |
|---|---|---|
| Secuencial por nombre | Recorre el arreglo comparando el nombre uno por uno hasta encontrar coincidencia | Módulo 1 y 3 |
| Directa por código | Recorre el arreglo comparando el código numérico del producto | Módulo 1 |

## Ordenamientos

| Algoritmo | Criterios disponibles | Módulo |
|---|---|---|
| Bubble Sort | Precio asc/desc, stock asc/desc, ventas acumuladas | Módulo 3 |
| Selection Sort | Precio asc/desc, stock asc/desc, ventas acumuladas | Módulo 3 |

---

# Uso de Matrices

Se utilizará una matriz para almacenar estadísticas de ventas mensuales:

```cpp
int ventasPorMes[12][MAX_VENTAS];   // guarda IDs de ventas por mes
int conteoVentasMes[12] = {0};      // cuántas ventas hay en cada mes
```

Cada fila representa un mes (0 = enero, 11 = diciembre). Al registrar una venta, se guarda su ID en la fila del mes correspondiente. Para generar el reporte mensual, se suman los totales de todas las ventas de cada fila.

---

# Manejo de Excepciones

El sistema implementará `try/catch` en los siguientes casos:

| Situación | Qué se atrapa |
|---|---|
| El usuario escribe letras donde debe ir un número | `invalid_argument` o fallo de `cin` |
| Se intenta abrir un archivo que no existe o está bloqueado | Excepción de archivo |
| Stock negativo o precio igual a cero | Excepción lanzada manualmente |
| Opción de menú fuera del rango válido | `out_of_range` lanzado manualmente |

---

# Cobertura de Requerimientos Técnicos

| Requerimiento | Cómo se cumple | Módulo |
|---|---|---|
| `struct Producto` | Declarado con 7 campos incluyendo `activo` y `totalVendido` | Módulo 1 |
| `struct Venta` | Declarado con arreglo de `DetalleVenta` y todos los totales | Módulo 2 |
| `struct DetalleVenta` | Sub-estructura dentro de Venta con precio y subtotal por línea | Módulo 2 |
| `productos.dat` | Lectura y escritura del arreglo `Producto[]` en binario | Módulo 1 |
| `ventas.dat` | Lectura y escritura del arreglo `Venta[]` en binario | Módulo 2 |
| Mínimo 10 funciones | 25+ funciones declaradas, cada una con responsabilidad única | Todos |
| Búsqueda secuencial por nombre | `buscarPorNombre()` recorre el arreglo posición por posición | Módulo 1+3 |
| Búsqueda por código | `buscarPorCodigo()` compara el campo código en cada posición | Módulo 1 |
| Bubble Sort | `ordenarBubble(criterio)` con 5 criterios de ordenamiento | Módulo 3 |
| Selection Sort | `ordenarSelection(criterio)` como segundo algoritmo | Módulo 3 |
| Matriz `ventasPorMes` | `int ventasPorMes[12][MAX_VENTAS]` declarada globalmente | Módulo 3 |
| `try/catch` | En menú principal, registro, venta y exportación de archivos | Todos |
| IVA 12% | `iva = base × 0.12` dentro de `calcularIVA()` | Módulo 2 |
| Descuentos automáticos | 5% si subtotal > Q500, 3% si `totalArticulos % 5 == 0` | Módulo 2 |
| `round()` / redondeo | Función `redondear(valor, decimales)` aplicada al total final | Módulo 2 |
| Operador `%` en lógica comercial | `totalArticulos % 5 == 0` para aplicar bono de descuento | Módulo 2 |

---

# Estado Actual del Proyecto

El proyecto se encuentra actualmente en la fase de:

- Análisis de requerimientos
- Diseño lógico del sistema
- Planificación modular
- Diseño de estructuras de datos (`struct`)
- Elaboración de pseudocódigo por módulo
- Definición de variables globales y constantes

---

# Próximo Avance

En el Avance 2 se implementará:

El Avance 2 contendrá la implementación completa de todas las funciones.

---

*Avance 1 — Diseño y Análisis del Sistema*
Curso: Programación 1
Nombre del alumno: Moisés Abinadí Farfan González
9941 - 25 - 86
