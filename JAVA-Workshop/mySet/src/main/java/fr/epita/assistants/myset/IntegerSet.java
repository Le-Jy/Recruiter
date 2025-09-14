package fr.epita.assistants.myset;

import java.util.ArrayList;

public class IntegerSet {
    ArrayList<Integer> base_;

    public IntegerSet() {
        this.base_ = new ArrayList<Integer>();
    }

    public void insert(Integer i) {
        if (this.base_.isEmpty())
            this.base_.add(i);
        int tmp = 0;
        for (Integer current : this.base_) {
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

    public void remove(Integer i) {
        int counter = 0;
        for (Integer current : this.base_) {
            if (current.compareTo(i) == 0) {
                this.base_.remove(counter);
                return;
            }
            if (i < current)
                return;
            counter++;
        }
    }

    public boolean has(Integer i) {
        for (Integer current : this.base_) {
            if (current.compareTo(i) == 0)
                return true;
        }
        return false;
    }

    public boolean isEmpty() {
        return this.base_.isEmpty();
    }

    public Integer min() {
        return this.base_.get(0);
    }

    public Integer max() {
        return this.base_.get(this.base_.size() - 1);
    }

    public int size() {
        int size = 0;
        for (Integer integer : this.base_) {
            size++;
        }
        return size;
    }

    public static IntegerSet intersection(IntegerSet a, IntegerSet b) {
        IntegerSet result = new IntegerSet();
        for (Integer current : a.base_) {
            if (b.has(current))
                result.insert(current);
        }
        return result;
    }

    public static IntegerSet union(IntegerSet a, IntegerSet b) {
        IntegerSet result = new IntegerSet();
        for (Integer current : a.base_) {
            result.insert(current);
        }
        for (Integer current : b.base_)
            result.insert(current);
        return result;
    }
}
