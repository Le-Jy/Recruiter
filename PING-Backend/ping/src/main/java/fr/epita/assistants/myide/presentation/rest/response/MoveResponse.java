package fr.epita.assistants.myide.presentation.rest.response;

import java.nio.file.Path;

import com.fasterxml.jackson.databind.ObjectMapper;

import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.node.NodeImpl;
import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.MoveRequest;
import fr.epita.assistants.myide.presentation.rest.request.PathRequest;
import jakarta.ws.rs.core.Response;

public class MoveResponse {
    public static Response moveResponse(String request, ProjectServiceImpl projectServiceImpl) {

        try {
            ObjectMapper mapper = new ObjectMapper();
            MoveRequest req = mapper.readValue(request, MoveRequest.class);

            Path src = req.getSrc();
            if (src == null || src.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (!src.toFile().exists()) {
                return Response.status(404).build();
            }

            Path dst = req.getDst();
            if (dst == null || dst.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (!dst.toFile().exists()) {
                return Response.status(404).build();
            }

            Node nodeToMove;
            if (src.toFile().isDirectory()) {
                nodeToMove = new NodeImpl(src, Node.Types.FOLDER);

            } else if (src.toFile().isFile()) {
                nodeToMove = new NodeImpl(src, Node.Types.FILE);
            } else {
                return Response.status(403).build();
            }

            if (!dst.toFile().isDirectory()) {
                return Response.status(403).build();
            }
            Node destNode = new NodeImpl(dst, Node.Types.FOLDER);


            Node movedNode = projectServiceImpl.getNodeService().move(nodeToMove, destNode);
            // System.out.println(movedNode.toString());

            return Response.ok(movedNode).build();
        } catch (Exception e) {

            return Response.status(400).build();
        }
    }
}
