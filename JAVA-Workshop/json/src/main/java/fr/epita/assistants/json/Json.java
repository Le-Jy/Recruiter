package fr.epita.assistants.json;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class Json {

    public static void addToJson(String first, String second, String path) {
        File file = new File(path);
        ObjectMapper mapper = new ObjectMapper();
        JsonNode rootNode;
        try {
            rootNode = mapper.readTree(file);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        if (rootNode == null) {
            rootNode = mapper.createObjectNode();
        }
        ObjectNode result = ((ObjectNode) rootNode).put(first,second);
        try {
            mapper.writer().writeValue(file, result);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }


    }
}
