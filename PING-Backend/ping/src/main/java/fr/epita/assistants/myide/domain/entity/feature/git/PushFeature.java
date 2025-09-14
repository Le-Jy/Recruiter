package fr.epita.assistants.myide.domain.entity.feature.git;

import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;

import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.PushCommand;
import org.eclipse.jgit.internal.storage.file.FileRepository;
import org.eclipse.jgit.transport.PushResult;
import org.eclipse.jgit.transport.RemoteRefUpdate;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.ProcessFeatureReport;
import jakarta.ws.rs.core.Response.Status;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class PushFeature implements Feature {

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

        PushCommand push = git.push();

        // Should be a git push no force
        push.setForce(false);

        // push.setPushOptions(command);

        try {
            // Need to check if the res is up to date
            Iterable<PushResult> pushRes = push.call();
            for (PushResult pRes : pushRes) {
                for (RemoteRefUpdate rem_ref_update : pRes.getRemoteUpdates()) {
                    if (rem_ref_update.getStatus() == RemoteRefUpdate.Status.UP_TO_DATE) {

                        git.close();
                        rapport.add("Everything up-to-date");
                        return new ProcessFeatureReport(rapport, false);
                    }
                }
            }
            
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
        return Mandatory.Features.Git.PUSH;
    }
    
}
