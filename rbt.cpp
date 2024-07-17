#include "rbt.hpp"




bool Tree::rbt     = true;
bool Tree::verbose = false;




Tree::Tree() : root(nullptr), sz(0) {}


size_t Tree::size() const { return sz; }




Tree::node* Tree::insert_without_balancing(int val) {
    //
    node* new_node = new node(val);
    
    if(root)
    {
        if   (root->insert_node(new_node)){ ++sz; }
        else { return nullptr; }
    }
    else
    {
        root = new_node;
        ++sz;
    }
    
    return new_node;
}

bool Tree::node::insert_node(node* n) {
    //
    if(n->val < val)
    {
        if(left)
        {
            return left->insert_node(n);
        }
        else
        {
            left = n;
            n->parent = this;
            return true;
        }
    }
    
    if(n->val > val)
    {
        if(right)
        {
            return right->insert_node(n);
        }
        else
        {
            right = n;
            n->parent = this;
            return true;
        }
    }
    
    else
    {
        delete n;
        return false;
    }
}




void Tree::insert_nodes_below(node* n) {
    insert_without_balancing(n->val);
    if (n->left)  { insert_nodes_below(n->left);  }
    if (n->right) { insert_nodes_below(n->right); }
}
void Tree::delete_nodes_below(node* n) {
    //
    if(n->left) { delete_nodes_below(n->left); }
    if(n->right) { delete_nodes_below(n->right); }
    delete n;
}

Tree::Tree(const Tree& other) : Tree() {
    if (other.root) {
        insert_nodes_below(other.root);
    }

    if (rbt) {
        //
        iterator a = this->begin();
        iterator b = other.begin();
        // increment both iterators simulataneously to keep them synchronized
        while(a != this->end() && b != other.end())
        {
            a.curr->color = b.curr->color;
            a++;
            b++;
        }
    }
        
}
Tree::~Tree() {
    if(root){
        delete_nodes_below(root);
    }
}

void Tree::help_print(node* n, size_t depth, size_t spaces) const {
    //
    if (n->right){ help_print(n->right, depth + 1, spaces); }
        
    for (size_t i = 0; i < depth*spaces; ++i){ std::cout << ' '; }

    if (n->parent){
        if (n->val > n->parent->val) { std::cout << '/'; }
        else { std::cout << '\\'; }
    }
    else { std::cout << '-'; }
    
    
    if (rbt){
        if(n->color == node::Color::black) { std::cout << "(b) "; }
        if(n->color == node::Color::red) { std::cout << "(r) "; }
    }
    
    std::cout << n->val << '\n';
    
    if (n->left) { help_print(n->left, depth + 1, spaces); }
    
}
void Tree::print() const {
    //
    
    if (root)
    {
        int max = std::max(std::abs(root->far_right()->val), std::abs(root->far_left()->val));
        int spaces;
        
        if (rbt) { spaces = 7; }
        else { spaces = 3; }
        
        help_print(root, 0, std::log10(max) + spaces);
    }
    std::cout << '\n';
    
}




void Tree::swap(Tree& other) {
    std::swap(root, other.root);
}
Tree::Tree(Tree&& other) : Tree() {
    swap(other);
}
Tree& Tree::operator=(Tree other) {
    swap(other);
    return *this;
}




Tree::iterator Tree::begin() const {
    if (root) {
        return iterator(this, root->far_left());
    }
    return iterator(this, nullptr);
}
Tree::iterator Tree::end() const {
    return iterator(this, nullptr);
}




Tree::iterator Tree::find(int val) const {
    //
    auto curr_node = root;
        
    while(curr_node)
    {
        if(curr_node->val == val)
        {
            return iterator(this, curr_node);
        }
        
        if(curr_node->val < val)
        {
            curr_node = curr_node->right;
        }
        else
        {
            curr_node = curr_node->left;
        }
    }
    return iterator(this, nullptr);
}




Tree::iterator& Tree::iterator::operator++() {
    if (!container) {
        throw std::logic_error("you asked to increment an invalid iterator");
    }

    if (!curr) {
        if (container->root) {
            curr = container->root->far_left();
        }
        return *this;
    }
    
    if(container->root->far_right() == curr)
        {
            curr = nullptr;
        }
        
        else if(curr->right)
        {
            curr = curr->right->far_left();
        }
        else
        {
            while(curr->parent)
            {
                if(curr->parent->left == curr) // curr->parent->val > curr->val
                {
                    curr = curr->parent;
                    break;
                }
                else
                {
                    curr = curr->parent;
                }
                
            }
        }

    //
    return *this;
}

