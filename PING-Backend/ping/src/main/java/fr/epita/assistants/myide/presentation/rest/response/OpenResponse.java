package fr.epita.assistants.myide.presentation.rest.response;

import java.nio.file.Path;
import java.nio.file.Paths;

import com.fasterxml.jackson.databind.ObjectMapper;

import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.PathRequest;
import jakarta.ws.rs.core.Response;
import fr.epita.assistants.myide.utils.Logger;

public class OpenResponse {
    public static Response openProjectResponse(String request, ProjectServiceImpl projectServiceImpl) {

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

            Project project = projectServiceImpl.load(path);
            if (project == null) {
                return Response.status(400).build();
            }

            // System.out.println(project.getRootNode().toString());
            // System.out.println(project.getFeatures());

            return Response.ok(project).build();
        } catch (Exception e) {

            return Response.status(400).build();
        }
    }

    public static Response openFileResponse(String request, ProjectServiceImpl projectServiceImpl) {
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
            
            Node node = projectServiceImpl.getNodeService().load(path);

            if (node == null) {
                return Response.status(400).build();
            }

            // System.out.println(node.toString());

            return Response.ok(node).build();
        } catch (Exception e) {
            return Response.status(400).build();
        }
    }
}
