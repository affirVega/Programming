use std::io;

fn main() {
    let mut input = String::new();
    let mut result = 1.0;

    println!("Введите вещественное число, возводимое в степень, \
и целое число - степень, разделённые новой строкой.");

    io::stdin()
        .read_line(&mut input)
        .expect("Произошла ошибка при чтении из стандартного входа (stdin).");

    let a: f64 = input
        .trim().parse()
        .expect("Введено не вещественное число!");

    input.clear();

    io::stdin()
        .read_line(&mut input)
        .expect("Произошла ошибка при чтении из стандартного входа (stdin).");

    let n: i64 = input
        .trim().parse()
        .expect("Введено не целое число!");

    for _ in 0..n.abs() { /* Промежуток [0; n), код выполняется ровно n раз */
        result *= a;
    }

    if n < 0 {
        result = 1f64 / result;
    }

    println!("{}", result);
}
