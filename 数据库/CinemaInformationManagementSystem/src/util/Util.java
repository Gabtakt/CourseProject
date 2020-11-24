package util;

import data.Tuple;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Util {

    public static boolean isNumeric(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }
        for (int i = 0; i < str.length(); i++) {
            if (!Character.isDigit(str.charAt(i)) && str.charAt(i) != '.') {
                return false;
            }
        }
        return true;
    }

    public static boolean timeConflictDetection(Tuple<Integer,Integer> time, ArrayList<Tuple<Integer,Integer>> timeList) {
        if (time == null || timeList == null) {
            return false;
        }
        else if (timeList.isEmpty()) {
            return true;
        }
        ArrayList<Integer> beginTimeList = new ArrayList<>();
        ArrayList<Integer> endTimeList = new ArrayList<>();
        beginTimeList.add(time.getP1());
        endTimeList.add(time.getP2());
        for (Tuple<Integer,Integer> timeTuple : timeList) {
            beginTimeList.add(timeTuple.getP1());
            endTimeList.add(timeTuple.getP2());
        }
        System.out.println("排序前："+beginTimeList);
        System.out.println("排序前："+endTimeList);
        beginTimeList.sort((o1, o2) -> {
            if (o1 > o2) {
                return 1;
            } else if (o1.equals(o2)) {
                return 0;
            }
            return -1;
        });
        endTimeList.sort((o1, o2) -> {
            if (o1 > o2) {
                return 1;
            }
            else if (o1.equals(o2)) {
                return 0;
            }
            return -1;
        });
        System.out.println("排序后："+beginTimeList);
        System.out.println("排序后："+endTimeList);
        for (int i = 1; i < beginTimeList.size(); i++) {
            if (beginTimeList.get(i) < endTimeList.get(i - 1) + Config.CLEAR_TIME) {
                return false;
            }
        }
        return true;
    }
}
