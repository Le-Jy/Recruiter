package fr.epita.assistants.streamstudent;

import java.util.Comparator;
import java.util.Optional;
import java.util.stream.Stream;

public class Streamer {
    public Stream<Pair<Integer, String>> validator(Stream<Pair<Integer, String>> stream) {
        return stream.filter(G -> G.getKey() >= 0 && G.getKey() <= 100).filter(L -> L.getValue().matches("^[^_.]*[_.][^_.]*$"));
    }

    public Stream<Pair<Integer, String>> orderGrade(Stream<Pair<Integer, String>> stream) {
        return stream.sorted((G, L) -> {
            if (G.getKey().compareTo(L.getKey()) == 0) {
                return G.getValue().compareTo(L.getValue());
            } else return G.getKey().compareTo(L.getKey());
        });
    }

    public Stream<Pair<Integer, String>> lowercase(Stream<Pair<Integer, String>> stream) {
        return stream.map(G -> {
                    if (G.getValue().matches("^[A-Z]*[a-z._]*[A-Z]+[a-z._]*$")) {
                        return new Pair<>(G.getKey() / 2, G.getValue().toLowerCase());
                    }
                    return G;
                }
        );
    }

    public Optional<Pair<Integer, String>> headOfTheClass(Stream<Pair<Integer, String>> stream) {
        if (stream != null) {
            return stream.max((G, L) -> {
                if (G.getKey().compareTo(L.getKey()) == 0) {
                    return -G.getValue().compareTo(L.getValue());
                }
                return G.getKey().compareTo(L.getKey());
            });
        }
        return Optional.empty();
    }

    public Stream<Pair<Integer, String>> quickFix(Stream<Pair<Integer, String>> stream) {
        return stream.map(G -> {
            if (G.getValue().toLowerCase().matches("^ma.*$") || G.getValue().toLowerCase().matches("^l.*x$")) {
                var tmp = G.getKey() * 2;
                var result = new Pair<>(G.getKey() * 2, G.getValue());
                if (tmp > 100)
                    result = new Pair<>(100, G.getValue());
                return result;
            }
            return G;
        });
    }

    public Stream<Pair<Integer, String>> encryption(Stream<Pair<Integer, String>> stream) {
        return stream.map(G -> {
            final int mid = G.getValue().length() / 2; //get the middle of the String
            String[] parts = {G.getValue().substring(0, mid),G.getValue().substring(mid)};
            String reverseWord = new String(parts[1] + parts[0]);
            return new Pair<>(G.getKey(), reverseWord);
        });
    }
}

