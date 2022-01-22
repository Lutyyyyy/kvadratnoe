#include <TXlib.h>
#include <stdio.h>
#include <math.h>
//#include <assert.h>



//=============================================================================
//=============================================================================

const double Precision = 1e-5;

//-----------------------------------------------------------------------------

bool is_zero (double value);


//{----------------------------------------------------------------------------
//! Эта функция вычисляет количество решений квадратного уравнения, а также численные значения этих решений
//!
//! @param[in]  a - коэффициент при старшем члене квадратного трехчлена
//! @param[in]  b - коэффициент при среднем члене квадратного трехчлена
//! @param[in]  c - коэффициент при свободног члене квадратного трехчлена
//! @param[out] x1 - меньший (или единственнный в случае линейности уравнения) корень уравнения
//! @param[out] x2 - больший корень уравнения
//!
//!  @return    Количество решения квадратного трехчлена
//}----------------------------------------------------------------------------

int Solve_Square (double a, double b, double c, double* x1, double* x2);


int is_Equal (double value1, double value2);
void Print_Roots (int Number_of_Roots, double* x1, double* x2);
void Clear_Buffer ();
void Input_Numbers (double* a, double* b, double* c);
int Unit_Test (int number, double a, double b, double c, double ref_x1, double ref_x2, int ref_nRoots);
int Unit_Test_Fails ();

//-----------------------------------------------------------------------------



//=============================================================================
//=============================================================================


//-----------------------------------------------------------------------------

bool is_zero (double value)
    {
    return (fabs (value) < Precision);
    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int Solve_Square (double a, double b, double c, double* x1, double* x2)
    {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (is_zero (a))
        {
        if (is_zero (b))
            {
            return (is_zero (c)) ? 3 : 0;
            }

        *x1 = -c / b;
        return 1;
        }
    else
        {
        double D = b * b - 4 * a * c;

        if (is_zero (D))
            {
            *x1 = -b / (2 * a);
            return 1;
            }
        else if (D < 0)
            return 0;
        else
            {
            double sqrt_D = sqrt (D);

            *x1 = (-b - sqrt_D) / (2 * a);
            *x2 = (-b + sqrt_D) / (2 * a);

            return 2;
            }
        }
    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int is_Equal (double value1, double value2)
    {
    double difference = fabs (value1) - fabs (value2);
    return (fabs (difference) < Precision);
    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void Print_Roots (int Number_of_Roots, double* x1, double* x2)
    {
    switch (Number_of_Roots)
        {
        case 0:
            printf ("\nNo solutions\n\n");
            break;

        case 1:
            printf ("\nx1 = x2 = x = %lg\n\n", *x1);
            break;

        case 2:
            printf ("\nx1 = %f\nx2 = %lg\n\n", *x1, *x2);
            break;

        case 3:
            printf ("\nAny number\n\n");
            break;

        default:
            printf ("\nError");
            break;
        }

    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void Clear_Buffer ()
    {
    while (getchar() != '\n')
        {
        ;
        }
    }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void Input_Numbers (double* a, double* b, double* c)
    {
    bool OK = false;

    while (OK == false)
        {
        int nInput_Numbers = scanf ("%lg %lg %lg", a, b, c);

        if (nInput_Numbers < 3)
            {
            printf ("Please, enter numbers:\n");
            Clear_Buffer ();
            }
        else
            OK = true;
        }
    }

//-----------------------------------------------------------------------------

int Unit_Test_Fails ()
{
    int fails = 0;
    fails += Unit_Test (1, 1, -9, 8, 1, 7, 1);
    fails += Unit_Test (2, 1, -5, 4, 1, 4, 2);
    return fails;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int Unit_Test (int number, double a, double b, double c, double ref_x1, double ref_x2, int ref_nRoots)
    {
    double x1 = NAN, x2 = NAN;

    int Roots = Solve_Square (a, b, c, &x1, &x2);

    int nRoots_mistake = (Roots == ref_nRoots) ? 0 : 1;
    if (nRoots_mistake)
        printf("Test #%d failed: Should be %d Root(s)\n" "Computed %d Root(s)\n", number, ref_nRoots, Roots);

    int mistake = (!(((x1 == ref_x1 && x2 == ref_x2) || (x1 == ref_x2 && x2 == ref_x1)))) ? 1 : 0;
    if (mistake)
        printf("Test #%d failed: Should be %lg, %lg\n" "Computed %lg, %lg\n", number, x1, x2, ref_x1, ref_x2);

    return mistake;
    }

//-----------------------------------------------------------------------------



//=============================================================================

int main ()
    {
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    int fails = Unit_Test_Fails();
    printf("%d", fails);

    printf ("\nEnter a, b and c:\n");
    Input_Numbers (&a, &b, &c);

    int nRoots = Solve_Square (a, b, c, 0, 0);
    Print_Roots (nRoots, &x1, &x2);

    return 0;
    }

//=============================================================================

