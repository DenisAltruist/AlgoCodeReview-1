#include <iostream>
#include <utility>


template <typename T> class List;

template <typename T>
class ListElement {
 friend class List<T>;
 private:
     T key;
     ListElement *ptr;

 public:
     ListElement() : ptr(nullptr) {};

     ListElement(T value): key(value), ptr(nullptr) {};

     void SetKey(T value) {
        key = value;
     }

     ListElement* GetNext() const {
        return ptr;
     }

     T GetKey() const {
        return key;
     }
};

template <typename T>
class List {

 private:
    ListElement<T> *first, *last;
    bool isEmpty;

 public:
     List(): first(nullptr), last(nullptr), isEmpty(true) {};

    ListElement<T>* GetFirst() const {
        return first;
    }

    ListElement<T>* GetLast() const {
        return last;
    }

    void SetFree() {
        while (first != nullptr) {
            ListElement<T>* temp = first;
            first = first->ptr;
            delete temp;
        }
        last = nullptr;
        isEmpty = true;
    }

    void Copy(ListElement<T>* newFirst, ListElement<T>* newLast) {
        SetFree();
        while (newFirst != newLast) {
            Push(newFirst->GetKey());
            newFirst = newFirst.GetNext();
        }
    }

    void Push(T value) {
        if (isEmpty) {
            first = new ListElement<T>(value);
            last = first;
            isEmpty = false;
        } else {
            last->ptr = new ListElement<T>(value);
            last = last->ptr;
        }
    }

    List& operator= (const List& rhs) {
        SetFree();
        ListElement<T>* p = rhs.GetFirst();
        while (p != nullptr) {
            Push(p->key);
            p = p->ptr;
        }
        return *this;
    }

    ~List() {
        SetFree();
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const List<T>& A) {
    ListElement<T>* ptr = A.GetFirst();
    while (ptr != nullptr) {
        out << ptr->GetKey() << " ";
        ptr = ptr->GetNext();
    }
    return out;
}

template <typename T>
class MergeSorter {
 private:
    List<T> HelpingList;

 public:
     void Merge(ListElement<T>* lp, ListElement<T>* mp, ListElement<T>* rp) {
        ListElement<T>* ip = lp;
        ListElement<T>* jp = mp;
        ListElement<T>* rightBorder = rp->GetNext();
        ListElement<T>* midBorder = mp;
        HelpingList.SetFree();
        while (ip != midBorder || jp != rightBorder) {
            if (jp == rightBorder || (ip != midBorder && ip->GetKey() < jp->GetKey())) {
                HelpingList.Push(ip->GetKey());
                ip = ip->GetNext();
            } else {
                HelpingList.Push(jp->GetKey());
                jp = jp->GetNext();
            }
        }
        ip = HelpingList.GetFirst();
        jp = lp;
        while (ip != nullptr) {
            jp->SetKey(ip->GetKey());
            jp = jp->GetNext();
            ip = ip->GetNext();
        }
     }

    ListElement<T>* Split(ListElement<T>* lp, ListElement<T>* rp, int length) {
        ListElement<T>* mp = lp;
        for (int i = 0; i < (length >> 1) - 1; ++i) {
            mp = mp->GetNext();
        }
        return mp;
    }

    void Sort(ListElement<T>* lp, ListElement<T>* rp, int length) {
        if (length == 1) {
            return;
        }
        ListElement<T>* mp = Split(lp, rp, length);
        Sort(lp, mp, (length >> 1));
        mp = mp->GetNext();
        Sort(mp, rp, length - (length >> 1));
        Merge(lp, mp, rp);
    }
};

int main() {
    int n;
    std::cin >> n;
    List<int> A;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        A.Push(x);
    }
    MergeSorter<int> MS;
    MS.Sort(A.GetFirst(), A.GetLast(), n);
    std::cout << A << "\n";
    return 0;
}
