package fr.epita.assistants.embedfiles;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Optional;
import java.util.stream.Collectors;

public class DisplayEmbedFile {
    private final String filename;

    public DisplayEmbedFile(String filename) {
        this.filename = filename;
    }

    public Optional<String> display() {
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream(this.filename);
        Optional <String> result = Optional.empty();
        if (inputStream == null)
            return result;
        try {
            try (InputStreamReader inputStreamReader = new InputStreamReader(inputStream, StandardCharsets.UTF_8);
                     BufferedReader bufferedReader = new BufferedReader(inputStreamReader)) {
                result = Optional.of(bufferedReader.lines().collect(Collectors.joining("\n")) + '\n');
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }
}
