package main

import (
	"fmt"
	"os/exec"
)

func readMod(name string) string {
	cmd := exec.Command("sh", "-c", "cat /proc/"+name)
	out, err := cmd.CombinedOutput()
	if err != nil {
		return "Error en la lectura de modulo " + name
	}
	output := string(out[:])

	return output
}

func main() {
	fmt.Println(readMod("ram_201800712"))
}
