use std::io;

fn main() {
    let mut input = String::new();

    println!("Калькулятор принимает строку в формате рациональное число, оператор (+-*/) и рациональное число, разделённые пробелом");

    io::stdin()
        .read_line(&mut input)
        .expect("Ошибка при чтении из консоли");

    let mut iter = input.split_whitespace();
    let a: f64 = iter.next().unwrap().parse().unwrap();
    let ch: char = iter.next().unwrap().parse().unwrap();
    let b: f64 = iter.next().unwrap().parse().unwrap();

    match ch {
        '*' => println!("{}", a * b),
        '-' => println!("{}", a - b),
        '+' => println!("{}", a + b),
        '/' => if b == 0f64 {
            println!("{}", f64::NAN);
        } else {
            println!("{}", a / b);
        },
        _   => println!("Неизвестный оператор."),
    };
}
