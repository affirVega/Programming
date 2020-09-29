use std::io;

fn read_f64() -> f64 {
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Произошла ошибка при чтении из стандартного входа (stdin).");

    let f: f64 = input
        .trim().parse()
        .expect("Введено не вещественное число!");

    f
}

fn main() {
    println!("Введите 3 вещественных числа, каждое в отдельной строке.");

    let a: f64 = read_f64();
    let b: f64 = read_f64();
    let c: f64 = read_f64();

    if a == 0.0 {
        if b == 0.0 {
            println!("Корней нет.");
        } else {
            println!("x = {}", -c / b);
        }
    } else {
        let d = b*b - 4.0*a*c;
        if d < 0.0 {
            println!("Не найдено действительных корней");
        } else if d == 0.0 {
            println!("x = {}", -b/(2.0*a));
        } else {
            let d_sqrt = d.sqrt();
            let x_one = (-b + d_sqrt) / (2.0 * a);
            let x_two = (-b - d_sqrt) / (2.0 * a);
            println!("x1 = {}\nx2 = {}", x_one, x_two);
        }
    }
}
