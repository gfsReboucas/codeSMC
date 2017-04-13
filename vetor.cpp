/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "vetor.h"

/// Construtores:
/// construtor padrão
vetor::vetor()
{
    dimensao = 1;
    v = new double[dimensao];

    for(int i = 0; i < dimensao; i++)
        v[i] = 0.0;
}

/// construtor do tamanho. O explicit serve pra prevenir a conversão automática
vetor::vetor(int d)
{
    dimensao = d;
    v = new double[dimensao];

    for(int i = 0; i < dimensao; i++)
        v[i] = 0.0;
}

/// construtor a partir de um array-C
vetor::vetor(const double *w, int d)
{
    dimensao = d;
    v = new double[dimensao];

    for(int i = 0; i < dimensao; i++)
        v[i] = w[i];
}

/// construtor a partir de um valarray
vetor::vetor(const valarray<double> &w)
{
    dimensao = w.size();
    v = new double[dimensao];

    for(int i = 0; i < dimensao; i++)
        v[i] = w[i];
}

/// construtor de cópia
vetor::vetor(const vetor &w)
{
    dimensao = w.retDimensao();
    v = new double[dimensao];

    for(int i = 0; i < dimensao; i++)
        v[i] = w(i);
}

/// Demais métodos:
/// exibe o vetor no console
void vetor::show() const
{
    cout << "|";
    for(int i = 0; i < dimensao; i++)
    {
        scout << "\t" << v[i];
    }
    cout << "\t|^T\n\n";
}

/// retorna a dimensão do vetor
inline int vetor::retDimensao() const
{
    return dimensao;
}

/// retorna um subvetor
vetor vetor::subvetor(int li, int lf)
{
    int d = lf - li + 1;

    if(d == 1)
        throw except("Método subvetor()\nErro! Indices iguais.\n");
    else if(d < 1)
        throw except("Método subvetor()\nErro! Indices trocados.\n");

    vetor ret(d);

    for(int i = 0; i < d; i++)
        ret(i) = v[i + d - 1];

    return ret;
}

/// Operadores:
/// atribuição
vetor& vetor::operator=(const vetor &w)
{
    if(this != &w)
    {
        dimensao = w.retDimensao();
        double *tmp = new double[dimensao];
        delete [] v;

        for(int i = 0; i < dimensao; i++)
            tmp[i] = w(i);

        v = tmp;
    }

    return *this;
}

/// acesso/atribuição aos elementos do vetor
double& vetor::operator()(int i)
{
    if((i < 0) or (i >= dimensao))
        throw except("Método operator()\nErro! Indice invalido.\n");

    return v[i];
}

/// acesso aos elementos de um vetor const
double vetor::operator()(int i) const
{
    if((i < 0) or (i >= dimensao))
        throw except("Método operator() const\nErro! Indice invalido.\n");

    return v[i];
}

/// *this = *this + vetor
vetor& vetor::operator+=(const vetor &v)
{
    vetor tmp(*this);
    *this = tmp + v;
    return *this;
}

/// *this = *this - vetor
vetor& vetor::operator-=(const vetor &v)
{
    vetor tmp(*this);
    *this = tmp - v;
    return *this;
}

/// *this = *this*k
vetor& vetor::operator*=(const double &k)
{
    vetor tmp(*this);
    *this = k*tmp;
    return *this;
}

/// *this = *this/k
vetor& vetor::operator/=(const double &k)
{
    vetor tmp(*this);
    *this = tmp/k;
    return *this;
}

vetor vetor::operator-() const
{
    return -1.0*(*this);
}

/// Destrutor:
vetor::~vetor()
{
    delete [] v;
}

/// Operadores globais:
vetor operator+(const vetor &v, const vetor &w)
{
    int sv = v.retDimensao();       int sw = w.retDimensao();

    if(sv != sw)
        throw except("operator+\nErro! Dimensoes incompativeis.\n");

    vetor ret(sv);

    for(int i = 0; i < sv; i++)
        ret(i) = v(i) + w(i);

    return ret;
}

vetor operator-(const vetor &v, const vetor &w)
{
    return v + w*(-1.0);
}

vetor operator*(const vetor &v, const double &a)
{
    int sv = v.retDimensao();
    vetor ret(sv);

    for(int i = 0; i < sv; i++)
        ret(i) = a*v(i);

    return ret;
}

vetor operator*(const double &a, const vetor &v)
{
    return v*a;
}

vetor operator/(const vetor &v, const double &a)
{
    if(a == 0.0)
        throw except("operator/\nErro! Divisao por zero.\n");

    return (1.0/a)*v;
}

ostream& operator<<(ostream &ret, const vetor &v)
{
    int a = v.retDimensao();

    for(int i = 0; i < a; i++)
        ret << "\t" << v(i);

    return ret;
}

/// Funções globais:
/// retorna a norma i do vetor
double norma(const vetor &v, int b)
{
    if(b < 0)
    throw except("Funcao norma\nErro! Norma invalida.\n");

    double ret = 0.0;
    int d = v.retDimensao();
    switch(b)
    {
        case 0:
            ret = max(abs(v));
        break;

        case 1:
            for(int i = 0; i < d; i++)
                ret += abs(v(i));
        break;

        case 2:
            for(int i = 0; i < d; i++)
                ret += pow(v(i), 2);

            ret = sqrt(ret);
        break;

        default:
            for(int i = 0; i < d; i++)
                ret += pow(v(i), b);

            ret = pow(ret, 1.0/b);
    }

    return ret;
}

/// aplica o módulo a cada elemento do vetor
vetor abs(const vetor &v)
{
    int d = v.retDimensao();
    vetor ret(d);

    for(int i = 0; i < d; i++)
        ret(i) = abs(v(i));

    return ret;
}

