//
//              LAPACK++ 1.1 Linear Algebra Package 1.1
//               University of Tennessee, Knoxvilee, TN.
//            Oak Ridge National Laboratory, Oak Ridge, TN.
//        Authors: J. J. Dongarra, E. Greaser, R. Pozo, D. Walker
//                 (C) 1992-1996 All Rights Reserved
//
//                             NOTICE
//
// Permission to use, copy, modify, and distribute this software and
// its documentation for any purpose and without fee is hereby granted
// provided that the above copyright notice appear in all copies and
// that both the copyright notice and this permission notice appear in
// supporting documentation.
//
// Neither the Institutions (University of Tennessee, and Oak Ridge National
// Laboratory) nor the Authors make any representations about the suitability
// of this software for any purpose.  This software is provided ``as is''
// without express or implied warranty.
//
// LAPACK++ was funded in part by the U.S. Department of Energy, the
// National Science Foundation and the State of Tennessee.


#include <stdlib.h>
#include "lafnames.h"
#include LA_COL_VECTOR_DOUBLE_H

void mult2(double* v, int len)
{
    for (int i = 0; i < len; i++)
        v[i] *= 2;
}

LaColVectorDouble madd(const LaColVectorDouble &A, const LaColVectorDouble &B)
{
    if (A.debug())
    {
        std::cout << ">>> madd(A,B) \n";
        std::cout << "    A: " << A.info() << std::endl;
        std::cout << "    B: " << B.info() << std::endl;
    }

    if (A.size() != B.size())
    {
        std::cerr << "LaColVectorDouble madd(LaColVectorDouble &A, LaColVectorDouble &B): \
            non-conformant arrays.\n";

        return LaColVectorDouble(0);       // 0x0 matrix
    }

    int i;
    LaColVectorDouble result(A.size());


    for (i = 0; i < A.size(); i++)
        result(i) = A(i) + B(i);

    if (A.debug())
    {
        std::cout << "   A+B: " << result.info() << std::endl;
        std::cout << "<<< madd(A,B)\n";
    }
    return result;

}

int main(int argc, char *argv[])
{
    int N;

    if (argc < 2) exit(1);

    N = atoi(argv[1]);

    double v[100];
    int i;
    for (i = 0; i < 100; i++)
        v[i] = 0;

    LaIndex I(2, 4);

    // Test constructors
    //
    LaColVectorDouble A;
    std::cout << std::endl << "null consturctor " << std::endl;
    std::cout << "A(): " << A.info() << std::endl;

    LaColVectorDouble C(N);
    std::cout << std::endl << "(int) constructor " << std::endl;
    std::cout << "C(N) : " << C.info() << std::endl;


    LaColVectorDouble F(v, 10);
    std::cout << std::endl ;
    std::cout << "(double*, int) constructor " << std::endl;
    std::cout << "F(v,10): " << F.info() << std::endl;

    C = 5.5;
    std::cout << std::endl;
    std::cout << "test operator=(double) " << std::endl;
    std::cout << "C = 5.5: " << C.info() << std::endl;
    std::cout << C << std::endl;

    C(I) = 7.7;
    C(I);
    std::cout << std::endl;
    std::cout << "test C(const LaIndex&) constructor" << std::endl;
    std::cout << "C(I)=7.7: " << C(I).info() << std::endl;
    std::cout << "C(I): " << C(I) << std::endl;
    std::cout << C << std::endl;

    std::cout << std::endl;
    std::cout << "test start(),inc(),end() " << std::endl;
    std::cout << "C.start(): " << C.start() << std::endl;
    std::cout << "C.inc(): " << C.inc() << std::endl;
    std::cout << "C.end(): " << C.end() << std::endl;

    A.ref(C);
    std::cout << std::endl;
    std::cout << "test ref(const LaGenMatDouble &)" << std::endl;
    std::cout << "A.ref(C): " << A.info() << std::endl;
    std::cout << A << std::endl;

    C = 1.1;
    A.inject(C);
    std::cout << std::endl;
    std::cout << "C = 1.1\n";
    std::cout << "test inject(const LaGenMatDouble &)" << std::endl;
    std::cout << "A.inject(C): " << A.info() << std::endl;
    std::cout << A << std::endl;

    A.copy(C);
    std::cout << std::endl;
    std::cout << "test copy(const LaGenMatDouble &)" << std::endl;
    std::cout << "A.copy(C): " << A.info() << std::endl;
    std::cout << "       C : " << C.info() << std::endl;
    std::cout << A << std::endl;


    LaColVectorDouble D(C);        // D is also N,N
    std::cout << std::endl << "test X(const &X) constructor " << std::endl;
    std::cout << "D(C) :" << D.info() << std::endl;

    LaColVectorDouble T;
    std::cout << std::endl;
    std::cout << "test call to madd()" << std::endl;
    std::cout << T.ref(madd(D, C)).info() << std::endl;
    std::cout << T << std::endl;
}
