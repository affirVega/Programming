#include <iostream>

double BMI(double weight, double height) {
	return weight / (height * height);
}

void printBMI(double BMI) {
	if (BMI < 18.5)
		std::cout << "Underweight";
	else if (BMI < 25.0)
		std::cout << "Normal weight";
	else if (BMI < 30.0)
		std::cout << "Overweight";
	else
		std::cout << "Obesity";

	std::cout << std::endl;
}

int main() {
	double weight, height;
	std::cout << "Введите свой вес и рост через пробел: ";
	std::cin >> weight >> height;

	printBMI(BMI(weight, height/100.0));
}
