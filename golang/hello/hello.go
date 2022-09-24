package main

import (
	"fmt"

	"example.com/greetings"
)

func main() {
	message1, message2 := greetings.Hello("Hogetter")
	fmt.Println(message1)
	fmt.Println(message2)

	var a int = 1
	var b int = 1

	for i := 0; i < 10; i++ {
		a, b = greetings.Fibonacci(a, b)
	}
	// fmt.Printf("a=%d, b=%d\n", a, b)

}
