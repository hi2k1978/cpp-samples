package greetings

import (
	"errors"
	"fmt"
	"math/rand"
	"time"
)

func Hello(name string) (string, string, error) {
	if name == "" {
		return "", "", errors.New("empty name")
	}
	message1 := fmt.Sprintf(randomFormat(), name)
	message2 := fmt.Sprintf("Hi, %v, goodbye", name)
	fmt.Printf("message1: type is %t\n", message1)
	return message1, message2, nil
}

func init() {
	rand.Seed(time.Now().UnixNano())
}

func randomFormat() string {
	formats := []string{
		"Hi, %v. Welcome!",
		"Great to see you, %v",
		"Hail, %v! Well met!",
	}
	return formats[rand.Intn(len(formats))]
}

func Fibonacci(a int, b int) (int, int){
	fmt.Printf("a=%d, b=%d\n", a, b)
	return a+b, a
}

