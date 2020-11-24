package data;

import javafx.collections.ObservableList;

/**
 * 泛型二元组类
 * @param <T1> 第一项
 * @param <T2> 第二项
 */
public class Tuple<T1,T2> {
    private  T1 p1;
    private  T2 p2;

    public Tuple(T1 p1, T2 p2) {
        this.p1 = p1;
        this.p2 = p2;
    }

    public T1 getP1() {
        return p1;
    }

    public T2 getP2() {
        return p2;
    }

    public void setP1(T1 p1) {
        this.p1 = p1;
    }

    public void setP2(T2 p2) {
        this.p2 = p2;
    }

    @Override
    public String toString() {
        return p1 + "-" + p2;
    }

    public boolean equals(Tuple<T1,T2> tuple) {
        if (tuple == null) {
            return false;
        }
        if (tuple == this) {
            return true;
        }
        return this.p1.equals(tuple.getP1()) && this.p2.equals(tuple.p2);
    }

    public boolean beContained(ObservableList<Tuple<T1,T2>> tupleList) {
        if (tupleList == null) {
            return false;
        }
        for (Tuple<T1,T2> tuple : tupleList) {
            if (this.equals(tuple)) {
                return true;
            }
        }
        return false;
    }
}
