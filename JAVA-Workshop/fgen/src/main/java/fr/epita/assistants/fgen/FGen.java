package fr.epita.assistants.fgen;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class FGen {

    public FGen(final String inputPath) throws RuntimeException {
        String cwd = new File("").getAbsolutePath();
        cwd = cwd + '/';
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream(inputPath);
        if (inputStream == null)
            throw new RuntimeException(inputPath + " :File not found");
        List<String> commands = new ArrayList<String>();
        String line;
        try (InputStreamReader inputStreamReader = new InputStreamReader(inputStream, StandardCharsets.UTF_8);
             BufferedReader bufferedReader = new BufferedReader(inputStreamReader)) {
            while ((line = bufferedReader.readLine()) != null) {
                commands.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        for (String command : commands) {
            if (command.charAt(0) == '+') {
                StringBuilder tmp = new StringBuilder(cwd);
                command = command.substring(2);
                List<String> files = new ArrayList<String>();
                files = List.of(command.split("((?<=/))"));
                for (String file : files) {
                    tmp.append(file);
                    File file1 = new File(String.valueOf(tmp));
                    if (file.charAt(file.length() - 1) == '/') {
                        file1.mkdirs();
                    } else {
                        try {
                            file1.createNewFile();
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    }
                }
            } else if (command.charAt(0) == '>') {
                StringBuilder tmp = new StringBuilder(cwd);
                command = command.substring(2);
                tmp.append(command);
                if (!new File(String.valueOf(tmp)).isDirectory())
                    throw new RuntimeException(tmp + " :No such directory");
                cwd = String.valueOf(tmp + "/");
            } else if (command.charAt(0) == '-') {
                StringBuilder tmp = new StringBuilder(cwd);
                command = command.substring(2);
                tmp.append(command);
                File file = new File(String.valueOf(tmp));
                if (file.exists() && file.isDirectory()) {
                    deleteDirectory(file);
                }
                else
                    file.delete();
            }
        }
    }


    private void deleteDirectory(File file) {
        File[] contents = file.listFiles();
        if (contents != null) {
            for (File f : contents) {
                deleteDirectory(f);
            }
        }
        file.delete();
    }
}
