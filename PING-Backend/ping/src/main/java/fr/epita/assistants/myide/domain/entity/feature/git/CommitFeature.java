package fr.epita.assistants.myide.domain.entity.feature.git;

import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;

import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.CommitCommand;
import org.eclipse.jgit.internal.storage.file.FileRepository;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.ProcessFeatureReport;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class CommitFeature implements Feature {

    @Override
    public @NotNull ExecutionReport execute(Project project, Object... params) {

        List<String> command = new ArrayList<>();
        for (Object param : params) {
            command.add(param.toString());
        }

        List<String> rapport = new ArrayList<String>();

        String gitPath = project.getRootNode().getPath().toAbsolutePath().toString() + "/.git";
        FileRepository gitRepo = null;

        try {
            gitRepo = new FileRepository(gitPath);
        } catch (Exception e) {
      
            rapport.add(e.getMessage());

            gitRepo.close();
            return new ProcessFeatureReport(rapport, false);
        }
        
        Git git = new Git(gitRepo);

        CommitCommand commit = git.commit();
        
        if (params.length > 0) {
            commit.setMessage(params[0].toString());
        }

        try {
            commit.call();
        } catch (Exception e) {

            rapport.add(e.getMessage());

            git.close();
            return new ProcessFeatureReport(rapport, false);
        }
        
        git.close();
        gitRepo.close();

        return new ProcessFeatureReport(rapport, true);
    }

    @Override
    public @NotNull Type type() {
        return Mandatory.Features.Git.COMMIT;
    }
    
}
