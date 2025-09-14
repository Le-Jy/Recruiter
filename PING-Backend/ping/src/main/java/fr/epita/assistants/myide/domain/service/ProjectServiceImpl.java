package fr.epita.assistants.myide.domain.service;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;

import javax.management.RuntimeErrorException;
import javax.validation.constraints.NotNull;

import fr.epita.assistants.MyIde.Configuration;
import fr.epita.assistants.myide.domain.entity.Aspect;
import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.aspect.AnyAspect;
import fr.epita.assistants.myide.domain.entity.aspect.GitAspect;
import fr.epita.assistants.myide.domain.entity.aspect.MavenAspect;
import fr.epita.assistants.myide.domain.entity.project.ProjectImpl;
import jakarta.inject.Inject;

public class ProjectServiceImpl implements ProjectService {

    private Configuration configuration;
    private NodeServiceImpl nodeServiceImpl;
    private List<Project> projects;

    public ProjectServiceImpl(Configuration configuration) {
        this.configuration = configuration;
        this.nodeServiceImpl = new NodeServiceImpl();
        this.projects = new ArrayList<>();
    }

    public Optional<Project> getProject(@NotNull Path root) {
        return projects.stream().filter(p -> p.getRootNode().getPath().equals(root)).findFirst();
    }

    @Override
    @Inject
    public @NotNull Project load(@NotNull Path root) {
        // Ensure the root path is a folder.
        if (!root.toFile().isDirectory()) {
            return null;
        }

        Optional<Project> project = getProject(root);
        if (project.isPresent()) {
            projects.remove(project.get());
        }

        Node rootNode = nodeServiceImpl.load(root);

        Set<Aspect> aspects = new HashSet<Aspect>();

        ProjectImpl projectImpl = new ProjectImpl().withRootNode(rootNode).withAspects(aspects);
        try {
            projectImpl.addAspect(new AnyAspect(projectImpl, this.configuration));
        } catch (Exception e) {
            return null;
        }

        File pom = new File(root.toFile(), "pom.xml");
        if (pom.exists() && pom.isFile()) {
            projectImpl.addAspect(new MavenAspect());
        }

        File git = new File(root.toFile(), ".git");
        if (git.exists() && git.isDirectory()) {
            projectImpl.addAspect(new GitAspect());
        }

        projects.add(projectImpl);

        return projectImpl;
    }

    @Override
    public @NotNull Project update(@NotNull Node node, int from, int to, byte[] insertedContent) {
        Node rootNode = nodeServiceImpl.update(node, from, to, insertedContent);
        // TODO : detecter le type de project (Aspects etc...)
        return new ProjectImpl().withRootNode(rootNode);
    }

    @Override
    public @NotNull Feature.ExecutionReport execute(@NotNull final Project project,
            @NotNull final Feature.Type featureType, final Object... params) {
        return project.getFeature(featureType).get().execute(project, params);
    }

    @Override
    public @NotNull NodeService getNodeService() {
        return this.nodeServiceImpl;
    }
}
