use std::io;
mod point;

fn main() {
    let mut input = String::new();
    
    println!("Введите цифру метода ввода\n1. Координаты вершин треугольника\n2. Стороны треугольника");

    io::stdin
        .read_line(&mut input)
        .expect("Ошибка чтения из stdin.");
    
    let choice: i32 = input.parse().unwrap();
    input.clear();

    if choise == 1 {
        
        

    } else if choise == 2 {
        


    } else {
        
        println!("Неизвестный метод.");

    }
}
