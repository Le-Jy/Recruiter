package fr.epita.assistants.myide.domain.entity.feature.any;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.HashSet;
import java.util.Set;

import javax.validation.constraints.NotNull;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.AnyFeatureReport;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class CleanupFeature implements Feature {

    @Override
    public @NotNull ExecutionReport execute(Project project, Object... params) {

        File myideignore = RemoveTrashFiles.getMyIdeIgnore(project);

        if (myideignore == null) {
            return new AnyFeatureReport(project, true);
        }

        Set<String> trashFiles = RemoveTrashFiles.getTrashFiles(myideignore);

        if (trashFiles == null) {
            return new AnyFeatureReport(project, false);
        }

        try {
            RemoveTrashFiles.removeTrashFiles(project.getRootNode(), trashFiles);
        } catch (Exception e) {
            return new AnyFeatureReport(project, false);
        }

        return new AnyFeatureReport(project, true);
    }

    @Override
    public @NotNull Type type() {
        return Mandatory.Features.Any.CLEANUP;
    }
}
