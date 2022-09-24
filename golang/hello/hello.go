package main

import (
	"fmt"
	"log"	
	"example.com/greetings"	
)

func main() {
	log.SetPrefix("greetings: ")
	log.SetFlags(0)

	message1, message2, err := greetings.Hello("Hogetter")
	// message1, message2, err := greetings.Hello("")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(message1)
	fmt.Println(message2)

	var a int = 1
	var b int = 1

	for i := 0; i < 10; i++ {
		a, b = greetings.Fibonacci(a, b)
	}
	// fmt.Printf("a=%d, b=%d\n", a, b)
}
