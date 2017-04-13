/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "misc.h"

int permutSymbol(int i, int j, int k)
{
    int ret = 0;

    if((i == j) or (j == k) or (k == i))
        ret = 0;
    else
    {
    if(((i == 1) and (j == 2) and (k == 3)) or ((i == 2) and (j == 3) and (k == 1)) or ((i == 3) and (j == 1) and (k == 2)))
        ret = +1;

    if(((i == 3) and (j == 2) and (k == 1)) or ((i == 1) and (j == 3) and (k == 2)) or ((i == 2) and (j == 1) and (k == 3)))
        ret = -1;
    }

    return ret;
}


double Rand(double a, double b)
{/** \brief Gera um número pseudo-aleatório no intervalo \f$ (a,b) \f$
  *  \param a Menor elemento do conjunto dos possíveis números que podem ser gerados
  *  \param b Maior elemento do conjunto dos possíveis números que podem ser gerados */
    if(b < a)
    throw except("Função Rand\nErro! O segundo parametro é menor que o primeiro.\n");

    if(b == a)
    return a;
    else
    return (b - a)*(rand() / double(RAND_MAX)) + a;
}

unsigned long long int fatorial(int a)
{
    if(a < 0)
    throw except("Função fatorial\nErro! Nao existe fatorial de numero negativo.\n");

    if(a > 20)
    throw except("Função fatorial\nErro! Memoria incompativel.\n");

    unsigned long long int ret = 1.0;

    if((a == 0) or (a == 1))
    {
        return ret;
    }
    else
    {
        for(int i = 2; i <= a; i++)
            ret = i*ret;
    }

    return ret;
}

int binomial(int n, int k)
{
    return fatorial(n)/(fatorial(k)*fatorial(n - k));
}

double pertTriang(double &x, double a, double b, double c)
{
    double ret;

    if((x <= a) or (c <= x))
        ret = 0.0;
    else if((a <= x) and (x <= b))
        ret = (x - a)/(b - a);
    else if((b <= x) and (x <= c))
        ret = (c - x)/(c - b);

    return ret;
}

double pertTrapez(double &x, double a, double b, double c, double d)
{
    double ret;

    if(c == b)
        ret = pertTriang(x, a,b,d);
    else
    {
        if((x <= a) or (d <= x))
            ret = 0.0;
        if((a <= x) and (x <= b))
            ret = (x - a)/(b - a);
        if((b <= x) and (x <= c))
            ret = 1.0;
        if((c <= x) and (x <= d))
            ret = (d - x)/(d - c);
    }

    return ret;
}

double sat(double x)
{
    return (fabs(x) < 1.0 ? x : sgn(x));
}

double sgn(double x)
{
    return ( x < 0.0 ? -1.0 : 1.0);
}
