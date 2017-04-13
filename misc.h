/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   misc.h
 * Author: gerreb
 *
 * Created on January 28, 2016, 10:08 PM
 */

#ifndef MISC_H
#define MISC_H

#include <iostream> // cin, cout...
#include <valarray> // C++ array
#include <complex> // complex numbers
#include <stdexcept> // exceptions
#include <cmath> // general math stuff
#include <fstream> // file manipulation
#include <cstdlib> // rand()
#include <utility> // pair
#include <sys/types.h> // this library is optional, but we recommend it when using system calls, because some of their definitions use aliases for standard types that may change one day. [Beginning Linux Programming, 4ed]
#include <sys/stat.h>

using namespace std;

#define scout cout << scientific << showpos // scientific notation and signal, always

class except: public runtime_error
{/** \class except
     \brief class for general exceptions. */
public:
    except(const string &m):runtime_error(m) {}
};

int permutSymbol(int, int, int);

double Rand(double, double);

unsigned long long int fatorial(int);

int binomial(int, int);

double pertTriang(double &, double, double, double);

double pertTrapez(double &, double, double, double, double);

double sat(double);

double sgn(double);

#endif /* MISC_H */

