#include <iostream>
#include <thread>

using namespace std;

void fun_1() {
    cout << "Hilo #1 : " << this_thread::get_id() << endl;
}

void fun_2() {
    cout << "Hilo #2 : " << this_thread::get_id() << endl;
}

void fun_3() {
    cout << "Hilo #2 : " << this_thread::get_id() << endl;
}

void saludar(const string& nombre) {
    cout << "Hola " << nombre << "!!!\n";
}

void sumar(int a, int b, int& total) {
    total = a + b;
//    cout << "Hilo de Sumar: " << this_thread::get_id() << endl;
}

void ejemplo_1() {
    std::cout << "Hilo Principal: " << this_thread::get_id() << std::endl;
    fun_1();
    fun_2();
    fun_3();
    thread t1(fun_1);
    thread t2(fun_2);
    thread t3(fun_3);
    t1.join();
    t2.join();
    t3.join();
}

void ejemplo_2() {
    thread t1;
    t1 = thread(saludar, "Jose");
    t1.join();
}

void ejemplo_3() {
    int x = 0;
    thread t1;
    t1 = thread(sumar, 10, 20, ref(x));
    t1.join();
    cout << x << endl;
//    cout << "Hilo de Ejemplo 3: " << this_thread::get_id() << endl;
}

void ejemplo_lambda() {
    int x = 0;
    int y = 0;
    int z = 0;

    auto lambda = [&](int a, int b, int c){
        x *= a;
        y *= b;
        z *= c;
        cout << x << y << z << endl;
    };
    lambda(1, 2, 3);
}

void ejemplo_4() {
    int total = 0;
    thread t1;
    t1 = thread([&]{ sumar(10, 20, total); });
    t1.join();
    cout << total << endl;
}

struct A {
    void metodo_1() {
        cout << "metodo_1" << endl;
    }
    void saludar(const string& nombre) {
        cout << "Hola " << nombre << "!!!\n";
    }

    void sumar(int a, int b, int& total) {
        total = a + b;
    }

    void metodo_2() {
        thread t1;
        t1 = thread([&](){ this->metodo_1(); });
        t1.join();
    }

    void metodo_3() {
        thread t1;
        int total = 0;
        t1 = thread(&A::sumar, this, 30, 40, ref(total));
        t1.join();
        cout << total;
    }

    void metodo_4() {
        thread t1;
        int total = 0;
        t1 = thread([&]{ this->sumar(30, 40, total); });
        t1.join();
        cout << total;
    }
};

void ejemplo_5() {
    thread t1;
    A a;
    t1 = thread([&a](){ a.metodo_1(); });
    t1.join();
}

void ejemplo_6() {
    thread t1;
    A a;
    t1 = thread(&A::metodo_1, &a);
    t1.join();

    t1 = thread(&A::saludar, &a, "Maria");
    t1.join();

    int total = 0;
    t1 = thread(&A::sumar, &a, 20, 60, ref(total));
    t1.join();
    cout << total << endl;

    a.metodo_2();
    a.metodo_3();
    a.metodo_4();
}

int main() {
    cout << "Hilo de main: " << this_thread::get_id() << endl;
//    ejemplo_2();
//    ejemplo_3();
//    ejemplo_4();
//    ejemplo_5();
    ejemplo_6();
    return 0;
}
