package fr.epita.assistants.myide.domain.entity.feature.any;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Set;

import org.apache.commons.io.FileUtils;

import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;

public class RemoveTrashFiles {
    static public Set<String> getTrashFiles(File myideignore) {
        Set<String> trashFiles = new HashSet<>();

        try (BufferedReader br = new BufferedReader(new FileReader(myideignore))) {

            String line;

            while ((line = br.readLine()) != null) {
                if (!line.trim().isEmpty()) {
                    trashFiles.add(line.trim());
                }
            }

        } catch (Exception e) {
            return null;
        }

        return trashFiles;
    }

    static public void removeTrashFiles(Node node, Set<String> trashFiles) throws IOException {

        if (node.isFile()) {
            return;
        }

        for (int i = 0; i < node.getChildren().size(); i++) {
            Node child = node.getChildren().get(i);
            for (String file : trashFiles) {
                // if (child.getPath().toString().equals(file)) {
                if (child.getPath().getFileName().equals(Paths.get(file))) {
                    if (child.getType() == Node.Types.FOLDER) {
                        FileUtils.deleteDirectory(child.getPath().toFile());
                    } else {
                        Files.delete(child.getPath());
                    }

                    node.removeChildren(child);
                    i--;
                    break;
                }
            }
        }

        for (Node child : node.getChildren()) {
            removeTrashFiles(child, trashFiles);
        }
    }
    
    static public File getMyIdeIgnore(Project project) {
        File myideignore = null;
        for (Node child : project.getRootNode().getChildren()) {
            if (child.getPath().toFile().getName().equals(".myideignore")) {
                myideignore = child.getPath().toFile();
                break;
            }
        }

        return myideignore;
    }
}
