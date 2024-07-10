pub mod person {
    #[derive(Debug)]
    pub struct Person {
        name: String,
        age: u8,
        car: String,
    }

    impl Person {
        pub fn default() -> Person {
            Person {
                name: String::default(),
                age: u8::default(),
                car: String::default()
            }
        }

        pub fn new(name: String, age: u8, car: String) -> Person {
            Person {
                name,
                age,
                car,
            }
        }

        pub fn clone(&self) -> Person {
            Person {
                name: self.name.clone(),
                age: self.age,
                car: self.car.clone(),
            }
        }

        pub fn name(&self) -> &str {
            &self.name[..]
        }

        pub fn age(&self) -> u8 {
            self.age
        }

        pub fn car(&self) -> &str {
            &self.car[..]
        }
    }
}

pub mod node {
    use super::person::Person;

    #[derive(Debug)]
    pub struct Node {
        item: crate::Person,
        prox: Option<Box<Node>>,
    }

    impl Node {
        pub fn default() -> Self {
            Self {
                item: crate::Person::default(),
                prox: None,
            }
        }

        pub fn new(item: crate::Person) -> Self {
            Self {
                item,
                prox: None,
            }
        }

        pub fn item(&self) -> &Person {
            &self.item
        }

        pub fn prox(&self) -> Option<Box<Node>> {
            // TODO
        }
    }
}

pub mod stack {
    #[derive(Debug)]
    pub struct Stack {
        content: Vec<crate::Person>,
        len: i32,
    }

    impl Stack {
        pub fn new() -> Self {
            Self {
                content: Vec::new(),
                len: 0,
            }
        }
        
        pub fn insert(&mut self, p: crate::Person) {
            self.content.push(p);
            self.len = self.len + 1;
        }

        pub fn remove(&mut self) -> crate::Person {
            let element: crate::Person = self.content
                .pop()
                .unwrap_or_else(|| crate::Person::default());
            self.content.pop(); 
            self.len = self.len - 1;
            return element;
        }
    }
}
