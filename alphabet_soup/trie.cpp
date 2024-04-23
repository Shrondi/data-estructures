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

    //
    assert(is_empty());
}

Trie::Trie(TrieNode::Ref root_node, std::string const &pref)
{
    // TODO

    //
    assert(prefix() == pref);
}

Trie::Trie(std::istream &in) noexcept(false)
{
    // TODO

    //
}

bool Trie::is_empty() const
{
    bool ret_v = true;
    // TODO

    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    // TODO

    //
    return ret_val;
}

void Trie::set_prefix(const std::string &new_p)
{
    // TODO

    //
    assert(prefix() == new_p);
}

bool Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    // TODO

    //
    return ret_val;
}

TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node;
    // TODO

    //
    return node;
}

void Trie::set_root(TrieNode::Ref const &new_r)
{
    // TODO

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

    //
}

void Trie::retrieve(std::vector<std::string> &keys) const
{
    assert(!is_empty());
    // TODO
    // Remember add the subtrie's prefix to the retrieve keys.

    //
}

Trie Trie::child(std::string const &postfix) const
{
    assert(!is_empty());
    Trie ret_v;
    // TODO
    // Hint: use find_node() to follow the chain of nodes whose represent postfix.

    //
    assert(ret_v.is_empty() || ret_v.prefix() == (prefix() + postfix));
    return ret_v;
}

bool Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    // TODO

    //
    return ret_val;
}

Trie Trie::current() const
{
    assert(current_exists());
    Trie ret_v;
    // TODO

    //
    return ret_v;
}

char Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    // TODO

    //
    return symbol;
}

void Trie::insert(std::string const &k)
{
    assert(k != "");
    // TODO

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

    //
    return node;
}

std::ostream &
Trie::fold(std::ostream &out) const
{
    // TODO

    //
    return out;
}

bool Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    // TODO

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

    //
    assert(!current_exists() ||
           current().prefix() == (prefix() + current_symbol()));
}

void Trie::goto_next_symbol()
{
    assert(current_exists());
    // TODO

    //
}
