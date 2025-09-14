package fr.epita.assistants.mykitten;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class MyKitten {
    /**
     * Initializer.
     *
     * @param srcPath Source file path.
     */
    public MyKitten(String srcPath) {
        try {
            streamContent = Files.lines(Paths.get(srcPath));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Use the streamContent to replace `wordToReplace` with "miaou". Don't forget
     * to add the line number beforehand for each line. Store the new
     * result directly in the streamContent field.
     *
     * @param wordToReplace The word to replace
     */
    public void replaceByMiaou(String wordToReplace) {
        AtomicInteger nbLines = new AtomicInteger(1);
        streamContent = streamContent.map(S ->  nbLines.getAndIncrement() + " " + S.replaceAll(wordToReplace, "miaou"));
    }

    /**
     * Use the streamContent to write the content into the destination file.
     *
     * @param destPath Destination file path.
     */
    public void toFile(String destPath) {
        BufferedWriter bufferedWriter = null;
        try {
            bufferedWriter = new BufferedWriter(new FileWriter(destPath));
            bufferedWriter.write(streamContent.collect(Collectors.joining("\n")));
            } catch (IOException ex) {
            throw new RuntimeException(ex);
        }finally {
            assert bufferedWriter != null;
            try {
                bufferedWriter.close();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
    }
    }

    /**
     * Creates an instance of MyKitten and calls the above methods to do it
     * straightforwardly.
     *
     * @param srcPath       Source file path
     * @param destPath      Destination file path
     * @param wordToReplace Word to replace
     */
    public static void miaou(String srcPath, String destPath, String wordToReplace) {
        var kitten = new MyKitten(srcPath);
        kitten.replaceByMiaou(wordToReplace);
        kitten.toFile(destPath);
    }
    public Stream<String> streamContent;
}
