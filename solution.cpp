#include <iostream>

using namespace std;

class ListElement {
 friend class List;
 private:
     int key;
     ListElement *ptr;
 public:
     ListElement() {
        ptr = nullptr;
     }

     ListElement(int value) {
         key = value;
         ptr = nullptr;
     }

     void SetKey(int value) {
        key = value;
     }

     ListElement* getNext() const {
        return ptr;
     }

     int getKey() const {
        return key;
     }
};

class List {
 friend void MergeSort(List& A, int length);
 private:
    ListElement *first, *last;
    bool isEmpty;

 public:
     List() {
        isEmpty = true;
        first = nullptr;
        last = nullptr;
     }

    ListElement* getFirst() const {
        return first;
    }

    ListElement* getLast() const {
        return last;
    }

    void SetFree() {
        while (first != nullptr) {
            ListElement* temp = first;
            first = first -> ptr;
            delete temp;
        }
        last = nullptr;
        isEmpty = true;
    }

    void Copy(ListElement* newFirst, ListElement* newLast) {
        SetFree();
        ListElement* currPtr = newFirst;
        while (1) {
            Push(currPtr -> getKey());
            if (currPtr == newLast) {
                break;
            }
            currPtr = currPtr -> getNext();
        }
    }

    void Push(int value) {
        if (isEmpty) {
            first = new ListElement(value);
            last = first;
            isEmpty = false;
        } else {
            last -> ptr = new ListElement(value);
            last = last -> ptr;
        }
    }

    void operator =(const List& rhs) {
        SetFree();
        ListElement* p = rhs.getFirst();
        while (p != nullptr) {
            Push(p -> key);
            p = p -> ptr;
        }
    }
    ~List() {
        SetFree();
    }


};

ostream& operator <<(ostream& out, const List& A) {
    ListElement* ptr = A.getFirst();
    while (ptr != nullptr) {
        out << ptr -> getKey() << " ";
        ptr = ptr -> getNext();
    }
    return out;
}


List T;

void MergeSort(ListElement* lp, ListElement* rp, int length) {
    if (length == 1) {
        return;
    }
    int lengthOfTheLeftPart = (length >> 1);
    ListElement* mp = lp;
    for (int i = 0; i < lengthOfTheLeftPart - 1; ++i) {
        mp = mp -> getNext();
    }
    MergeSort(lp, mp, lengthOfTheLeftPart);
    mp = mp -> getNext();
    MergeSort(mp, rp, length - lengthOfTheLeftPart);
    T.SetFree();

    ListElement* ip = lp;
    ListElement* jp = mp;
    int cntOfStepsIp = lengthOfTheLeftPart;
    int cntOfStepsJp = length - cntOfStepsIp;
    while (cntOfStepsIp != 0 || cntOfStepsJp != 0) {
        if ((ip != mp) && ((cntOfStepsJp == 0) || (ip -> getKey() < jp -> getKey()))) {
            T.Push(ip -> getKey());
            ip = ip -> getNext();
            --cntOfStepsIp;
        } else {
            T.Push(jp -> getKey());
            jp = jp -> getNext();
            --cntOfStepsJp;
        }
    }
    ListElement* ptr = T.getFirst();
    while (ptr != nullptr) {
        lp -> SetKey(ptr -> getKey());
        lp = lp -> getNext();
        ptr = ptr -> getNext();
    }
}

int main() {
    int n;
    cin >> n;
    List A;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        A.Push(x);
    }
    MergeSort(A.getFirst(), A.getLast(), n);
    cout << A << "\n";
    return 0;
}