/// retorna o maior elemento do vetor
double max(const vetor &v)
{
    int d = v.retDimensao();
    double ret = v(0);

    for(int i = 1; i < d; i++)
    {
        if(v(i) > ret)
            ret = v(i);
    }

    return ret;
}

vetor sgn(vetor &v)
{
    int d = v.retDimensao();
    vetor ret(d);

    for(int i = 0; i < d; i++)
        ret(i) = sgn(v(i));

    return ret;
}
vetor sat(vetor &v)
{
    int d = v.retDimensao();
    vetor ret(d);

    for(int i = 0; i < d; i++)
        ret(i) = sat(v(i));

    return ret;
}

/// retorna o produto interno entre vetores
double prodInterno(const vetor &v, const vetor &w)
{
    int sa = v.retDimensao();
    int sb = w.retDimensao();

    if(sa != sb)
        throw except("Funcao prodInterno\nErro! Dimensoes incompativeis.\n");

    double ret = 0.0;

    for(int i = 0; i < sa; i++)
        ret += v(i)*w(i);

    return ret;
}

/// Função que retorna o produto vetorial entre vetores
vetor prodVetorial(const vetor &a, const vetor &b)
{
    int sa = a.retDimensao();
    int sb = b.retDimensao();

    if((sa != sb) or (sa > 3) or (sb > 3))
        throw except("Funcao prodVetorial\nErro! Dimensoes incompativeis.\n");

    vetor ret(3);

    ret(0) = a(1)*b(2) - a(2)*b(1);
    ret(1) = a(2)*b(0) - a(0)*b(2);
    ret(2) = a(0)*b(1) - a(1)*b(0);

//    for(int i = 0; i < sa; i++)
//        for(int j = 0; j < sa; j++)
//            for(int k = 0; k < sa; k++)
//                ret(i) += permutSymbol(i,j,k)*a(j)*b(k);

    return ret;
}

/// retorna um vetor unitário
vetor unitVet(const vetor &v, int a)
{
    double tmp = norma(v, a);

    if(tmp == 0.0)
    throw except("Funcao unitVet\nErro! Vetor de norma nula.\n");

    return v/tmp;
}

/// retorna um vetor com os coeficientes de um polinômio Hurwitz de grau g e raizes todas iguais a q
vetor hurwitz(int g, double q)
{
    vetor ret(g + 1);

    for(int i = 0; i < g + 1; i++)
        ret(i) = pow(q, g - i)*binomial(g, q);

    return ret;
}

/// retorna um vetor com senos e cossenos da série de fourier truncada
vetor fourier(int a, double t)
{
    vetor ret(2*a + 1);

    for(int i = 0; i < a; i++)
    {
        ret(2*i) = sin(t*(i+1));
        ret(2*i + 1) = cos(t*(i+1));
    }

    ret(2*a) = 1.0;

    return ret;
}

/// retorna um vetor com o polinomio, explico depois!
vetor polinomio(int a, double x)
{
    vetor ret(a + 1);

    for(int i = 0; i < a; i++)
        ret(i) = pow(x,i);

    return ret;
}

vetor membership(double &s, double &phi)
{
    vetor ret;

//    valarray<double> c12(9); /// caso I, II
//    c12[0] = -phi;        c12[8] = -c12[0];
//    c12[1] = -5.0e-3;     c12[7] = -c12[1];
//    c12[2] = -1.0e-3;     c12[6] = -c12[2];
//    c12[3] = -0.5e-3;     c12[5] = -c12[3];
//    c12[4] = 0.0;

//    vetor tmp1(7); /// caso I
//    tmp1(0) = pertTrapez(s, c12[0], c12[0], c12[1], c12[2]);
//    tmp1(6) = pertTrapez(s, c12[6], c12[7], c12[8], c12[8]);

//    for(int i = 1; i < 6; i++) /// caso I
//        tmp1(i) = pertTriang(s, c12[i], c12[i + 1], c12[i + 2]);

//    vetor tmp2(6); /// caso II
//    tmp2(0) = pertTrapez(s, c12[0], c12[0], c12[1], c12[2]);
//    tmp2(5) = pertTrapez(s, c12[6], c12[7], c12[8], c12[8]);
//
//    for(int i = 1; i < 5; i++) /// caso II
//        tmp2(i) = pertTriang(s, c12[i], c12[i + 1], c12[i + 2]);

    valarray<double> c3(8); /// caso III
    c3[0] = -phi;        c3[7] = -c3[0];
    c3[1] = -5.0e-3;     c3[6] = -c3[1];
    c3[2] = -1.0e-3;     c3[5] = -c3[2];
    c3[3] = -0.5e-3;     c3[4] = -c3[3];

    vetor tmp3(6); /// caso III
    tmp3(0) = pertTrapez(s, c3[0], c3[0], c3[1], c3[2]);
    tmp3(5) = pertTrapez(s, c3[6], c3[7], c3[8], c3[8]);

    for(int i = 1; i < 5; i++) /// caso III
        tmp3(i) = pertTriang(s, c3[i], c3[i + 1], c3[i + 2]);

//    ret = tmp1; /// caso I
//    ret = tmp2; /// caso II
    ret = tmp3; /// caso III

    return unitVet(ret, 1); /// todos os casos
}

/// retorna um vetor randômico
vetor randVet(int a, double b, double c)
{
    vetor ret(a);

    for(int i = 0; i < a; i++)
        ret(i) = Rand(b, c);

    return ret;
}

//vetor concatenaVert(const vetor &x, const vetor &y)
//{
//    int d1 = x.retDimensao();
//    int d2 = y.retDimensao();
//
//    int d = d1 + d2;
//
//    vetor ret(d);
//}