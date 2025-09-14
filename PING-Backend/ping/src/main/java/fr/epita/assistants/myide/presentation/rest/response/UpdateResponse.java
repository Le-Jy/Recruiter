package fr.epita.assistants.myide.presentation.rest.response;

import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.fasterxml.jackson.databind.ObjectMapper;

import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.UpdateRequest;
import jakarta.ws.rs.core.Response;
import fr.epita.assistants.myide.domain.entity.node.NodeImpl;
import fr.epita.assistants.myide.domain.entity.Node;

public class UpdateResponse {

    public static Response getResponse(String request, ProjectServiceImpl projectServiceImpl)
    {
        try {
            ObjectMapper mapper = new ObjectMapper();
            UpdateRequest req = mapper.readValue(request, UpdateRequest.class);

            Path path = req.getPath();
            int from = req.getFrom();
            int to = req.getTo();
            byte[] content = req.getContent().getBytes();

            if (path == null || path.toString().isEmpty())
            {
                // System.out.println("not goof");
                return Response.status(400).build();
            }

            // GET THE NODE TO THE CORRESPONDING PATH
            Node node = new NodeImpl(path, Node.Types.FILE);

            try {
                Project project = projectServiceImpl.update(node, from, to, content);
            } catch (Exception e) {
                return Response.status(400).build();
            }

            return Response.ok().build();

        } catch (Exception e) {

            return Response.status(400).build();
        }
    }
}