Tree::iterator& Tree::iterator::operator--() {
    if (!container) {
        throw std::logic_error("you asked to decrement an invalid iterator");
    }

    if (!curr) {
        if (container->root) {
            curr = container->root->far_right();
        }
        return *this;
    }
    
    if(container->root->far_left() == curr)
        {
            curr = nullptr;
        }
        
        else if(curr->left)
        {
            curr = curr->left->far_right();
        }
        else
        {
            while(curr->parent)
            {
                if(curr->parent->right == curr)  // curr->parent->val < curr->val
                {
                    curr = curr->parent;
                    break;
                }
                else
                {
                    curr = curr->parent;
                }
                
            }
        }

    //
    return *this;
}



bool Tree::node::is_left_child(){
    if(parent)
    {
        return parent->left == this;
    }
    return false;
}

bool Tree::node::is_right_child(){
    if(parent)
    {
        return parent->right == this;
    }
    return false;
}

bool Tree::node::has_no_children(){
    return left == nullptr && right == nullptr;
}

bool Tree::node::is_red(){
    return color == node::Color::red;
}

bool Tree::node::is_black(){
    return color == node::Color::black;
}

void Tree::node::make_red(){ color = node::Color::red; }

void Tree::node::make_black(){ color = node::Color::black; }

void Tree::node::make_double_black(){ color = node::Color::double_black; }

Tree::node* Tree::node::get_sibling() {
    
    if(parent){
        
        if(is_left_child())
        {
            return parent->right;
        }
        else
        {
            return parent->left;
        }
    }
    else
    {
        throw std::logic_error("you asked for the sibling of a node without a parent");
    }
    
}
Tree::node* Tree::node::get_parent() { return parent; }

Tree::node* Tree::node::get_auncle() {

    if(get_grandparent())
    {
        return get_parent()->get_sibling();
    }
    else
    {
        throw std::logic_error("you asked for the auncle of a node without a grandparent");
    }
}
Tree::node* Tree::node::get_grandparent() {
    
    if(get_parent())
    {
        return get_parent()->get_parent();
    }
    else
    {
        throw std::logic_error("you asked for the grandparent of a node without a parent");
    }
}


/*
     p             p
     |             |
     n      =>     r
    / \           / \
   l   r         n  rr
      / \       / \
     rl rr     l  rl
*/
void Tree::ccw_rotate(node* n) {
    
    if(n->right) {
        
        if(n->parent)
        {
            n->right->parent = n->parent; // n's right node R gets n's parent (r's parent is now p)
            
            if(n->parent->right == n)
            {
                n->parent->right = n->right; // the right of n's parent becomes R
            }
            else
            {
                n->parent->left = n->right; // the left of n's parent becomes L
            }
            
        }
        
        else
        {
            n->right->parent = nullptr; // n->parent
            root = n->right;
        }
        
        n->parent = n->right; // n's parent becomes r
        
        if(n->right->left)
        {
            auto rl = n->right->left; // make a copy of rl
            
            n->right->left = n; // r gets n as its left
            
            rl->parent = n; // rl's parent gets n
                
            n->right = rl; // n's right becomes rl
        }
        else
        {
            n->right->left = n;
            n->right = nullptr;
        }
        
        
    }
    else
    {
        throw std::logic_error("you attempted a ccw rotation on a node without a right child");
    }
    
}

/*
       p         p
       |         |
       n    =>   l
      / \       / \
     l   r     ll  n
    / \           / \
   ll lr         lr  r
*/

void Tree::cw_rotate(node* n) {
    
    if(n->left) {
        
        if(n->parent)
        {
            n->left->parent = n->parent; // n's right node R gets n's parent (r's parent is now p)
            
            if(n->parent->left == n)
            {
                n->parent->left = n->left; // the right of n's parent becomes R
            }
            else
            {
                n->parent->right = n->left; // the left of n's parent becomes L
            }
            
        }
        else
        {
            n->left->parent = nullptr; // n->parent
            root = n->left;
        }
        
        n->parent = n->left;
        
        if(n->left->right)
        {
            auto lr = n->left->right;
            
            n->left->right = n;
                
            lr->parent = n;
                
            n->left = lr;
            
        }
        else
        {
            n->left->right = n;
            n->left = nullptr;
        }
        

    }
    else
    {
        throw std::logic_error("you attempted a cw rotation on a node without a left child");
    }
    
}
    



