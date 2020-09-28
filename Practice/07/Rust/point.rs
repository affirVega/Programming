pub struct Point {
    x: f64,
    y: f64,
}

pub fn point_distance(a: &Point, b: &Point) -> f64 {
    ((a.x - b.x).pow(2) + (a.y - b.y).pow(2)).sqrt()
}
