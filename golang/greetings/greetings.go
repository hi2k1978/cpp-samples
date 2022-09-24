package greetings

import "fmt"

func Hello(name string) (string, string) {
	var message1 = fmt.Sprintf("Hi, %v, welcome", name)
	message2 := fmt.Sprintf("Hi, %v, goodbye", name)
	fmt.Printf("message1: type is %t\n", message1)
	return message1, message2
}

func Fibonacci(a int, b int) (int, int){
	fmt.Printf("a=%d, b=%d\n", a, b)
	return a+b, a
}

