/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vetor.h
 * Author: gerreb
 *
 * Created on February 11, 2016, 9:02 PM
 */

#ifndef VETOR_H
#define VETOR_H

#include "misc.h"

class vetor{
    public:
        vetor(); /// construtor padrão
        explicit vetor(int); /// construtor do tamanho. O explicit serve pra prevenir a conversão automática
        vetor(const double*, int); /// construtor a partir de um array-C
        vetor(const valarray<double> &); /// construtor a partir de um valarray
        vetor(const vetor &); /// construtor de cópia

        void show() const; /// método que exibe o vetor no console
        inline int retDimensao() const; /// retorna a dimensão do vetor
        vetor subvetor(int, int); /// retorna um subvetor

        vetor& operator=(const vetor &); /// operador de atribuição
        double& operator()(int); /// acesso/atribuição aos elementos do vetor
        double operator()(int) const; /// acesso aos elementos de um vetor const
        vetor& operator+=(const vetor &); /// *this = *this + vetor
        vetor& operator-=(const vetor &); /// *this = *this - vetor
        vetor& operator*=(const double &);/// *this = *this*k
        vetor& operator/=(const double &);/// *this = *this/k
        vetor operator-() const;

        ~vetor(); /// destrutor
    private:
        int dimensao; /// dimensão do vetor
        double *v; /// armazenamento do vetor
};

/// Operadores globais:
vetor operator+(const vetor &, const vetor &);
vetor operator-(const vetor &, const vetor &);
vetor operator*(const vetor &, const double &);
vetor operator*(const double &, const vetor &);
vetor operator/(const vetor &, const double &);
ostream& operator<<(ostream &, const vetor &); /// \todo friend??

/// Funções globais:
double norma(const vetor &, int); /// Função que retorna a norma i do vetor
vetor abs(const vetor &); /// aplica o módulo a cada elemento do vetor
double max(const vetor &); /// retorna o maior elemento do vetor
vetor sgn(vetor &);
vetor sat(vetor &);
double prodInterno(const vetor &, const vetor &); /// retorna o produto interno entre vetores
vetor prodVetorial(const vetor &, const vetor &); /// Função que retorna o produto vetorial entre vetores
vetor unitVet(const vetor &, int); /// Função que retorna um vetor unitário

vetor hurwitz(int, double); /// Função que retorna um vetor com os coeficientes de um polinômio Hurwitz de grau g e raizes todas iguais a q
vetor fourier(int, double); /// Função que retorna um vetor com senos e cossenos da série de Fourier truncada
vetor polinomio(int, double); /// Função que retorna um vetor com o polinomio, explico depois!
vetor membership(double &, double &);
vetor randVet(int, double, double); /// Função que retorna um vetor randômico

vetor concatenaVert(const vetor &, const vetor &); /// \todo
//matriz concatenaHor(const vetor &, const vetor &); /// \todo

#endif // VETOR_H