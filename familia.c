#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_age(pid_t pid, int age) {
  printf("Processo %d com %d anos de idade.\n", pid, age);
}

int main() {
  pid_t pid1, pid2, gpid1, gpid2;
  int age = 0;

  printf("Processo pai nasceu.\n");
  print_age(getpid(), age++);

  pid1 = fork(); // Primeiro filho
  if (pid1 == 0) {
    // Código do primeiro filho
    sleep(14); // Pai tem o primeiro filho aos 14 anos
    printf("Primeiro filho nasceu.\n");
    print_age(getpid(), age++);

    gpid1 = fork(); // Primeiro neto
    if (gpid1 == 0) {
      // Código do primeiro neto
      sleep(12); // Primeiro neto morre aos 12 anos
      printf("Primeiro neto nasceu.\n");
      print_age(getpid(), age++);
      printf("Primeiro neto morreu aos 12 anos.\n");
      exit(0);
    }
    wait(NULL); // Esperar pelo primeiro neto
    printf("Primeiro filho morreu aos 30 anos.\n");
    exit(0);
  }

  pid2 = fork(); // Segundo filho
  if (pid2 == 0) {
    // Código do segundo filho
    sleep(16); // Pai tem o segundo filho aos 16 anos
    printf("Segundo filho nasceu.\n");
    print_age(getpid(), age++);

    gpid2 = fork(); // Segundo neto
    if (gpid2 == 0) {
      // Código do segundo neto
      sleep(18); // Segundo neto morre aos 18 anos
      printf("Segundo neto nasceu.\n");
      print_age(getpid(), age++);
      printf("Segundo neto morreu aos 18 anos.\n");
      exit(0);
    }
    wait(NULL); // Esperar pelo segundo neto
    printf("Segundo filho morreu aos 30 anos.\n");
    exit(0);
  }

  // Código do processo pai
  while (age <= 60) {
    sleep(1); // 1 ano = 1 segundo
    age++;
    if (age == 14 || age == 16) {
      printf("O pai tem um filho aos %d anos.\n", age);
    } else if (age == 26 || age == 30) {
      printf("O pai é avó novamente aos %d anos.\n", age);
    }
    print_age(getpid(), age);
  }

  // Esperar pelos filhos
  wait(NULL);
  wait(NULL);

  printf("Processo pai morreu aos 60 anos.\n");
  return 0;
}
