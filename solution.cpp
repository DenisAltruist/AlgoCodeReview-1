#include <iostream>

class ListElement {
 friend class List;
 private:
     int key;
     ListElement *ptr;

 public:
     ListElement() : ptr(nullptr) {};

     ListElement(int value): key(value), ptr(nullptr) {};

     void SetKey(int value) {
        key = value;
     }

     ListElement* GetNext() const {
        return ptr;
     }

     int GetKey() const {
        return key;
     }
};

class List {
 friend class MergeSorter;
 private:
    ListElement *first, *last;
    bool isEmpty;

 public:
     List(): first(nullptr), last(nullptr), isEmpty(true) {};

    ListElement* GetFirst() const {
        return first;
    }

    ListElement* GetLast() const {
        return last;
    }

    void SetFree() {
        while (first != nullptr) {
            ListElement* temp = first;
            first = first->ptr;
            delete temp;
        }
        last = nullptr;
        isEmpty = true;
    }

    void Copy(ListElement* newFirst, ListElement* newLast) {
        SetFree();
        ListElement* currPtr = newFirst;
        while (1) {
            Push(currPtr->GetKey());
            if (currPtr == newLast) {
                break;
            }
            currPtr = currPtr->GetNext();
        }
    }

    void Push(int value) {
        if (isEmpty) {
            first = new ListElement(value);
            last = first;
            isEmpty = false;
        } else {
            last->ptr = new ListElement(value);
            last = last->ptr;
        }
    }

    void operator= (const List& rhs) {
        SetFree();
        ListElement* p = rhs.GetFirst();
        while (p != nullptr) {
            Push(p->key);
            p = p->ptr;
        }
    }
    ~List() {
        SetFree();
    }
};

std::ostream& operator<< (std::ostream& out, const List& A) {
    ListElement* ptr = A.GetFirst();
    while (ptr != nullptr) {
        out << ptr->GetKey() << " ";
        ptr = ptr->GetNext();
    }
    return out;
}

class MergeSorter {
 private:
    List T;

 public:
    void Sort(ListElement* lp, ListElement* rp, int length) {
        if (length == 1) {
            return;
        }
        int lengthOfTheLeftPart = (length >> 1);
        ListElement* mp = lp;
        for (int i = 0; i < lengthOfTheLeftPart - 1; ++i) {
            mp = mp->GetNext();
        }
        Sort(lp, mp, lengthOfTheLeftPart);
        mp = mp->GetNext();
        Sort(mp, rp, length - lengthOfTheLeftPart);
        T.SetFree();
        ListElement* ip = lp;
        ListElement* jp = mp;
        int cntOfStepsIp = lengthOfTheLeftPart;
        int cntOfStepsJp = length - cntOfStepsIp;
        while (cntOfStepsIp != 0 || cntOfStepsJp != 0) {
            if ((ip != mp) && ((cntOfStepsJp == 0) || (ip->GetKey() < jp->GetKey()))) {
                T.Push(ip->GetKey());
                ip = ip->GetNext();
                --cntOfStepsIp;
            } else {
                T.Push(jp->GetKey());
                jp = jp->GetNext();
                --cntOfStepsJp;
            }
        }
        ListElement* ptr = T.GetFirst();
        while (ptr != nullptr) {
            lp->SetKey(ptr->GetKey());
            lp = lp->GetNext();
            ptr = ptr->GetNext();
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    List A;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        A.Push(x);
    }
    MergeSorter MS;
    MS.Sort(A.GetFirst(), A.GetLast(), n);
    std::cout << A << "\n";
    return 0;
}
