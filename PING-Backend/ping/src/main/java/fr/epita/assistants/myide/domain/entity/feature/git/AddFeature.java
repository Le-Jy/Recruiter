package fr.epita.assistants.myide.domain.entity.feature.git;

import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;

import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.AddCommand;
import org.eclipse.jgit.internal.storage.file.FileRepository;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.ProcessFeatureReport;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class AddFeature implements Feature {
    
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

        AddCommand add = git.add();
        List<String> files_to_add = new ArrayList<String>();
        boolean need_to_add_files = true;
        
        for (Object param : params) {

            // Get the root path and add the file to add to the addCommand
            Path to_add = project.getRootNode().getPath().toAbsolutePath().resolve(param.toString());

            // When the file is not present, we need to throw an error and don't ad anything
            if (!to_add.toFile().exists()) {
                rapport.add("One or more files are not present in the directory, retry");

                git.close();
                return new ProcessFeatureReport(rapport, false);
            }
            
            files_to_add.add(param.toString());
        }

        // Add the files if they are all present
        for (String it : files_to_add) {
            add.addFilepattern(it);
        }

        try {
            add.call();
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
        return Mandatory.Features.Git.ADD;
    }
    
}
