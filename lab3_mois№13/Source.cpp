#include <iostream>
#include <ctime>
using namespace std;

struct NodeBase {
    NodeBase* next;
    NodeBase* prev;
    NodeBase() : next(this), prev(this) {}
    NodeBase(NodeBase* next_, NodeBase* prev_)
        : next(next_), prev(prev_) {
        prev->next = next->prev = this;
    }
    virtual ~NodeBase() {
        next->prev = prev;
        prev->next = next;
    }
};

template <typename Tp_>
struct Node : public NodeBase {
    Tp_ data;
    Node(NodeBase* next_, NodeBase* prev_, const Tp_& data_)
        : NodeBase(next_, prev_), data(data_) {}
};

template <typename Tp_>
class Deque {
public:
    typedef Tp_ ValueType;
    typedef Node<Tp_> NodeType;
    Deque() : node_() {}
    ~Deque() {
        clear();
    }
    void push_Back(const ValueType& value) {
        new NodeType(&node_, node_.prev, value);
    }
    void push_Front(const ValueType& value) {
        new NodeType(node_.next, &node_, value);
    }
    ValueType front() const {
        return static_cast<NodeType*>(node_.next)->data;
    }
    ValueType back() const {
        return static_cast<NodeType*>(node_.prev)->data;
    }
    ValueType pop_Front() {
        ValueType result = front();
        delete node_.next;
        return result;
    }
    ValueType pop_Back() {
        ValueType result = back();
        delete node_.prev;
        return result;
    }
    bool Empty() {
        return node_.next == node_.prev;
    }
    void clear() {
        while (!Empty()) {
            delete node_.next;
        }
    }
    void size() {
        size_t result = 0;
        for (NodeBase* node = node_.next; node != &node_; node = node->next)
            ++result;
        return result;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Deque& deque) {
        for (NodeBase* node = deque.node_.next; node != &deque.node_;
            node = node->next)
            stream << static_cast<NodeType*>(node)->data << " ";
        return stream;
    }
private:
    NodeBase node_;
};

int main(int argc, char* argv[]) {
    //���������������
    setlocale(LC_ALL, "RU");
    //���������� ����������
    int size;
    //���������� ���� ������� ����
    Deque<int> a;
    //���� ������� ����������� ���������
    cout << " ����������� ��������� ����: ";
    cin >> size;
    //���������� ����
    for (int i = 0; i < size; i++)
    {
        int tmp = rand() % 14 + 1;
        a.push_Back(tmp);
    }
    //����� ����
    /*cout << "\n ���: ";
    for (int i = 0; i < size; i++)
    {
        int temp = a.pop_Front();
        cout << temp << ' ';
        a.push_Back(temp);
    }*/
    cout << a << endl;
    //����� �������� ��������� � ����
    for (int i = 0; i < size; i++)
    {
        //���� ��������
        if (!(i % 2))
        {
            a.push_Back(a.pop_Front());
        }
        //���� ������
        else
        {
            a.pop_Front();
        }
    }
    //����� ��������� ����
    cout << "\n ��� ���������: ";
    for (int i = 0; i < (size/2 + size%2); i++)
    {
        int temp = a.pop_Front();
        cout << temp<< ' ';
        a.push_Back(temp);
    }
    //�������
    a.clear();
    system("PAUSE");
    return 0;
}