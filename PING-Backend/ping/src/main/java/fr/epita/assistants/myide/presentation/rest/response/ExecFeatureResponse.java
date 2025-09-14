package fr.epita.assistants.myide.presentation.rest.response;

import java.nio.file.Path;
import java.util.Optional;

import com.fasterxml.jackson.databind.ObjectMapper;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Feature.ExecutionReport;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.service.ProjectServiceImpl;
import fr.epita.assistants.myide.presentation.rest.request.ExecFeatureRequest;
import jakarta.ws.rs.core.Response;

public class ExecFeatureResponse {
    public static Response execFeatureResponse(String request, ProjectServiceImpl projectServiceImpl) {

        try {

            ObjectMapper mapper = new ObjectMapper();
            ExecFeatureRequest req = mapper.readValue(request, ExecFeatureRequest.class);

            Path path = req.getProject();
            if (path == null || path.toString().isEmpty()) {
                return Response.status(400).build();
            }
            if (!path.toFile().exists()) {
                return Response.status(404).build();
            }

            // Project project = projectServiceImpl.load(path);
            Optional<Project> projectOpt = projectServiceImpl.getProject(path);
            if (!projectOpt.isPresent()) {
                return Response.status(404).build();
            }

            Project project = projectServiceImpl.load(path); //projectOpt.get();

            Feature.Type feature;
            try {
                feature = Mandatory.Features.Any.valueOf(req.getFeature());
            } catch (Exception eAny) {
                try {
                    feature = Mandatory.Features.Git.valueOf(req.getFeature());
                } catch (Exception eGit) {
                    feature = Mandatory.Features.Maven.valueOf(req.getFeature());
                }
            }

            if (!project.getFeature(feature).isPresent()) {
                return Response.status(400).build();
            }

            ExecutionReport executionReport = projectServiceImpl.execute(project, feature, req.getParams().toArray());

            return Response.ok(executionReport).build();
        } catch (Exception e) {
            return Response.status(400).build();
        }
    }

}
