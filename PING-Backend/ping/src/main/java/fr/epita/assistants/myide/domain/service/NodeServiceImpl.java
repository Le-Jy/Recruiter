package fr.epita.assistants.myide.domain.service;

import java.awt.Desktop;
import java.io.*;
import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

import org.apache.commons.io.FileUtils;

import java.io.FileReader;
import java.nio.file.Files;

import jakarta.enterprise.context.ApplicationScoped;
import jakarta.ws.rs.BadRequestException;
import lombok.NoArgsConstructor;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Node.Type;
import fr.epita.assistants.myide.domain.entity.node.NodeImpl;

public class NodeServiceImpl implements NodeService {

    @Override
    public Node create(Node folder, String name, Type type) {

        try {
            if (type == Node.Types.FOLDER) {
                Files.createDirectories(folder.getPath().resolve(name));
            } else if (type == Node.Types.FILE) {
                Files.createFile(folder.getPath().resolve(name));
            }

            Node newNode = load(folder.getPath().resolve(name));
            folder.addChildren(newNode);

            return newNode;
        } catch (Exception e) {
            throw new RuntimeException();
        }
    }

    // Need to check if what we need to throw in case of an Exception (Check news)
    // May also need to double check the method to be sure rewriting the whole file
    // if ok
    @Override
    public Node update(Node node, int from, int to, byte[] insertedContent) {
        if (!node.isFile()) {
            throw new RuntimeException();
        }
        try {
            String file = new String(Files.readAllBytes(node.getPath()));

            // Check if all the given informations are good
            if (from < 0 || to > file.length() || from > to) {
                throw new RuntimeException();
            }

            // RandomAccessFile rafAccessFile = new RandomAccessFile(node.getPath().toString(), "rws");
            // rafAccessFile.write(insertedContent, from, new String(insertedContent).length());
            // rafAccessFile.close();

            String newFile = file.substring(0, from) + new String(insertedContent) + file.substring(to);
            // Update the file
            Files.write(node.getPath(), newFile.getBytes(), StandardOpenOption.TRUNCATE_EXISTING);

        } catch (Exception e) {
            throw new RuntimeException();
        }

        return node;
    }

    @Override
    public boolean delete(Node node) {
        try {
            if (node.getType() == Node.Types.FOLDER) {
                FileUtils.deleteDirectory(node.getPath().toFile());
            } else {
                Files.delete(node.getPath());
            }
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    @Override
    public Node move(Node nodeToMove, Node destinationFolder) {
        try {
            if (nodeToMove.isFolder()) {
                FileUtils.moveDirectoryToDirectory(nodeToMove.getPath().toFile(), destinationFolder.getPath().toFile(),
                        false);
            } else {
                FileUtils.moveFileToDirectory(nodeToMove.getPath().toFile(), destinationFolder.getPath().toFile(),
                        false);
            }

            Node newNode = load(
                    destinationFolder.getPath().resolve(nodeToMove.getPath().getFileName()));

            return newNode;
        } catch (Exception e) {
            throw new RuntimeException();
        }
    }

    @Override
    public Node load(Path path) {
        File dir = path.toFile();
        if (dir.isDirectory()) {
            Node dirNode = new NodeImpl(path, Node.Types.FOLDER);
            File[] childFiles = dir.listFiles();

            for (File child : childFiles) {
                Node childNode = load(Paths.get(child.getPath()));
                dirNode.addChildren(childNode);
            }
            return dirNode;
        } else {
            return new NodeImpl(path, Node.Types.FILE);
        }
    }

}
