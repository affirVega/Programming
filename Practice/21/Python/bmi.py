def bmi(weight: float, height: float) -> float:
    return weight / (height**2)
    
def print_bmi(bmi: float) -> float:
    if   bmi < 18.5:
        print("Underweight")
    elif bmi < 25.0:
        print("Normal weight")
    elif bmi < 30.0:
        print("Overweight")
    else:
        print("Obesity")

weight, height = map(float, input("Введите вес и рост через пробел: ").split(" "))
print(weight, height)
print_bmi(bmi(weight, height/100))
