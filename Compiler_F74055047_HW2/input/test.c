/*
 * 2019 Spring Compiler Course Assignment 2 
 */

float c = 1.5;

bool loop(int n, int m) {
    while (n > m) {
        n--;
    }
    return true;
}

int main() {
    // Declaration
    int x;
    int i;
    int a = (5 > b) + (b + 3);
    string y = "She is a girl";

    print(y); // print

    // if condition
    if (a > 10) {
        x += a;
        print(x);
    } else if (a == 10){
        x = a % 10 + 10 * 7; /* Arithmetic */
        print(x);
        if (1) {
            x += a;
            print(x);
        }
    }
    loop(x, i);
    print("Hello World");

    return 0; 
}
