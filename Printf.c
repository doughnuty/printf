#include <stdarg.h>
#include<fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/* This program converts/prints:
 * 1. int to signed decimal
 * 2. int to unsigned octal
 * 3. int to unsigned decimal
 * 4. int to unsigned hexadecimal
 * 5. int to unsigned char (writes resulting character)
 * 6. pointer to a string up to NUL
 * 7. void* in hexadecimal
 */
int my_printf(char *format,...); //main part of printf function
int my_putchar(int a); //putchar for printing args
int my_puts (char *s); //prints string
char* convert(unsigned long a, int base);  //converting decimal to octal, hexadecimal, etc.
void test_2() {
    printf("<#3>\n");
    char a = 'b';
    char* p = &a;
    int my_printf_ret_value = my_printf("%d - %d - %p!\n", 2048, 0, p);
    int printf_ret_value = printf("%d - %d - %p!\n", 2048, 0, p);
    printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? "RED" : "GREEN" , my_printf_ret_value, printf_ret_value, "NORMAL");
    printf("</#3>\n");
}
int main() {
    test_2();
}
int my_putchar(int a){
    write(1, &a, 1);
    return 1;
}
int my_puts (char *s){
    int i = 0;
    while (s && *s){
        my_putchar (*s++);
        i++;
    }
    return i;
}
char* convert(unsigned long a, int base){  //converting decimal to octal, hexadecimal, etc.
    if(a == 0) return "0";
    static char new[32] = {0};
    int i = 30;
    for(; a!= 0; i--){
        new[i] = "0123456789ABCDEF"[a % base];
        a /= base;
    }
    return &new[i+1];
}
int my_printf(char* restrict format, ...){
    void* p;
    char *inp;
    char *out;
    int number;
    int answer = 0;
    va_list arg;
    va_start(arg, format);

    for(inp = format; *inp != '\0'; inp++ ){
        while(*inp != '%' && *inp != '\0') {
            answer += my_putchar(*inp++);
        }
        if(*inp == '\0') break;

        inp++;
        switch(*inp){
            case 'd': number = va_arg(arg, int);
                if(number<0) {
                    number = -number;
                    answer += my_putchar('-');
                }
                answer += my_puts(convert(number, 10));
                break;
            case 'o': number = va_arg(arg, unsigned int);
                answer += my_puts(convert(number, 8));
                break;
            case 'u': number = va_arg(arg, unsigned int);
                answer += my_puts(convert(number, 10));
                break;
            case 'x': number = va_arg(arg, unsigned int);
                answer += my_puts(convert(number, 16));
                break;
            case 'c': number = va_arg(arg, int);
                answer += my_putchar(number);
                break;
            case 's': out = va_arg(arg, char*);
                answer += my_puts(out);
                break;
            case 'p': p = va_arg(arg, void*);
                answer += my_puts("0x");
                answer += my_puts(convert((unsigned long) p, 16));
                break;
        }
    }
    va_end(arg);
    return answer;
}