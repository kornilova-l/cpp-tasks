//
// Created by Liudmila Kornilova on 12.05.17.
//

#ifndef DICTIONARY_CLOSEDHASH_H
#define DICTIONARY_CLOSEDHASH_H

#include <iostream>
#include <string.h>

using namespace std;


template<class T>
class ClosedHash {
public:
    void insert(const T val) {

        int hash = hashCode_(val);

        if (hashTable[hash] == 0) {  // if this element of hash table is empty
            insertToPos_(hash, val);
            return;
        }
        int pos = findPosForNew_(hash, val);
        if (pos != -1) {  // if place was found
            insertToPos_(pos, val);
        }

    }

    /**
     * Delete element from table
     * @param val
     */
    void del(const T val) {
        int pos = find_(val);
        if (pos != -1) {
            /*
             * if assign 0 to hashTable[val] it will be impossible to understand
             * if it was deleted or never assinged
             */
            hashTable[pos] = EMPTY_ELEM;
        }
    }

    int member(const T val) const {
        if (find_(val) != -1) {  // if name is in table
            return 1;
        }
        return 0;
    }

    void print() const {
        int isEmpty = 1;
        for (int i = 0; i < B; i++) {  // for all elements in hash table
            if (hashTable[i] != 0 && hashTable[i] != EMPTY_ELEM) {  // if name is not empty
                cout << i << " - ";
                isEmpty = 0;
                cout << *hashTable[i] << " (hash = " << hashCode_(*hashTable[i]) << ")" << endl;
            }
        }
        if (isEmpty == 1)
            cout << "dict is empty";
        cout << endl;
    }

    /**
     * Clear hash-table
     */
    void makeNull() {
        for (int i = 0; i < B; i++) {  // for all elements in hash table
            if (hashTable[i] != 0) {  // if value exists
                delete[] hashTable[i];
                hashTable[i] = 0;
            }
        }
    }

    int size() {
        int size = 0;
        for (int i = 0; i < B; i++) {
            if (hashTable[i] != 0 && hashTable[i] != EMPTY_ELEM) {
                size++;
            }
        }
        return size;
    }

private:

    static const int B = 100;
    T *hashTable[B];
    T * const EMPTY_ELEM = new T();

//    int countKey_(const char *name) const;

    int getNext_(int pos) const {
        return (pos + 1) % B;
    }

    int find_(const T val) const {
        int hash = hashCode_(val);
        // check first:
        if (hashTable[hash] == 0) {  // if there is no names with such hash
            return -1;
        }
        if (isEqual_(*hashTable[hash], val)) {  // if name was found
            return hash;
        }
        // check all
        int pos = getNext_(hash);
        while (pos != hash) {  // for all elements
            if (hashTable[pos] == 0) {  // if there is no more names with this hash
                return -1;
            }
            if (isEqual_(*hashTable[pos], val)) {  // if name was found
                return pos;
            }
            pos = getNext_(pos);
        }
        // now hash table does not have gaps and name was not found
        return -1;
    }

    int countKey_(int val) const {
        int hash = 0;
        while (val > 0) {
            hash += val % 10;
            val /= 10;
        }
        return hash;
    }

    int countKey_(const string val) const {
        int key = 0;
        for(const char& c : val) {
            key += c;
        }
        return key;
    }

    int hashCode_(const T val) const {
        return countKey_(val) % B;
    }

    void insertToPos_(int hash, int val) {
        hashTable[hash] = new int(val);
    }

    void insertToPos_(int hash, const string val) {
        hashTable[hash] = new string(val);
    }

    int findPosForNew_(int hash, const T val) {
        int firstUsedAndEmpty = -1;  // element which was used but now empty
        int pos = getNext_(hash);
        // check first element (it cannot be checked in loop)
        if (isEqual_(*hashTable[hash], val)) {  // if name is already in list
            return -1;
        }
        if (hashTable[hash] == EMPTY_ELEM) {  // find first elem which was used but now empty
            firstUsedAndEmpty = hash;
        }
        while (pos != hash) {  // for all elements in hash table
            if (hashTable[pos] == 0) {  // if first empty elem is found
                if (firstUsedAndEmpty == -1) {  // if there was no used elements
                    return pos;
                }
                return firstUsedAndEmpty;
            }
            if (hashTable[pos] == EMPTY_ELEM &&
                firstUsedAndEmpty == -1) {  // find first elem which was used but now empty
                firstUsedAndEmpty = pos;
            }
            if (isEqual_(*hashTable[pos], val)) {  // if name is already in list
                return -1;
            }
            pos = getNext_(pos);
        }
        // in this situation all elements were at least ones assigned, but equal name was not found
        if (firstUsedAndEmpty == -1) {  // if there is no empty elements
            return -1;
        }
        return firstUsedAndEmpty;
    }

    int isEqual_(const string val1, const string val2) const {
        return val1.compare(val2) == 0;
    }

    int isEqual_(int val1, int val2) const {
        return val1 == val2;
    }
};


#endif //DICTIONARY_CLOSEDHASH_H
