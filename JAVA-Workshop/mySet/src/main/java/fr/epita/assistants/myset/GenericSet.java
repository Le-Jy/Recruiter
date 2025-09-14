package fr.epita.assistants.myset;

import java.util.ArrayList;

public class GenericSet<T extends Comparable<T>> {
    ArrayList<T> base_;

    public GenericSet() {
        this.base_ = new ArrayList<T>();
    }

    public void insert(T i) {
        if (this.base_.isEmpty())
            this.base_.add(i);
        int tmp = 0;
        for (T current : this.base_) {
            if (current.compareTo(i) == 0)
                return;
            if (current.compareTo(i) > 0) {
                this.base_.add(tmp, i);
                return;
            } else
                tmp++;
        }
        this.base_.add(tmp, i);
    }

    public void remove(T i) {
        int counter = 0;
        for (T current : this.base_) {
            if (current.compareTo(i) == 0) {
                this.base_.remove(counter);
                return;
            }
            if (i.compareTo(current) < 0)
                return;
            counter++;
        }
    }

    public boolean has(T i) {
        for (T current : this.base_) {
            if (current.compareTo(i) == 0)
                return true;
        }
        return false;
    }

    public boolean isEmpty() {
        return this.base_.isEmpty();
    }

    public T min() {
        return this.base_.get(0);
    }

    public T max() {
        return this.base_.get(this.base_.size() - 1);
    }

    public int size() {
        int size = 0;
        for (T T : this.base_) {
            size++;
        }
        return size;
    }

    public static <T extends Comparable<T>> GenericSet<T> intersection(GenericSet<T> a, GenericSet<T> b) {
        GenericSet<T> result = new GenericSet<>();
        for (T current : a.base_) {
            if (b.has(current))
                result.insert(current);
        }
        return result;
    }

    public static <T extends Comparable<T>> GenericSet<T> union(GenericSet<T> a, GenericSet<T> b) {
        GenericSet<T> result = new GenericSet<>();
        for (T current : a.base_) {
            result.insert(current);
        }
        for (T current : b.base_)
            result.insert(current);
        return result;
    }
}
