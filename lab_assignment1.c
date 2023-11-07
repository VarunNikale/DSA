#include <stdio.h>
#include <stdlib.h>


struct Term
{
    int coefficient;
    int exponent;
    struct Term *next;
};

typedef struct Term Polynomial;

// Function to create a new term
Polynomial *createTerm(int coef, int exp)
{
    Polynomial *term = (Polynomial *)malloc(sizeof(Polynomial));
    term->coefficient = coef;
    term->exponent = exp;
    term->next = NULL;
    return term;
}

// Function to add a term to a polynomial
void addTerm(Polynomial **poly, int coef, int exp)
{
    Polynomial *newTerm = createTerm(coef, exp);

    if (*poly == NULL)
    {
        *poly = newTerm;
        return;
    }

    Polynomial *current = *poly;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newTerm;
}

// Function to add two polynomials
Polynomial *addPolynomials(Polynomial *poly1, Polynomial *poly2)
{
    Polynomial *result = NULL;

    while (poly1 != NULL && poly2 != NULL)
    {
        if (poly1->exponent > poly2->exponent)
        {
            addTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        }
        else if (poly1->exponent < poly2->exponent)
        {
            addTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        }
        else
        {
            addTerm(&result, poly1->coefficient + poly2->coefficient, poly1->exponent);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // Add any remaining terms from both polynomials
    while (poly1 != NULL)
    {
        addTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL)
    {
        addTerm(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}
// Function to multiply two polynomials
Polynomial *Pmult(Polynomial *poly1, Polynomial *poly2)
{
    Polynomial *result = NULL;

    while (poly1 != NULL)
    {
        Polynomial *temp = NULL;
        Polynomial *current = poly2;

        while (current != NULL)
        {
            addTerm(&temp, poly1->coefficient * current->coefficient, poly1->exponent + current->exponent);
            current = current->next;
        }

        result = addPolynomials(result, temp);
        poly1 = poly1->next;

        // Free memory for the temporary polynomial
        while (temp != NULL)
        {
            Polynomial *tempTerm = temp;
            temp = temp->next;
            free(tempTerm);
        }
    }

    return result;
}

void displayPolynomial(Polynomial *poly)
{
    while (poly != NULL)
    {
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL)
        {
            printf(" + ");
        }
    }
    printf("\n");
}
// Function to subtract two polynomials
Polynomial *Psub(Polynomial *poly1, Polynomial *poly2)
{
    Polynomial *result = NULL;

    while (poly1 != NULL || poly2 != NULL)
    {
        int coef1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int coef2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;

        if (exp1 > exp2)
        {
            addTerm(&result, coef1, exp1);
            poly1 = poly1->next;
        }
        else if (exp1 < exp2)
        {
            addTerm(&result, -coef2, exp2);
            poly2 = poly2->next;
        }
        else
        {
            addTerm(&result, coef1 - coef2, exp1);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    return result;
}

int main()
{
    Polynomial *poly1 = NULL;
    Polynomial *poly2 = NULL;

    int terms1, terms2;
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &terms1);

    printf("Enter the coefficients and exponents of the terms in the first polynomial:\n");
    for (int i = 1; i <= terms1; i++)
    {
        int coef, exp;
        printf("Enter the %dth coefficient and exponent\n", i);
        scanf("%d %d", &coef, &exp);
        addTerm(&poly1, coef, exp);
    }

    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &terms2);

    printf("Enter the coefficients and exponents of the terms in the second polynomial:\n");
    for (int i = 1; i <= terms2; i++)
    {
        int coef, exp;
        printf("Enter the %dth coefficient and exponent\n", i);
        scanf("%d %d", &coef, &exp);
        addTerm(&poly2, coef, exp);
    }

    printf("First polynomial: ");
    displayPolynomial(poly1);

    printf("Second polynomial: ");
    displayPolynomial(poly2);

    Polynomial *sumPoly = addPolynomials(poly1, poly2);
    printf("Sum of the polynomials: ");
    displayPolynomial(sumPoly);

    Polynomial *productPoly = Pmult(poly1, poly2);
    printf("Product of the polynomials: ");
    displayPolynomial(productPoly);

    //Free memory for product polynomial
    while (productPoly != NULL)
    {
        Polynomial *temp = productPoly;
        productPoly = productPoly->next;
        free(temp);
    }

//     Polynomial *diffPoly = Psub(poly1, poly2);
//     printf("Difference of the polynomials: ");
//     displayPolynomial(diffPoly);

//   //  Free memory for difference polynomial
//     while (diffPoly != NULL)
//     {
//         Polynomial *temp = diffPoly;
//         diffPoly = diffPoly->next;
//         free(temp);
//     }

    // Free memory
    while (poly1 != NULL)
    {
        Polynomial *temp = poly1;
        poly1 = poly1->next;
        free(temp);
    }

    while (poly2 != NULL)
    {
        Polynomial *temp = poly2;
        poly2 = poly2->next;
        free(temp);
    }

    while (sumPoly != NULL)
    {
        Polynomial *temp = sumPoly;
        sumPoly = sumPoly->next;
        free(temp);
    }

    return 0;
}
