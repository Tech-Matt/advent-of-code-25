use std::fs::File;
use std::io::{BufRead, BufReader};
use std::str::FromStr;

const SAFE_SIZE: u64 = 100; // 0 to 99

struct Move {
    direction: char,
    value: u64,
}

/*
 * The struct safe has only one element, curr_index, which points to the last element which has been selected after a 'Move'
 * - curr_index can only be decreased or increased by decrease() or increase()
 */
struct Safe {
    curr_index : u64,
}

impl Safe {
    fn new() -> Self {
        Safe { curr_index: 50}
    }
    fn increase(&mut self, value: u64) {
        self.curr_index = (self.curr_index + value) % SAFE_SIZE;
    }

    fn decrease(&mut self, value: u64) {
        self.curr_index = (self.curr_index + SAFE_SIZE - (value % SAFE_SIZE)) % SAFE_SIZE;
    }
}



impl FromStr for Move {
    type Err = String;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        if s.is_empty() {
            return Err("Empty string".to_string());
        }

        let direction = s.chars().next().unwrap();
        let value = s[1..].parse::<u64>()
            .map_err(|_| "Invalid number".to_string())?;

        Ok(Move { direction, value })
    }
}

fn main() {

    // Initilize safe
    let mut safe = Safe::new();
    // Reading data
    let file = File::open("../data.txt").expect("Failed to open file");
    let reader = BufReader::new(file);

    // keeps track of how many times the safe index goes to zero
    let mut n_zeros: u64 = 0;

    // Parsing data
    for line in reader.lines() {
        let line = line.expect("Failed to read line");
        match line.parse::<Move>() {
            Ok(mv) => {
                println!("Direction: {}, Value: {}", mv.direction, mv.value);
                if mv.direction == 'L' {
                    safe.decrease(mv.value);    
                }
                else if mv.direction == 'R' {
                    safe.increase(mv.value);
                }
                else {
                    panic!("Wrong Direction Format");
                }
                if safe.curr_index == 0 {
                    n_zeros += 1;
                }
            },
            Err(e) => eprintln!("Parse Error: {}", e),
        }
    }

    // Printing results
    println!("Total number of zeros: {}", n_zeros);
}
