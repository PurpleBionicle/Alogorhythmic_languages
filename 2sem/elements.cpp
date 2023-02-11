#ifndef INCLUDE_ELEMENTS_HPP_
#define INCLUDE_ELEMENTS_HPP_
#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>
#include <vector>

// ЛИТЕРАЛЫ
long double operator"" _mH(long double inductor) {
    return inductor * pow(10, -6);
}

long double operator"" _nH(long double inductor) {
    return inductor * pow(10, -9);
}

long double operator"" _mF(long double capasitor) {
    return capasitor * pow(10, -6);
}

long double operator"" _nF(long double capasitor) {
    return capasitor * pow(10, -9);
}
struct Power {};

class Element {
public:
    [[nodiscard]] virtual float CalculateResistance(const Power& p) const = 0;
    virtual ~Element() = default;
};

class GroupConnections : public Element {
protected:
    std::vector<Element*> elements;

public:
    void addElements(Element* element) { elements.push_back(element); }
};

class SequentialConnections : public GroupConnections {
public:
    [[nodiscard]] float CalculateResistance(const Power& p) const override {
        float sum = 0.;
        for (Element* element : elements) {
            sum += element->CalculateResistance(p);
        }
        return sum;
    }
};

class ParallelConnections : public GroupConnections {
public:
    [[nodiscard]] float CalculateResistance(const Power& p) const override {
        float invertedSum = 0.;
        for (Element* element : elements) {
            invertedSum += 1 / element->CalculateResistance(p);
        }
        return 1 / invertedSum;
    }
};

class Resistor : public Element {
private:
    float resistance;

public:
    explicit Resistor(float res) { resistance = res; }

    [[nodiscard]] float CalculateResistance(
            [[maybe_unused]] const Power& p) const final {
        return resistance;
    };
};

class Group_of_elements : public Element {
private:
    float resistance;

public:
    explicit Group_of_elements(float res) { resistance = res; }

    [[nodiscard]] float CalculateResistance(
            [[maybe_unused]] const Power& p) const final {
        return resistance;
    };
};

class Capacitor : public Element {
private:
    float capacitor;
    int frequency = 50;

public:
    explicit Capacitor(float cap) { capacitor = cap; }

    [[nodiscard]] float CalculateResistance(
            [[maybe_unused]] const Power& p) const final {
        return 1 / (capacitor * 2 * M_PI * frequency);
    };
};

class Inductor : public Element {
private:
    float inductor;
    int frequency = 50;

public:
    explicit Inductor(float ind) { inductor = ind; }
    [[nodiscard]] float CalculateResistance(
            [[maybe_unused]] const Power& p) const final {
        return inductor * 2 * M_PI * frequency;
    };
};

#endif  // INCLUDE_ELEMENTS_HPP_