package fr.epita.assistants.myide.presentation.rest;

import java.nio.file.Paths;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import fr.epita.assistants.MyIde.Configuration;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.PathRequest;

import fr.epita.assistants.myide.presentation.rest.response.*;

import fr.epita.assistants.myide.utils.Logger;

@Path("/api")
@Consumes(MediaType.APPLICATION_JSON)
@Produces(MediaType.APPLICATION_JSON)
public class MyIdeEndpoint {

    ProjectServiceImpl projectServiceImpl = new ProjectServiceImpl(null);

    @GET @Path("/hello")
    public Response helloWorld() {
        Logger.log("Saying hello !");
        return Response.ok("Hello World !").build();
    }

    @POST @Path("/open/project")
    public Response openProject(String req) {
        Logger.log("Opening project, query : " + req);
        Response response = OpenResponse.openProjectResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error opening folder : " + (response.getStatus() == 400 ? "Bad Request" : "Not Found"));
        }
        // Logger.log("Project opened");
        return response;
    }

    @POST @Path("/open/file")
    public Response openFile(String req) {
        Logger.log("Opening file, query : " + req);
        Response response = OpenResponse.openFileResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error opening file : " + (response.getStatus() == 400 ? "Bad Request" : "Not Found"));
        }
        // else {
        //     Logger.log("File opened");
        // }
        return response;
    }

    @POST @Path("/create/folder")
    public Response createFolder(String req) {
        Logger.log("Creating folder, query : " + req);
        Response response =  CreateResponse.createFolderResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error creating folder : Bad Request");
        }
        // else {
        //     Logger.log("Folder created");
        // }
        return response;
    }

    @POST @Path("/create/file")
    public Response createFile(String req) {
        Logger.log("Creating file, query : " + req);
        Response response =  CreateResponse.createFileResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error creating file : Bad Request");
        }
        // else {
        //     Logger.log("File created");
        // }
        return response;
    }

    @POST @Path("/delete/folder")
    public Response deleteFolder(String req) {
        Logger.log("Deleting folder, query : " + req);
        Response response =  DeleteResponse.deleteFolderResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error deleting folder, status :" + response.getStatus());
        }
        // else {
        //     Logger.log("Folder deleted");
        // }
        return response;
    }

    @POST @Path("/delete/file")
    public Response deleteFile(String req) {
        Logger.log("Deleting file, query : " + req);
        Response response =  DeleteResponse.deleteFileResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error deleting file, status :" + response.getStatus());
        }
        // else {
        //     Logger.log("File deleted");
        // }
        return response;
    }

    @POST @Path("/move")
    public Response move(String req) {
        Logger.log("Moving node, query : " + req);
        Response response =  MoveResponse.moveResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error moving node, status :" + response.getStatus());
        }
        // else {
        //     Logger.log("Node moved");
        // }
        return response;
    }
    
    @POST @Path("/update")
    public Response updateProject(String req)
    {
        Logger.log("Updating file, query : " + req);
        Response createResponse = UpdateResponse.getResponse(req, projectServiceImpl);
        if (createResponse.getStatus() != 200) {
            Logger.logError("Error while updating file, status :" + createResponse.getStatus());
        }
        // else {
        //     Logger.log("File updated");
        // }
        return createResponse;
    }

    @POST @Path("/execFeature")
    public Response execFeature(String req) {
        Logger.log("Executing feature, query : " + req);
        Response response = ExecFeatureResponse.execFeatureResponse(req, projectServiceImpl);
        if (response.getStatus() != 200) {
            Logger.logError("Error while executing feature, status :" + response.getStatus());
        }
        // else {
        //     Logger.log("Feature executed");
        // }
        return response;
    }
}
