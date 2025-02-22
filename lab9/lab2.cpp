#include <iostream>
#include <vector>
#include <algorithm>

class Polynomial
{
private:
    // Each term is represented as a pair (coefficient, exponent)
    std::vector<std::pair<int, int>> terms;

    // Helper function to sort terms by exponent (descending order)
    void sortTerms()
    {
        std::sort(terms.begin(), terms.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b)
                  {
                      return a.second > b.second; // Sort by exponent (highest first)
                  });
    }

    // Helper function to combine like terms (terms with the same exponent)
    void combineLikeTerms()
    {
        std::vector<std::pair<int, int>> uniqueTerms;
        for (const auto &term : terms)
        {
            auto it = std::find_if(uniqueTerms.begin(), uniqueTerms.end(),
                                   [&term](const std::pair<int, int> &t)
                                   { return t.second == term.second; });
            if (it != uniqueTerms.end())
            {
                it->first += term.first; // Add coefficients if exponents match
            }
            else
            {
                uniqueTerms.push_back(term);
            }
        }
        terms = uniqueTerms;
    }

public:
    // Default Constructor
    Polynomial() {}

    // Parameterized Constructor
    Polynomial(const std::vector<std::pair<int, int>> &inputTerms) : terms(inputTerms)
    {
        sortTerms();
        combineLikeTerms();
    }

    // Destructor
    ~Polynomial() {}

    // Accessor Function: Get coefficient by exponent
    int getCoefficient(int exponent) const
    {
        auto it = std::find_if(terms.begin(), terms.end(),
                               [exponent](const std::pair<int, int> &term)
                               { return term.second == exponent; });
        if (it != terms.end())
        {
            return it->first;
        }
        return 0; // Return 0 if no term with the given exponent exists
    }

    // Mutator Function: Set coefficient for a specific exponent
    void setCoefficient(int exponent, int newCoefficient)
    {
        auto it = std::find_if(terms.begin(), terms.end(),
                               [exponent](const std::pair<int, int> &term)
                               { return term.second == exponent; });
        if (it != terms.end())
        {
            it->first = newCoefficient; // Update existing term
        }
        else
        {
            terms.push_back({newCoefficient, exponent}); // Add new term
        }
        sortTerms();
        combineLikeTerms();
    }

    // Overload Addition Operator (+)
    Polynomial operator+(const Polynomial &other) const
    {
        Polynomial result = *this; // Copy current polynomial
        for (const auto &term : other.terms)
        {
            result.setCoefficient(term.second, result.getCoefficient(term.second) + term.first);
        }
        return result;
    }

    // Overload Subtraction Operator (-)
    Polynomial operator-(const Polynomial &other) const
    {
        Polynomial result = *this; // Copy current polynomial
        for (const auto &term : other.terms)
        {
            result.setCoefficient(term.second, result.getCoefficient(term.second) - term.first);
        }
        return result;
    }

    // Overload Multiplication Operator (*)
    Polynomial operator*(const Polynomial &other) const
    {
        Polynomial result;
        for (const auto &term1 : terms)
        {
            for (const auto &term2 : other.terms)
            {
                int newCoefficient = term1.first * term2.first;
                int newExponent = term1.second + term2.second;
                result.setCoefficient(newExponent, result.getCoefficient(newExponent) + newCoefficient);
            }
        }
        return result;
    }

    // Overload Assignment Operator (=)
    Polynomial &operator=(const Polynomial &other)
    {
        if (this != &other)
        {
            terms = other.terms;
        }
        return *this;
    }

    // Overload Compound Addition Assignment (+=)
    Polynomial &operator+=(const Polynomial &other)
    {
        *this = *this + other;
        return *this;
    }

    // Overload Compound Subtraction Assignment (-=)
    Polynomial &operator-=(const Polynomial &other)
    {
        *this = *this - other;
        return *this;
    }

    // Overload Compound Multiplication Assignment (*=)
    Polynomial &operator*=(const Polynomial &other)
    {
        *this = *this * other;
        return *this;
    }

    // Print Polynomial
    void print() const
    {
        for (size_t i = 0; i < terms.size(); ++i)
        {
            if (i > 0 && terms[i].first > 0)
            {
                std::cout << " + ";
            }
            else if (terms[i].first < 0)
            {
                std::cout << " - ";
            }
            std::cout << std::abs(terms[i].first);
            if (terms[i].second > 0)
            {
                std::cout << "x";
                if (terms[i].second > 1)
                {
                    std::cout << "^" << terms[i].second;
                }
            }
        }
        std::cout << std::endl;
    }
};

// Main Function to Test the Polynomial Class
int main()
{
    Polynomial p1({{3, 2}, {2, 1}, {1, 0}}); // 3x^2 + 2x + 1
    Polynomial p2({{1, 3}, {4, 1}});         // x^3 + 4x

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    Polynomial sum = p1 + p2;
    std::cout << "Sum (p1 + p2): ";
    sum.print();

    Polynomial difference = p1 - p2;
    std::cout << "Difference (p1 - p2): ";
    difference.print();

    Polynomial product = p1 * p2;
    std::cout << "Product (p1 * p2): ";
    product.print();

    p1 += p2;
    std::cout << "p1 after p1 += p2: ";
    p1.print();

    p1 -= p2;
    std::cout << "p1 after p1 -= p2: ";
    p1.print();

    p1 *= p2;
    std::cout << "p1 after p1 *= p2: ";
    p1.print();

    return 0;
}