package fr.epita.assistants.linkedlist;

public class LinkedList<T extends Comparable<T>> {
    T data;
    LinkedList<T> next;
    int size;

    /**
     * Initializes the list
     **/
    public LinkedList() {
        this.next = null;
        this.data = null;
        this.size = 0;
    }

    /**
     * Inserts the specified element into the list.
     * The elements must be sorted in ascending order.
     * null elements should be at the end of the list.
     *
     * @param e Element to be inserted
     **/
    public void insert(T e) {

        if (this.size == 0) {
            this.data = e;
            this.size++;
            return;
        }

        LinkedList<T> newElement = new LinkedList<T>();
        newElement.data = e;
        if (e == null) {
            LinkedList<T> tmp = this;
            while (tmp.next != null)
                tmp = tmp.next;
            tmp.next = newElement;
            newElement.next = null;
            return;
        }
        if (this.size == 1) {
            this.size++;
            if (this.data != null && e.compareTo(this.data) > 0) {
                this.next = newElement;
                newElement.next = null;
            } else {
                newElement.data = this.data;
                newElement.next = this.next;
                this.data = e;
                this.next = newElement;
            }
        } else {
            this.size++;
            LinkedList<T> tmp = this;
            LinkedList<T> prev = null;
            while (tmp.data != null && e.compareTo(tmp.data) > 0) {
                prev = tmp;
                if (tmp.next == null) {
                    tmp.next = newElement;
                    newElement.next = null;
                    return;
                }
                tmp = tmp.next;
            }
            if (prev != null){
                prev.next = newElement;
                newElement.next =tmp;
            }
            else {
                newElement.data = this.data;
                this.data = e;
                newElement.next = this.next;
                this.next = newElement;

            }
        }
    }

    /**
     * Returns the n-th element in the list.
     *
     * @param i Index
     * @return The element at the given index
     * @throws IndexOutOfBoundsException if there is no element at this
     *                                   index.
     **/
    public T get(int i) {
        if (i < 0 || i >= this.size)
            throw new IndexOutOfBoundsException();
        int j = 0;
        LinkedList<T> tmp = this;
        while (tmp.next != null && j < i) {
            j++;
            tmp = tmp.next;
        }
        return tmp.data;
    }

    /**
     * Removes the first occurrence of the specified element in the list.
     *
     * @param e Element to remove
     * @return returns the element that has been removed or null
     **/
    public T remove(T e) {
        LinkedList<T> curr = this;
        LinkedList<T> prev = null;
        LinkedList<T> next = this.next;
        T res = null;
        while (curr != null && curr.data != null && e.compareTo(curr.data) > 0) {
            prev = curr;
            curr = next;
            if (next != null)
                next = next.next;
        }
        if (curr == null || curr.data == null)
            return null;
        if (e.compareTo(curr.data) == 0) {
            this.size--;
            res = curr.data;
            if (prev == null) {
                if (this.next == null)
                    this.data = null;
                else {
                    this.data = this.next.data;
                    this.next = this.next.next;
                }
            } else
                prev.next = next;
        }
        return res;
    }

    /**
     * Returns the size of the list.
     *
     * @return Number of elements in the list
     **/
    public int size() {
        return this.size;
    }

    /**
     * Removes all elements from the list.
     **/
    public void clear() {
        this.next = null;
        this.data = null;
        this.size = 0;
    }
}
