//---------------------------------------------------------------------------

#pragma hdrstop

#include <Vcl.Grids.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include "matriz.h"
#include "cadena.h"
#include "numero.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/*
1) Cargar matriz Randomicamente (m x n)
	- - -
	- - -
	- - -
*/
void cargar_columna_random(TStringGrid* v, byte c, byte n)
{
    if (n == 0) {
        // nada
    } else {
        cargar_columna_random(v, c, n - 1);
        v->Cells[c][n - 1] = Random(10) + 1;
    }
}

void cargar_random(TStringGrid* v, byte m, byte n)
{
    if (n == 0) {
        // nada
    } else {
        cargar_columna_random(v, n - 1, m);
        cargar_random(v, m, n - 1);
    }
}

/*
2) Cargar matriz por filas (m x n)
	1 2 3
	4 5 6
	7 8 9
*/
void cargar_fila(TStringGrid* v, byte f, byte n)
{
    if (n == 0) {
        // nada
    } else if (n == 1) {
        v->Cells[0][f] = f * v->ColCount + 1;
    } else {
        cargar_fila(v, f, n - 1);
        v->Cells[n - 1][f] = StrToInt(v->Cells[n - 2][f]) + 1;
    }
}

void cargar_por_filas(TStringGrid* v, byte m, byte n)
{
    if (m == 0) {
        // nada
    } else {
        cargar_por_filas(v, m - 1, n);
        cargar_fila(v, m - 1, n);
    }
}

/*
3) Cargar matriz por columnas (m x n)
	1 4 7
	2 5 8
	3 6 9
*/
void cargar_columna(TStringGrid* v, byte c, byte n)
{
    if (n == 0) {
        // nada
    } else if (n == 1) {
        v->Cells[c][0] = c * v->RowCount + 1;
    } else {
        cargar_columna(v, c, n - 1);
        v->Cells[c][n - 1] = StrToInt(v->Cells[c][n - 2]) + 1;
    }
}

void cargar_por_columnas(TStringGrid* v, byte m, byte n)
{
    if (n == 0) {
        // nada
    } else {
        cargar_por_columnas(v, m, n - 1);
        cargar_columna(v, n - 1, m);
    }
}

/*
4) Ordenar Las Filas Ascendentemente
	5 2 1 5    1 2 5 5
	9 2 2 1 -> 1 2 2 9
	1 3 8 2    1 2 3 8

*/
void mover_el_numero_mayor_al_final_de_la_columna(
    TStringGrid* v, byte m, byte n)
{
    if (n == 0) {
        // nada
    } else if (n == 1) {
        // nada
    } else {
        mover_el_numero_mayor_al_final_de_la_columna(v, m, n - 1);
        if (StrToInt(v->Cells[n - 2][m]) > StrToInt(v->Cells[n - 1][m])) {
            String temp = v->Cells[n - 2][m];
            v->Cells[n - 2][m] = v->Cells[n - 1][m];
            v->Cells[n - 1][m] = temp;
        }
    }
}

void ordenar_fila_burbuja_ascedente(TStringGrid* v, byte m, byte n)
{
    if (n == 0) {
        // nada
    } else if (n == 1) {
        // nada
    } else {
        mover_el_numero_mayor_al_final_de_la_columna(v, m, n);
        ordenar_fila_burbuja_ascedente(v, m, n - 1);
    }
}

void ordenar_filas_burbuja_ascedente(TStringGrid* v, byte m, byte n)
{
    if (n == 0) {
        // nada
    } else {
        ordenar_filas_burbuja_ascedente(v, m, n - 1);
        ordenar_fila_burbuja_ascedente(v, n - 1, m);
    }
}
/*
5) Cargar matriz triangular inferior izquierda (m x m) m = 5 , n = 5
	1
	2  3
	4  5  6
	7  8  9  10
*/

void cargar_fila_triangular_inferior_izquierda(TStringGrid* v, byte f, byte n)
{
    if (n == 0) {
        // nada
    } else if (n == 1) { // averiguar cual es la formula
        v->Cells[0][f] = 1;
    } else {
        cargar_fila_triangular_inferior_izquierda(v, f, n - 1);
        v->Cells[n - 1][f] = StrToInt(v->Cells[n - 2][f]) + 1;
    }
}
void cargar_triangular_inferior_izquierda(TStringGrid* v, byte m, byte n)
{
    if (m == 0) {
        // nada
    } else {
        cargar_fila_triangular_inferior_izquierda(v, m - 1, n);
        cargar_triangular_inferior_izquierda(v, m - 1, n - 1);
    }
}

/*
6)  Cargar matriz L invertida (mxm)
	1 2 3 4
	2 2 3 4
	3 3 3 4
	4 4 4 4
*/

void llenar_L(TStringGrid* v, byte f, byte n)
{
    if (n == 0) {
        // nada
    } else {
        llenar_L(v, f, n - 1);
        v->Cells[n - 1][f] = f + 1;
        v->Cells[f][n - 1] = f + 1;
    }
}

void cargar_L(TStringGrid* v, byte m)
{
    if (m == 0) {
        // nada
    } else {
        cargar_L(v, m - 1);
        llenar_L(v, m - 1, m);
    }
}

/*
7)  Cargar matriz circular (mxm)

	3 3 3 3 3
	3 2 2 2 3
	3 3 1 2 3    <- 1
	3 2 2 2 3
	3 3 3 3 3

	3 3 3 3 3 3
	3 2 2 2 2 3
	3 2 1 1 2 3
	3 2 1 1 2 3  <- 2
	3 2 2 2 2 3
	3 3 3 3 3 3
*/

void llenar_circulo(TStringGrid* v, byte fa, byte fb, byte a, byte n, byte z)
{
    if (n == 0) {
        // nada
    } else {
        llenar_circulo(v, fa, fb, a, n - 1, z);
        v->Cells[n + a - 1][fb] = z;
        v->Cells[fb][n + a - 1] = z;
        v->Cells[n + a - 1][fa] = z;
        v->Cells[fa][n + a - 1] = z;
    }
}

void cargar_circular(TStringGrid* v, byte fa, byte fb)
{
    byte m = fb - fa + 1;
    if (m == 0) {
        // nada
    } else if (m == 1) {
        v->Cells[fb][fb] = 1;
    } else {
        cargar_circular(v, fa + 1, fb - 1);
        llenar_circulo(v, fa, fb, fa, m, (m + 1) / 2);
    }
}

/*
8)  Cargar cuadrado magico (mxm)
	17 24  1  3  15
	23  5  7 14  16
	 4  6 13 20  22    , m = 5
	10 12 19 21  3
	11 18 25  2  9
*/

void cargar_magico(TStringGrid* v, byte m, byte z, byte &f, byte &c)
{
    if (m % 2 == 0 || z == 0) {
        throw new Exception("La fila o la columna no debe ser par");
    } else if (z == 1) {
        f = 0;
        c = m / 2;
        v->Cells[c][f] = 1;
    } else {
        cargar_magico(v, m, z - 1, f, c);
        if ((z - 1) % m == 0) { // r2
            f++;
        } else { // r1
            c = (c + 1) % m;
            if (f == 0) {
                f = m - 1;
            } else {
                f--;
            }
        }
        v->Cells[c][f] = z;
    }
}

