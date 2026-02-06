/* INSTRUÇÕES
    1. Ler a o nome e a nota de x alunos.
    2. Salvá-los num arquivo (nota: um aluno também terá um id em
       adição ao nome e nota).
    3. Ler os alunos do arquivo.

    Desafio bônus: salvar os nomes dos alunos em ordem alfabética.

    Se preocupar com tratamento de erros e segurança não é necessário
    para este exercício.
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "test.txt"

#define STUDENT_COUNT 5
#define STUDENT_NAME_MAX_LEN 80
typedef struct Student {
    char name[STUDENT_NAME_MAX_LEN];
    int grade;
    int id;
} Student;

bool comes_first(char *name, char *other)
{
    int i;
    for (i = 0; name[i] == other[i]; i++)
        ;
    return name[i] < other[i];
}

void sort_students(Student *students, int len)
{
    // Bubble sort é fácil de implementar e funciona bem o bastante
    // nesse caso

    bool found;
    do {
        bool changed = false;
        for (int i = 0; i < len - 1; i++) {
            if (!comes_first(students[i].name, students[i + 1].name)) {
                Student s = students[i];
                students[i] = students[i + 1];
                students[i + 1] = s;
                changed = true;
            }
        }
        found = !changed;
    } while (!found);
}

void get_input_and_write()
{
    Student students[STUDENT_COUNT];
    for (int i = 0; i < STUDENT_COUNT; i++) {
        students[i].id = (i + 1) * 123;

        printf("Insira o nome do estudante de ID %d: ", students[i].id);
        gets(students[i].name);

        printf("Insira a nota do estudante de ID %d: ", students[i].id);
        scanf("%d", &students[i].grade);

        // Descartar caracteres posteriores do input stream
        char ch;
        while ((ch = getchar()) != '\n' && ch == EOF)
            ;
    }

    sort_students(students, STUDENT_COUNT);

    // Formato:
    // id
    // nome
    // nota
    FILE *f;
    if ((f = fopen(FILE_NAME, "w")) == NULL) {
        return;
    }

    for (int i = 0; i < STUDENT_COUNT; i++) {
        Student s = students[i];
        fprintf(f, "%d\n%s\n%d\n", s.id, s.name, s.grade);
    }

    fclose(f);
}

void read_file_and_display()
{
    Student students[STUDENT_COUNT];
    FILE *f;
    if ((f = fopen(FILE_NAME, "r")) == NULL) {
        return;
    }

    for (int i = 0; i < STUDENT_COUNT; i++) {
        fscanf(f, "%d\n%s\n%d\n", &students[i].id, &students[i].name,
            &students[i].grade);
        Student sd = students[i];
        printf("ID: %d, nome: %s, nota: %d\n", sd.id, sd.name, sd.grade);
    }
    fclose(f);
}

int main()
{
    get_input_and_write();
    read_file_and_display();
    remove(FILE_NAME);

    return 0;
}
