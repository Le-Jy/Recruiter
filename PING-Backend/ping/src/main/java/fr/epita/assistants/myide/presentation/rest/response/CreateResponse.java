package fr.epita.assistants.myide.presentation.rest.response;

import java.nio.file.Path;

import com.fasterxml.jackson.databind.ObjectMapper;

import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.PathRequest;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Node.Type;
import fr.epita.assistants.myide.domain.entity.node.NodeImpl;
import jakarta.ws.rs.core.Response;

public class CreateResponse {
    public static Response createFolderResponse(String request, ProjectServiceImpl projectServiceImpl) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            PathRequest req = mapper.readValue(request, PathRequest.class);

            Path path = req.getPath();
            if (path == null || path.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (path.toFile().exists()) {
                return Response.status(400).build();
            }
            Path parentPath = path.getParent();

            while (parentPath != null && !parentPath.toFile().exists()) {
                parentPath = parentPath.getParent();
            }

            if (parentPath == null) {
                return Response.status(400).build();
            }

            Node parent = new NodeImpl(parentPath, Node.Types.FOLDER);

            Node newNode = projectServiceImpl.getNodeService().create(parent, parentPath.relativize(path).toString(), Node.Types.FOLDER);
            if (newNode == null) {
                return Response.status(400).build();
            }
            // System.out.println(newNode.toString());

            return Response.ok(newNode).build();
        } catch (Exception e) {

            return Response.status(400).build();
        }
    }

    public static Response createFileResponse(String request, ProjectServiceImpl projectServiceImpl) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            PathRequest req = mapper.readValue(request, PathRequest.class);

            Path path = req.getPath();
            if (path == null || path.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (path.toFile().exists()) {
                return Response.status(400).build();
            }
            Path parentPath = path.getParent();

            if (parentPath == null || !parentPath.toFile().exists()) {
                return Response.status(400).build();
            }

            Node parent = new NodeImpl(parentPath, Node.Types.FOLDER);

            Node newNode = projectServiceImpl.getNodeService().create(parent, parentPath.relativize(path).toString(), Node.Types.FILE);
            if (newNode == null) {
                return Response.status(400).build();
            }
            // System.out.println(newNode.toString());

            return Response.ok(newNode).build();
        } catch (Exception e) {

            return Response.status(400).build();
        }
    }
    
}
