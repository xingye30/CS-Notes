#ifndef _Polynomial_H
#define _Polynomial_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Polynomial; 

void ZeroPolynomial(Polynomial Poly);
void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum);
void MultPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolyProd);

#endif