# Sistema de Gestión de Ventas e Inventario para Tienda

## Avance 1 – Diseño y Análisis del Sistema

---

# Descripción del Proyecto

El presente proyecto consiste en el desarrollo de un sistema de consola en C++ orientado a la administración de ventas e inventario para una tienda.

El sistema permitirá gestionar productos, controlar stock, registrar ventas y generar reportes estadísticos mediante el uso de archivos binarios, programación estructurada y modularización.

Además, se implementarán validaciones, búsquedas, ordenamientos y manejo de excepciones para mejorar la integridad y organización del sistema.

---

# Objetivo General

Desarrollar un sistema de gestión de ventas e inventario en C++ que permita administrar productos y ventas utilizando archivos binarios, modularización y estructuras de programación.

---

# Objetivos Específicos

- Registrar productos.
- Buscar productos por código y nombre.
- Actualizar stock y modificar precios.
- Registrar ventas con múltiples productos.
- Validar stock disponible.
- Aplicar IVA y descuentos automáticos.
- Generar reportes estadísticos.
- Exportar reportes a archivos `.txt`.
- Implementar búsqueda y ordenamiento.
- Aplicar manejo de excepciones mediante `try/catch`.

---

# Tecnologías Utilizadas

- Lenguaje: C++
- Paradigma: Programación estructurada
- Persistencia de datos: Archivos binarios
- Entorno de desarrollo: Visual Studio Code
- Control de versiones: Git / GitHub

---

# Estructura General del Sistema

El sistema estará dividido en los siguientes módulos:

## Módulo 1 – Gestión de Productos

Permitirá:

- Registrar productos
- Listar productos
- Buscar productos
- Actualizar stock
- Modificar precios
- Desactivar productos

---

## Módulo 2 – Proceso de Venta

Permitirá:

- Crear ventas
- Seleccionar múltiples productos
- Validar stock
- Calcular subtotal
- Aplicar IVA
- Aplicar descuentos
- Guardar ventas
- Descontar stock automáticamente

---

## Módulo 3 – Reportes

Permitirá:

- Mostrar productos con menor stock
- Mostrar productos más vendidos
- Mostrar ventas del día
- Mostrar ventas por mes
- Ordenar productos

---

## Módulo 4 – Utilidades

Permitirá:

- Exportar reportes a `.txt`
- Reiniciar inventario
- Mostrar estadísticas generales

---

# Estructuras Principales

## Struct Producto

```cpp
struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    int ventasAcumuladas;
    bool activo;
};
```

---

## Struct DetalleVenta

```cpp
struct DetalleVenta {
    int codigoProducto;
    char nombreProducto[50];
    int cantidad;
    float precioUnitario;
    float subtotal;
};
```

---

## Struct Venta

```cpp
struct Venta {
    int codigoVenta;
    DetalleVenta detalles[20];
    int cantidadDetalles;
    float subtotal;
    float iva;
    float descuento;
    float total;
    int dia;
    int mes;
    int anio;
};
```

---

# Archivos Binarios

El sistema utilizará los siguientes archivos binarios:

```text
productos.dat
ventas.dat
```

Estos archivos permitirán almacenar información de forma permanente.

---

# Modularización

El sistema será dividido en múltiples funciones para mejorar organización, mantenimiento y reutilización de código.

## Funciones propuestas

```cpp
menuPrincipal()
registrarProducto()
listarProductos()
buscarProductoPorCodigo()
buscarProductoPorNombre()
actualizarStock()
modificarPrecio()
desactivarProducto()
crearVenta()
validarStock()
calcularVenta()
guardarVenta()
generarReportes()
ordenarProductos()
exportarReporteTxt()
```

---

# Diseño Lógico General

```text
Inicio
   ↓
Menú principal
   ↓
Gestión de productos
   ↓
Proceso de ventas
   ↓
Reportes
   ↓
Utilidades
   ↓
Salir
   ↓
Fin
```

---

# Pseudocódigo – Registro de Producto

```text
Inicio registrarProducto

Solicitar código
Solicitar nombre
Solicitar precio
Solicitar stock

Validar datos

Si los datos son válidos Entonces
    Guardar producto
Sino
    Mostrar error
Fin Si

Fin registrarProducto
```

---

# Pseudocódigo – Proceso de Venta

```text
Inicio crearVenta

subtotal = 0

Repetir

    Solicitar código de producto

    Buscar producto

    Si existe Entonces

        Solicitar cantidad

        Si stock suficiente Entonces
            Agregar producto a la venta
            Descontar stock
            Actualizar subtotal
        Sino
            Mostrar "Stock insuficiente"
        Fin Si

    Sino
        Mostrar "Producto no encontrado"
    Fin Si

Hasta que usuario termine

Aplicar IVA
Aplicar descuentos
Calcular total
Guardar venta

Fin crearVenta
```

---

# Búsquedas y Ordenamientos

## Búsquedas

- Búsqueda secuencial por nombre
- Búsqueda por código

---

## Ordenamientos

Se implementarán algoritmos como:

- Bubble Sort
- Selection Sort

---

# Uso de Matrices

Se utilizará una matriz para almacenar estadísticas de ventas mensuales.

```cpp
float ventasPorMes[12][31];
```

---

# Manejo de Excepciones

El sistema implementará `try/catch` para:

- validación de entradas,
- manejo de errores de archivos,
- control de conversiones inválidas.

---

# Estado Actual del Proyecto

Actualmente el proyecto se encuentra en fase de:

- análisis,
- diseño lógico,
- planificación modular,
- diseño de estructuras,
- elaboración de pseudocódigo.

---

# Próximo Avance

En el siguiente avance se implementará:

- menú funcional,
- registro real de productos,
- archivos binarios,
- búsquedas,
- validaciones,
- proceso básico de ventas.

---

# Autor

Proyecto académico – Programación en C++
