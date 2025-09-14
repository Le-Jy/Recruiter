package fr.epita.assistants.jws.converter;

import javax.enterprise.context.ApplicationScoped;
import java.sql.Timestamp;
import java.time.Instant;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

@ApplicationScoped
public class RleConverter {

    private String encoding(String input) {
        StringBuilder result = new StringBuilder();
        int count = 1;
        char[] chars = input.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            char c = chars[i];
            if (count < 9 && i + 1 < chars.length && c == chars[i + 1]) {
                count++;
            } else {
                result.append(count).append(c);
                count = 1;
            }
        }
        return result.toString();
    }

    private String decoding(String input) {
        StringBuilder result = new StringBuilder();
        char[] chars = input.toCharArray();

        int count = 0;
        for (char c : chars) {
            if (Character.isDigit(c)) {
                count = 10 * count + Character.getNumericValue(c);
            } else {
                result.append(String.join("", Collections.nCopies(count, String.valueOf(c))));
                count = 0;
            }
        }
        return result.toString();
    }
    public List<String> rleToNormal(List<String> input) {
        List<String> output = new ArrayList<>();
        input.forEach(L -> output.add(decoding(L)));
        return output;
    }
    public List<String> normalToRle(List<String> input) {
        List<String> output = new ArrayList<>();
        input.forEach(L -> output.add(encoding(L)));
        return output;
    }

    public List<String> copyMap(List<String> map) {
        List<String> res = new ArrayList<>(map);
        return res;
    }

    public static boolean comparerTimestamps(Timestamp timestamp1, Long delaiMillisecondes) {
        return timestamp1.compareTo(Timestamp.from(Instant.now().minusMillis(delaiMillisecondes))) > 0;
    }
}