void Tree::correct_double_red_at(node* n) {
    if(n == nullptr){ return; }
    
    // case 0
    if(n == root)
    {
        if(verbose)
        {
            std::cout << "dr case 0: at root" << std::endl;
        }
        n->color = node::Color::black; // make the root black
        return;
    }

    
    // case 1
    if(n->parent->color == node::Color::black)
    {
        if(verbose)
        {
            std::cout << "dr case 1: black parent" << std::endl;
        }
        return;
    }
        
        
    // case 2
    if(n->get_auncle())
    {
        if(n->get_auncle()->color == node::Color::red)
        {
            if(verbose)
            {
                std::cout << "dr case 2: red parent, red auncle" << std::endl;
            }
            n->parent->color = node::Color::black; // make parent black
            n->get_auncle()->color = node::Color::black; // make auncle black
            n->get_grandparent()->color = node::Color::red; // make the grandparent red
            correct_double_red_at(n->get_grandparent()); // recurse to fix potential double red
            return;
        }
    }
    if(!(n->get_auncle()) || n->get_auncle()->color == node::Color::black)
    {
        if(n->parent->is_left_child() == n->is_left_child())
        {
        // case 3
            if(verbose)
            {
                std::cout << "dr case 3: red parent, black auncle, n and p are same-sided children" << std::endl;
            }
            n->parent->color = node::Color::black;
            n->get_grandparent()->color = node::Color::red;
            
            if(n->parent->is_right_child())
            {
                ccw_rotate(n->get_grandparent());
            }
            else
            {
                cw_rotate(n->get_grandparent());
            }
        }
        else
        {
            // case 4
            if(verbose)
            {
                std::cout << "dr case 4: red parent, black auncle, n and p are other-side children" << std::endl;
            }
            
            if(n->is_right_child())
            {
                ccw_rotate(n->parent);
                correct_double_red_at(n->left);
                return;
            }
            else
            {
                cw_rotate(n->parent);
                correct_double_red_at(n->right);
                return;
            }
        }
            
    }
        
    

}


void Tree::insert(int val) {
    auto node = insert_without_balancing(val);
    if(rbt)
    {
        correct_double_red_at(node);
    }
}







void Tree::erase(iterator it) {
    if (!it.curr || (it.container != this)) {
        throw std::logic_error("you asked to erase an element using an invalid iterator");
    }

    if (it.curr->left) {
        it.curr->val = it.curr->left->far_right()->val;
        erase(--it);
        return;
    }
    if (it.curr->right) {
        it.curr->val = it.curr->right->far_left()->val;
        erase(++it);
        return;
    }
    if (it.curr == root) {
        delete root; root = nullptr; --sz;
        return;
    }


    if (rbt) {
        if (it.curr->is_black()) {
            it.curr->make_double_black();
            correct_double_black_at(it.curr);
        }
    }


    if (it.curr->is_left_child()) {
        it.curr->parent->left = nullptr;
    }
    else {
        it.curr->parent->right = nullptr;
    }
    delete it.curr; --sz;
}




