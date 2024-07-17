#ifndef rbt_hpp
#define rbt_hpp








#include <iostream>
#include <cmath>
#include <algorithm>

#include <utility>
#include <stdexcept>








class Tree {
private:
    class node;




public:
    static bool rbt;
    static bool verbose;




    Tree();

    Tree(const Tree&);
    ~Tree();

    void swap(Tree&);
    Tree(Tree&&);

    Tree& operator=(Tree);




    class iterator {
    public:
        iterator& operator++();
        iterator& operator--();
        iterator  operator++(int) { iterator copy(*this); ++(*this); return copy; }
        iterator  operator--(int) { iterator copy(*this); --(*this); return copy; }

        friend bool operator==(const iterator& it1, const iterator& it2) {
            return (it1.curr == it2.curr) && (it1.container == it2.container);
        }
        friend bool operator!=(const iterator& it1, const iterator& it2) {
            return (it1.curr != it2.curr) || (it1.container != it2.container);
        }

        const int& operator*() const { return curr->val; }


    private:
        const Tree* container;
        node* curr;

        iterator(const Tree* t, node* n) : container(t), curr(n) {}

        friend Tree;
    };

    using const_iterator = iterator;




    size_t size() const;
    void print() const;

    iterator find(int) const;

    iterator begin() const;
    iterator end() const;

    void insert(int);
    void erase(iterator);




private:
    node* root;
    size_t sz;




    node* insert_without_balancing(int);


    void insert_nodes_below(node*);
    void delete_nodes_below(node*);

    void help_print(node*, size_t, size_t) const;




    void ccw_rotate(node*);
    void cw_rotate(node*);

    void correct_double_red_at(node*);
    void correct_double_black_at(node*);




    class node {
        enum class Color { red, black, double_black };


        int val;

        node* parent;
        node* left;
        node* right;

        Color color;


        node(int v) : val(v), parent(nullptr), left(nullptr), right(nullptr), color(Color::red) {}


        bool is_left_child();
        bool is_right_child();
        bool has_no_children();

        bool is_red();
        bool is_black();

        void make_red();
        void make_black();
        void make_double_black();

        node* get_sibling();
        node* get_parent();
        node* get_auncle();
        node* get_grandparent();


        node* far_left() {
            node* n = this;

            while (n->left) {
                n = n->left;
            }
            return n;
        }

        node* far_right() {
            node* n = this;

            while (n->right) {
                n = n->right;
            }
            return n;
        }


        bool insert_node(node*);


        friend Tree;
        friend iterator;
    };
};




#endif /* rbt_hpp */
