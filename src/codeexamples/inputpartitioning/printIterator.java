package codeexamples.inputpartitioning;

import java.util.ArrayList;
import java.util.Iterator;

public interface printIterator {
    private static void printIterator(Iterator<String> iter)
    {
        while(iter.hasNext()) {
            String element = (String) iter.next();
            System.out.print(element + "\n");
        }
    }
    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<>();
        list.add("apple");
        list.add("pie");
        Iterator iter = list.iterator();
        printIterator(iter);
        Iterator iter2 = list.iterator();
        iter2.next();
        iter2.remove();
        printIterator(iter2);
    }
}
