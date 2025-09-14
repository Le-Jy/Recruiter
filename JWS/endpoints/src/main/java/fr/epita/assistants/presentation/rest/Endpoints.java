package fr.epita.assistants.presentation.rest;

import com.fasterxml.jackson.databind.ObjectMapper;
import fr.epita.assistants.presentation.rest.request.ReverseRequest;
import fr.epita.assistants.presentation.rest.response.HelloResponse;
import fr.epita.assistants.presentation.rest.response.ReverseResponse;
import lombok.SneakyThrows;
import org.eclipse.microprofile.openapi.annotations.parameters.RequestBody;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/")
@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.MEDIA_TYPE_WILDCARD)
public class Endpoints {
    @SneakyThrows
    @Path("/hello/{name}")
    @GET
    public Response helloname(@PathParam("name") String name) {
        ObjectMapper res = new ObjectMapper();
        String tmp = res.writeValueAsString(new HelloResponse(name));
        return Response.ok(tmp).build();
    }

    @SneakyThrows
    @Path("/reverse")
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response reverse(@RequestBody ReverseRequest requestBody) {
        if (requestBody == null || requestBody.getContent() == null || requestBody.getContent().isEmpty())
            return Response.status(Response.Status.BAD_REQUEST).entity("Request body or content is null").build();
        String content = requestBody.getContent();
        ObjectMapper tmp = new ObjectMapper();
        ReverseResponse tmp1 = new ReverseResponse(content);
        String res = tmp.writeValueAsString(tmp1);
        return Response.ok(res).build();
    }
}