void Tree::correct_double_black_at(node* n) {
    if (n == root) {
        if (verbose) {
            std::cout << "db case 0: at root\n";  // Lindstrom's I.
        }

//         A double-black node warns us that we need to
//
//          - lower the black depth of parent->sibling branches by 1
//            while preserving the black depth of the grandparent->sibling branches;
//
//         or
//
//          - increase the black depth of ?->node branches by 1
//            while preserving the black depth of all other branches.
//
//         When we're at the root there are no
//         parent->sibling or grandparent->sibling branches,
//         so we can accomplish the first goal by doing nothing.

        n->make_black();
        return;
    }


//     By reaching here,
//     we know n has a parent.
    node* p = n->get_parent();
//
//     n has a sibling because...
    node* s = n->get_sibling();
//
//     1) When correct_double_black_at is originally called,
//        it is called on a previously black node, and
//        one sees that black, non-root nodes always have siblings
//        by considering the black depth of their parents.
//
//     2) Each case that uses recursion (cases 1, 3, and 6)
//        either
//               i) does an operation that
//                  preserves black depths and
//                  calls correct_double_black_at
//                  on the same node
//                  (case 1 and case 6);
//        or
//              ii) calls correct_double_black_at
//                  on a previously black node
//                  closer to the root while
//                  creating an inbalance below
//                  (case 3).


    if (s->is_red()) {
        if (verbose) {
            std::cout << "db case 1: sibling is red\n";  // Lindstrom's II.
        }

//         The sibling is red.
//         Change it.
        s->make_black();

//         Since the sibling is red,
//         the parent is black.
//         Change it.
        p->make_red();

        if  (n->is_left_child()) { ccw_rotate(p); }
        else                     {  cw_rotate(p); }

//         The problem has not been fixed,
//         but we've reduced to another case:
//         the parent is now red,
//         so the sibling must be black.
//         Moreover, since the operation above
//         preserved black depths,
//         this sibling cannot be the external node.
        correct_double_black_at(n);
        return;
    }


//     By reaching here,
//     we know n's sibling is black.

    if ((!s->left || s->left->is_black()) && (!s->right || s->right->is_black())) {
        n->make_black();
        s->make_red();

        if (p->is_red()) {
            if (verbose) {
                std::cout << "db case 2: sibling is black with black children, parent is red\n";  // Lindstrom's V.A.
            }

            p->make_black();

//             We've successfully
//              - lowered the black depth of
//                parent->sibling branches and
//              - preserved the black depth of
//                grandparent->sibling branches.
            return;
        }
        else {
            if (verbose) {
                std::cout << "db case 3: sibling is black with black children, parent is black\n";  // Lindstrom's V.B.
            }

            p->make_double_black();

//             We've successfully
//              - lowered the black depth of
//                parent->sibling branches.
//
//             However, we've also
//              - lowered the black depth of
//                grandparent->sibling branches,
//
//             so we need to lower
//             the black depth of
//             grandparent->auncle branches.

            correct_double_black_at(p);

//             Note: above p, the tree has not changed,
//             so p, which used to be black,
//             is either the root or has a sibling.
            return;
        }
    }

//     By reaching here,
//     we know n's sibling is black with a red child.

    if (n->is_left_child()) {
        if (s->right && s->right->is_red()) {

            n->make_black();
            s->right->make_black();

            if (p->is_red()) {
                if (verbose) {
                     // Lindstrom's IV.A.
                    std::cout << "db case 4: sibling is black with a red child which is other-sided to n, parent is red\n";
                }

                s->make_red();
                p->make_black();
            }
            else {
                if (verbose) {
                     // Lindstrom's IV.B.
                    std::cout << "db case 5: sibling is black with a red child which is other-sided to n, parent is black\n";
                }
            }

            ccw_rotate(p);

//             We've successfully
//              - increased the black depth of ?->node branches and
//              - preserved the black depth of all other branches.
            return;
        }
        else {
            if (verbose) {
                 // Lindstrom's III.
                std::cout << "db case 6: sibling is black with a red child which is the same-sided as n\n";
            }

            s->left->make_black();
            s->make_red();
            cw_rotate(s);

//             The problem has not been fixed,
//             but we've reduced to another case:
//             it has a black sibling with a
//             red child which is other-sided to n,
//             case 4 or 5.
            correct_double_black_at(n);
            return;
        }
    }
    else {
         // The same with left/right and ccw/cw swapped...

        if (s->left && s->left->is_red()) {

            n->make_black();
            s->left->make_black();

            if (p->is_red()) {
                if (verbose) {
                     // Lindstrom's IV.A.
                    std::cout << "db case 4: sibling is black with a red child which is other-sided to n, parent is red\n";
                }

                s->make_red();
                p->make_black();
            }
            else {
                if (verbose) {
                     // Lindstrom's IV.B.
                    std::cout << "db case 5: sibling is black with a red child which is other-sided to n, parent is black\n";
                }
            }

            cw_rotate(p);
            return;
        }
        else {
            if (verbose) {
                 // Lindstrom's III.
                std::cout << "db case 6: sibling is black with a red child which is the same-sided as n\n";
            }

            s->right->make_black();
            s->make_red();
            ccw_rotate(s);

            correct_double_black_at(n);
            return;
        }
    }
}

