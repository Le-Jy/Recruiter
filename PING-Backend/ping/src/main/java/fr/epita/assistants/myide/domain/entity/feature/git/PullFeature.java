package fr.epita.assistants.myide.domain.entity.feature.git;

import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;

import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.MergeCommand;
import org.eclipse.jgit.api.PullCommand;
import org.eclipse.jgit.internal.storage.file.FileRepository;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.ProcessFeatureReport;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class PullFeature implements Feature {

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

        PullCommand pull = git.pull();
        
        // Set the FastForwardMode for pull
        // May need to change it, not sure it's applicable for all pull  
        pull.setFastForward(MergeCommand.FastForwardMode.FF);

        try {
            pull.call();
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
        return Mandatory.Features.Git.PULL;
    }
    
}
