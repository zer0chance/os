#include <iostream>
#include <fstream>
#include <string>

typedef unsigned int uint;

std::string filename("data.dat");

// class Node 
// {
// public:
//     Node(){};
//     Node(std::string name, uint mark) : _next(NULL)   
//     {
//         this->_name = name;
//         this->_mark = mark;    
//     }
   
//     Node* next() const { return _next; }
//     std::string name() const { return _name; }
//     uint mark() const { return _mark; }
//     void info() const { std:: cout << "\n Name: " << _name << "\n Mark: " << _mark; }

//     void set_next(Node* node) { _next = node; }

// private:
//     Node* _next; 
//     std::string _name;
//     uint _mark;
// };

struct Node 
{
    Node() : next(NULL) {};
    Node(std::string name, uint mark) : next(NULL)   
    {
        this->name = name;
        this->mark = mark;    
    }

    void info() const { std:: cout << "\n Name: " << name << "\n Mark: " << mark; }

    Node* next; 
    std::string name;
    uint mark;
};

void serialize(Node* n)
{
    std::ofstream ofs(filename);
    while (n != NULL)
    {
        ofs.write(reinterpret_cast<char*>(n), sizeof(*n));
        n = n->next;
    }

    ofs.close();
}   

Node* deserialize()
{
    Node* head = NULL;
    Node* n;
    Node* m;
    
    std::ifstream ifs(filename);

    while(1)
    {
        n = new Node;
        ifs.read(reinterpret_cast<char*>(n), sizeof(*n));      
        if (ifs.gcount() < sizeof(Node)) break;
        
        if (head == NULL) 
            head = n;
        else 
            m->next = n;
    
        m = n;
    }

    ifs.close();
    return head;
}   

int main()
{
    Node* n1 = new Node("Mark", 4);
    Node* n2 = new Node("Stas", 5);
    Node* n3 = new Node("Vika", 3);
    n1->next = n2 ; n2->next = n3;
    std::cout << "\n Before serialization: ";
    n1->info();
    n2->info();
    n3->info();

    serialize(n1);

    std::cout << "\n After serialization: ";
    Node* head = deserialize();
    for(Node* n = head; n != NULL; n = n->next)
        n->info();

    return 0;
}