#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

typedef unsigned int uint;

static constexpr char* filename((char*)"data.dat");

class StudentMarks
{
private:
    struct Node
    {
        Node() : next(NULL) {};
        Node(char* name, uint mark) : next(NULL)
        {
            this->name = name;
            this->mark = mark;
        }

        void info() const { std:: cout << "\n " << name << ": " << mark; }

        Node* next;
        char* name;
        uint mark;
    };

    Node* head;
    Node* tail;

public:
    StudentMarks() : head(NULL), tail(NULL) {}
    void print_list() const { for (Node* n = head; n != NULL; n = n->next) n->info(); }

    void append(char* name, uint mark) {
        if (head == NULL) { head = new Node(name, mark); tail = head; }
        else { tail->next = new Node(name, mark); tail = tail->next; }
    }
    void append(Node* n) {
        if (head == NULL) { head = new Node(*n); tail = head; }
        else { tail->next = new Node(*n); tail = tail->next; }
    }

    void insert(char* name, uint mark, uint pos) {
        if (pos == 0) {
            Node* new_node = new Node(name, mark);
            new_node->next = head;
            head = new_node;
        } else {
            Node* n = head;
            uint count = 0;
            
            while (count < pos - 1)
            {
                assert(n->next != NULL);
                n = n->next;
                count++;
            }
            
            Node* new_node = new Node(name, mark);
            new_node->next = n->next;
            n->next = new_node;
        }    
    }

    void remove(uint pos) {
        if (pos == 0) {
            Node* t = head;
            head = head->next;
            delete t;
        } else {
            Node* n = head;
            uint count = 0;
            
            while (count < pos - 1)
            {
                assert(n->next != NULL);
                n = n->next;
                count++;
            }
            
            Node* t = n->next;
            n->next = t->next;
            delete t;
        }    
    }

    void operator[](uint pos) const
    {
        Node* n = head;
        uint count = 0;

        while (count != pos)
        {
            assert(n->next != NULL);
            n = n->next;
            count++;
        }
        n->info();
    }

    void free_list() { 
        Node* t;
        Node* n = head;
        while(n != NULL) 
        {
            t = n->next;
            delete n;
            n = t; 
        }
        head = NULL; 
        tail = NULL;
    }

    void serialize() const
    {
        std::ofstream ofs(filename);
        
        Node* n = head;
        while (n != NULL)
        {
            ofs.write(reinterpret_cast<char*>(n), sizeof(*n));
            n = n->next;
        }

        ofs.close();
    }   

    void deserialize()
    {
        free_list();
        std::ifstream ifs(filename);

        while(!ifs.eof()) {
            Node* n = new Node;
            if(ifs.read(reinterpret_cast<char*>(n), sizeof(*n)).gcount() < sizeof(*n)) { delete n; break; }   
            append(n);
            delete n;
        }

        ifs.close();
    }
};


int main()
{
    StudentMarks sm;
    sm.append((char*)"Max", 4);
    sm.append((char*)"Julia", 5);
    sm.append((char*)"Ugin", 3);

    sm.insert((char*)"Pavel", 5, 0);
    sm.insert((char*)"Stepan", 2, 2);
    std::cout << "\n Before serialization: ";
    sm.print_list();

    sm.serialize();
    sm.deserialize();

    std::cout << "\n\n After serialization: ";
    sm.print_list();

    std::cout << "\n\n Second student: ";
    sm[2];

    sm.remove(2);

    std::cout << "\n\n Result: ";
    sm.print_list();

    sm.free_list();
    return 0;
}