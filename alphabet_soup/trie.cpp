/**
 * @file trie.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include "trie.hpp"

Trie::Trie()
{
    // TODO
    _root = nullptr;
    _prefix = "";
    //
    assert(is_empty());
}

Trie::Trie(TrieNode::Ref root_node, std::string const &pref)
{
    // TODO
    _root = root_node;
    _prefix = pref;
    //
    assert(prefix() == pref);
}

Trie::Trie(std::istream &in) noexcept(false)
{
    // TODO
    std::string token;

    in >> token;
    if (token == "["){

        in >> token;
        if (token != "\""){
            throw std::runtime_error("Wrong input format");
        }

        _prefix = "";
        while (in >> token && token != "\""){
            try{
                _prefix += static_cast<char>(std::stoi(token, nullptr, 16));
            }catch(...){
                throw std::runtime_error("Wrong input format");
            }
        }

        if (token != "\""){
            throw std::runtime_error("Wrong input format");
        }

        _root = TrieNode::create(in);

        in >> token;
        if (token != "]"){
            throw std::runtime_error("Wrong input format");
        }

    }else if(token == "[]"){
        _prefix = "";
        _root = nullptr;

    }else{
        throw std::runtime_error("Wrong input format");
    }
    //
}

bool Trie::is_empty() const
{
    bool ret_v = true;
    // TODO
    ret_v = _root == nullptr;
    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    // TODO
    ret_val = _prefix;
    //
    return ret_val;
}

void Trie::set_prefix(const std::string &new_p)
{
    // TODO
    _prefix = new_p;
    //
    assert(prefix() == new_p);
}

bool Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    // TODO
    ret_val = _root->is_key();
    //
    return ret_val;
}

TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node;
    // TODO
    node = _root;
    //
    return node;
}

void Trie::set_root(TrieNode::Ref const &new_r)
{
    // TODO
    _root = new_r;
    //
    assert(root() == new_r);
}

bool Trie::has(std::string const &k) const
{
    assert(!is_empty());
    bool found = false;
    // TODO
    // Hint: use find_node() to do this.
    // Remember: The Trie can have a prefix==k but does not store the key k.

    TrieNode::Ref node = find_node(k);
    found = node != nullptr && node->is_key();

    //
    return found;
}

/**
 * @brief Helper function to retrieve the keys.
 *
 * This function does a recursive preorder traversal of the trie's nodes
 * keeping the current prefix and the retrieved keys as functions parameters.
 *
 * @param[in] node is the current node.
 * @param[in] prefix is the current prefix.
 * @param[in,out] keys are the retrieved keys.
 */
static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> &keys)
{
    // TODO
    // Remember: node->is_key() means the prefix is a key too.

    if (node->is_key()){
        keys.push_back(prefix);
    }

    node->goto_first_child();

    while (node->current_exists()){
        preorder_traversal(node->current_node(), prefix + node->current_symbol(), keys);
        node->goto_next_child();
    }

    //
}

void Trie::retrieve(std::vector<std::string> &keys) const
{
    assert(!is_empty());
    // TODO
    // Remember add the subtrie's prefix to the retrieve keys.
    preorder_traversal(_root, prefix(), keys);
    //
}

Trie Trie::child(std::string const &postfix) const
{
    assert(!is_empty());
    Trie ret_v;
    // TODO
    // Hint: use find_node() to follow the chain of nodes whose represent postfix.
    TrieNode::Ref node = find_node(postfix);
    if (node != nullptr){
        ret_v = Trie(node, postfix);
    }
    //
    assert(ret_v.is_empty() || ret_v.prefix() == (prefix() + postfix));
    return ret_v;
}

bool Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    // TODO
    ret_val = _root->current_exists();
    //
    return ret_val;
}

Trie Trie::current() const
{
    assert(current_exists());
    Trie ret_v;
    // TODO
    ret_v = Trie(root(), prefix() + current_symbol());
    //
    return ret_v;
}

char Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    // TODO
    symbol = _root->current_symbol();
    //
    return symbol;
}

void Trie::insert(std::string const &k)
{
    assert(k != "");
    // TODO

    if (is_empty()){
        _root = TrieNode::create(false);
    }

    TrieNode::Ref node = _root;

    for (size_t i = 0; i < k.size(); ++i){
        if (node->has(k[i])){
            node = node->child(k[i]);
        }else{
            TrieNode::Ref newNode = TrieNode::create(false);
            node->set_child(k[i], newNode);
            node = newNode;
        }
    }

    node->set_is_key_state(true);

    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const &pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    // TODO
    // Remember: the prefix "" must return the trie's root node.

    node = _root;
    
    size_t i = 0;
    while (i < pref.size() && node != nullptr){
        if (node->has(pref[i])){
            node = node->child(pref[i]);
            ++i;
        }else{
            node = nullptr;
        }
    }

    //
    return node;
}

std::ostream &
Trie::fold(std::ostream &out) const
{
    // TODO

    if (is_empty()){
        out << "[ ]";

    }else{

        out << "[ \" ";
        if (prefix() != ""){
            for (char c : prefix()){
                out << std::hex << static_cast<uint16_t>(c) << " ";
            }
        }
        out << "\" ";

        _root->fold(out);

        out << " ]";
    }

    //
    return out;
}

bool Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    // TODO
    found = _root->find_child(symbol);
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol() == symbol);
    return found;
}

void Trie::goto_first_symbol()
{
    assert(!is_empty());
    // TODO
    _root->goto_first_child();
    //
    assert(!current_exists() ||
           current().prefix() == (prefix() + current_symbol()));
}

void Trie::goto_next_symbol()
{
    assert(current_exists());
    // TODO
    _root->goto_next_child();
    //
}
