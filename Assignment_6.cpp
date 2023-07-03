/*
Assignment 6
Student ID: 10138372
Program that defines a heirachy of geometric shapes and classes calculating there are and volume.
*/
#include <iostream>
#include <vector>
#include <iomanip>
// Function to check if input is valid (non-negative)
void validate_input(double value) {
    if (value < 0) {
        throw std::invalid_argument("Cannot accept negative numbers.");
    }
}
// The base class for all shapes
class shape {
public:
    virtual ~shape() {}
    virtual void info() const = 0;
    virtual double area() const = 0;
    virtual double volume() const = 0;
};
// Inheritance classes from shape
class two_dimensional : public shape {
public:
    virtual ~two_dimensional() {}
    double volume() const override {
        return 0.0;
    }
};
class three_dimensional : public shape {
public:
    virtual ~three_dimensional() {}
};
// Rectangular class that inherits from two_dimensional class
class rectangle : public two_dimensional {
protected:
    double width, height;
public:
    rectangle(double width, double height)
        : width(width), height(height) {
        validate_input(width);
        validate_input(height);
    }
    void info() const override {
        std::cout << "Rectangle" << std::endl;
    }
    double area() const override {
        return width * height;
    }
};
// Square class that inherits from two_dimensional class
class square : public rectangle {
public:
    square(double side)
        : rectangle(side, side) {
        validate_input(side);
    }
    void info() const override {
        std::cout << "Square" << std::endl;
    }
};
// Ellipsoidal class that inherits from two_dimensional class
class ellipse : public two_dimensional {
protected:
    double major_axis, minor_axis;
public:
    ellipse(double major_axis, double minor_axis)
        : major_axis(major_axis), minor_axis(minor_axis) {
        validate_input(major_axis);
        validate_input(minor_axis);
    }
    void info() const override {
        std::cout << "Ellipse" << std::endl;
    }
    double area() const override {
        return 3.14159 * major_axis * minor_axis;
    }
};
// Circle class that inherits from ellipse class
class circle : public ellipse {
public:
    circle(double radius)
        : ellipse(radius, radius) {
        validate_input(radius);
    }
    void info() const override {
        std::cout << "Circle" << std::endl;
    }
};
// Cuboid class that inherits from three_dimensional class
class cuboid : public three_dimensional {
protected:
    double length, width, height;
public:
    cuboid(double length, double width, double height)
        : length(length), width(width), height(height) {
        validate_input(length);
        validate_input(width);
        validate_input(height);
    }
    void info() const override {
        std::cout << "Cuboid" << std::endl;
    }
    double area() const override {
        return 2 * (length * width + width * height + height * length);
    }
    double volume() const override {
        return length * width * height;
    }
};
// Cube class that inherits from cuboid class
class cube : public cuboid {
public:
    cube(double side)
        : cuboid(side, side, side) {
        validate_input(side);
    }
    void info() const override {
        std::cout << "Cube" << std::endl;
    }
};
// Ellipsoid class that inherits from three_dimensional class
class ellipsoid : public three_dimensional {
protected:
    double a, b, c;
public:
    ellipsoid(double a, double b, double c)
        : a(a), b(b), c(c) {
        validate_input(a);
        validate_input(b);
        validate_input(c);
    }
    void info() const override {
        std::cout << "Ellipsoid" << std::endl;
    }
    double area() const override {
        double p = 1.61;
        return 4 * 3.14159 * pow((pow(a * b, p) + pow(a * c, p) + pow(b * c, p)) / 3, 1 / p);
    }
    double volume() const override {
        return 4 / 3.0 * 3.14159 * a * b * c;
    }
};
// Sphere class that inherits from ellipsoid class
class sphere : public ellipsoid {
public:
    sphere(double radius)
        : ellipsoid(radius, radius, radius) {
        validate_input(radius);
    }
    void info() const override {
        std::cout << "Sphere" << std::endl;
    }
};
// Prism class that inherits from three_dimensional class
class prism : public three_dimensional {
private:
    double depth;
    two_dimensional* base_shape;
public:
    prism(double depth, two_dimensional* base_shape)
        : depth(depth), base_shape(base_shape) {
        validate_input(depth);
    }
    ~prism() {
        delete base_shape;
    }
    void info() const override {
        std::cout << "Prism" << std::endl;
    }
    double area() const override {
        return 2 * base_shape->area() + depth * base_shape->area();
    }
    double volume() const override {
        return depth * base_shape->area();
    }
};
int main() {
    std::vector<shape*> shapes;
    try {
        shapes.push_back(new rectangle(6, 5));
        shapes.push_back(new circle(1));
        shapes.push_back(new cube(7));
        shapes.push_back(new sphere(9));
        shapes.push_back(new prism(5, new rectangle(1, 3)));
        // Prints volumes and areas of shapes
        for (shape* shape_pointer : shapes) {
            shape_pointer->info();
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Area: " << shape_pointer->area() << std::endl;
            std::cout << "Volume: " << shape_pointer->volume() << std::endl;
            std::cout << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    for (shape* shape_pointer : shapes) {
        delete shape_pointer;
    }
    return 0;
}