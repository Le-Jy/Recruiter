package fr.epita.assistants.myide.presentation.rest.response;

import java.nio.file.Path;

import com.fasterxml.jackson.databind.ObjectMapper;

import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.node.NodeImpl;
import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.PathRequest;
import jakarta.ws.rs.core.Response;

public class DeleteResponse {
    public static Response deleteFolderResponse(String request, ProjectServiceImpl projectServiceImpl) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            PathRequest req = mapper.readValue(request, PathRequest.class);

            Path path = req.getPath();
            if (path == null || path.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (!path.toFile().exists()) {
                return Response.status(404).build();
            }
            if (!path.toFile().isDirectory()) {
                return Response.status(400).build();
            }

            Node node = new NodeImpl(path, Node.Types.FOLDER);

            if (!projectServiceImpl.getNodeService().delete(node)) {
                return Response.status(403).build();
            }

            return Response.ok().build();
        } catch (Exception e) {
            return Response.status(400).build();
        }
    }

    public static Response deleteFileResponse(String request, ProjectServiceImpl projectServiceImpl) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            PathRequest req = mapper.readValue(request, PathRequest.class);

            Path path = req.getPath();
            if (path == null || path.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (!path.toFile().exists()) {
                return Response.status(404).build();
            }
            if (!path.toFile().isFile()) {
                return Response.status(400).build();
            }

            Node node = new NodeImpl(path, Node.Types.FILE);

            if (!projectServiceImpl.getNodeService().delete(node)) {
                return Response.status(403).build();
            }

            return Response.ok().build();
        } catch (Exception e) {
            return Response.status(400).build();
        }
    }

}
