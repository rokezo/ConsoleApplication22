#include <iostream>
#include <string>

//1 завдяня

using namespace std;

class DomesticAnimal {
protected:
    string name;
    string characteristics;

public:
    DomesticAnimal(string name, string characteristics) : name(name), characteristics(characteristics) {}

    void showInfo() {
        cout << "Name: " << name << endl;
        cout << "Characteristics: " << characteristics << endl;
    }

    virtual void sound() = 0; 

class Dog : public DomesticAnimal {
public:
    Dog(string name, string characteristics) : DomesticAnimal(name, characteristics) {}

    void sound() override {
        cout << "Woof!" << endl;
    }
};

class Cat : public DomesticAnimal {
public:
    Cat(string name, string characteristics) : DomesticAnimal(name, characteristics) {}

    void sound() override {
        cout << "Meow!" << endl;
    }
};

class Parrot : public DomesticAnimal {
public:
    Parrot(string name, string characteristics) : DomesticAnimal(name, characteristics) {}

    void sound() override {
        cout << "Polly wants a cracker!" << endl;
    }
};

int main() {
    Dog dog("Buddy", "Friendly and loyal");
    Cat cat("Whiskers", "Playful and curious");
    Parrot parrot("Polly", "Colorful and chatty");

    dog.showInfo();
    dog.sound();

    cat.showInfo();
    cat.sound();

    parrot.showInfo();
    parrot.sound();

    return 0;
}



//2 завданя 

#include <iostream>
#include <string>

using namespace std;

class String {
protected:
    char* str;
    int length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* str) {
        length = strlen(str);
        this->str = new char[length + 1];
        strcpy(this->str, str);
    }

    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    int getLength() const {
        return length;
    }

    void clear() {
        delete[] str;
        str = nullptr;
        length = 0;
    }

    ~String() {
        delete[] str;
    }

    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, str);
        strcat(temp, other.str);
        delete[] str;
        str = temp;
        length += other.length;
        return *this;
    }

    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const String& str) {
        os << str.str;
        return os;
    }
};

class BitString : public String {
public:
    BitString(const char* str) : String(str) {
        for (int i = 0; i < length; i++) {
            if (str[i] != '0' && str[i] != '1') {
                throw invalid_argument("Invalid bit string");
            }
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        String::operator=(other);
        return *this;
    }
};

int main() {
    String str1("Hello");
    String str2(" World");

    cout << str1 + str2 << endl;

    BitString bitStr("101010");
    try {
        BitString invalidBitStr("123");
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}