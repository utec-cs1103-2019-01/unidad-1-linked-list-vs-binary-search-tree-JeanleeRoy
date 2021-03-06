//
// Created by ruben on 4/5/19.
//

#include "LinkedList.h"

UTEC::Node::Node(const Location & data):data{data}, right{nullptr}, left{nullptr}{}

UTEC::LinkedList::LinkedList():head{nullptr}, tail{nullptr}{};
UTEC::LinkedList::~LinkedList() {
    Node* temp = head;
    while (temp->right != nullptr){
        delete temp;
        temp = temp->right;
    }
    delete temp;
}

int UTEC::LinkedList::size() {
    int count = 0;
    Node* actual = head;
    while(actual != nullptr) {
        count++;
        actual = actual->right;
    }
    return count;
}

bool UTEC::LinkedList::is_empty() {
    return head == nullptr;
}

UTEC::Node *UTEC::LinkedList::get_head() {return head;}

UTEC::Node *UTEC::LinkedList::get_tail() { return tail;}

void UTEC::LinkedList::add_head(const Location& data) {
    Node* temp = new Node(data);
    if (is_empty()) {
        tail = temp;
        head = temp;
    } else {
        temp->right = head;
        head->left = temp;
        head = temp;
    }
}

void UTEC::LinkedList::add_tail(const Location& data) {
    Node* temp = new Node(data);
    if (is_empty()) {
        tail = temp;
        head = temp;
    } else {
        tail->right = temp;
        temp->left=tail;
        tail = temp;
    }
}
void UTEC::LinkedList::print(){
    if (is_empty())std::cout<<"La lista esta vacia"<<std::endl;
    else {
        Node* temp = head;
        while (temp != tail){
            temp->data.printLocation();
            temp = temp->right;
        }
        delete temp;
    }
}
void UTEC::LinkedList::insert(int position, const Location &data) {
    Node* inserted = new Node(data);
    Node* temp = head;
    for (int i = 1; i < position; ++i) {
        temp = temp->right;
    }
    inserted->left = temp;
    inserted->right = temp->right;
    temp->right = inserted;

}

UTEC::Node* UTEC::LinkedList::search(int position_id) {
    Node *temp = head;
    while (temp->data.get_id() != position_id) {
        temp = temp->right;
    }
    if (temp->right == nullptr) {
        return nullptr;
    } else {
        return temp;
    }
}
void UTEC::load_locations(UTEC::LinkedList *linked_list, std::string file_name) {
    std::ifstream documento(file_name);
    if (documento.is_open()) {
        std::string e[7];
        std::string linea;
        std::getline(documento, linea);
        while (!documento.eof()) {
            std::getline(documento, linea);
            std::istringstream iss(linea);
            unsigned int count = 0;
            while (std::getline(iss, linea, ',')) {
                e[count] = linea;
                count++;
            }
            Location nodeValue(std::stoi(e[0]), e[1], e[2], std::stod(e[3]), std::stod(e[4]), e[5], e[6]);
            linked_list->add_tail(nodeValue);
        }
    }
    documento.close();
}