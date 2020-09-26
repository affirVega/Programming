use std::io;

fn main() {
    let mut input = String::new;

    io::stdin()
        .read_line(&mut input)
        .expect("Не удалось прочесть строку.");

    let inputs: Vec<f64> = input.split(" ")
        .map(|x| x.parse()
                  .expect("Не вещественное число!"))
        .collect();


}
