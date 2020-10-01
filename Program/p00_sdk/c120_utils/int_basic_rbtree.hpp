/* ********* * ********* * ********* * ********* * *********
 *
 * int_basic_rbtree.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: basic Red Black Tree struct for other container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_BASIC_RBTREE_HPP__)
#define __INT_BASIC_RBTREE_HPP__

#include "int_basic_slot_allocator.hpp"
#include "int_pair.hpp"

namespace std
{

namespace std_rbtree
{

struct rbtree_dummy_type
{};

template<typename Key_Ty, typename Val_Ty = rbtree_dummy_type>
class rbtree;

typedef boole RB_TREE_COLOR;
#define RB_TREE_BLACK (boole_false)
#define RB_TREE_RED   (boole_true)

template<typename Key_Ty, typename Val_Ty = rbtree_dummy_type>
class rbtree_node;

class rbtree_base_node;

class rbtree_base_iter;

template<typename Ctnr_Ty>
class rbtree_iter;

template<typename Ctnr_Ty>
class rbtree_ritr;

template<typename Ctnr_Ty>
class rbtree_const_iter;

template<typename Ctnr_Ty>
class rbtree_const_ritr;

class rbtree_base_node
{
public:
    rbtree_base_node() :
        prnt(nullptr),
        left(nullptr),
        right(nullptr),
        color(RB_TREE_RED)
    {}

    rbtree_base_node(rbtree_base_node *p, rbtree_base_node *l, rbtree_base_node *r, RB_TREE_COLOR c) :
        prnt(p),
        left(l),
        right(r),
        color(c)
    {}

    ~rbtree_base_node() = default;

    bool i_am_left() const noexcept
    {
        assert(prnt);
        return this == prnt->left;
    }

    bool i_am_right() const noexcept
    {
        assert(prnt);
        return this == prnt->right;
    }

    rbtree_base_node *&parent_arm() noexcept
    {
        assert(prnt);
        return i_am_left() ? prnt->left : prnt->right;
    }

    rbtree_base_node *mysibling() const noexcept
    {
        return this == prnt->left ? prnt->right : prnt->left;
    }

    rbtree_base_node *prnt;
    rbtree_base_node *left;
    rbtree_base_node *right;
    RB_TREE_COLOR     color;
};

template<typename Key_Ty>
class rbtree_node<Key_Ty, rbtree_dummy_type> : public rbtree_base_node
{
public:
    using NodeData_Ty = const Key_Ty;

public:
    rbtree_node(const Key_Ty &k) :
        rbtree_base_node(),
        key(k)
    {}

    ~rbtree_node() noexcept
    {}

    Key_Ty &mykey() noexcept
    {
        return key;
    }

    const Key_Ty *mydata() const noexcept
    {
        return &key;
    }

private:
    Key_Ty key;
};

template<typename Key_Ty, typename Val_Ty>
class rbtree_node : public rbtree_base_node
{
public:
    using NodeData_Ty = pair<const Key_Ty, Val_Ty>;

public:
    rbtree_node(const Key_Ty &k, const Val_Ty &v) :
        rbtree_base_node(),
        duo(k, v)
    {}

    rbtree_node(const Key_Ty &k, Val_Ty &&v) :
        rbtree_base_node(),
        duo(k, v)
    {}

    rbtree_node(const Key_Ty &k) :
        rbtree_base_node(),
        duo(k)
    {}

    ~rbtree_node() noexcept
    {}

    const Key_Ty &mykey() const noexcept
    {
        return duo.first;
    }

    pair<Key_Ty, Val_Ty> &mypair() noexcept
    {
        return duo;
    }

    pair<const Key_Ty, Val_Ty> *mydata() noexcept
    {
        return pointer_convert(&duo, 0, NodeData_Ty*);
    }

private:
    pair<Key_Ty, Val_Ty> duo;
};

class rbtree_base_iter
{
    template<typename Key_Ty> friend class set;
    template<typename Key_Ty, typename Val_Ty> friend class map;

public:
    void _search_next() noexcept
    {
        assert(node);
        if (node->prnt == nullptr)
        {
            while (node->left)
            {
                node = node->left;
            }
        }
        else if (node->right)
        {
            node = node->right;
            while (node->left)
            {
                node = node->left;
            }
        }
        else
        {
            while (node->i_am_right())
            {
                node = node->prnt;
            }
            node = node->prnt;
        }
    }

    void _search_prev() noexcept
    {
        assert(node);
        if (node->prnt == nullptr)
        {
            if (node->left)
            {
                node = node->left;
            }
            while (node->right)
            {
                node = node->right;
            }
        }
        else if (node->left)
        {
            node = node->left;
            while (node->right)
            {
                node = node->right;
            }
        }
        else
        {
            while (node->prnt && node->i_am_left())
            {
                node = node->prnt;
            }
            if (node->prnt)
            {
                node = node->prnt;
            }
        }
    }

    rbtree_base_iter(rbtree_base_node *p_nod) :
        node(p_nod)
    {}

    ~rbtree_base_iter() = default;

    rbtree_base_node *node;
};

template<typename Key_Ty, typename Val_Ty>
class rbtree_iter<rbtree<Key_Ty, Val_Ty>> : public rbtree_base_iter
{
    friend class rbtree<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class set;
    template<typename Key_Ty, typename Val_Ty> friend class map;

    using Container_Ty = rbtree<Key_Ty, Val_Ty>;
    using Self_Ty = rbtree_iter<Container_Ty>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    rbtree_iter() :
        rbtree_base_iter(nullptr)
    {}

    rbtree_iter(const Self_Ty &rhs) :
        rbtree_base_iter(rhs.node)
    {}

    rbtree_iter(Node_Ty *p_nod) :
        rbtree_base_iter(p_nod)
    {}

    ~rbtree_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        _search_next();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        _search_prev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        _search_next();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        _search_prev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    NodeData_Ty *operator ->() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }

    NodeData_Ty &operator *() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class rbtree_ritr<rbtree<Key_Ty, Val_Ty>> : public rbtree_base_iter
{
    friend class rbtree<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class set;
    template<typename Key_Ty, typename Val_Ty> friend class map;

    using Container_Ty = rbtree<Key_Ty, Val_Ty>;
    using Self_Ty = rbtree_ritr<Container_Ty>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    rbtree_ritr() :
        rbtree_base_iter(nullptr)
    {}

    rbtree_ritr(const Self_Ty &rhs) :
        rbtree_base_iter(rhs.node)
    {}

    rbtree_ritr(Node_Ty *p_nod) :
        rbtree_base_iter(p_nod)
    {}

    ~rbtree_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        _search_prev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        _search_next();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        _search_prev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        _search_next();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    NodeData_Ty *operator ->() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }

    NodeData_Ty &operator *() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class rbtree_const_iter<rbtree<Key_Ty, Val_Ty>> : public rbtree_base_iter
{
    friend class rbtree<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class set;
    template<typename Key_Ty, typename Val_Ty> friend class map;

    using Container_Ty = rbtree<Key_Ty, Val_Ty>;
    using Self_Ty = rbtree_const_iter<Container_Ty>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    rbtree_const_iter() :
        rbtree_base_iter(nullptr)
    {}

    rbtree_const_iter(const Self_Ty &rhs) :
        rbtree_base_iter(rhs.node)
    {}

    rbtree_const_iter(Node_Ty *p_nod) :
        rbtree_base_iter(p_nod)
    {}

    ~rbtree_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        _search_next();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        _search_prev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        _search_next();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        _search_prev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    const NodeData_Ty *operator ->() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }

    const NodeData_Ty &operator *() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class rbtree_const_ritr<rbtree<Key_Ty, Val_Ty>> : public rbtree_base_iter
{
    friend class rbtree<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class set;
    template<typename Key_Ty, typename Val_Ty> friend class map;

    using Container_Ty = rbtree<Key_Ty, Val_Ty>;
    using Self_Ty = rbtree_const_ritr<Container_Ty>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    rbtree_const_ritr() :
        rbtree_base_iter(nullptr)
    {}

    rbtree_const_ritr(const Self_Ty &rhs) :
        rbtree_base_iter(rhs.node)
    {}

    rbtree_const_ritr(Node_Ty *p_nod) :
        rbtree_base_iter(p_nod)
    {}

    ~rbtree_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        _search_prev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        _search_next();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        _search_prev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        _search_next();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    const NodeData_Ty *operator ->() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }

    const NodeData_Ty &operator *() const noexcept
    {
        assert_info(node->prnt, "Cannot refer to no data iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class rbtree
{
public:
    using Self_Ty = rbtree<Key_Ty, Val_Ty>;
    using Node_Ty = rbtree_node<Key_Ty, Val_Ty>;
    using BaseNode_Ty = rbtree_base_node;

    using Iter_Ty = rbtree_iter<Self_Ty>;
    using Ritr_Ty = rbtree_ritr<Self_Ty>;
    using cIter_Ty = rbtree_const_iter<Self_Ty>;
    using cRitr_Ty = rbtree_const_ritr<Self_Ty>;

    friend class rbtree_iter<Self_Ty>;
    friend class rbtree_ritr<Self_Ty>;
    friend class rbtree_const_iter<Self_Ty>;
    friend class rbtree_const_ritr<Self_Ty>;

    //# triple [black_depth : least_value : most_value] for debugging
    using Test_Type = triple<s64, Key_Ty, Key_Ty>;

public:
    s64 _size() const noexcept
    {
        return sz;
    }

    bool validation() noexcept
    {
        if (sz == 0 && myhead()->left == nullptr)
        {
            return true;
        }
        if (myhead()->left == nullptr)
        {
            return false;
        }
        return _validation_recur((Node_Ty*)myhead()->left).first != -1;
    }

protected:
    rbtree() :
        allocator(),
        head(nullptr, nullptr, nullptr, RB_TREE_BLACK),
        sz(0)
    {}

    ~rbtree() noexcept
    {
        _deconstruct_recur(myhead()->left);
    }

    Test_Type _validation_recur(Node_Ty *nod) noexcept
    {
        Test_Type test_error(-1LL);
        Test_Type empty_branch(s64_min);
        if (!nod)
        {
            return empty_branch;
        }
        Node_Ty *left = (Node_Ty*)nod->left;
        Node_Ty *right = (Node_Ty*)nod->right;
        if (left && left->prnt != nod)
        {
            return test_error;
        }
        if (right && right->prnt != nod)
        {
            return test_error;
        }
        if (nod->color == RB_TREE_RED)
        {
            if (left && left->color == RB_TREE_RED)
            {
                return test_error;
            }
            if (right && right->color == RB_TREE_RED)
            {
                return test_error;
            }
        }
        Test_Type left_test = _validation_recur(left);
        Test_Type right_test = _validation_recur(right);
        if (left_test == test_error || right_test == test_error)
        {
            return test_error;
        }
        Key_Ty mykey = nod->mykey();
        RB_TREE_COLOR mycolor = nod->color;
        if (left_test == empty_branch && right_test == empty_branch)
        {
            return Test_Type(nod->color == RB_TREE_RED ? 0 : 1, mykey, mykey);
        }
        else if (left_test == empty_branch)
        {
            if (mycolor != RB_TREE_BLACK || right_test.first != 0 || mykey >= right_test.second)
            {
                return test_error;
            }
            return Test_Type(1, mykey, right_test.third);
        }
        else if (right_test == empty_branch)
        {
            if (mycolor != RB_TREE_BLACK || left_test.first != 0 || mykey <= left_test.third)
            {
                return test_error;
            }
            return Test_Type(1, left_test.second, mykey);
        }
        else
        {
            if (left_test.first != right_test.first || mykey <= left_test.third || mykey >= right_test.second)
            {
                return test_error;
            }
            return Test_Type(left_test.first + (nod->color == RB_TREE_RED ? 0 : 1), left_test.second, right_test.third);
        }
    }

    void _clear() noexcept
    {
        sz = 0;
        _deconstruct_recur(myhead()->left);
        myhead()->left = nullptr;
    }

    void _deconstruct_recur(BaseNode_Ty *nod) noexcept
    {
        if (!nod)
        {
            return;
        }
        _deconstruct_recur(nod->left);
        _deconstruct_recur(nod->right);
        _destroy_node(nod);
    }

    void _insert(const Key_Ty &k) noexcept
    {
        _insert_node(k);
    }

    void _insert(const Key_Ty &k, const Val_Ty &v) noexcept
    {
        _insert_node(k, v);
    }

    void _insert(const Key_Ty &k, Val_Ty &&v) noexcept
    {
        _insert_node(k, v);
    }

    bool _erase(const Key_Ty &k) noexcept
    {
        Node_Ty *nod = _peek_node(k);
        if (nod)
        {
            _remove_node(nod);
            return true;
        }
        else
        {
            return false;
        }
    }

    Node_Ty *myhead() noexcept
    {
        return reinterpret_cast<Node_Ty*>(&head);
    }

    const Node_Ty *myhead() const noexcept
    {
        return reinterpret_cast<const Node_Ty*>(&head);
    }

    Node_Ty *_create_node(const Key_Ty &k) noexcept
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        new (nod) Node_Ty(k);
        return nod;
    }

    Node_Ty *_create_node(const Key_Ty &k, const Val_Ty &v) noexcept
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        new (nod) Node_Ty(k, v);
        return nod;
    }

    Node_Ty *_create_node(const Key_Ty &k, Val_Ty &&v) noexcept
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        new (nod) Node_Ty(k, v);
        return nod;
    }

    void _destroy_node(BaseNode_Ty *nod) noexcept
    {
        reinterpret_cast<Node_Ty*>(nod)->~Node_Ty();
        allocator.put(nod);
    }

    Node_Ty *_insert_node(const Key_Ty &k) noexcept
    {
        assert(sz >= 0);
        if (sz == 0)
        {
            Node_Ty *newnod = _create_node(k);
            assert(newnod);
            newnod->prnt = myhead();
            newnod->color = RB_TREE_BLACK;
            myhead()->left = newnod;
            ++sz;
            return newnod;
        }
        Node_Ty *ptr = (Node_Ty*)myhead()->left;
        while (1)
        {
            assert(ptr);
            if (k < ptr->mykey())
            {
                if (ptr->left)
                {
                    ptr = (Node_Ty*)ptr->left;
                }
                else
                {
                    ptr->left = _create_node(k);
                    assert(ptr->left);
                    ptr->left->prnt = ptr;
                    ptr = (Node_Ty*)ptr->left;
                    break;
                }
            }
            else if (k > ptr->mykey())
            {
                if (ptr->right)
                {
                    ptr = (Node_Ty*)ptr->right;
                }
                else
                {
                    ptr->right = _create_node(k);
                    assert(ptr->right);
                    ptr->right->prnt = ptr;
                    ptr = (Node_Ty*)ptr->right;
                    break;
                }
            }
            else
            {
                assert(ptr);
                return ptr;
            }
        }
        assert(ptr);
        _exam_node(ptr);
        ++sz;
        return ptr;
    }

    Node_Ty *_insert_node(const Key_Ty &k, const Val_Ty &v) noexcept
    {
        assert(sz >= 0);
        if (sz == 0)
        {
            Node_Ty *newnod = _create_node(k, v);
            assert(newnod);
            newnod->prnt = myhead();
            newnod->color = RB_TREE_BLACK;
            myhead()->left = newnod;
            ++sz;
            return newnod;
        }
        Node_Ty *ptr = (Node_Ty*)myhead()->left;
        while (1)
        {
            assert(ptr);
            if (k < ptr->mykey())
            {
                if (ptr->left)
                {
                    ptr = (Node_Ty*)ptr->left;
                }
                else
                {
                    ptr->left = _create_node(k, v);
                    assert(ptr->left);
                    ptr->left->prnt = ptr;
                    ptr = (Node_Ty*)ptr->left;
                    break;
                }
            }
            else if (k > ptr->mykey())
            {
                if (ptr->right)
                {
                    ptr = (Node_Ty*)ptr->right;
                }
                else
                {
                    ptr->right = _create_node(k, v);
                    assert(ptr->right);
                    ptr->right->prnt = ptr;
                    ptr = (Node_Ty*)ptr->right;
                    break;
                }
            }
            else
            {
                assert(ptr);
                return ptr;
            }
        }
        assert(ptr);
        _exam_node(ptr);
        ++sz;
        return ptr;
    }

    Node_Ty *_insert_node(const Key_Ty &k, Val_Ty &&v) noexcept
    {
        assert(sz >= 0);
        if (sz == 0)
        {
            Node_Ty *newnod = _create_node(k, v);
            assert(newnod);
            newnod->prnt = myhead();
            newnod->color = RB_TREE_BLACK;
            myhead()->left = newnod;
            ++sz;
            return newnod;
        }
        Node_Ty *ptr = (Node_Ty*)myhead()->left;
        while (1)
        {
            assert(ptr);
            if (k < ptr->mykey())
            {
                if (ptr->left)
                {
                    ptr = (Node_Ty*)ptr->left;
                }
                else
                {
                    ptr->left = _create_node(k, v);
                    assert(ptr->left);
                    ptr->left->prnt = ptr;
                    ptr = (Node_Ty*)ptr->left;
                    break;
                }
            }
            else if (k > ptr->mykey())
            {
                if (ptr->right)
                {
                    ptr = (Node_Ty*)ptr->right;
                }
                else
                {
                    ptr->right = _create_node(k, v);
                    assert(ptr->right);
                    ptr->right->prnt = ptr;
                    ptr = (Node_Ty*)ptr->right;
                    break;
                }
            }
            else
            {
                assert(ptr);
                return ptr;
            }
        }
        assert(ptr);
        _exam_node(ptr);
        ++sz;
        return ptr;
    }

    Node_Ty *_peek_node(const Key_Ty &k) noexcept
    {
        assert(sz >= 0);
        if (sz == 0)
        {
            return nullptr;
        }
        Node_Ty *ptr = (Node_Ty*)myhead()->left;
        while (1)
        {
            assert(ptr);
            if (k < ptr->mykey() && ptr->left)
            {
                ptr = (Node_Ty*)ptr->left;
            }
            else if (k > ptr->mykey() && ptr->right)
            {
                ptr = (Node_Ty*)ptr->right;
            }
            else if (k == ptr->mykey())
            {
                return ptr;
            }
            else
            {
                return nullptr;
            }
        }
        return nullptr;
    }

    void _remove_node(Node_Ty *nod) noexcept
    {
        assert(sz > 0);
        --sz;
        if (_remove_node_with_left_right(nod) || _remove_node_with_left(nod) || _remove_node_with_right(nod))
        {
            ;
        }
        else
        {
            _remove_node_no_child(nod);
        }
        nod->parent_arm() = nullptr;
        _destroy_node(nod);
    }

private:
    static void _swap_ptr(Node_Ty *&pn1, Node_Ty *&pn2) noexcept
    {
        Node_Ty *tmp = pn1;
        pn1 = pn2;
        pn2 = tmp;
    }

    static void _rotation_left(Node_Ty *nod) noexcept
    {
        assert(nod->right);
        Node_Ty *right = (Node_Ty*)nod->right;
        nod->parent_arm() = right;
        right->prnt = nod->prnt;
        nod->prnt = right;
        nod->right = right->left;
        if (nod->right)
        {
            nod->right->prnt = nod;
        }
        right->left = nod;
    }

    static void _rotation_right(Node_Ty *nod) noexcept
    {
        assert(nod->left);
        Node_Ty *left = (Node_Ty*)nod->left;
        nod->parent_arm() = left;
        left->prnt = nod->prnt;
        nod->prnt = left;
        nod->left = left->right;
        if (nod->left)
        {
            nod->left->prnt = nod;
        }
        left->right = nod;
    }

    void _exam_node(Node_Ty *nod) noexcept
    {
        assert(myhead()->left);
        assert(nod && nod->color == RB_TREE_RED);
        assert(nod->prnt);
        if (nod == myhead()->left)
        {
            nod->color = RB_TREE_BLACK;
            return;
        }
        if (nod->prnt->color == RB_TREE_BLACK)
        {
            return;
        }
        assert(nod->prnt && nod->prnt->prnt);
        bool this_is_left = nod->i_am_left();
        bool prnt_is_left = nod->prnt->i_am_left();
        Node_Ty *p = (Node_Ty*)nod->prnt;
        Node_Ty *pp = (Node_Ty*)nod->prnt->prnt;
        Node_Ty *uncle = (Node_Ty*)nod->prnt->mysibling();
        assert(p->color == RB_TREE_RED);
        assert(pp->color == RB_TREE_BLACK);

        s64 condition_code = 0;
        condition_code |= this_is_left ? (1LL << 0) : 0;
        condition_code |= prnt_is_left ? (1LL << 1) : 0;
        condition_code |= (uncle && uncle->color == RB_TREE_RED) ? (1LL << 2) : 0;

        switch (condition_code)
        {
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            //# has uncle, uncle is red
            assert(uncle->color == RB_TREE_RED);
            assert(p->color == RB_TREE_RED);
            assert(pp->color == RB_TREE_BLACK);
            pp->color = RB_TREE_RED;
            p->color = RB_TREE_BLACK;
            uncle->color = RB_TREE_BLACK;
            _exam_node(pp);
            break;

        case 0x02:
            //# i am right, parent is left
            _rotation_left(p);
            _swap_ptr(nod, p);
        case 0x03:
            //# i am left, parent is left
            pp->color = RB_TREE_RED;
            p->color = RB_TREE_BLACK;
            _rotation_right(pp);
            break;

        case 0x01:
            //# i am left, parent is right
            _rotation_right(p);
            _swap_ptr(nod, p);
        case 0x00:
            //# i am right, parent is right
            pp->color = RB_TREE_RED;
            p->color = RB_TREE_BLACK;
            _rotation_left(pp);
            break;

        default:
            assert(0);
            break;
        }
    }

    bool _remove_node_with_left_right(Node_Ty *nod) noexcept
    {
        Node_Ty *left = (Node_Ty*)nod->left;
        Node_Ty *right = (Node_Ty*)nod->right;
        if (!left || !right)
        {
            return false;
        }
        Node_Ty *p = (Node_Ty*)nod->prnt;
        RB_TREE_COLOR mycolor = nod->color;
        if (right->left)
        {
            Node_Ty *next = (Node_Ty*)right->left;
            while (next->left)
            {
                next = (Node_Ty*)next->left;
            }
            nod->parent_arm() = next;
            nod->prnt = next->prnt;
            nod->left = nullptr;
            nod->right = next->right;
            nod->color = next->color;
            next->parent_arm() = nod;
            next->prnt = p;
            next->left = left;
            next->right = right;
            next->color = mycolor;
            left->prnt = next;
            right->prnt = next;
        }
        else
        {
            nod->parent_arm() = right;
            nod->prnt = right;
            nod->left = nullptr;
            nod->right = right->right;
            nod->color = right->color;
            right->prnt = p;
            right->left = left;
            right->right = nod;
            right->color = mycolor;
            left->prnt = right;
        }
        if (nod->right)
        {
            nod->right->prnt = nod;
            _remove_node_with_right(nod);
        }
        else
        {
            _remove_node_no_child(nod);
        }
        return true;
    }

    bool _remove_node_with_left(Node_Ty *nod) noexcept
    {
        Node_Ty *left = (Node_Ty*)nod->left;
        if (!left)
        {
            return false;
        }
        assert(nod->right == nullptr);
        assert(nod->color == RB_TREE_BLACK);
        assert(nod->left->color == RB_TREE_RED);
        assert(nod->left->left == nullptr);
        assert(nod->left->right == nullptr);
        left->color = RB_TREE_BLACK;
        _rotation_right(nod);
        return true;
    }

    bool _remove_node_with_right(Node_Ty *nod) noexcept
    {
        Node_Ty *right = (Node_Ty*)nod->right;
        if (!right)
        {
            return false;
        }
        assert(nod->left == nullptr);
        assert(nod->color == RB_TREE_BLACK);
        assert(nod->right->color == RB_TREE_RED);
        assert(nod->right->left == nullptr);
        assert(nod->right->right == nullptr);
        right->color = RB_TREE_BLACK;
        _rotation_left(nod);
        return true;
    }

    void _remove_node_no_child(Node_Ty *nod) noexcept
    {
        assert(nod->left == nullptr && nod->right == nullptr);
        RB_TREE_COLOR mycolor = nod->color;
        if (mycolor == RB_TREE_RED || nod == myhead()->left)
        {
            return;
        }
        //# node color is black below
        Node_Ty *p = (Node_Ty*)nod->prnt;
        Node_Ty *mysibling = (Node_Ty*)nod->mysibling();
        assert(mysibling);
        if (mysibling->color == RB_TREE_RED)
        {
            //# parent is black, sibling is red, 2 black nephew
            assert(mysibling->left && mysibling->left->color == RB_TREE_BLACK);
            assert(mysibling->right && mysibling->right->color == RB_TREE_BLACK);
            assert(nod->prnt->color == RB_TREE_BLACK);
            p->color = RB_TREE_RED;
            mysibling->color = RB_TREE_BLACK;
            if (nod->i_am_left())
            {
                _rotation_left(p);
            }
            else
            {
                _rotation_right(p);
            }
        }
        _remove_black_node_no_child_black_sibling(nod);
    }

    void _remove_black_node_no_child_black_sibling(Node_Ty *nod) noexcept
    {
        assert(nod->left == nullptr && nod->right == nullptr);
        assert(nod->color == RB_TREE_BLACK);
        assert(nod->mysibling());
        assert(nod->mysibling()->color == RB_TREE_BLACK);
        Node_Ty *p = (Node_Ty*)nod->prnt;
        Node_Ty *mysibling = (Node_Ty*)nod->mysibling();
        Node_Ty *nephew_left = (Node_Ty*)mysibling->left;
        Node_Ty *nephew_right = (Node_Ty*)mysibling->right;
        if (nephew_left || nephew_right)
        {
            _remove_black_node_no_child_black_sibling_with_nephew(nod);
        }
        else
        {
            _remove_black_node_no_child_black_sibling_no_nephew(nod);
        }
    }

    void _remove_black_node_no_child_black_sibling_with_nephew(Node_Ty *nod) noexcept
    {
        assert(nod->color == RB_TREE_BLACK);
        assert(nod->mysibling()->color == RB_TREE_BLACK);
        assert(nod->mysibling()->left || nod->mysibling()->right);
        bool nod_is_left = nod->i_am_left();
        Node_Ty *p = (Node_Ty*)nod->prnt;
        Node_Ty *pp = (Node_Ty*)nod->prnt->prnt;
        Node_Ty *mysibling = (Node_Ty*)nod->mysibling();
        Node_Ty *nephew;
        if (nod_is_left)
        {
            if (mysibling->right == nullptr)
            {
                mysibling->color = RB_TREE_RED;
                mysibling->left->color = RB_TREE_BLACK;
                _rotation_right(mysibling);
                mysibling = (Node_Ty*)mysibling->prnt;
            }
            nephew = (Node_Ty*)mysibling->right;
            _rotation_left(p);
        }
        else
        {
            if (mysibling->left == nullptr)
            {
                mysibling->color = RB_TREE_RED;
                mysibling->right->color = RB_TREE_BLACK;
                _rotation_left(mysibling);
                mysibling = (Node_Ty*)mysibling->prnt;
            }
            nephew = (Node_Ty*)mysibling->left;
            _rotation_right(p);
        }
        assert(nephew->color == RB_TREE_RED);
        mysibling->color = p->color;
        nephew->color = RB_TREE_BLACK;
        p->color = RB_TREE_BLACK;
    }

    void _remove_black_node_no_child_black_sibling_no_nephew(Node_Ty *nod) noexcept
    {
        assert(nod->color == RB_TREE_BLACK);
        assert(nod->left == nullptr && nod->right == nullptr);
        assert(nod->mysibling()->color == RB_TREE_BLACK);
        assert(nod->mysibling()->left == nullptr && nod->mysibling()->right == nullptr);
        Node_Ty *p = (Node_Ty*)nod->prnt;
        Node_Ty *mysibling = (Node_Ty*)nod->mysibling();
        mysibling->color = RB_TREE_RED;
        if (p->color == RB_TREE_RED)
        {
            p->color = RB_TREE_BLACK;
        }
        else
        {
            _reduced_black_node_recur(p);
        }
    }

    void _reduced_black_node_recur(Node_Ty *nod) noexcept
    {
        if (nod == myhead()->left)
        {
            return;
        }
        assert(nod->color == RB_TREE_BLACK);
        assert(nod->mysibling());
        Node_Ty *p = (Node_Ty*)nod->prnt;
        Node_Ty *mysibling = (Node_Ty*)nod->mysibling();
        bool nod_is_left = nod->i_am_left();
        if (mysibling->color == RB_TREE_RED)
        {
            mysibling->color = RB_TREE_BLACK;
            p->color = RB_TREE_RED;
            if (nod_is_left)
            {
                _rotation_left(p);
                mysibling = (Node_Ty*)p->right;
            }
            else
            {
                _rotation_right(p);
                mysibling = (Node_Ty*)p->left;
            }
        }
        assert(mysibling);
        assert(mysibling->color == RB_TREE_BLACK);
        Node_Ty *far_nephew = nod_is_left ? (Node_Ty*)mysibling->right : (Node_Ty*)mysibling->left;
        Node_Ty *near_nephew = nod_is_left ? (Node_Ty*)mysibling->left : (Node_Ty*)mysibling->right;
        s64 condition_code = 0;
        condition_code |= nod_is_left ? 0 : (1LL << 3);
        condition_code |= p->color == RB_TREE_RED ? (1LL << 2) : 0;
        condition_code |= (near_nephew && near_nephew->color == RB_TREE_RED) ? (1LL << 1) : 0;
        condition_code |= (far_nephew && far_nephew->color == RB_TREE_RED) ? (1LL << 0) : 0;
        switch (condition_code)
        {
            //# node is left
        case 0x02:
        case 0x06: //# near nephew is red, far nephew is not red
            mysibling->color = RB_TREE_RED;
            near_nephew->color = RB_TREE_BLACK;
            _rotation_right(mysibling);
            mysibling = near_nephew;
            near_nephew = (Node_Ty*)mysibling->left;
            far_nephew = (Node_Ty*)mysibling->right;
        case 0x01:
        case 0x03:
        case 0x05:
        case 0x07: //# far nephew is red
            mysibling->color = p->color;
            p->color = RB_TREE_BLACK;
            far_nephew->color = RB_TREE_BLACK;
            _rotation_left(p);
            break;

            //# node is right
        case 0x0a:
        case 0x0e: //# near nephew is red, far nephew is not red
            mysibling->color = RB_TREE_RED;
            near_nephew->color = RB_TREE_BLACK;
            _rotation_left(mysibling);
            mysibling = near_nephew;
            near_nephew = (Node_Ty*)mysibling->right;
            far_nephew = (Node_Ty*)mysibling->left;
        case 0x09:
        case 0x0b:
        case 0x0d:
        case 0x0f: //# far nephew is red
            mysibling->color = p->color;
            p->color = RB_TREE_BLACK;
            far_nephew->color = RB_TREE_BLACK;
            _rotation_right(p);
            break;

        case 0x04:
        case 0x0c: //# parent is red, no nephew is red
            p->color = RB_TREE_BLACK;
            mysibling->color = RB_TREE_RED;
            break;

        case 0x00:
        case 0x08: //# parent is not red, no nephew is red
            mysibling->color = RB_TREE_RED;
            _reduced_black_node_recur(p);
            break;

        default:
            assert(0);
            break;
        }
    }

private:
    slot_allocator<sizeof(Node_Ty)> allocator;
    BaseNode_Ty head;
    s64 sz;
};

}

}

#endif //# __INT_BASIC_RBTREE_HPP__ ends
